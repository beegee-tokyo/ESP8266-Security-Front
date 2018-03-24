#include "Setup.h"
#include "declarations.h"

/**
 * Initialization of GPIO pins, WiFi connection, timers and sensors
 */
void setup() {

	initLeds();
	pinMode(pirPort, INPUT); // PIR signal
	pinMode(relayPort, OUTPUT); // Relay trigger signal
	pinMode(speakerPin, OUTPUT); // Loudspeaker/piezo signal
	digitalWrite(relayPort, LOW); // Turn off Relay
	digitalWrite(speakerPin, HIGH); // Switch Piezo buzzer off

	Serial.begin(115200);
	Serial.setDebugOutput(false);

	// Connect to one of the two alternative AP's
	connectInit();
	// Give it 5 seconds to connect
	long waitStart = millis();
	while (0) {
		if ((connStatus == CON_GOTIP) || ((millis()-waitStart)>5000)) {
			break;
		}
	}

	// Now other intializations can be done, but WiFi might not be working yet

	// Get initial value from LDR
	getLDR();

	// Start update of LDR value every 60 seconds
	getLDRTimer.attach(60, triggerGetLDR);

	// Start heart beat sending every 1 minute
	heartBeatTimer.attach(60, triggerHeartBeat);

	// Initialize interrupt for PIR signal
	attachInterrupt(pirPort, pirTrigger, CHANGE);

	// Initialize file system.
	bool spiffsOK = false;
	if (!SPIFFS.begin())
	{
		if (SPIFFS.format()){
			spiffsOK = true;
		}
	} else { // SPIFFS ready to use
		spiffsOK = true;
	}
	if (spiffsOK) {
		char tmpLoc[40];
		if (getConfigEntry("loc", tmpLoc)) {
			devLoc = String(tmpLoc);
		}
		if (getConfigEntry("light", tmpLoc)) {
			lightID = String(tmpLoc);
		}
		if (getConfigEntry("cam", tmpLoc)) {
			camID = String(tmpLoc);
		}
		if (getConfigEntry("sec", tmpLoc)) {
			secID = String(tmpLoc);
		}
	}

	if (alarmOn) {
		actLedFlashStart(1);
	} else {
		actLedFlashStop();
	}

	wdt_enable(WDTO_8S);
	wdtEnabled = true;
}
