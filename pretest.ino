/*
 *
 * This Arduino UNO R4 code is made available for public use without any restriction
 *
 */

#include <WiFiS3.h>
#include <MQTTClient.h>

int num_array[14][7] = {{ 1,1,1,1,1,1,0 },    // 0
                        { 0,1,1,0,0,0,0 },    // 1
                        { 1,1,0,1,1,0,1 },    // 2
                        { 1,1,1,1,0,0,1 },    // 3
                        { 0,1,1,0,0,1,1 },    // 4
                        { 1,0,1,1,0,1,1 },    // 5
                        { 1,0,1,1,1,1,1 },    // 6
                        { 1,1,1,0,0,0,0 },    // 7
                        { 1,1,1,1,1,1,1 },    // 8
                        { 1,1,1,0,0,1,1 }};    // 9

const char WIFI_SSID[] = "este11e";     // CHANGE TO YOUR WIFI SSID
const char WIFI_PASSWORD[] = "mhai13920";  // CHANGE TO YOUR WIFI PASSWORD

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

const char SUBSCRIBE_TOPIC_venus[] = "68070194/venus";
const char SUBSCRIBE_TOPIC_prob[] = "68070194/prob_stat";

const int PUBLISH_INTERVAL = 5000;  // 5 seconds

WiFiClient network;
MQTTClient mqtt = MQTTClient(256);

unsigned long lastPublishTime = 0;


const int red = 1;
const int green = 3;
const int blue = 2;
const int segment_a = 13; 
const int segment_b = 12; 
const int segment_c = 11;
const int segment_d = A2;
const int segment_e = A3;
const int segment_f = A4;
const int segment_g = A5;

void setup() {
  Serial.begin(9600);

  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
  pinMode(5, INPUT_PULLUP);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(segment_a, OUTPUT);   
  pinMode(segment_b, OUTPUT);   
  pinMode(segment_c, OUTPUT);   
  pinMode(segment_d, OUTPUT);   
  pinMode(segment_e, OUTPUT);   
  pinMode(segment_f, OUTPUT);   
  pinMode(segment_g, OUTPUT);  


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
  // รับมาทีละ 2 ไม่ได้ เปลี่ยนตรงนี้เอา
  if (mqtt.subscribe(SUBSCRIBE_TOPIC_prob))
    Serial.print("Arduino UNO R4 - Subscribed to the topic: ");
  else
    Serial.print("Arduino UNO R4 - Failed to subscribe to the topic: ");

  Serial.println(SUBSCRIBE_TOPIC_prob);
  Serial.println("Arduino UNO R4 - MQTT broker Connected!");
  
}

void sendToMQTT() {

  int adc = analogRead(A0);
  float R = 10000.0 * adc / (1023.0 - adc);
  float temp = 1.0 / (log(R / 10000.0) / 3950.0 + 1.0 / 298.15) - 273.15;

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

  displayDigit(payload.toInt());
}

void displayDigit(int digit) {
  // Set each segment according to the num_array for the given digit
  digitalWrite(segment_a, num_array[digit][0]);
  digitalWrite(segment_b, num_array[digit][1]);
  digitalWrite(segment_c, num_array[digit][2]);
  digitalWrite(segment_d, num_array[digit][3]);
  digitalWrite(segment_e, num_array[digit][4]);
  digitalWrite(segment_f, num_array[digit][5]);
  digitalWrite(segment_g, num_array[digit][6]);
}
