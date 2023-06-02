#ifndef OrangePi_IO_h
#define OrangePi_IO_h
#include "Arduino.h"


void input_from_orangepi();
void output_to_orangepi();
void send_msg_orangepi(String location, int value);
void settings_output_orangepi();
void device_status_output_orangepi();
void data_output_orangepi();


#endif
