/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>0
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 150
#define SERVOMAX 600

// Update these with values suitable for your network.

const char* ssid = "ASUS";
const char* password = "test1234";
const char* mqtt_server = "192.168.1.3";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
//  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  // motor setup
  pwm.begin();
  pwm.setPWMFreq(60);

  pwm1.begin();
  pwm1.setPWMFreq(60);
  yield();
  sit();
}


void  setServoPulse(uint8_t n, double pulse)
{
  double pulselen;

  pulselen = 1000000;
  pulselen /= 60;
//  Serial.print(pulselen);
  pulselen /= 4096;
//  Serial.print(pulselen);
  pulse *= 1000;
  pulse /= pulselen;
}

int   down = 0;
int   right_wave = 0;
int   left_wave = 0;
int   raand = 0;
int up = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");
  }

//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if (strcmp(topic, "nod") == 0)
  {
//    Serial.println("nod");
    nod();
  }
  else if (strcmp(topic, "hands/up") == 0)
  {
//    Serial.println("hands up");
    hands_up(&down, &up, &right_wave, &left_wave);
  }
  else if (strcmp(topic, "twist/right") == 0)
  {
//    Serial.println("twist right");
    twist_left();
  }
  else if (strcmp(topic, "hands/down") == 0)
  {
    Serial.println("hands down");
    hands_down(&down, up, right_wave, left_wave);
  }
  else if (strcmp(topic, "twist/left") == 0)
  {
//    Serial.println("twist left");
    twist_right();
  }
  else if (strcmp(topic, "wave/left") == 0)
  {
//    Serial.println("wave left");
    wave_left_hand(&left_wave);
  }
  else if (strcmp(topic, "wave/right") == 0)
  {
//    Serial.println("wave right");
    wave_right_hand(&right_wave);
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
//    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
//      Serial.println("connected");
//      Serial.println("subscribing");
      // Once connected, publish an announcement...
      // ... and resubscribe
      while (!client.subscribe("nod")) {delay(1000);}
      while (!client.subscribe("hands/up")) {delay(1000);}
      while (!client.subscribe("hands/down")) {delay(1000);}
      while (!client.subscribe("twist/left")) {delay(1000);}
      while (!client.subscribe("twist/right")) {delay(1000);}
      while (!client.subscribe("wave/right")) {delay(1000);}
      while (!client.subscribe("wave/left")) {delay(1000);}
//      Serial.println("subscribed");
    } else {
//      Serial.print("failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  lastMsg = millis();
}

bool check = false;

void loop() {
  LED();
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(100);
  if (!check) {
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    client.publish("outTopic", msg);
    check = true;
  }
}
