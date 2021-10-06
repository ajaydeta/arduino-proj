#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const char *AP_PASS = "12345678";

//=======SETUP FUNCTION========
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  delay(2000);
  serverSetup();
  wifiSetup();
}

void wifiSetup(){
  Serial.println("Starting AP for setting");
  WiFi.softAP(getId(), AP_PASS);
  Serial.println("Started");
  Serial.println("Ip address: ");
  Serial.println(WiFi.softAPIP().toString());
  Serial.println("Starting webservice");
}

void serverSetup(){
  server.on("/", HTTP_GET, httpRoot);
  server.on("/", HTTP_POST, httpSet);
  server.begin();
  Serial.println("Webservice started");
}

// http function
void httpRoot()
{
  char x[512];
  sprintf(x, "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1\"><h1>%s Wifi Setup<\/h1><form method=\"post\"><p>SSID\/Hotspot\/AP Name (Non 5GHz)<\/p><input type=\"text\" name=\"ssid\"\/><p>Password<\/p><input type=\"text\" name=\"pass\"\/><p><input type=\"submit\"\/><\/p><\/form>", getId().c_str());
  server.send(200, "text/html", x);
}

void httpSet()
{
  // check if server has ssid request
  if (!server.hasArg("ssid") || server.arg("ssid") == NULL)
  {
    server.send(200, "text/plain", "Harap isi data dibawah");
  }
  else
  {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");
    Serial.println("Got ssid " + ssid);
    Serial.println("Got pass " + pass);
    server.send(200, "text/plain", "Setup complete. please unplug and plug again");
    ESP.restart();
  }
}

String getId()
{
  String mac = WiFi.macAddress();
  mac.replace(":", "");
  return mac;
}

//======END SETUP FUNCTION======

void loop() {
  // put your main code here, to run repeatedly:

}
