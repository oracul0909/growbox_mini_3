#ifndef Sensors_h
#define Sensors_h


void Sensors_init();
void Sensors_run();
void Dht_inside_run();
void Dht_outside_run();
void LightMeter_run();
void Ground_humidity_sensor_run();
void Overflow_sensor_run();
void lock_run();
void Serial_sensor_output();


#endif
