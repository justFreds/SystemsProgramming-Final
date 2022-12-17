#include <WiFi.h>
#include <PubSubClient.h>

#define LED 23
#define LED2    22
#define LED3  21
#define LED4  14
#define LED5  12
#define LED6  32
#define LED7  33
#define LED8  25
#define LED9  26

// WiFi
const char *ssid = "LA500"; // Enter your WiFi name
const char *password = "myemelmatt";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/led";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;
int count = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 client.publish(topic, "Hi EMQX I'm ESP32 ^^");
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 String message;
 //const char charmessage;
 for (int i = 0; i < length; i++) {
     //Serial.print((char) payload[i]);
     message = message + (char)payload[i]; //convert *byte to string
     //charmessage = charmessage + (char)payload[i];
 }
 Serial.print(message);
 //client.publish(topic, "9");
 if (message == "off") { digitalWrite(LED, LOW); }   // LED on
 if (message == "10") { digitalWrite(LED, HIGH); } // LED off
 if (message == "20") { digitalWrite(LED2, HIGH); }
 if (message == "30") { digitalWrite(LED3, HIGH); }
 if (message == "40") { digitalWrite(LED4, HIGH); }
 if (message == "50") { digitalWrite(LED5, HIGH); }
 if (message == "60") { digitalWrite(LED6, HIGH); }
 if (message == "70") { digitalWrite(LED7, HIGH); }
 if (message == "80") { digitalWrite(LED8, HIGH); }
 if (message == "90") { digitalWrite(LED9, HIGH); }
 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
 client.loop();
 if (count == 0){
   client.publish(topic, "testing");
   count++;
 }
}
