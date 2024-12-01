#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
char auth[] = "0hSh0tf93S8svwmypVem6vTDhXaJT65P";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName"; //Tên wifi
char pass[] = "YourPassword";   //Mật khẩu wifi
#include <TinyGPSPlus.h>
TinyGPSPlus gps;
#include <SoftwareSerial.h>
SoftwareSerial Neo6M(D1, D2); // RX, TX
float flat = 0.000000, flon = 0.000000;
WidgetMap dinhvi(V0);
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (Neo6M.available())
      gps.encode(Neo6M.read());
    flat =  gps.location.lat(), 6;
    flon =  gps.location.lng(), 6;
   Serial.print("FAT: ");
    Serial.print(flat,6);
      Serial.print(" ---- FLON: ");
      Serial.println(flon,6); 
  }
  while (millis() - start < ms);
}
void setup() {
  Serial.begin(9600);
  Neo6M.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.en-26.com", 8080);
}

void loop() {
  Blynk.run();
  smartDelay(1000);
  dinhvi.location(1,String(flat,6), String(flon,6),"VI TRI CUA TOI");
  delay(2000);
}
