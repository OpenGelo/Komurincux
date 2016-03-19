#include<Wire.h>
#include<CMPS10.h>
#include <Servo.h> 
CMPS10 compass;
Servo kiri;
Servo kanan;
Servo syaw;
int Pitch,Roll,Yaw;
 
void setup() 
{
  Serial.begin(9600);
  kiri.attach(9);
  kanan.attach(10);
} 
 
void loop() 
{
  //pit();
  yaw();
  Pitch=compass.pitch();
  Yaw=compass.bearing();
  Serial.print(Pitch);Serial.print("\t");Serial.println(Yaw);
  //Serial.print("\t");Serial.println(Yaw); 
} 

void pit()
{
  Pitch=compass.pitch();
  if(Pitch <= -1)
  {
    kiri.write(90-(Pitch*(-1)));
    kanan.write(90+(Pitch*(-1)));
  }
  Pitch=compass.pitch();
  if(Pitch > 0)
  {
    kiri.write(90+Pitch);
    kanan.write(90-Pitch);
  }
}

void yaw()
{
  Yaw=compass.bearing();
  if(Yaw>=0 && Yaw<=180)
  {
    int kr=map(Yaw,180,0,90,0);
    kiri.write(kr);
    int kn=map(Yaw,180,0,90,0);
    kanan.write(kn);
  }
  Yaw=compass.bearing();
  if(Yaw>=181&&Yaw<=359)
  {
    int kr=map(Yaw,181,360,90,180);
    kiri.write(kr);
    int kn=map(Yaw,181,360,90,180);
    kanan.write(kn);
  }
}
  
