#include "Server.h"
#include "Data.h"
#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"
#include "SPIFFS.h"

extern Data_struct Data;
extern Settings_struct Settings;
extern Device_status_struct Device_status;
extern Main_data_struct Main_data;

AsyncWebServer server(80);

bool WifiIsOn = false;

IPAddress local_IP(192, 168, 10, 1);
// Задаем IP-адрес сетевого шлюза:
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   // опционально
IPAddress secondaryDNS(8, 8, 4, 4); // опционально

const char *ssid = "FitoboT";
const char *password = "Intler-s.ru";


void Wifibegin()
{
  Serial.begin(115200);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
  {
    Serial.println("STA Failed to configure");
    //  "Не удалось задать статический IP-адрес"
  }
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  WifiIsOn = true;
}


void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}


void SwitchParamEvent(String Param, String val)
{
  Param.replace("b", "");
  Param.trim();
  uint8_t AddrNum = Param.toInt();
  uint8_t Value = val.toInt();
  //Serial.print(AddrNum);
  //Serial.print(" ");
  //Serial.println(Value);
  write_data(AddrNum, Value);
}


bool Server_init()
{
  Wifibegin();
  server.begin();
  if (SPIFFS.begin(true))
  {
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", String(), false); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css", false); });

    server.on("/jquery.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/jquery.js", "text/javascript", false); });

    server.on("/flotr2.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/flotr2.min.js", "text/javascript", false); });

    server.on("/button_control.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/button_control.js", "text/javascript", false); });

    server.on("/server_IO.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/server_IO.js", "text/javascript", false); });

    server.on("/graph.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/graph.js", "text/javascript", false); });

    server.on("/logo.png", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/logo.png", "image/png", false); });

    server.on("/head.png", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/head.png", "image/png", false); });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/favicon.ico", "image/x-icon", false); });

    server.on("/fromserver.json", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
                request->send(200, "application/json", generate_json());
                Serial.println("json posted"); });

    server.on("/update2.php", HTTP_POST, [](AsyncWebServerRequest *request)
              { request->send(200); });

    server.on("/onserver.php", HTTP_POST, [](AsyncWebServerRequest *request)
              {
                String message;

                int params = request->params();
                for(int i = 0; i < params; i++)
                {
                  AsyncWebParameter* p = request->getParam(i);
                  if(p->isPost())
                  {
                    String Number =  p->name().c_str();
                    String Val =  p->value().c_str();
                    //Serial.print(Number);
                    //Serial.print(" ");
                    //Serial.println(Val);
                    SwitchParamEvent(Number,Val);
                  }
                }   
                Serial.println("Detected");
                request->send(200); });

    server.onNotFound(notFound);

    return true;
  }
  else
  {
    return false;
  }
}