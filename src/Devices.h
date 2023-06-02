#ifndef Devices_h
#define Devices_h


void Devices_init();
void Devices_run();
void Device_control(int device_status, int device_pin);


void Water_pump_run();
void Overflow_led_run();
void fan_outside_run();
void heater_system_run();
void white_light_run();
void fito_light_run();
//void BT_run();
void rtc_update_check();
void rtc_transmit();


void Debug_settings();


#endif
