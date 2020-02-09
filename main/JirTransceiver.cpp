/*
 * JirTransceiver.cpp
 *
 *  Created on: 16-Jan-2020
 *      Author: suraj
 */

#include "JirTransceiver.h"
JirTransceiver::JirTransceiver() {
	// TODO Auto-generated constructor stub
	JJLOG.println("JirTransceiver constructor");

}

JirTransceiver::~JirTransceiver() {
	// TODO Auto-generated destructor stub
}

void JirTransceiver::setInstance(IRrecv *tempIRrecv, IRsend *tempIRsend)
{
	//INFO("msg"); not work here
	JJLOG.println("IR Instance setting");
	ptrIRrecv = tempIRrecv;
	ptrIRsend = tempIRsend;
}

void JirTransceiver::JirTransceiverLoop()
{
	GlobalMutexLU.lock();
	//ptrIRrecv->enableIRIn();
	if (	ptrIRrecv->decode(&JResults)	 && irDisabler	)
	{

		uint16_t *_irRawArrayLocal 	= resultToRawArray(&JResults);
		uint16_t _irSizeLocal 		= getCorrectedRawLength(&JResults);
		JJLOG.println("IR data collected, Lenght:\t " + String (_irSizeLocal) );

		if (waitingToGetIRdata){
		globalIRVector.clear();
		globalIRVector.push_back(_irSizeLocal);
		for (int i = 0; i < _irSizeLocal+1; i++)
			globalIRVector.push_back(_irRawArrayLocal[i]);}
		//printIRvectorData(&globalIRVector);
		waitingToGetIRdata  = waitingToGetIRdata ?  false : true;
		delete _irRawArrayLocal;

	}
	//ptrIRrecv->disableIRIn();
	GlobalMutexLU.unlock();

}
IRContainer JirTransceiver::getIRData()
{
	ptrIRrecv->enableIRIn();
	waitingToGetIRdata = true;
	while(waitingToGetIRdata);	JJLOG.println("got IR data");
	ptrIRrecv->disableIRIn();
	return globalIRVector;
}
void JirTransceiver::printIRvectorData(IRContainer *tempData)
{
	JJLOG.println("\nIR data printing starting");
	for (auto it = tempData->begin(); it != tempData->end(); it++)
	{
		JJLOG.print(*it);JJLOG.print(',');
	}
	JJLOG.println("\nIR data end");
}

void JirTransceiver::SendIRFromIRContainer(IRContainer *ptrIRContainer)
{
	GlobalMutexLU.lock();
	ptrIRrecv->disableIRIn();
	uint16_t size = ptrIRContainer->front();
	ptrIRContainer->erase (ptrIRContainer->begin());
	ptrIRContainer->shrink_to_fit();

//printing
	JJLOG.println("IR size\t: " + String (size ) );
	int countert = 0;
	uint16_t *somePatiya = (uint16_t *)malloc(size * sizeof(uint16_t));

	auto it = ptrIRContainer->begin();
	for (int lloop = 0; lloop < size; lloop++)
	{
		somePatiya[lloop] = *it; ++it;
	}
	ptrIRsend->sendRaw(somePatiya, size, JkFrequency);
	delete[] somePatiya;
	ptrIRrecv->enableIRIn();
	GlobalMutexLU.unlock();
}

void JirTransceiver::ReadFileSendIR(String file_name)
{
	//ptrIRsend->sendRaw(irCodeArray, irCodeLen, JkFrequency);
}

