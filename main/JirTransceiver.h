/*
 * JirTransceiver.h
 *
 *  Created on: 16-Jan-2020
 *      Author: suraj
 */

#ifndef MAIN_JIRTRANSCEIVER_H_
#define MAIN_JIRTRANSCEIVER_H_


#include <mutex>          // std::mutex

#include "wasteGlobal.h"


#include <Arduino.h>

// ir recever header

#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>

// ir sender header
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include <vector>
struct some123{uint16_t* temp; uint16_t tempsize;};



class JirTransceiver {
public:
	JirTransceiver();
	virtual ~JirTransceiver();

	IRrecv *ptrIRrecv;
	IRsend *ptrIRsend;

	std::mutex Jmutex;           // mutex for critical section
	//some123 *som2;
	// recevre varibles
	#if DECODE_AC
	const uint8_t JkTimeout = 50;
	#else   // DECODE_AC
	const uint8_t JkTimeout = 15;
	#endif  // DECODE_AC
	const uint16_t JkMinUnknownSize = 12;
	#define LEGACY_TIMING_INFO false

	const uint16_t JkRecvPin = 19;
	const uint32_t JkBaudRate = 115200;
	const uint16_t JkCaptureBufferSize = 1024;

	const uint16_t JkFrequency = 38;

	// sender varivbales
	const uint16_t JkIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).


//	uint16_t rawData[67] = {9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550,
//	                        600, 1650, 650, 550, 600, 1650, 650, 1650, 650, 1650,
//	                        600, 550, 650, 1650, 650, 1650, 650, 550, 600, 1650,
//	                        650, 1650, 650, 550, 650, 550, 650, 1650, 650, 550,
//	                        650, 550, 650, 550, 600, 550, 650, 550, 650, 550,
//	                        650, 1650, 600, 550, 650, 1650, 650, 1650, 650, 1650,
//	                        650, 1650, 650, 1650, 650, 1650, 600};
//
	decode_results JResults;  // Somewhere to store the results

    //IRContainer irData;

// global value storing ir size and data
	uint16_t *_irRawArray;
	uint16_t _irSize;

	uint16_t *Jraw_array;
	uint16_t Jsize;

	volatile bool someFlag = true;

	void setInstance(IRrecv *tempIRrecv, IRsend *tempIRsend);
	void JirTransceiverLoop();
	void sendIR();
	void getIRarrayData();
	void ReadFileSendIR(String file_name);
	void SendIRFromIRContainer(IRContainer *ptrIRContainer);
	void saveIRdata(jStr arg1, jStr arg2);


	IRContainer globalIRVector;
	IRContainer globalIRVector123;
	IRContainer getIRData();
	//void printIRvectorData(IRContainer tempData);
	void printIRvectorData(IRContainer *tempData);

	volatile bool waitingToGetIRdata = false;
private:

};

#endif /* MAIN_JIRTRANSCEIVER_H_ */
