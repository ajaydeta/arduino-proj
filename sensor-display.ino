#include "DHT.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

DHT dht(2, DHT11);
Adafruit_SSD1306 display(4);

float h, t;
int gas;
int powerPinMQ = 13;
int readMQ = A0;

void setup() {
  pinMode(powerPinMQ, OUTPUT);
  
//  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop() {
  digitalWrite(powerPinMQ, HIGH);

  gas = analogRead(readMQ);
  h = dht.readHumidity();
  t = dht.readTemperature();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Suhu: ");
  display.setCursor(0, 12);
  display.print("Klmbn: ");
  display.setCursor(0, 24);
  display.print("Gas: ");

  display.setCursor(44, 0);
  display.print(t);
  display.setCursor(44, 12);
  display.print(h);
  display.setCursor(44, 24);
  display.print(gas);
//
//  Serial.print("suhu: ");
//  Serial.print(t);
//  Serial.println(" c");
//
//  Serial.print("kelembaban: ");
//  Serial.print(h);
//  Serial.println("%");
//
//  Serial.print("gas: ");
//  Serial.print(gas);
//  Serial.println("");
//  Serial.println("");
display.display();
  delay(1);
}
