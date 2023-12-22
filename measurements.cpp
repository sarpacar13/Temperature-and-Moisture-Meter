#include <DHT.h>
#include <esp_sleep.h>
#include <Preferences.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ThingSpeak.h>

#define DHT_SENSOR_PIN pin no
#define DHT_SENSOR_TYPE DHT22
#define SOIL_MOISTURE_SENSOR_PIN pin no

const char* ssid = "ssid";
const char* password = "password";
const char* THINGSPEAK_API_KEY = "key";
const unsigned long THINGSPEAK_CHANNEL_ID = id;



DHT dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
Preferences preferences;
WiFiClient client;

void setup() {
  Serial.begin(9600);
  
  dht_sensor.begin();
  pinMode(SOIL_MOISTURE_SENSOR_PIN, INPUT);
  preferences.begin("env-data", false);
  connectToWiFi();
  
  takeReading();
  checkAndSendData();
  

  // Wake up and take a reading
  

  // Check if it's time to send data to ThingSpeak
  
}

void loop() {
  // Empty - all operations are in setup as we are using deep sleep
}

void takeReading() {
  float humidity = dht_sensor.readHumidity();
  float temperature = dht_sensor.readTemperature();
  int soilMoisture = analogRead(SOIL_MOISTURE_SENSOR_PIN);

  // Store data in NVM or RTC memory
  preferences.putFloat("humidity", humidity);
  preferences.putFloat("temperature", temperature);
  preferences.putInt("soilMoisture", soilMoisture);

  // Repeat for temperature and soil moisture
}

void checkAndSendData() {
  uint64_t currentTime = esp_timer_get_time() / 1000000ULL;
  int hourMarker = preferences.getInt("hourMarker", 100);

  //if (currentTime - hourMarker >= 100) {
    // Reset timer
    preferences.putInt("hourMarker", currentTime);

    // Connect to WiFi
    connectToWiFi();

    // Initialize ThingSpeak
    ThingSpeak.begin(client);

    // Retrieve data from NVM
    float avgHumidity = preferences.getFloat("humidity", 0);
    float avgTemperature = preferences.getFloat("temperature", 0);
    int avgSoilMoisture = preferences.getInt("soilMoisture", 0);

    // Send data to ThingSpeak
    ThingSpeak.setField(1, avgTemperature);
    ThingSpeak.setField(2, avgHumidity);
    ThingSpeak.setField(3, avgSoilMoisture);
    ThingSpeak.writeFields(THINGSPEAK_CHANNEL_ID, THINGSPEAK_API_KEY);

    // Clear the stored values after sending
    preferences.putFloat("avgHumidity", 0);
    preferences.putFloat("avgTemperature", 0);
    preferences.putInt("avgSoilMoisture", 0);
  

  // Go to deep sleep for a period (e.g., 5 minutes)
  goToDeepSleep(60); // Sleep for 5 minutes
  //}
}



void connectToWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
    }
  }
}

void goToDeepSleep(uint64_t sleepTimeInSeconds) {
  esp_sleep_enable_timer_wakeup(sleepTimeInSeconds * 1000000ULL);
  esp_deep_sleep_start();
}
