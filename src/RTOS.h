#ifndef RTOS_H
#define RTOS_H

class RTOS{
  public:
  
  RTOS(void){
    Frequency = 100;    
        }
  RTOS(long Time){
    Frequency = Time;
    }

  bool Timer();
  bool setState(bool State);
  long Frequency;
  
  private:

  long _Last_time;
  bool _State = false;

};
#endif
