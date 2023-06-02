#include "Sensors.h"
#include "Devices.h"
#include "Nextion_IO.h"
#include "OrangePi_IO.h"
#include "SPIFFS_services.h"
#include "RTOS.h"
#include "Server.h"
//#define DEBUG


RTOS Timer_1_second(1000);
RTOS Timer_2_seconds(2000);
RTOS Timer_1_minute(60000);


void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial2.setTimeout(100);
  
  Server_init();
  Sensors_init();
  Devices_init();
  SPIFFS_init();
  SPIFFS_data_read();
  output_to_nextion();
  Timer_1_second.setState(true);
  Timer_2_seconds.setState(true);
  Timer_1_minute.setState(true);
}


void loop()
{
  input_from_nextion();
  rtc_update_check();
  if(Timer_1_second.Timer())
  {
    Devices_run();
    output_to_nextion();
    SPIFFS_data_write();
    //SPIFFS_data_show();
    //Serial_sensor_output();
  }

  if(Timer_2_seconds.Timer())
  {
    Sensors_run();
  }

  if(Timer_1_minute.Timer())
  {
    rtc_update_check();
    rtc_transmit();
  }
  //input_from_orangepi();
}
