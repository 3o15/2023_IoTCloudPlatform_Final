#include <ArduinoBearSSL.h>
#include <ArduinoECCX08.h>
#include <ArduinoMqttClient.h>
#include <WiFiNINA.h> // change to #include <WiFi101.h> for MKR1000
#include <Servo.h>


#include "arduino_secrets.h"

#define LED_1_PIN 5
#define trig 7
#define echo 6
#define MQ2pin A0

#include <ArduinoJson.h>
#include "Led.h"

/////// Enter your sensitive data in arduino_secrets.h
const char ssid[] = SECRET_SSID;
const char pass[] = SECRET_PASS;
const char broker[] = SECRET_BROKER;
const char *certificate = SECRET_CERTIFICATE;

Servo servo;
WiFiClient wifiClient;            // Used for the TCP socket connection
BearSSLClient sslClient(wifiClient); // Used for SSL/TLS connection, integrates with ECC508
MqttClient mqttClient(sslClient);

unsigned long lastMillis = 0;

Led led1(LED_1_PIN);

const char *sentence1 = "close"; // 전역 레벨에서 선언

void setup() {
  Serial.begin(115200);
  while (!Serial);

  servo.attach(2);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(LED_1_PIN, OUTPUT);


  if (!ECCX08.begin()) {
    Serial.println("No ECCX08 present!");
    while (1);
  }

  // Set a callback to get the current time
  // used to validate the servers certificate
  ArduinoBearSSL.onGetTime(getTime);

  // Set the ECCX08 slot to use for the private key
  // and the accompanying public certificate for it
  sslClient.setEccSlot(0, certificate);

  // Optional, set the client id used for MQTT,
  // each device that is connected to the broker
  // must have a unique client id. The MQTTClient will generate
  // a client id for you based on the millis() value if not set
  //
  // mqttClient.setId("clientId");

  // Set the message callback, this function is
  // called when the MQTTClient receives a message
  mqttClient.onMessage(onMessageReceived);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!mqttClient.connected()) {
    // MQTT client is disconnected, connect
    connectMQTT();
  }

  // poll for new MQTT messages and send keep alives
  mqttClient.poll();

  // publish a message roughly every 5 seconds.
  if (millis() - lastMillis > 5000) {
    lastMillis = millis();
    char payload[512];
    getDeviceStatus(payload);
    sendMessage(payload);
  }
}

unsigned long getTime() {
  // get the current time from the WiFi module  
  return WiFi.getTime();
}

void connectWiFi() {
  Serial.print("Attempting to connect to SSID: ");
  Serial.print(ssid);
  Serial.print(" ");

  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the network");
  Serial.println();
}

void connectMQTT() {
  Serial.print("Attempting to MQTT broker: ");
  Serial.print(broker);
  Serial.println(" ");

  while (!mqttClient.connect(broker, 8883)) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }
  Serial.println();

  Serial.println("You're connected to the MQTT broker");
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe("$aws/things/MyMKRWiFi1010/shadow/update/delta");
}

void getDeviceStatus(char *payload) {
    int angle = 0;
    float air = analogRead(MQ2pin);
    float duration = ultrasonic();
    float weight = ((float)(340 * duration) / 10000) / 2;
    const char *sentence2;

    const char *led = (led1.getState() == LED_ON) ? "ON" : "OFF";

    if (strcmp(sentence1, "open") == 0) {
        angle = 70;
        servo.write(angle);
        servo.write(0);
        if (weight >= 30) {
            servo.write(-90);
            sentence1 = "close";
        }
    }

    if (air > 90) {
        sentence2 = "Please change the toilet pad";
        digitalWrite(LED_1_PIN, HIGH);
        delay(1000);
    } else {
        sentence2 = " ";
        digitalWrite(LED_1_PIN, LOW);
        delay(1000);
    }

    sprintf(payload, "{\"state\":{\"reported\":{\"weight\":\"%0.2f\",\"LED\":\"%s\",\"air\":\"%0.2f\",\"msg1\":\"%s\",\"msg2\":\"%s\"}}}", weight, led, air, sentence1, sentence2);
    //sprintf(payload, "{\"state\":{\"reported\":{\"air\":\"%0.2f\",,\"msg2\":\"%s\"}}}", air, sentence2);
}

void sendMessage(char* payload) {
  char TOPIC_NAME[]= "$aws/things/MyMKRWiFi1010/shadow/update";
  
  Serial.print("Publishing send message:");
  Serial.println(payload);
  mqttClient.beginMessage(TOPIC_NAME);
  mqttClient.print(payload);
  mqttClient.endMessage();
}

void onMessageReceived(int messageSize) {
    int receivedAngle = 0;

    char buffer[512];
    int count = 0;
    while (mqttClient.available()) {
        buffer[count++] = (char)mqttClient.read();
    }
    buffer[count] = '\0'; // Null-terminate the buffer

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, buffer);
    JsonObject root = doc.as<JsonObject>();
    JsonObject state = root["state"];
    const char *led = state["LED"];
    const char *receivedSentence1 = state["msg1"];

    // Update sentence1 based on the received message
    if (strcmp(receivedSentence1, "open") == 0 || strcmp(receivedSentence1, "close") == 0) {
        sentence1 = receivedSentence1;
    }

    char payload[512];

    if (strcmp(led, "ON") == 0) {
        led1.on();
        sprintf(payload, "{\"state\":{\"reported\":{\"LED\":\"%s\"}}}", "ON");
        sendMessage(payload);
    } else if (strcmp(led, "OFF") == 0) {
        led1.off();
        sprintf(payload, "{\"state\":{\"reported\":{\"LED\":\"%s\"}}}", "OFF");
        sendMessage(payload);
    }

    if (strcmp(receivedSentence1, "open") == 0) {
        receivedAngle = 70;
        servo.write(receivedAngle);
        sprintf(payload, "{\"state\":{\"reported\":{\"msg1\":\"%s\"}}}", "open");
        sendMessage(payload);
    } else if (strcmp(receivedSentence1, "close") == 0) {
        receivedAngle = -90;
        servo.write(receivedAngle);
        sprintf(payload, "{\"state\":{\"reported\":{\"msg1\":\"%s\"}}}", "close");
        sendMessage(payload);
    }
}

long ultrasonic(){
  long duration;

  digitalWrite(trig, LOW);
  digitalWrite(echo, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(echo, LOW);

  duration = pulseIn(echo, HIGH);

  return duration;
}
