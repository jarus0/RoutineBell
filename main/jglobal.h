#define $$$$$ "JARUS"

#include <iostream>


// future modification needed
#include <DS3232RTC.h>      // https://github.com/JChristensen/DS3232RTC
#include <Streaming.h>      // http://arduiniana.org/libraries/streaming/
extern DS3232RTC RTC;


extern bool flagForFLowExecution; // bad way to do it
#include "JarusAccessories.h"
extern JarusAccessories objJarusAccessories;


//extern objects
//#include "objJarusAccessories.h"
#include "Filerelatedoperations.h"
//header
#include <mutex>          // std::mutex
extern std::mutex Jmutex;           // mutex for critical section


extern File_related_operations jobjFileOperation;


#include "JirTransceiver.h"
extern JirTransceiver objJirTransceiver;

#include "RMTClass.h"
extern RMTClass objRGB;

#include <IRrecv.h>
extern IRrecv irrecv;
