#include<Wire.h>
#include<CMPS10.h>
#include <Servo.h> 
CMPS10 compass;
Servo myservo;
Servo myservo1;
int Pitch,i,t;
 
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(9);
  myservo1.attach(10);
} 
 
void loop() 
{
  if(Serial.available()>0)
  {
    int a=Serial.read();
    if(a=='1')
    {
      for(i=0;i=7000;i++)
      {
        Serial.println(t);
        t++;
        Pitch=compass.pitch();
        if(Pitch < 0)
        {
          myservo.write(90-(Pitch*(-1)));
          myservo1.write(Pitch+90);
        }
        else if (Pitch >=1)
        {
          myservo.write(Pitch+90);
          myservo1.write(90-(Pitch*(-1)));
        }
        else
        {
          myservo.write(90);
        }
        delay(1);
        if(i>=7000)
        {
          return;
        }
      }
    }
  }
} 
