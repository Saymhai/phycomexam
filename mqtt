#include <WiFi.h>
#include <MQTT.h>

const char WIFI_SSID[] = "este11e";
const char WIFI_PASSWORD[] = "mhai13920";

// 1. เปลี่ยน Broker ให้ตรงกับ HTML และใช้พอร์ต 1883 สำหรับไมโครคอนโทรลเลอร์
const char MQTT_BROKER_ADRRESS[] = "mqtt-dashboard.com"; 
const int MQTT_PORT = 1883; 
const char MQTT_CLIENT_ID[] = "uno-client-suwannee-994"; 
const char MQTT_USERNAME[] = "";
const char MQTT_PASSWORD[] = "";

const char PUBLISH_TOPIC[] = "phycom/suwannee/status"; 
// 2. ใช้ wildcard '#' เพื่อรับทั้ง /red, /green, /blue ที่ส่งมาจากหน้าเว็บ
const char SUBSCRIBE_TOPIC[] = "phycom/suwannee/#"; 

const int PIN_RED   = 9;  
const int PIN_GREEN = 11; 
const int PIN_BLUE  = 10;

WiFiClient espClient;
MQTTClient mqttClient;

void connectWiFi() {
  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

void connectMQTT() {
  Serial.print("Connecting to MQTT...");
  while (!mqttClient.connect(MQTT_CLIENT_ID, MQTT_USERNAME, MQTT_PASSWORD)) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nConnected!");
  mqttClient.subscribe(SUBSCRIBE_TOPIC);
}

// 3. ปรับฟังก์ชันดักฟังตาม Topic (/red, /green, /blue) และ Payload ("on", "off") จาก HTML
void messageReceived(String &topic, String &payload) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(" | Payload: ");
  Serial.println(payload);

  // Common Anode: LOW = ติด, HIGH = ดับ
  if (topic.endsWith("/red")) {
    if (payload == "on") {
      digitalWrite(PIN_RED, LOW);
    } else if (payload == "off") {
      digitalWrite(PIN_RED, HIGH);
    }
  } 
  else if (topic.endsWith("/green")) {
    if (payload == "on") {
      digitalWrite(PIN_GREEN, LOW);
    } else if (payload == "off") {
      digitalWrite(PIN_GREEN, HIGH);
    }
  } 
  else if (topic.endsWith("/blue")) {
    if (payload == "on") {
      digitalWrite(PIN_BLUE, LOW);
    } else if (payload == "off") {
      digitalWrite(PIN_BLUE, HIGH);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  // Common Anode: สั่ง HIGH เพื่อปิดไฟเริ่มต้น
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_BLUE, HIGH);

  connectWiFi();

  mqttClient.begin(MQTT_BROKER_ADRRESS, MQTT_PORT, espClient);
  mqttClient.onMessage(messageReceived); 
}

void loop() {
  mqttClient.loop();
  delay(10);

  if (!mqttClient.connected()) {
    connectMQTT();
  }
}
