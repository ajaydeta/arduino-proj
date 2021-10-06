#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

Adafruit_SSD1306 display(4);

void setup(){
  setPin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
}

void loop(){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Suhu: ");
  display.display();
  delay(1);
}


void setPin(){
    pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(2, HIGH);
}
