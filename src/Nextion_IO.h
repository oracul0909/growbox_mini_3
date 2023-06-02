#ifndef Nextion_IO_h
#define Nextion_IO_h
#include "Arduino.h"

void send_msg_nextion(String location, int value);
void end_of_msg();
void settings_output_nextion();
void device_status_output_nextion();
void data_output_nextion();
void output_to_nextion();
void input_from_nextion();

#endif
