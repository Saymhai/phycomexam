/*
 *
 * This Arduino UNO R4 code is made available for public use without any restriction
 *
 */

#include <WiFiS3.h>
#include <MQTTClient.h>

const char WIFI_SSID[] = "este11e";     // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "mhai";  // CHANGE TO YOUR WIFI PASSWORD

const char MQTT_BROKER_ADRRESS[] = "phycom.it.kmitl.ac.th";  // CHANGE TO MQTT BROKER'S ADDRESS
//const char MQTT_BROKER_ADRRESS[] = "192.168.0.11";  // CHANGE TO MQTT BROKER'S IP ADDRESS
const int MQTT_PORT = 1883;
const char MQTT_CLIENT_ID[] = "arduino-uno-r4-suwannee";  // CHANGE IT AS YOU DESIRE
const char MQTT_USERNAME[] = "";              // CHANGE IT IF REQUIRED, empty if not required
const char MQTT_PASSWORD[] = "";              // CHANGE IT IF REQUIRED, empty if not required

// The MQTT topics that Arduino should publish/subscribe
const char PUBLISH_TOPIC_temp[] = "68070194/temp";       // CHANGE IT AS YOU DESIRE
const char PUBLISH_TOPIC_poten[] = "68070194/light";   
const char PUBLISH_TOPIC_ultra[] = "68070194/food";  
const char PUBLISH_TOPIC_door[] = "68070194/door";  

const char SUBSCRIBE_TOPIC[] = "68070194/temp/#";  // CHANGE IT AS YOU DESIRE
const char SUBSCRIBE_TOPIC_venus[] = "68070194/venus";

const int PUBLISH_INTERVAL = 5000;  // 5 seconds

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;

const int red = 1;
const int green = 3;
const int blue = 2;

void setup() {
  Serial.begin(9600);

  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    Serial.print("Arduino UNO R4 - Attempting to connect to SSID: ");
    Serial.println(WIFI_SSID);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // print your board's IP address:
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  connectToMQTT();
}

void loop() {
  mqtt.loop();

  if (millis() - lastPublishTime > PUBLISH_INTERVAL) {
    sendToMQTT();
    lastPublishTime = millis();
  }
}

void connectToMQTT() {
  // Connect to the MQTT broker
  mqtt.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, network);

  // Create a handler for incoming messages
  mqtt.onMessage(messageReceived);

  Serial.print("Arduino UNO R4 - Connecting to MQTT broker");

  while (!mqtt.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if (!mqtt.connected()) {
    Serial.println("Arduino UNO R4 - MQTT broker Timeout!");
    return;
  }

  // Subscribe to a topic, the incoming messages are processed by messageHandler() function
  if (mqtt.subscribe(SUBSCRIBE_TOPIC_venus))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC_venus);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
}

void sendToMQTT() {

  int tempRaw = analogRead(A0);
  double voltage = (tempRaw * 5.0) / 1023.0;
  double temp = (voltage - 0.5) * 100.0;

  String val_str_temp = String(temp);
  char messageBuffer_temp[10];
  val_str_temp.toCharArray(messageBuffer_temp, 10);
  mqtt.publish(PUBLISH_TOPIC_temp, messageBuffer_temp);

  int poten = analogRead(A1);
  String val_str_poten = String(poten);
  char messageBuffer_poten[10];
  val_str_poten.toCharArray(messageBuffer_poten, 10);
  mqtt.publish(PUBLISH_TOPIC_poten, messageBuffer_poten);


  digitalWrite(9, HIGH);
  delayMicroseconds(10);
  digitalWrite(9, LOW);
  int pulseWidth = pulseIn(8, HIGH);
  long distance = pulseWidth/29/2;
  if (distance > 20) {
    mqtt.publish(PUBLISH_TOPIC_ultra, "off");
  } else {
    mqtt.publish(PUBLISH_TOPIC_ultra, "on");
  }

  int butt = digitalRead(5);
  if (distance >= 20 && butt == LOW) {
    mqtt.publish(PUBLISH_TOPIC_door, "on");
  } else {
    mqtt.publish(PUBLISH_TOPIC_door, "off");
  }
  

  Serial.println("Arduino UNO R4 - sent to MQTT:");
  Serial.print("- topic: ");
  Serial.println(PUBLISH_TOPIC_temp);
  Serial.println("- payload:");
  Serial.println(messageBuffer_temp);
  Serial.println(messageBuffer_poten);
  Serial.println(distance);
  Serial.println(butt);

}

void messageReceived(String &topic, String &payload) {
  Serial.println("Arduino UNO R4 - received from MQTT:");
  Serial.println("- topic: " + topic);
  Serial.println("- payload:");
  Serial.println(payload);

  int num = payload.toInt();
  if (num <= 50 && num >= 36) {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
  } else if (num <= 35 && num >= 26) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
  } else if (num <= 25 && num >= 10) {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
  } else {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
  }
}
