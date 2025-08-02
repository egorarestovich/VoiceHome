#include <SoftwareSerial.h>
#include "DHT.h"

#define SMOKE_SENSOR_PIN   A2
#define LIGHT_PIN          8
#define KETTLE_PIN         4
#define FAN_PIN            2
#define RELAY_FREE_PIN     5

#define DHT_PIN            12
#define DHT_TYPE           DHT11
DHT dht(DHT_PIN, DHT_TYPE);

#define SMOKE_THRESHOLD    450

SoftwareSerial mySerialBT(9, 10);  // RX=9, TX=10

char command = 0;  // Команда от Bluetooth или Serial

void setup() {
  Serial.begin(9600);
  mySerialBT.begin(9600);

  pinMode(LIGHT_PIN,      OUTPUT);
  pinMode(KETTLE_PIN,     OUTPUT);
  pinMode(FAN_PIN,        OUTPUT);
  pinMode(RELAY_FREE_PIN, OUTPUT);

  digitalWrite(LIGHT_PIN,      LOW);
  digitalWrite(KETTLE_PIN,     LOW);
  digitalWrite(FAN_PIN,        LOW);
  digitalWrite(RELAY_FREE_PIN, LOW);

  dht.begin();

  Serial.println("Система запущена.");
}

void loop() {
  if (mySerialBT.available()) {
    command = mySerialBT.read();
  }
  if (Serial.available()) {
    command = Serial.read();
  }

  if (command >= '1' && command <= '9') {
    handleCommand(command - '0');
    command = 0;
  }

  int smokeValue = analogRead(SMOKE_SENSOR_PIN);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  String status = "Всё хорошо";

  if (smokeValue > SMOKE_THRESHOLD) {
    status = "В доме обнаружена утечка газа";
    Serial.println("Внимание: утечка газа!");
  }

  if (isnan(temperature)) temperature = -99;
  if (isnan(humidity))    humidity    = -99;

  String message = String(temperature) + "°:" +
                   String(humidity) + "%:" +
                   status + ":" + ";";

  mySerialBT.println(message);
  Serial.println(message);

  delay(300);
}

void handleCommand(int cmd) {
  switch (cmd) {
    case 1:
      digitalWrite(LIGHT_PIN, HIGH);
      break;
    case 2:
      digitalWrite(LIGHT_PIN, LOW);
      break;
    case 3:
      digitalWrite(KETTLE_PIN, HIGH);
      break;
    case 4:
      digitalWrite(KETTLE_PIN, LOW);
      break;
    case 5:
      digitalWrite(RELAY_FREE_PIN, HIGH);
      break;
    case 6:
      digitalWrite(RELAY_FREE_PIN, LOW);
      break;
    case 7:
      digitalWrite(FAN_PIN, HIGH);
      break;
    case 8:
      digitalWrite(FAN_PIN, LOW);
      break;
    case 9:
      digitalWrite(LIGHT_PIN,      LOW);
      digitalWrite(KETTLE_PIN,     LOW);
      digitalWrite(FAN_PIN,        LOW);
      digitalWrite(RELAY_FREE_PIN, LOW);
      break;
    default:
      Serial.print("Неизвестная команда: ");
      Serial.println(cmd);
      break;
  }
}
