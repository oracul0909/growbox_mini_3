#include "Wire.h"
#include "Devices.h"
#include "Arduino.h"
#include "Data.h"
//#include "BluetoothSerial.h"
#include "SPI.h"
#include "Adafruit_Sensor.h"
#include "RTClib.h"


extern Data_struct Data;
extern Settings_struct Settings;
extern Device_status_struct Device_status;


#define water_pump_pin   26
#define fan_inside_pin   32
#define fan_outside_pin  4
#define heater_lamp_pin  27
#define fito_light_pin   14
#define white_light_pin  33
#define overflow_led_pin 18


RTC_DS3231 rtc;


void Devices_init() {
  rtc.begin();
  rtc_update_check();
  pinMode(water_pump_pin,   OUTPUT);  //инициализация пина насоса
  pinMode(fan_inside_pin,   OUTPUT);  //инициализация пина вентилятора обогрева
  pinMode(fan_outside_pin,  OUTPUT);  //инициализация пина вентилятора
  pinMode(fito_light_pin,   OUTPUT);  //инициализация пина освещения
  pinMode(white_light_pin,  OUTPUT);  //инициализация пина освещения
  pinMode(heater_lamp_pin,  OUTPUT);  //инициализация пина обогрева
  pinMode(overflow_led_pin, OUTPUT);  //инициализация пина светодиода перелива
  Device_status.water_pump_status = 0;
  Device_status.fan_outside_status = 0;
  Device_status.heater_lamp_status = 0;
  Device_status.fan_inside_status = 0;
  Device_status.white_light_status = 0;
  Device_status.fito_light_status = 0;
}


void Devices_run() {
  //Data.temperature_inside = int(random(0,50));
  //Data.temperature_outside = int(random(0,50));
  //Data.humidity_inside = int(random(0,100));
  //Data.humidity_outside = int(random(0,100));
  //Data.ground_humidity = int(random(0,100));
  Water_pump_run();
  Overflow_led_run();
  fan_outside_run();
  heater_system_run();
  white_light_run();
  fito_light_run();
  //BT_run();
  rtc_update_check();
}


/*
 * функция включает или выключает устройство в зависимости от его статуса
 */
void Device_control(int device_status, int device_pin) {
  if(device_status) {
    digitalWrite(device_pin, HIGH);
  } else {
    digitalWrite(device_pin, LOW);
  }
}


/*
 * функция управлет водяным насосом, учитывая перелив
 */
void Water_pump_run() {
  if(Device_status.overflow_led_status > 0) {
    Device_status.water_pump_status = 0;
    
  } else if(Settings.water_forcibly_stop > 0) {
    Device_status.water_pump_status = 0;
    
  } else if(Data.ground_humidity > Settings.ground_humidity_max) {
    Device_status.water_pump_status = 0;
    
  } else if(Data.ground_humidity < Settings.ground_humidity_min) {
    Device_status.water_pump_status = 1;
  }
  Device_control(Device_status.water_pump_status, water_pump_pin);
}


/*
 * контроль светодиода перелива
 */
void Overflow_led_run() {
 Device_control(Device_status.overflow_led_status, overflow_led_pin);
}


/*
 * контроль наружного вентилятора
 */
void fan_outside_run() {
  if(Data.nextion_time > Settings.day_time_start &&
     Data.nextion_time < Settings.night_time_start) {                                   //день
    if(Data.temperature_inside > Settings.temperature_inside_day + 2 &&
       Data.temperature_outside < Data.temperature_inside) {
      Device_status.fan_outside_status = 1;
    } else if(Data.humidity_inside > Settings.humidity_inside_day + 2 &&
              Data.humidity_outside < Data.humidity_inside) {
      Device_status.fan_outside_status = 1;    
    } else if(Data.temperature_inside <= Settings.temperature_inside_day ||
              Data.humidity_inside <= Settings.humidity_inside_day) {
      Device_status.fan_outside_status = 0;
    }
  } else {                                                                              //ночь
    if(Data.temperature_inside > Settings.temperature_inside_night + 2 && 
       Data.temperature_outside < Data.temperature_inside) {
      Device_status.fan_outside_status = 1;
    } else if(Data.humidity_inside > Settings.humidity_inside_night + 2 &&
              Data.humidity_outside < Data.humidity_inside) {
      Device_status.fan_outside_status = 1;
    } else if(Data.temperature_inside <= Settings.temperature_inside_night ||
              Data.humidity_inside <= Settings.humidity_inside_night) {
      Device_status.fan_outside_status = 0;
    }
  }
  Device_control(Device_status.fan_outside_status, fan_outside_pin);
}


/*
 * контроль системы обогрева
 */
void heater_system_run() {
  if(Data.nextion_time > Settings.day_time_start &&
     Data.nextion_time < Settings.night_time_start) {                                   //день
    if(Data.temperature_inside < Settings.temperature_inside_day - 2) {
      Device_status.heater_lamp_status = 1;
      Device_status.fan_inside_status = 1;
    } else if(Data.temperature_inside >= Settings.temperature_inside_day) {
      Device_status.heater_lamp_status = 0;
      Device_status.fan_inside_status = 0;
    }
  } else {                                                                               //ночь
    if(Data.temperature_inside < Settings.temperature_inside_night - 2) {
      Device_status.heater_lamp_status = 1;
      Device_status.fan_inside_status = 1;
    } else if(Data.temperature_inside >= Settings.temperature_inside_night) {
      Device_status.heater_lamp_status = 0;
      Device_status.fan_inside_status = 0;
    }
  }
  Device_control(Device_status.heater_lamp_status, heater_lamp_pin);
  Device_control(Device_status.fan_inside_status, fan_inside_pin);
}


/*
 * контроль лампы дневного света
 */
void white_light_run() {
  if(Settings.white_forcibly_stop > 0) {
    Device_status.white_light_status = 0;
  } else if(Data.nextion_time < Settings.day_time_start ||
            Data.nextion_time > Settings.night_time_start) {
    Device_status.white_light_status = 0;
  } else if(Settings.only_one_light > 0 && Device_status.fito_light_status > 0) {
    Device_status.white_light_status = 0;
  } else if(Data.light_intencity > Settings.light_intencity_border) {
    Device_status.white_light_status = 0;
  } else {
    Device_status.white_light_status = 1;
  }
  Device_control(Device_status.white_light_status, white_light_pin);
}


/*
 * контроль фито лампы
 */
void fito_light_run() {
  if(Settings.fito_forcibly_stop > 0) {
    Device_status.fito_light_status = 0;
  } else if(Data.nextion_time < Settings.fito_light_time_start ||
            Data.nextion_time > Settings.fito_light_time_stop) {
    Device_status.fito_light_status = 0;
  } else {
    Device_status.fito_light_status = 1;
  }
  Device_control(Device_status.fito_light_status, fito_light_pin);
}


//BluetoothSerial SerialBT;


/*
 * запуск bluetooth
 */
//void BT_run() {
//  if(Device_status.bluetooth_status > 0) {
//    SerialBT.begin("Grow_box_mini");
//  } else {
//    SerialBT.end();
//  }
//}


/*
 * обновление дата/время на модуле часов
 */
void rtc_update_check()
{
  if(Data.time_updated == 1)
  {
    rtc.adjust(DateTime(Data.time_year,
                        Data.time_month,
                        Data.time_date,
                        Data.time_hour,
                        Data.time_minute,
                        0));
    Data.time_updated = 0;
  }
}


/*
 * отправка дата/время с модуля часов
 */
void rtc_transmit()
{
  if(Data.time_updated == 0)
  {
    DateTime now = rtc.now();
    Data.time_hour = now.hour();
    Data.time_minute = now.minute();
    Data.nextion_time = Data.time_hour*60 + Data.time_minute;
  }
}
