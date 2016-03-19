#include <Servo.h>
Servo servo;
Servo esc;
int i,perintah;
int pos = 0;
 
void setup()
{
  Serial.begin(9600);
  servo.attach(10);
  esc.attach(9);
  servo.write(0);
  esc.write(10);
  Serial.println();
  Serial.println();
  Serial.println("Sistem Telah Aktif !");
  Serial.println("Petunjuk :");
  Serial.println("\tx : Untuk Membuka Parasut Darurat");
  Serial.println("\t0 : Untuk Pengujian EDF");
  Serial.println("\t1 : Untuk Meluncurkan Roket ! (Hati-hati)");
  Serial.println("\t2 : Untuk Mengunci Parasut");
  delay(500);
  Serial.println();
  Serial.println("Sedang Menunggu Perintah...");
}
 
void loop()
{
  perintah=Serial.read();
  if(perintah=='0')
  {
    Serial.println();
    Serial.println("Menyiapkan Pengujian EDF...");
    Serial.println("Parasut Terkunci...");
    Serial.println("\tPengujian +- 7 Detik");
    esc.write(64);
    delay(2000);
    esc.write(0);
    delay(500);
    Serial.println("Pengujian Selesai...");
    return;
  }
  if(perintah=='1')
  {
    Serial.println();
    Serial.println();
    Serial.println("Menyiapkan Peluncuran...");
    Serial.println("Parasut Terkunci...");
    Serial.println("\tMeluncur ! +- 7 Detik");
    servo.write(15);
    esc.write(50);
    delay(100);
    for(i=50;i<=179;i++)
    {
      perintah=Serial.read();
      if(perintah=='x')
      {
        esc.write(0);
        delay(2000);
        Serial.println();
        Serial.println("EDF OFF");
        servo.write(150);
        delay(500);
        Serial.println();
        Serial.println("Parasut Dibuka");
        return;
      }
      esc.write(i);
      delay(1);
    }
    Serial.println();
    Serial.println("Full Throttle");
    esc.write(179);
    delay(30);
    for(i=0;i<=7000;i++)
    {
      perintah=Serial.read();
      if(perintah=='x')
      {
        esc.write(0);
        delay(2000);
        Serial.println();
        Serial.println("EDF OFF");
        servo.write(150);
        delay(500);
        Serial.println();
        Serial.println("Parasut Dibuka");
        return;
      }
      esc.write(179);
      delay(1);
    } 
    esc.write(0);
    delay(2000);
    Serial.println();
    Serial.println("EDF OFF");
    servo.write(150);
    delay(500);
    Serial.println();
    Serial.println("Parasut Dibuka");
    return;
  }
  if(perintah=='2')
  {
    esc.write(0);
    delay(100);
    servo.write(15);
    delay(500);
    Serial.println();
    Serial.println("Parasut Dikunci");
    return;
  }
  if(perintah=='x')
  {
    esc.write(0);
    delay(100);
    servo.write(150);
    delay(500);
    Serial.println();
    Serial.println();
    Serial.println("Parasut Dibuka");
    return;
  }
  else
  {
    return;
  }
}
