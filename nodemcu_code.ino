#include <Wire.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = "RhUOP9Gx7-9KA1E_oI23qFpFIfuYRPUI";//Enter your Auth token
char ssid[] = "TP-LINK";//Enter your WIFI name
char pass[] = "ABC";//Enter your WIFI password
 
BlynkTimer timer;
bool pinValue = 0;
 
#define trig D3
#define echo D4
#define relay D5
 
void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(relay, OUTPUT);
  Wire.begin(D2, D1);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, Wlevel);
  digitalWrite(relay, HIGH);
}
 
BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}
 
 
void loop() {
  Blynk.run();
  timer.run();
}
 
void Wlevel() {
  if (pinValue == 1) {
    digitalWrite(relay, LOW);
  } else if (pinValue == 0) {
    digitalWrite(relay, HIGH);
  }
 
  digitalWrite(trig, LOW);
  delayMicroseconds(4);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = duration*0.034/2;
 
  Blynk.virtualWrite(V1, distance);
  Serial.println(distance);
}
