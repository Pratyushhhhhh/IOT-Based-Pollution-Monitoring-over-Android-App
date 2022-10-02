# IOT-Based-Pollution-Monitoring-over-Android-App
In this project, MQ135 gas sensor and DHT 11 sensors are used to collect real-time pollution levels and using IOT the data is displayed on an Android App.

The Air quality and temperature data is collected by the MQ135 and DHT sensors.  The calibrated sensors make the output voltage proportional to the concentration of polluting gases in Parts per Million (ppm).
The data is displayed on 16x2 LCD and then using ESP8266 the data is sent to the cloud and stored in Google Firebase. An android application is built using MIT app inventor which displays the real-time data and send notification when pollution level rises.

The Android App also has speech assistance, dynamic image assistance and notification assistance. All these change as the quality of air changes.
