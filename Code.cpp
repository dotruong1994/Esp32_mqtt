#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "likeasir";
const char* pass = "dientu174";
const char* brokerUser = "dotruong1994@gmail.com";
const char* brokerPass = "8db5dd9d";
const char* broker = "mqtt.dioty.co";

WiFiClient espClient;
PubSubClient client(espClient);

void setupWifi(){
  delay(100);
  Serial.print("\nConnecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid , pass);

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print("-");
  }
  Serial.print("\nConnected to: ");
  Serial.println(ssid);
}

void reconnect(){
  while(!client.connected()){
    Serial.print("\nConnecting to ");
    Serial.println(broker);
    if(client.connect("esp_steve", brokerUser, brokerPass)){
      Serial.print("\nConnected to ");
      Serial.println(broker);
      //client.subscribe(inTopic);
    } else {
      Serial.println("\n Trying to reconnect");
      delay(5000);
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupWifi();
  client.setServer(broker,1883);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
    reconnect();
  }
  client.loop();
}
