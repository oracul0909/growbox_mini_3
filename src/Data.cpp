#include "Data.h"


Data_struct Data;


Settings_struct Settings;


Device_status_struct Device_status;


Main_data_struct Main_data;


void write_data(int key, int val)
{
    switch(key)
    {
      case 1: Settings.day_time_start = val; break;           //Timeday
      case 2: Settings.night_time_start = val; break;         //Timenight
      case 3: Settings.humidity_inside_day = val; break;      //Hday
      case 4: Settings.humidity_inside_night = val; break;    //Hnight
      case 5: Settings.ground_humidity_max = val; break;      //GHmin
      case 6: Settings.ground_humidity_min = val; break;      //GHmax
      case 7: Settings.water_forcibly_stop = val; break;      //Wstop
      case 8: Settings.temperature_inside_day = val; break;   //Tday
      case 9: Settings.temperature_inside_night = val; break; //Tnight
      case 10: Settings.fito_light_time_start = val; break;   //FITOon
      case 11: Settings.fito_light_time_stop = val; break;    //FITOoff
      case 12: Settings.fito_forcibly_stop = val; break;      //FITOstop
      case 13: Settings.only_one_light = val; break;          //ONLYFANS
      case 14: Settings.light_intencity_border = val; break;  //WHITEborder
      case 15: Settings.white_forcibly_stop = val; break;     //WHITEstop
      case 16: Device_status.wi_fi_status = val; break;       //WIFI
      case 17: Device_status.bluetooth_status = val; break;   //BT
      case 18: Data.time_updated = val; break;                //RTCFlag
      case 19: Data.time_hour = val; break;                   //HOUR
      case 20: Data.time_minute = val; break;                 //MINUTE
      case 21: Data.time_date = val; break;                   //DATE
      case 22: Data.time_month = val; break;                  //MONTH
      case 23: Data.time_year = val; break;                   //YEAR
    }
}


String generate_string(String key, int val)
{
  return ("\"" + key + "\": " + String(val) + ",");
}


String generate_string_nocomma(String key, int val)
{
  return ("\"" + key + "\": " + String(val));
}


String generate_json()
{
  String json;
  json = "{";
  json += generate_string("DATA_TEMPERATURE_INSIDE", Data.temperature_inside);
  json += generate_string("DATA_TEMPERATURE_OUTSIDE", Data.temperature_outside);
  json += generate_string("DATA_HUMIDITY_INSIDE", Data.humidity_inside);
  json += generate_string("DATA_HUMIDITY_OUTSIDE", Data.humidity_outside);
  json += generate_string("DATA_GROUND_HUMIDITY", Data.ground_humidity);
  json += generate_string("DATA_LIGHT_INTENCITY_BORDER", Settings.light_intencity_border);
  json += generate_string("DATA_WATER_FORCIBLY_STOP", Settings.water_forcibly_stop);
  json += generate_string("DATA_FITO_FORCIBLY_STOP", Settings.fito_forcibly_stop);
  json += generate_string("DATA_WHITE_FORCIBLY_STOP", Settings.white_forcibly_stop);
  json += generate_string("DATA_ONLY_ONE_LIGHT", Settings.only_one_light);
  json += generate_string("DATA_WATER_PUMP_STATUS", Device_status.water_pump_status);
  json += generate_string("DATA_FITO_LIGHT_STATUS", Device_status.fito_light_status);
  json += generate_string("DATA_WHITE_LIGHT_STATUS", Device_status.white_light_status);
  json += generate_string("DATA_TEMPERATURE_INSIDE_DAY", Settings.temperature_inside_day);
  json += generate_string("DATA_TEMPERATURE_INSIDE_NIGHT", Settings.temperature_inside_night);
  json += generate_string("DATA_HUMIDITY_INSIDE_DAY", Settings.humidity_inside_day);
  json += generate_string("DATA_HUMIDITY_INSIDE_NIGHT", Settings.humidity_inside_night);
  json += generate_string("DATA_GROUND_HUMIDITY_MAX", Settings.ground_humidity_max);
  json += generate_string_nocomma("DATA_GROUND_HUMIDITY_MIN", Settings.ground_humidity_min);
  json += "}";
  //Serial.println(json);
  return json;
}
