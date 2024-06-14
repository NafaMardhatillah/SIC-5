#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "MAN1";
const char *password = "majesa1234";
const char *serverName = "http://192.168.210.254:5000/submit";

#define SOUND_SENSOR_PIN 34 // Pin untuk sensor suara

void setup() {
  Serial.begin(115200);
  
  // Setup WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Setup pin sensor suara
  pinMode(SOUND_SENSOR_PIN, INPUT);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Membaca nilai dari sensor suara
    int soundValue = analogRead(SOUND_SENSOR_PIN);

    // Construct JSON payload
    String jsonPayload = "{\"sound\":";
    jsonPayload += soundValue;
    jsonPayload += "}";

    // Send POST request
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    delay(1000); // Delay sebelum pengukuran berikutnya
  } else {
    Serial.println("WiFi not connected");
    delay(1000);
  }
}
