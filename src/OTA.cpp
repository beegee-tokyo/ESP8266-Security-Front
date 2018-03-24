#include <Setup.h>

void initOTA() {
	// Create device ID from MAC address
	String macAddress = WiFi.macAddress();
	memcpy((void *) &hostApName[8], (void *) &macAddress[0], 2);
	memcpy((void *) &hostApName[10], (void *) &macAddress[9], 2);
	memcpy((void *) &hostApName[12], (void *) &macAddress[12], 2);
	memcpy((void *) &hostApName[14], (void *) &macAddress[15], 2);

	memcpy((void *) &OTA_HOST[4], (void *) &hostApName[8], 8);

	// Prepare OTA update listener
	ArduinoOTA.onStart([]() {
		wdt_disable();
		String debugMsg = "OTA start";
		sendRpiDebug(debugMsg, OTA_HOST);
		Serial.println(debugMsg);
		// Detach all interrupts and timers
		wdt_disable();
		doubleLedFlashStart(0.1);
		getLDRTimer.detach();
		alarmTimer.detach();
		heartBeatTimer.detach();
		stopListenToUDPbroadcast();

		WiFiUDP::stopAll();
		WiFiClient::stopAll();
		otaRunning = true;
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		digitalWrite(comLED, !digitalRead(comLED)); // Toggle blue LED
		digitalWrite(actLED, !digitalRead(actLED)); // Toggle red LED
	});
	ArduinoOTA.onError([](ota_error_t error) {
		digitalWrite(comLED, LOW); // Turn on blue LED
		digitalWrite(actLED, LOW); // Turn on red LED
	});
	ArduinoOTA.onEnd([]() {
		digitalWrite(comLED, HIGH); // Turn off blue LED
		digitalWrite(actLED, HIGH); // Turn off red LED
	});

	// Start OTA server.
	ArduinoOTA.setHostname(hostApName);
	ArduinoOTA.begin();

	MDNS.addServiceTxt("arduino", "tcp", "board", "ESP8266");
	MDNS.addServiceTxt("arduino", "tcp", "type", camDevice);
	MDNS.addServiceTxt("arduino", "tcp", "id", String(hostApName));
	MDNS.addServiceTxt("arduino", "tcp", "service", mhcIdTag);
	MDNS.addServiceTxt("arduino", "tcp", "loc", String(devLoc));
}
