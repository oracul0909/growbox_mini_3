//Фаил методов процессов реального времени
#include "RTOS.h"
#include "Arduino.h"


//Метод RTOS, запускающий проверку на наличие события

bool RTOS::Timer()
{
  if (_State) {
    if (millis() - _Last_time > Frequency) {
      _Last_time = millis();
      return true;
    } else {
      return false;
      _Last_time = millis();
    }
  } else {
    //_Last_time = millis();
    return false;

  }
}

bool RTOS::setState(bool State)
{
  _State = State;
  return true;
}
