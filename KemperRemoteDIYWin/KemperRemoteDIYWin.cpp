
#include "KemperRemoteDIYWin.h"

#include <windows.h>
#include <stdio.h>
#include "KemperRemoteDisplay.h"

#include "VirtualDisplaySerializer.h"
#include "SerialDisplaySerializer.h"



#include <iostream>
#include <cstdlib>
#include "RtMidi.h"


USING_NAMESPACE_KEMPER

int main() {

	//Sleep(10000);
	AbstractKemper* kemper;
	KemperMock kemperMock;
	Kemper kemperReal;
	
	//kemper = &kemperMock;
	kemperReal.setMidiPorts(0, 1);
	kemperReal.begin();
	kemper = &kemperReal;

	kemper->state.mode = MODE_BROWSE;

	//kemper->setRig(2);

	KemperRemote kemperRemote(kemper);

	VirtualDisplaySerializer displaySerializer(&Serial);
	VirtualDisplay displayProvider(&displaySerializer, 480, 272);
	KemperRemoteDisplay display(kemper, &kemperRemote, &displayProvider);

	SerialDisplaySerializer serialDisplaySerializer("COM7");
	VirtualDisplay displayProvider2(&serialDisplaySerializer, 480, 320);
	KemperRemoteDisplay display2(kemper, &kemperRemote, &displayProvider2);


	int buffer[10];

	//kemperRemote.read();
	//kemper.setRig(2);
	char rigName[20] = "";

	while (true) {
		kemper->read();
		kemperRemote.read();

		if (strcmp(kemper->state.rigName, rigName)) {
			memcpy(rigName, kemper->state.rigName, 20);
			//debug(rigName);
		}

		int sw = 0;
		sw = getc(stdin); //@ersin - test

		if (sw>0) {
			sw--;
			int pressed = 1;
			pressed = getc(stdin);

			if (sw < 100)
			{
				if (pressed)
					kemperRemote.onSwitchDown(sw);
				else
					kemperRemote.onSwitchUp(sw); 
			}
			else if (sw >= 100 && sw < 200)
			{
				if (pressed) {
					debug("Toggle stomp");
					debug(sw-100);
					kemper->toggleStomp(sw - 100);
				}
			}
			else if (sw >= 200 && sw < 300)
			{
				if (pressed) {
					if (sw == 200) {
						if (kemper->state.mode == MODE_BROWSE) {
							kemper->state.mode = MODE_PERFORM;
							kemper->setPerformance(kemper->state.performance, kemper->state.slot);
						}
						else if (kemper->state.mode == MODE_PERFORM) {
							kemper->state.mode = MODE_BROWSE;
							kemper->setRig(kemper->state.currentRig);
						}
					}
				}
			}
		}

		fflush(stdout);

		Serial.write(0xF0);
		for (int i=0;i<LED_COUNT*3;i++) {
			Serial.write(kemperRemote.leds[i]);
		}
		Serial.write(0xFF);
		Serial.flush();

		display.draw();
		display2.draw();
		//Sleep(50);
	}


}