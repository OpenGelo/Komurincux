#include<Wire.h>
#include<CMPS10.h>
#include <Servo.h> 
CMPS10 compass;
int Pitch,Down,Up,Normal;
Servo servo_kiri;
Servo servo_kanan;
 
void setup() 
{ 
  servo_kanan.attach(9);
  servo_kiri.attach(10);
} 
 
void loop() 
{
  Pitch=compass.pitch();
  if(Pitch < 0)
  {
    pembalik1();
  }
  else if (Pitch >=1)
  {
    pembalik2();
  }
  else
  {
    normal();
  }
}

void normal()
{
  servo_kanan.write(90);
  servo_kiri.write(90);
}
void barengdown()
{
  servo_kanan.write(90-(Pitch*(-1)));
  servo_kiri.write(90-(Pitch*(-1)));
}
void barengup()
{
  servo_kanan.write(Pitch+90);
  servo_kiri.write(Pitch+90);
}
void pembalik1()
{
  servo_kanan.write(Pitch+90);
  servo_kiri.write(90-(Pitch*(-1)));
}
void pembalik2()
{
  servo_kanan.write(90-(Pitch*(-1)));
  servo_kiri.write(Pitch+90);
}
