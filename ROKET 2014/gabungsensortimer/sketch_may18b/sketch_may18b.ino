
// 0 Terbang tanpa kontrol
// 1 Terbang dengan yaw
// 2 Terbang dengan Pitch
// y Uji yaw
// p Uji pitch
// d Kirim data saja
// t Tutup parasut
// b Buka parasut
// u Uji terbang
// x STOP Sistem darurat parasut Terbuka

#include<Wire.h>
#include<CMPS10.h>
#include <Servo.h> 
#include <BMP085.h>
CMPS10 compass;
Servo kiri;
Servo kanan;
Servo parasut;
Servo esc;
BMP085 dps = BMP085();
long Pressure = 0, Altitude = 0;
int i,Pitch,Yaw,idle,accX,accY,accZ,gyrX,gyrY,gyrZ,Ketinggian;
char Perintah;
 
void setup() 
{
  Serial.begin(9600);
  kiri.attach(3);
  kanan.attach(9);
  parasut.attach(10);
  esc.attach(11);
  kiri.write(90);
  kanan.write(90);
  parasut.write(10);
  esc.write(10);
  dps.init();
} 
 
void loop()
{
  Serial.begin(9600);
  esc.write(10);
  kiri.write(90);
  kanan.write(90);
  if(Serial.available()>0)
  {
    Perintah=Serial.read();
    {
      if(Perintah=='0')
      {
        Perintah=Serial.read();
        if(Perintah=='x')
        {
          kiri.write(90);
          kanan.write(90);
          esc.write(0);
          delay(2000);
          parasut.write(150);
          delay(500);
          return;
        }
        parasut.write(0);
        esc.write(10);
        kirim();
        for(i=10;i<=179;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(i);
          delay(1);
        }
        for(i=0;i<=185;i++) //265 = 10 detik... x detik= 265/10*x detik
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(179);
          kirim();
          delay(1);
        }
        for(i<=179;i=0;i--)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(i);
          delay(1);
        }
        kiri.write(90);
        kanan.write(90);
        esc.write(0);
        delay(2000);
        parasut.write(150);
        delay(500);
        notifikasiselesai();
        return;
      }
      if(Perintah=='1')
      {
        parasut.write(0);
        esc.write(10);
        kirim();
        for(i=10;i<=179;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(i);
          yaw();
          delay(1);
        }
        for(i=0;i<=265;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(179);
          yaw();
          kirim();
          delay(1);
        }
        for(i<=179;i=0;i--)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(7000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(i);
          yaw();
          delay(1);
        }
        kiri.write(90);
        kanan.write(90);
        esc.write(0);
        delay(2000);
        parasut.write(150);
        delay(500);
        notifikasiselesai();
        return;
      }
      if(Perintah=='2')
      {
        parasut.write(0);
        esc.write(10);
        kirim();
        for(i=10;i<=179;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(i);
          pit();
          delay(1);
        }
        for(i=0;i<=265;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(179);
          pit();
          kirim();
          delay(1);
        }
        kiri.write(90);
        kanan.write(90);
        esc.write(0);
        delay(2000);
        parasut.write(150);
        delay(500);
        notifikasiselesai();
        return;
      }
      if(Perintah=='y')
      {
        for(i=0;i<=9000;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            parasut.write(150);
            delay(500);
            return;
          }
          yaw();
          kirim();
        }
        notifikasiselesai();
      }
      if(Perintah=='p')
      {
        for(i=0;i<=9000;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            parasut.write(150);
            delay(500);
            return;
          }
          pit();
          kirim();
        }
        notifikasiselesai();
      }
      if(Perintah=='d')
      {
        for(i=0;i<=9000;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            parasut.write(150);
            delay(500);
            return;
          }
          kirim();
        }
        notifikasiselesai();
      }
      if(Perintah=='t')
      {
        parasut.write(10);
        delay(500);
      }
      if(Perintah=='b')
      {
        parasut.write(150);
        delay(500);
      }
      if(Perintah=='u')
      {
        parasut.write(10);
        esc.write(10);
        kirim();
        for(i=10;i<=64;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(i);
          yaw();
          delay(1);
        }
        for(i=0;i<=200;i++)
        {
          Perintah=Serial.read();
          if(Perintah=='x')
          {
            kiri.write(90);
            kanan.write(90);
            esc.write(0);
            delay(2000);
            parasut.write(150);
            delay(500);
            return;
          }
          esc.write(65);
          yaw();
          kirim();
          delay(1);
        }
        kiri.write(90);
        kanan.write(90);
        esc.write(0);
        delay(2000);
        parasut.write(150);
        delay(500);
        notifikasiselesai();
        return;
      }
    }
  }
}
        

void pit()
{
  Pitch=compass.pitch();
  if(Pitch <= -1)
  {
    kiri.write(90+(Pitch*(-1)));
    kanan.write(90-(Pitch*(-1)));
  }
  Pitch=compass.pitch();
  if(Pitch > 0)
  {
    kiri.write(90-Pitch);
    kanan.write(90+Pitch);
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

void kirim()
{
  accX=100*compass.acceleration_x();
  accY=100*compass.acceleration_y();
  accZ=100*compass.acceleration_z();
  gyrX=compass.roll();
  gyrY=compass.pitch();
  gyrZ=compass.bearing();
  if(accX>99){accX=99;}
  if(accY>99){accY=99;}
  if(accZ>99){accZ=99;}
  if(accX<-99){accX=-99;}
  if(accY<-99){accY=-99;}
  if(accZ<-99){accZ=-99;}
  else{accX=accX;accY=accY;accZ=accZ;}
  dps.getAltitude(&Altitude);
  Ketinggian=Altitude/100;
  char data[30];
  sprintf(data,"%03d %03d %03d %03d %03d %03d %06d",accX,accY,accZ,gyrX,gyrY,gyrZ,Ketinggian);
  Serial.print("HDR ");
  Serial.println(data);
}

void notifikasiselesai()
{
  Serial.println("HDR OFF OFF");
}
