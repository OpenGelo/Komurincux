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

  Pitch=compass.pitch();
  if(Pitch >=0 && Pitch <=90 )
  {
    int kr=map(Pitch,90,0,90,0);
    int kn=map(Pitch,90,0,90,180);
    kiri.write(kr);
    kanan.write(kn);
  }
  Pitch=compass.pitch();
  if(Pitch >= -90 && Pitch <= -1)
  {
    int kr=map(Pitch,-90,-1,90,180);
    int kn=map(Pitch,-90,-1,90,0);
    kiri.write(kr);
    kanan.write(kn);
  }
  Roll=compass.roll();
  if(Roll<0)
  {
    int kr=map(Roll,
  delay(1);
  Serial.print(Pitch);Serial.print("\t");Serial.println(Roll);
  //Serial.print("\t");Serial.println(Yaw); 
} 
