#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int moisturePin = A0;
int smokePin = A1;
int ldrPin = A2;
int smokeThreshold = 500;
int moistureThreshold = 500;
int ldrThreshold = 500;

int smokeLedPin = 3;
int moistureLedPin = 4;
int ldrLedPin = 5;
int tempLedPin = 6;

void setup() {
  Serial.begin(9600);
  pinMode(smokePin, INPUT);
  pinMode(moisturePin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(smokeLedPin, OUTPUT);
  pinMode(moistureLedPin, OUTPUT);
  pinMode(ldrLedPin, OUTPUT);
  pinMode(tempLedPin, OUTPUT);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int smokeValue = analogRead(smokePin);
  int moistureValue = analogRead(moisturePin);
  int ldrValue = analogRead(ldrPin);

  if (smokeValue > smokeThreshold) {
    digitalWrite(smokeLedPin, HIGH);
  } else {
    digitalWrite(smokeLedPin, LOW);
  }

  if (moistureValue > moistureThreshold) {
    digitalWrite(moistureLedPin, HIGH);
  } else {
    digitalWrite(moistureLedPin, LOW);
  }

  if (ldrValue > ldrThreshold) {
    digitalWrite(ldrLedPin, HIGH);
  } else {
    digitalWrite(ldrLedPin, LOW);
  }

  if (!isnan(h) && !isnan(t)) {
    if (t > 25.0) {
      digitalWrite(tempLedPin, HIGH);
    } else {
      digitalWrite(tempLedPin, LOW);
    }
  }

  delay(1000);
}
