#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <stdio.h>

Adafruit_SSD1306 display(4);
Adafruit_MPU6050 mpu;

int displayPin = 13;

void setup() {
  pinMode(displayPin, OUTPUT);
  digitalWrite(displayPin, HIGH);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");


   mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
   mpu.setGyroRange(MPU6050_RANGE_500_DEG);
   mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  float acceleration[3] = {a.acceleration.x, a.acceleration.y, a.acceleration.z};
  float gyro[3] = {g.gyro.x, g.gyro.y, g.gyro.z};
  float temperature = temp.temperature;
  
//  char gyroStr[80];
//  sprintf(gyroStr,"x: %f, y: %f, z: %f", gyro[0], gyro[1], gyro[2]);
//sprintf(gyroStr,"%f", gyro[0]);
  
  display.clearDisplay();
  
//  display.setCursor(0, 0);
//  display.println("");
//  display.println("x: ");
//  display.println("y: ");
//  display.println("z: ");
//
//  display.setCursor(15, 0);
//  display.println("GIRO ");
//  display.setCursor(15, 0);
//  display.println(gyro[0]);
//  display.println(gyro[1]);
//  display.println(gyro[2]);
//  
//  
//
//  display.setCursor(60, 0);
//  display.println("ACLRTN ");
//  display.println(acceleration[0]);
//  display.println(acceleration[2]);
//  display.println(acceleration[2]);

 display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Connecting to SSID\n'adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.setCursor(0,0);
  
  display.display();
  delay(1000);

//  Serial.print("Acceleration X: ");
//  Serial.print(a.acceleration.x);
//  Serial.print(", Y: ");
//  Serial.print(a.acceleration.y);
//  Serial.print(", Z: ");
//  Serial.print(a.acceleration.z);
//  Serial.println(" m/s^2");
//
//  Serial.print("Rotation X: ");
//  Serial.print(gyro[0]);
//  Serial.print(", Y: ");
//  Serial.print(gyro[1]);
//  Serial.print(", Z: ");
//  Serial.print(gyro[2]);
//  Serial.println(" rad/s");
//
//  Serial.print("Temperature: ");
//  Serial.print(temp.temperature);
//  Serial.println(" degC");
//
//  Serial.println("");
//  delay(500);
}
