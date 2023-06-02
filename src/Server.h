#ifndef Server_h
#define Server_h
#include "Arduino.h"
#include <ESPAsyncWebServer.h>


void Wifibegin(void);
void notFound(AsyncWebServerRequest *request);
void Write_pins(int Addr, bool State);
void SwitchParamEvent(String Param, String val);
bool Server_init(void);


#endif
