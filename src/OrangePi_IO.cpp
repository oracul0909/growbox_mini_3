#include "OrangePi_IO.h"
#include "Arduino.h"
#include "Data.h"


extern Data_struct Data;
extern Settings_struct Settings;
extern Device_status_struct Device_status;
extern Main_data_struct Main_data;


void send_msg_orangepi(String location, int value) {
  Serial2.write('&');
  Serial2.print(location);
  Serial2.print(":");
  Serial2.print(value);
  Serial2.write('&');
}


void settings_output_orangepi() {
  send_msg_orangepi("01", Settings.day_time_start);
  send_msg_orangepi("02", Settings.night_time_start);
  send_msg_orangepi("03", Settings.humidity_inside_day);
  send_msg_orangepi("04", Settings.humidity_inside_night);
  send_msg_orangepi("05", Settings.ground_humidity_min);
  send_msg_orangepi("06", Settings.ground_humidity_max);
  send_msg_orangepi("07", Settings.water_forcibly_stop);
  send_msg_orangepi("08", Settings.temperature_inside_day);
  send_msg_orangepi("09", Settings.temperature_inside_night);
  send_msg_orangepi("10", Settings.fito_light_time_start);
  send_msg_orangepi("11", Settings.fito_light_time_stop);
  send_msg_orangepi("12", Settings.fito_forcibly_stop);
  send_msg_orangepi("13", Settings.only_one_light);
  send_msg_orangepi("14", Settings.light_intencity_border);
  send_msg_orangepi("15", Settings.white_forcibly_stop);
}


void device_status_output_orangepi() {
  send_msg_orangepi("16", Device_status.fan_outside_status);
  send_msg_orangepi("17", Device_status.heater_lamp_status);
  send_msg_orangepi("18", Device_status.water_pump_status);
  send_msg_orangepi("19", Device_status.wi_fi_status);
  send_msg_orangepi("20", Device_status.bluetooth_status);
  send_msg_orangepi("21", Device_status.fito_light_status);
  send_msg_orangepi("22", Device_status.white_light_status);
}


void data_output_orangepi() {
  send_msg_orangepi("23", Data.lock_status);
  send_msg_orangepi("24", Data.humidity_inside);
  send_msg_orangepi("25", Data.temperature_inside);
  send_msg_orangepi("26", Data.ground_humidity);
  send_msg_orangepi("27", Data.light_intencity);
}


void output_to_orangepi() {
  settings_output_orangepi();
  device_status_output_orangepi();
  data_output_orangepi();
}


String Serial_data = "";

void input_from_orangepi() {
  while(Serial2.available()) {
    Serial_data = Serial2.readStringUntil('&');
    int i = Serial_data.indexOf(":", 0);
    int key = Serial_data.substring(0, i).toInt();
    int val = Serial_data.substring(i+1, Serial_data.length()).toInt();
    switch(key)
    {
      case 1: Settings.day_time_start = val; break;
      case 2: Settings.night_time_start = val; break;
      case 3: Settings.humidity_inside_day = val; break;
      case 4: Settings.humidity_inside_night = val; break;
      case 5: Settings.ground_humidity_max = val; break;
      case 6: Settings.ground_humidity_min = val; break;
      case 7: Settings.water_forcibly_stop = val; break;
      case 8: Settings.temperature_inside_day = val; break;
      case 9: Settings.temperature_inside_night = val; break;
      case 10: Settings.fito_light_time_start = val; break;
      case 11: Settings.fito_light_time_stop = val; break;
      case 12: Settings.fito_forcibly_stop = val; break;
      case 13: Settings.only_one_light = val; break;
      case 14: Settings.light_intencity_border = val; break;
      case 15: Settings.white_forcibly_stop = val; break;
      case 19: Device_status.wi_fi_status = val; break;
      case 20: Device_status.bluetooth_status = val; break;
      case 23: Data.lock_status = val; break;
      case 24: Data.humidity_inside = val; break;
      case 25: Data.temperature_inside = val; break;
      case 26: Data.ground_humidity = val; break;
      case 27: Data.light_intencity = val; break;
    }
  }
}
