/*!
 *  @file       Kemper.h
 *  Project     Arduino Kemper MIDI Library
 *  @brief      Kemper MIDI Library for the Arduino
 *  @version    1.0
 *  @author     Ersin Basaran
 *  @date       16/07/15
 *  @license    GPL v3.0
*/
#pragma once 

#include "Arduino.h"

#include "Kemper_namespace.h"
#include "AbstractKemper.h"
#include "Stomp.h"
#include <stdlib.h> 
#include <time.h>    


BEGIN_KEMPER_NAMESPACE

class KemperMock : public AbstractKemper
{
	private:
		int lastMode;
		StompState defaultStompStates[2][RIG_COUNT*5][8];

	public:

		KemperMock();

		void read();

		void tunerOn(); 
		void tunerOff(); 
		void tapOn(); 
		void tapOff(); 

		void looperRecordPlayDown();
		void looperRecordPlayUp();
		void looperReverseDown();
		void looperReverseUp();
		void looperHalfTimeDown();
		void looperHalfTimeUp();
		void looperUndoDown();
		void looperUndoUp();
		void looperStopEraseDown();
		void looperStopEraseUp();
		void looperTriggerDown();
		void looperTriggerUp();

		void sendControlChange(byte data1, byte data2);
		void toggleStomp(byte idx); 
		void setPerformance(int idx, int slot = 0);
		void setRig(byte rig); 

};



END_KEMPER_NAMESPACE
