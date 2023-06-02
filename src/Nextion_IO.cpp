#include "Nextion_IO.h"
#include "Arduino.h"
#include "Data.h"


extern Data_struct Data;
extern Settings_struct Settings;
extern Device_status_struct Device_status;
extern Main_data_struct Main_data;


void end_of_msg() {
  for (int i = 0; i < 3; i++) {
    Serial2.write(0xFF);
  }
}


void send_msg_nextion(String location, int value) {
  Serial2.print(location);
  Serial2.print("=");
  Serial2.print(value);
  end_of_msg();
}


void settings_output_nextion() {
  send_msg_nextion("page5.Timeday.val",      Settings.day_time_start);
  send_msg_nextion("page5.Timenight.val",    Settings.night_time_start);
  send_msg_nextion("page6.Hday.val",         Settings.humidity_inside_day);
  send_msg_nextion("page6.Hnight.val",       Settings.humidity_inside_night);
  send_msg_nextion("page7.GHmin.val",        Settings.ground_humidity_min);
  send_msg_nextion("page7.GHmax.val",        Settings.ground_humidity_max);
  send_msg_nextion("page7.Wstop.val",        Settings.water_forcibly_stop);
  send_msg_nextion("page8.Tday.val",         Settings.temperature_inside_day);
  send_msg_nextion("page8.Tnight.val",       Settings.temperature_inside_night);
  send_msg_nextion("page10.FITOon.val",      Settings.fito_light_time_start);
  send_msg_nextion("page10.FITOoff.val",     Settings.fito_light_time_stop);
  send_msg_nextion("page10.FITOstop.val",    Settings.fito_forcibly_stop);
  send_msg_nextion("page10.ONLYFANS.val",    Settings.only_one_light);
  send_msg_nextion("page11.WHITEborder.val", Settings.light_intencity_border);
  send_msg_nextion("page11.WHITEstop.val",   Settings.white_forcibly_stop);
}


void device_status_output_nextion() {
  send_msg_nextion("page2.FAN.val",   Device_status.fan_outside_status);
  send_msg_nextion("page2.HEAT.val",  Device_status.heater_lamp_status);
  send_msg_nextion("page2.WATER.val", Device_status.water_pump_status);
  send_msg_nextion("page2.WIFI.val",  Device_status.wi_fi_status);
  send_msg_nextion("page2.BT.val",    Device_status.bluetooth_status);
  send_msg_nextion("page2.FITO.val",  Device_status.fito_light_status);
  send_msg_nextion("page2.White.val", Device_status.white_light_status);
}


void data_output_nextion() {
  send_msg_nextion("page2.LOCK.val",   Data.lock_status);
  send_msg_nextion("page2.HUM.val",    Data.humidity_inside);
  send_msg_nextion("page2.TEMP.val",   Data.temperature_inside);
  send_msg_nextion("page2.GHUM.val",   Data.ground_humidity);
  send_msg_nextion("page2.LIGHT.val",  Data.light_intencity);
  send_msg_nextion("page4.HOUR.val",   Data.time_hour);
  send_msg_nextion("page4.MINUTE.val", Data.time_minute);
  send_msg_nextion("page4.DATE.val",   Data.time_date);
  send_msg_nextion("page4.MONTH.val",  Data.time_month);
  send_msg_nextion("page4.YEAR.val",   Data.time_year);
}


void output_to_nextion() {
  settings_output_nextion();
  device_status_output_nextion();
  data_output_nextion();
}


String Serial2_data = "";

void input_from_nextion() {
  while(Serial2.available()) {
    Serial2_data = Serial2.readStringUntil('&');
    int i = Serial2_data.indexOf(":", 0);
    int key = Serial2_data.substring(0, i).toInt();
    int val = Serial2_data.substring(i+1, Serial2_data.length()).toInt();
    write_data(key, val);
  }
}
