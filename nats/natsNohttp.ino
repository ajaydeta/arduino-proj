#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoNATS.h>
#include <ArduinoJson.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

const char *WIFI_SSID = "Toko Bu Tetty";
const char *WIFI_PSK = "1122334455";
char *REPORT_DOOR = "report.door";

WiFiClient client;
NATS nats(
    &client,
    "192.168.2.6", NATS_DEFAULT_PORT,
    "user",
    "password");

void connect_wifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PSK);
    while (WiFi.status() != WL_CONNECTED)
    {
        yield();
    }
    nats.connect();
}

void mpu_setup()
{
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

// void nats_blink_handler(NATS::msg msg) {
//   int count = atoi(msg.data);
//   while (count-- > 0) {
//     digitalWrite(LED_BUILTIN, LOW);
//     delay(100);
//     digitalWrite(LED_BUILTIN, HIGH);
//     delay(100);
//   }
// }

// void nats_on_connect() {
//   nats.subscribe("blink", nats_blink_handler);
// }

void setup()
{
    Serial.begin(115200);
    //   pinMode(LED_BUILTIN, OUTPUT);
    //   digitalWrite(LED_BUILTIN, HIGH);

    connect_wifi();
    mpu_setup();

    //   nats.on_connect = nats_on_connect;
}

void loop()
{
    if (WiFi.status() != WL_CONNECTED)
        connect_wifi();
    nats.process();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    static long n = 0;
    if (millis() >= n)
    {

        const size_t capacity = JSON_OBJECT_SIZE(15);
        DynamicJsonDocument doc(capacity);
        doc["acceleration_x"] = a.acceleration.x;
        doc["acceleration_y"] = a.acceleration.y;
        doc["acceleration_z"] = a.acceleration.z;
        doc["gyro_x"] = g.gyro.x;
        doc["gyro_y"] = g.gyro.y;
        doc["gyro_z"] = g.gyro.z;

        char result[capacity];
        char buff[512];
        serializeJson(doc, result);
        strcpy(buff, result);

        Serial.println(result);
        n = millis() + 3000;
        nats.publish(REPORT_DOOR, buff);
    }

    yield();
}