# Temperature-and-Moisture-Meter
IoT based Temperature and Moisture Meter aims energy efficiency during the measurement period for optimized agricultural products


README for ESP32 DHT22 & Soil Moisture Sensor Project
Overview
This project involves the use of an ESP32 microcontroller to monitor environmental conditions using a DHT22 temperature and humidity sensor, and a soil moisture sensor. The data collected is sent to ThingSpeak, an IoT analytics platform, for remote monitoring. The ESP32 enters deep sleep mode between readings to conserve energy.

Hardware Requirements
ESP32 Microcontroller
DHT22 Temperature and Humidity Sensor
Soil Moisture Sensor
Connecting Wires
Power Source for ESP32

Software Dependencies
Arduino IDE
ESP32 Board Support Package for Arduino IDE
DHT Sensor Library (<DHT.h>)
WiFi Library for ESP32 (<WiFi.h>)
HTTP Client Library for ESP32 (<HTTPClient.h>)
ThingSpeak Library (<ThingSpeak.h>)
Preferences Library for ESP32 (<Preferences.h>)

Setup Instructions
Assemble Hardware: Connect the DHT22 sensor and soil moisture sensor to the ESP32 according to their pin configurations.
Configure WiFi and ThingSpeak:
Set your WiFi credentials: Replace "ssid" and "password" with your WiFi SSID and password.
Configure ThingSpeak: Replace THINGSPEAK_API_KEY and THINGSPEAK_CHANNEL_ID with your corresponding ThingSpeak channel credentials.
Install Arduino IDE and Libraries: If not already installed, download and install Arduino IDE. Add the ESP32 Board Support Package and install the required libraries listed in Software Dependencies.
Upload Code: Open the provided script in Arduino IDE, select the correct board and port for your ESP32, and upload the code.

Code Explanation
setup(): Initializes serial communication, sensors, and WiFi connection. It then takes a reading and checks if it's time to send data to ThingSpeak.
takeReading(): Reads data from the DHT22 and soil moisture sensor, storing the values in non-volatile memory.
checkAndSendData(): Checks if it's time to send data to ThingSpeak, and if so, sends the average of the stored readings.
connectToWiFi(): Manages the WiFi connection.
goToDeepSleep(): Puts the ESP32 into deep sleep mode for a specified time to save power.

Safety and Security
Network Security: The WiFi SSID and password are hardcoded, which may pose a security risk. Consider implementing a more secure method for handling credentials.
Data Privacy: Be aware of privacy concerns when sending data to the cloud.

Troubleshooting
Connection Issues: Check if the WiFi credentials and ThingSpeak API key and channel ID are correctly set.
Sensor Malfunction: Ensure that all connections are secure and the sensors are working properly.
Power Issues: Verify that the ESP32 is adequately powered.

Customization
Reading Frequency: Modify the goToDeepSleep function to change the interval between readings.
Data Fields: Adjust the fields sent to ThingSpeak based on your specific requirements.
