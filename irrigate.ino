#include <PubSubClient.h>
#include <Ethernet.h>
#include <Timer.h>
//#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
//#define DHTTYPE DHT22


const short VALVE_PIN = 3;          // Solenoid Valve Pin
const int WATERING_TIME = 30000;    // 30 Seconds

string message = "";
boolean watering = false;
boolean pumpOn = false;
Timer tWater;


IPAddress ip(172, 16, 0, 100);
IPAddress server(172, 16, 0, 2);
EthernetClient ethClient;
PubSubClient client(ethClient);


/* AUXILIARY FUNCTIONS: 
  - callback()
  - wateringOn()
  - wateringOff()
*/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  // Store the payload in the message var
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    message = message + (char)payload[i]
  }

  if message == "1" {
    digitalWrite(VALVE_PIN, HIGH);  
  } else if message == "0" {
    digitalWrite(VALVE_PIN, LOW);  
  }
  
  Serial.println();
}

void timeWateringOn() {
  digitalWrite(VALVE_PIN, HIGH);
  watering = true;
  tWater.after(WATERING_TIME, wateringOff);   
}

void timeWateringOff() {
  digitalWrite(VALVE_PIN, LOW);
  watering = false;
}

void setup() {
  // Setting up Serial console
  Serial.begin(57600);
  
  // put your setup code here, to run once:
  pinMode(VALVE_PIN, OUTPUT);     //Solenoid pin
  digitalWrite(VALVE_PIN, LOW);   //Make sure the valve is off

  // Configure the MQTT Client
  client.setServer(server, 1883);
  client.setCallback(controlPump);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Update timers
  tWater.update();

  cliente.loop()
}
