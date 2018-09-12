#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

MDNSResponder mdns;
ESP8266WebServer server(80);
// WIFI
const char* ssid     = "";
const char* password = "";
HTTPClient http;

// valve servo
int valveServoPos;
int valveServoPin = 12;
Servo valveServo;

// fan / relay pin
int fanPin = 13;

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
    sendSensorDataToServer(10, 11, 12);
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
    server.send(200, "text/html", "<p>start fan</p>");
    openValve();
  });

  server.on("/stop-watering", []() {
    server.send(200, "text/html", "<p>stop fan</p>");
    closeValve();
  });

  server.begin();
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, HIGH);
}

void startFan () {
  digitalWrite(fanPin, LOW);
}

void stopFan () {
  digitalWrite(fanPin, HIGH);
}

void openValve () {
  valveServo.attach(valveServoPin);
  for (valveServoPos = 80; valveServoPos >= 5; valveServoPos -= 1) {
    valveServo.write(valveServoPos);
    delay(30);
  }
  valveServo.detach();
}

void closeValve () {
  valveServo.attach(valveServoPin);
  for (valveServoPos = 5; valveServoPos <= 80; valveServoPos += 1) {
    valveServo.write(valveServoPos);
    delay(50);
  }
  valveServo.detach();
}

void sendSensorDataToServer (int temprature, int humidity, int soilmoisture) {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(
      "URL" +
      String(temprature) +
      "&humidity=" + String(humidity) +
      "&soilmoisture=" + String(soilmoisture),
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

void loop() {
  server.handleClient();
}
