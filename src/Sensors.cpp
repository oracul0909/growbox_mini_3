#include "Sensors.h"
#include "Data.h"
#include "Arduino.h"


extern Data_struct Data;
extern Settings_struct Settings;
extern Device_status_struct Device_status;


//создание объектов датчиков DHT11
#include <DHT.h>
#define DHTTYPE DHT11
#define dht_inside_pin 25
#define dht_outside_pin 15
DHT dht_inside(dht_inside_pin, DHTTYPE);
DHT dht_outside(dht_outside_pin, DHTTYPE);


//создание объекта датчика BH1750
#include <Wire.h>
#include <BH1750.h>
BH1750 lightMeter;


//аналоговый пин датчика влажности почвы
#define ground_humidity_sensor_pin 35

//цифровой пин датчика перелива
#define overflow_sensor_pin 36

//цифровой пин замка блокировки
#define lock_pin 12



//инициализация датчиков
void Sensors_init() {
  Wire.begin();
  dht_inside.begin();
  dht_outside.begin();
  lightMeter.begin();
  pinMode(lock_pin, INPUT_PULLUP);
}

//вызов функций работы всех датчиков
void Sensors_run() {
  Dht_inside_run();
  Dht_outside_run();
  LightMeter_run();
  Ground_humidity_sensor_run();
  Overflow_sensor_run();
  lock_run();
}


void Dht_inside_run() {
  Data.humidity_inside = int(dht_inside.readHumidity());
  Data.temperature_inside = int(dht_inside.readTemperature());
}


void Dht_outside_run() {
  Data.humidity_outside = int(dht_outside.readHumidity());
  Data.temperature_outside = int(dht_outside.readTemperature());
}


void LightMeter_run() {
  Data.light_intencity = int(lightMeter.readLightLevel());
}

int val_min = 5000;
int val_max = 0;
void Ground_humidity_sensor_run() {
  int val = int((analogRead(ground_humidity_sensor_pin)+
                   analogRead(ground_humidity_sensor_pin)+
                   analogRead(ground_humidity_sensor_pin)+
                   analogRead(ground_humidity_sensor_pin)+
                   analogRead(ground_humidity_sensor_pin))/5);
  if(val < val_min) {val_min = val;}
  if(val > val_max) {val_max = val;}
  Data.ground_humidity = 100 - constrain(map(val, val_min, val_max, 0, 100), 0, 100);
}


void Overflow_sensor_run() {
  Device_status.overflow_led_status = digitalRead(overflow_sensor_pin);
}


void lock_run() {
  Data.lock_status = digitalRead(lock_pin);
}


void Serial_sensor_output() {
  Serial.print(Data.lock_status);
  Serial.print(" ");
  Serial.print(Data.humidity_inside);
  Serial.print(" ");
  Serial.print(Data.temperature_inside);
  Serial.print(" ");
  Serial.print(Data.ground_humidity);
  Serial.print(" ");
  Serial.println(Data.light_intencity);
}
