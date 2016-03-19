#include<Wire.h>
#include<CMPS10.h>
#include <Servo.h> 
CMPS10 compass;
Servo myservo;
Servo myservo1;
int Pitch;
 
void setup() 
{ 
  myservo.attach(9);
  myservo1.attach(10);
} 
 
void loop() 
{
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
} 
