// Mendefinisikan Library untuk Acces Point
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Mendefinisikan Acces Point
const char *ssid = "Sensor Habis Pakan";
const char *password = "";
ESP8266WebServer server(80);

// Mendefinisikan Limit Switch, Buzzer, dan Kondisi
int lmSwitch = 5;
int buzzer = 16;
int kondisi;

void setup()
{
  // Memanggil Serial Monitor
  Serial.begin(9600);

  // Memanggil Limit Switch dan Buzzer
  pinMode(lmSwitch, INPUT); // Bila intterup ganti jadi iNPUT_PULLUP
  pinMode(buzzer, OUTPUT);

  /* Bila menggunakan interrupt
     attachInterrupt(digitalPinToInterrupt(lmSwitch),bacaSwitch,RAISING);
  */

  // Mengkondigurasikan Acces Point
  delay(1000);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password); // Password bisa dihapus bila ingin open
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  // Membaca Switch
  bacaSwitch();
  // Menghandle server
  server.handleClient();
}

// Fungsi dari server
void handleRoot() {
  String kondisiPakan;
  if (kondisi == 1) {
    kondisiPakan = "Habis";
  } else
  {
    kondisiPakan = "Masih ada";
  }
  String html = "<html> <head><meta http-equiv=\"refresh\" content=\"2\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <title>Sensor Habis Pakan</title> </head> <body> <h1>Pembacaan Sensor Habis Pakan</h1> <p>Kondisi pakan : <b>";
  html += kondisiPakan;
  html += "</b></p> </body> </html>";
  server.send(200, "text/html", html);
}

 void bacaSwitch() {
  kondisi = digitalRead(lmSwitch);
  if (kondisi == 1)
  {
    digitalWrite(buzzer, HIGH);
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }
   //tone(buzzer, 1000);
}

