#include<Wire.h>
#include<CMPS10.h>
#include <BMP085.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
TinyGPSPlus gps;
SoftwareSerial mySerial(3,4);
AltSoftSerial ss;
int reset=7;
byte incomingbyte;
int a=0x0000,j=0,k=0,count=0,hpix=0,vpix=1;     
uint8_t MH,ML;
boolean EndFlag=0;                              
void SendResetCmd();
void SendTakePhotoCmd();
void SendReadDataCmd();
void StopTakePhotoCmd();
CMPS10 compass;
BMP085 dps = BMP085();
long Pressure = 0, Altitude = 0;
int i=1,accX,accY,accZ,gyrX,gyrY,gyrZ,Ketinggian,Suhu,AnalogIn;
float latitude,longitude;

void setup()
{
  digitalWrite(reset,HIGH);
  delay(200);
  pinMode(reset,OUTPUT);
  digitalWrite(reset,HIGH);
  delay(200);
  Serial.begin(57600);
  mySerial.begin(38400);
  ss.begin(38400);
  Wire.begin();
  //dps.init(MODE_STANDARD,100,true);
  dps.init();
  sedang();
  delay(1000);
  SendResetCmd();
  delay(1000);
}

void loop()
{
  if(Serial.available()>0)
  {
    char Perintah=Serial.read();
//******************************************************************************
//      AT              ********************************************************
//******************************************************************************
    if(Perintah=='0')
    {
      Serial.flush();
      mySerial.flush();
      ss.flush();
      delay(100);
      Serial.begin(57600);
      ss.begin(38400);
      delay(100);
      for(i=0;i<=10;i++)
      {
        latitude=gps.location.lat(), gps.location.isValid(), 11, 6;
        longitude=gps.location.lng(), gps.location.isValid(), 12, 6;
        smartDelay(10);
      }
      Serial.println();
      i=1;
      while(i=1)
      {
        Serial.print("005 ");
        /*
        Serial.print("Home = ");
        Serial.print(latitude,6);
        Serial.print(" ");
        Serial.print(longitude,6);
        Serial.print(" ");
        */
        static const double ACUAN_LAT = latitude, ACUAN_LON = longitude;
        double courseToAcuan =TinyGPSPlus::courseTo(gps.location.lat(),gps.location.lng(),ACUAN_LAT,ACUAN_LON);
        int sudut=courseToAcuan;
        dps.getAltitude(&Altitude);
        Ketinggian=Altitude;
        if(Ketinggian<0)
        {
          Ketinggian=0;
        }
        if(Ketinggian>90)
        {
          Ketinggian=90;
        }
        char data[10];
        sprintf(data,"P%06dY%03dL",Ketinggian,sudut);
        Serial.print(data);
        Serial.println();
        i=1;
        smartDelay(1000);
        char Perintah=Serial.read();
        if(Perintah=='x')
        {
          return;
          delay(1000);
        }
      }
    } 
//******************************************************************************
// Sensor dan GPS       ********************************************************
//******************************************************************************
    if(Perintah=='1')
    {
      Serial.flush();
      mySerial.flush();
      ss.flush();
      delay(100);
      Serial.begin(57600);
      ss.begin(38400);
      delay(100);
      latitude=gps.location.lat(), gps.location.isValid(), 11, 6;
      longitude=gps.location.lng(), gps.location.isValid(), 12, 6;
      Serial.println();
      i=1;
      while(i=1)
      {
        accX=10*compass.acceleration_x();
        accY=10*compass.acceleration_y();
        accZ=10*(compass.acceleration_z()-1);
        gyrX=compass.roll();
        gyrY=compass.pitch();
        gyrZ=compass.bearing();
        dps.getAltitude(&Altitude);
        Ketinggian=Altitude/100;
        AnalogIn=analogRead(A0);
        Suhu=(5.0*AnalogIn*100)/1024;
        if(accX>99){accX=99;}
        if(accY>99){accY=99;}
        if(accZ>99){accZ=99;}
        if(accX<-99){accX=-99;}
        if(accY<-99){accY=-99;}
        if(accZ<-99){accZ=-99;}
        else{accX=accX;accY=accY;accZ=accZ;}
        Serial.print("005");
        Serial.print(" ");
        char data[34];
        sprintf(data,"%03d %03d %03d %03d %03d %03d %06d %03d",accX,accY,accZ,gyrX,gyrY,gyrZ,Ketinggian,Suhu);
        Serial.print(data);
        Serial.print(" ");
        static const double ACUAN_LAT = latitude, ACUAN_LON = longitude;
        printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
        Serial.print(" ");
        printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
        Serial.println();
        i=1;
        smartDelay(0);
        char Perintah=Serial.read();
        if(Perintah=='x')
        {
          return;
          delay(1000);
        }
      }
    }
//******************************************************************************
//   Kamera Saja        ********************************************************
//******************************************************************************
    if(Perintah=='2')
    {
      Serial.flush();
      mySerial.flush();
      ss.flush();
      delay(100);
      Serial.begin(57600);
      mySerial.begin(38400);
      delay(100);
      Serial.println();
      Serial.println("005FF");
      SendResetCmd();delay(1000);
      sedang();delay(500);
      SendTakePhotoCmd();delay(500);
      while(mySerial.available()>0)
      {
        incomingbyte=mySerial.read();
      }
      byte a[32];
      while(!EndFlag)
      {
        j=0;
        k=0;
        count=0;
        SendReadDataCmd();
        delay(75);
        while(mySerial.available()>0)
        {
          incomingbyte=mySerial.read();
          k++;
          if((k>5)&&(j<32)&&(!EndFlag))
          {
            a[j]=incomingbyte;
            if((a[j-1]==0xFF)&&(a[j]==0xD9))
            EndFlag=1;
            j++;
            count++;
          }
        }
        for(j=0;j<count;j++)
        {
          if(a[j]<0x10)
          Serial.print("0");
          Serial.print(a[j],HEX);
        }
        Serial.println();
        char Perintah=Serial.read();
        if(Perintah=='x')
        {
          delay(1000);
          digitalWrite(reset,LOW);
          delay(3000);
          return;
        }
      }
      delay(1000);
      digitalWrite(reset,LOW);
      delay(3000);
      return;
    }
//******************************************************************************
// OTOMATIS DENGAN TIMER *******************************************************
//******************************************************************************
    if(Perintah=='a')
    {
      latitude=gps.location.lat(), gps.location.isValid(), 11, 6;
      longitude=gps.location.lng(), gps.location.isValid(), 12, 6;
      Serial.println();
      for(i=0;i<=290;i++)
      {
        accX=10*compass.acceleration_x();
        accY=10*compass.acceleration_y();
        accZ=10*(compass.acceleration_z()-1);
        gyrX=compass.roll();
        gyrY=compass.pitch();
        gyrZ=compass.bearing();
        dps.getAltitude(&Altitude);
        Ketinggian=Altitude/100;
        AnalogIn=analogRead(A0);
        Suhu=(5.0*AnalogIn*100)/1024;
        if(accX>99){accX=99;}
        if(accY>99){accY=99;}
        if(accZ>99){accZ=99;}
        if(accX<-99){accX=-99;}
        if(accY<-99){accY=-99;}
        if(accZ<-99){accZ=-99;}
        else{accX=accX;accY=accY;accZ=accZ;}
        Serial.print("005");
        Serial.print(" ");
        char data[34];
        sprintf(data,"%03d %03d %03d %03d %03d %03d %06d %03d",accX,accY,accZ,gyrX,gyrY,gyrZ,Ketinggian,Suhu);
        Serial.print(data);
        Serial.print(" ");
        static const double ACUAN_LAT = latitude, ACUAN_LON = longitude;
        printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
        Serial.print(" ");
        printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
        Serial.println();
        delay(15);
        Perintah=Serial.read();
        if(Perintah=='x')
        {
          return;
          delay(1000);
        }
      }
      i=1;
      while(i=1)
      {
        Serial.flush();
        mySerial.flush();
        ss.flush();
        delay(100);
        Serial.begin(57600);
        mySerial.begin(38400);
        delay(100);
        Serial.println();
        Serial.println("005FF");
        SendResetCmd();delay(3000);
        sedang();delay(500);
        SendTakePhotoCmd();delay(100);
        while(mySerial.available()>0)
        {
          incomingbyte=mySerial.read();
        }
        byte a[32];
        while(!EndFlag)
        {
          j=0;
          k=0;
          count=0;
          SendReadDataCmd();
          delay(75);
          while(mySerial.available()>0)
          {
            incomingbyte=mySerial.read();
            k++;
            if((k>5)&&(j<32)&&(!EndFlag))
            {
              a[j]=incomingbyte;
              if((a[j-1]==0xFF)&&(a[j]==0xD9))
              EndFlag=1;
              j++;
              count++;
            }
          }
          for(j=0;j<count;j++)
          {
            if(a[j]<0x10)
            Serial.print("0");
            Serial.print(a[j],HEX);
          }
          Serial.println();
          ResetComm();
        }
        delay(1000);
        digitalWrite(reset,LOW);
        delay(3000);
        return;
      }
    }
  }
  latitude=gps.location.lat(), gps.location.isValid(), 11, 6;
  longitude=gps.location.lng(), gps.location.isValid(), 12, 6;
  smartDelay(1000);
}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  Serial.print(val, prec);
  int vi = abs((int)val);
  int flen = prec + (val < 0.0 ? 2 : 1); // . dan -
  flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
  for (int i=flen; i<len; ++i)
  //Serial.print(' ');
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}

static void printFloatstanby(float val, bool valid, int len, int prec)
{
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1);
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
    smartDelay(0);
}

void SendResetCmd()
{
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x26);
  mySerial.write((byte)0x00);
}

void sedang()// ukuran 320*240 , lihat datasheet.
{
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x31);
  mySerial.write((byte)0x05);
  mySerial.write((byte)0x04);
  mySerial.write((byte)0x01);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x19);
  mySerial.write((byte)0x11);      
}

void SendTakePhotoCmd()
{
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x36);
  mySerial.write((byte)0x01);
  mySerial.write((byte)0x00);  
}

void SendReadDataCmd()
{
  MH=a/0x100;
  ML=a%0x100;
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x32);
  mySerial.write((byte)0x0c);
  mySerial.write((byte)0x00); 
  mySerial.write((byte)0x0a);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)MH);
  mySerial.write((byte)ML);   
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x20);
  mySerial.write((byte)0x00);  
  mySerial.write((byte)0x0a);
  a+=0x20;
}

void StopTakePhotoCmd()
{
  mySerial.write((byte)0x56);
  mySerial.write((byte)0x00);
  mySerial.write((byte)0x36);
  mySerial.write((byte)0x01);
  mySerial.write((byte)0x03);        
}

void ResetComm()
{
  char Perintah=Serial.read();
  if(Perintah=='x')
  {
    delay(1000);
    digitalWrite(reset,LOW);
    delay(3000);
    return;
  }
}

void ResetCommRtrn()
{
  char Perintah=Serial.read();
  if(Perintah=='x')
  {
    return;
    delay(1000);
  }
}

void Reset()
{
  delay(1000);
  digitalWrite(reset,LOW);
  delay(3000);
  return;
}
