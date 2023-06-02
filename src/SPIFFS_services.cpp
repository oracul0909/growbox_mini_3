#include "SPIFFS_services.h"
#include "Data.h"
#include "FS.h"
#include "SPIFFS.h"



extern Data_struct Data;
extern Settings_struct Settings;
extern Device_status_struct Device_status;
extern Main_data_struct Main_data;


void SPIFFS_init() {
  if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED)){
        Serial.println("SPIFFS Mount Failed");
        return;
  }
}

String FileName = "Saved_settings";

void SPIFFS_data_read() {
  File myFile = SPIFFS.open(String(String("/") + String(FileName) + String(".txt")), FILE_READ);
  myFile.read((byte *)&Main_data, sizeof(Main_data));
  Data = Main_data.Data_2;
  Settings = Main_data.Settings_2;
  Device_status = Main_data.Device_status_2;
  myFile.close();
}

void SPIFFS_data_write() {
  File myFile = SPIFFS.open(String(String("/") + String(FileName) + String(".txt")), FILE_WRITE);
  Main_data.Data_2 = Data; 
  Main_data.Settings_2 = Settings;
  Main_data.Device_status_2 = Device_status;
  myFile.write((byte *)&Main_data, sizeof(Main_data));
  myFile.close();
}

void SPIFFS_data_show() {
  File myFile = SPIFFS.open(String(String("/") + String(FileName) + String(".txt")), FILE_READ);
  myFile.read((byte *)&Main_data, sizeof(Main_data));
  Serial.println(Main_data.Data_2.ground_humidity);
  myFile.close();
}
