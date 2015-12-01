#include <ESP8266WiFi.h>
#include "SocketIOClient.h"

// replace with your ssid/password
const char* ssid     = "ssid";
const char* password = "password";

SocketIOClient client;

// replace with a host/port that has socket.io server
char hostname[] = "192.168.1.28";
int port = 3000;

WiFiClient wifiClient;

void ondata(SocketIOClient client, char *data) {    
  Serial.print(data);
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  connectToWifi();

  client.setDataArrivedDelegate(ondata);
  if (!client.connect(hostname, port)) {
    Serial.println(F("Not connected."));
  } else {
    Serial.println("Connected to host");
  }
}


void loop() {
  client.monitor();  
}

void connectToWifi() {  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(ssid);
  
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());      
  }
}

