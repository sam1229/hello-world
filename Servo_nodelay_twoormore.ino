#include <Servo.h> 

class Sweeper
{
  Servo servo;              // the servo
  int pos;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;  // interval between updates
  int maxang;
  unsigned long lastUpdate; // last update of position

public: 
  Sweeper(int interval,int incr,int ang)
  {
    updateInterval = interval;
    increment = incr;
    maxang = ang;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      if ((pos >= maxang) || (pos <= 0)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};
 
 
Sweeper sweeper1(10,1,90);
Sweeper sweeper2(10,2,180);
 
void setup() 
{ 
  Serial.begin(9600);
  sweeper1.Attach(9);
  sweeper2.Attach(10);
} 
 
 
void loop() 
{ 
  sweeper1.Update();
  sweeper2.Update();
  
}
