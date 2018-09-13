#include <dht.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

MDNSResponder mdns;
ESP8266WebServer server(80);
const char* ssid     = "";
const char* password = "";
HTTPClient http;

// valve servo
int valveServoPos;
int valveServoPin = 12;
Servo valveServo;

// fan
int fanPin = 13;

// humidity and temperature sensor
dht DHT;
int humidityTemperaturePin = 14;

// local state
boolean isFanOn = false;
boolean isWaterValveOpen = false;
boolean isTopHatchOpen = false;

void setup() {
  Serial.begin(74880);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP()))
    Serial.println("MDNS responder started");

  server.on("/", []() {
    Serial.println("hello world");
    server.send(200, "text/html", "<p>Hello World</p>");
  });

  server.on("/start-fan", []() {
    server.send(200, "text/html", "<p>start fan</p>");
    startFan();
  });

  server.on("/stop-fan", []() {
    server.send(200, "text/html", "<p>stop fan</p>");
    stopFan();
  });

  server.on("/start-watering", []() {
    server.send(200, "text/html", "<p>start watering</p>");
    openValve();
  });

  server.on("/stop-watering", []() {
    server.send(200, "text/html", "<p>stop watering</p>");
    closeValve();
  });

  server.on("/read-send", []() {
    readTemperatureAndHumidity();
    delay(100);
    server.send(200, "text/html", "<p>temperature: " + String(DHT.temperature) + " humidity: " + String(DHT.humidity) + "</p>");
    sendSensorDataToServer(String(DHT.temperature), String(DHT.humidity), 0);
  });

  server.on("/read", []() {
    readTemperatureAndHumidity();
    delay(100);
    server.send(200, "text/html", "<p>temperature: " + String(DHT.temperature) + " humidity: " + String(DHT.humidity) + "</p>");
  });

  server.begin();
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  closeValve();
}

void startFan () {
  isFanOn = true;
  digitalWrite(fanPin, HIGH);
}

void stopFan () {
  isFanOn = false;
  digitalWrite(fanPin, LOW);
}

void openValve () {
  valveServo.attach(valveServoPin);
  delay(100);
  for (valveServoPos = 80; valveServoPos >= 5; valveServoPos -= 1) {
    valveServo.write(valveServoPos);
    delay(30);
  }
  isWaterValveOpen = true;
  delay(100);
  valveServo.detach();
}

void closeValve () {
  valveServo.attach(valveServoPin);
  isWaterValveOpen = true;
  delay(100);
  for (valveServoPos = 5; valveServoPos <= 80; valveServoPos += 1) {
    valveServo.write(valveServoPos);
    delay(50);
  }
  isWaterValveOpen = false;
  delay(100);
  valveServo.detach();
}

void readTemperatureAndHumidity() {
  int chk = DHT.read11(humidityTemperaturePin);
}

void sendSensorDataToServer (String temprature, String humidity, int soilmoisture) {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(
      "URL" +
      temprature +
      "&humidity=" + humidity +
      "&soilmoisture=" + String(soilmoisture) +
      "&isFanOn=" + (isFanOn ? "true" : "false") +
      "&isWaterValveOpen=" + (isWaterValveOpen ? "true" : "false") +
      "&isTopHatchOpen=" + (isTopHatchOpen ? "true" : "false"),
      "imaginarykey"
    );

    int httpCode = http.GET();
    Serial.println("Http code");
    Serial.print(httpCode);
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    }
    http.end();
  }
}


#define MIN (1000UL * 60 * 15)
unsigned long rolltime = millis() + MIN;

void loop() {
  server.handleClient();

  if((long)(millis() - rolltime) >= 0) {
    //  Do your five minute roll stuff here
    rolltime += MIN;
    readTemperatureAndHumidity();
    delay(100);
    sendSensorDataToServer(String(DHT.temperature), String(DHT.humidity), 0);
  }
}
