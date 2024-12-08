#include <SoftwareSerial.h>
#include "DHT.h"

#define smokePin A2

int sensorThres = 450;
String ok = "";
int utqk_ccfr = 0;

SoftwareSerial mySerialBT(9, 10);
DHT dht(12, DHT11);

void setup() {
  mySerialBT.begin(9600);
  Serial.begin(9600);
  digitalWrite(8, 0);//свет
  digitalWrite(5, 0);//свободное реле
  digitalWrite(2, 0);//вентилятор
  digitalWrite(4, 0);//чайник
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokePin);
  int temp = dht.readTemperature();
  int vl = dht.readHumidity();
  if (mySerialBT.available()) {
    utqk_ccfr = mySerialBT.read();
  }
  if (Serial.available()) {
    utqk_ccfr = Serial.read();
  }
  if(utqk_ccfr > 20){
    utqk_ccfr -= int('0');
  }
  if (utqk_ccfr == 1) {
    pinMode(8, OUTPUT);
    digitalWrite(8, 1);
  }
  if (utqk_ccfr == 2) {
    pinMode(8, OUTPUT);
    digitalWrite(8, 0);
  }
  if (utqk_ccfr == 3) {
    pinMode(4, OUTPUT);
    digitalWrite(2, 1);
  }
  if (utqk_ccfr == 4) {
    pinMode(4, OUTPUT);
    digitalWrite(2, 0);
  }
  if (utqk_ccfr == 5) {
    pinMode(5, OUTPUT);
    digitalWrite(4, 1);
  }
  if (utqk_ccfr == 6) {
    pinMode(5, OUTPUT);
    digitalWrite(4, 0);
  }
  if (utqk_ccfr == 7) {
    pinMode(2, OUTPUT);
    digitalWrite(5, 1);
  }
  if (utqk_ccfr == 8) {
    pinMode(2, OUTPUT);
    digitalWrite(5, 0);
  }
  if (utqk_ccfr == 9) {
    pinMode(8, OUTPUT);
       digitalWrite(8, 0);
      pinMode(5, OUTPUT);
       digitalWrite(5, 0);
      pinMode(4, OUTPUT);
       digitalWrite(4, 0);
      pinMode(2, OUTPUT);
       digitalWrite(2, 0);
  }
  if (analogSensor > sensorThres) {
    Serial.println(" Gaz!");
    ok = "В доме обнаружена утечка газа";
  }
  else {
    ok = "Всё хорошо";
  }
  String te = (String(temp) + "°" + ":" + String(vl) + "%" + ":" + ok + ":" + ";");
  mySerialBT.println(te);
  Serial.println(te);
  Serial.println(utqk_ccfr);
  delay(300);
}
