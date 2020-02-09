/*
 *
 *
 https://docs.google.com/spreadsheets/d/1Cfk_IDdZE-DAtPYoYZ0RZiF8-0p8qxWxYN2PI68zfl8/edit#gid=0
 https://github.com/adafruit/Adafruit_NeoPixel/issues/139

 tio /dev/ttyUSB1
 http://tio.github.io/

task list track
https://docs.google.com/document/d/1kLIEZrwxPbqwv2_YOFN4r8Y1-xA5nMCIpMyJpQoOGKQ/edit
eclips toolchain setup guide :- https://docs.espressif.com/projects/esp-idf/en/latest/get-started-legacy/eclipse-setup.html


Current Pinouts (randome choosee:think again at producntion time)
D15 			: to gnd : SPIFFS clear button
19				: IR Receiver
4				: IR Transmitter
22,21,23 (SCL,SDA,SQW)	: RTC pin (GV )
D5(5GS)			: RGB pin

https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Touch/TouchInterrupt/TouchInterrupt.ino
gpio19 gnd vin


*/


/*
   https://circuitdigest.com/microcontroller-projects/esp8266-deep-sleep-mode-programming-explanation
   https://diyprojects.io/esp8266-deep-sleep-mode-test-wake-pir-motion-detector/#.XQckYRYzaUk

   Max deep sleep time 70 minutes
   ESP.deepsleep(0), suspends the module until it is woken up by a spike on the RST pin
   ESP.deepsleep(5 * 1000000), wake up the module every 5 seconds
   ESP.deepsleep(5000000, RF_DISABLED), wakes up the module every 5 seconds without re-activating the WiFi modem
   https://learn.sparkfun.com/tutorials/transistors/applications-i-switches

   // make a c++ serial port logger program

*/
//#include <esp_http_server.h>

#define USE_SERIAL JJLOG
#define DBG_OUTPUT_PORT USE_SERIAL

#define RXD2 16
#define TXD2 17
#include <Arduino.h>
#include "esp_task_wdt.h"

#include <Arduino.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "FS.h"

#include <rom/rtc.h>

#include "nvs_flash.h"
#include "nvs.h"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>

#include <esp_http_server.h>

#include "CommunicationMode.h"

#include "jglobal.h"
// extern varibles declared once here


File_related_operations jobjFileOperation;
JirTransceiver objJirTransceiver;
std::mutex GlobalMutexLU;
JarusAccessories objJarusAccessories;
RMTClass objRGB;
#include "JWebSocketsServer.h"
extern JWebSocketsServer obj_JWebSocketsServer;
JWebSocketsServer obj_JWebSocketsServer;

bool irDisabler = true;           // mutex for critical section


bool flagForFLowExecution = false; // bad way to do it
bool jwebsocketFlag = false;
jStr cmdFromWebSocket;           // mutex for critical section
jStr replyToWebSocket;

#include "main.h"

#include "RMTClass.h"
#include <stdlib.h>

#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRac.h>
#include <IRtext.h>
#include <IRutils.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
IRrecv irrecv(objJirTransceiver.JkRecvPin, objJirTransceiver.JkCaptureBufferSize, objJirTransceiver.JkTimeout, true);
IRsend irsend(objJirTransceiver.JkIrLed);  // Set the GPIO to be used to sending the message.

//const byte interruptPin = 23;
#define interruptPin 23
volatile int interruptCounter = 0;
int numberOfInterrupts = 0;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR handleInterrupt() {
  portENTER_CRITICAL_ISR(&mux);
  interruptCounter++;
  portEXIT_CRITICAL_ISR(&mux);
}


// future modification needed
DS3232RTC RTC;
std::mutex Jmutex;           // mutex for critical section


enum device_mode
{
  ACCESS_POINT = 1,
  STATION_POINT,
};

#include <WS2812FX.h>
WS2812FX *jjjRGB;
#define LED_COUNT 1
#define LED_PIN 5

void JWebSocketsServer_handler (void *pvParameter)
{
	obj_JWebSocketsServer.jwebSocketInit();
	while(1)
	{
		esp_task_wdt_reset();
		vTaskDelay(100 / portTICK_PERIOD_MS);
		obj_JWebSocketsServer.jwebSocketLoop();
	}

}

void JirTransceiver_handler (void *pvParameter)
{
	JirTransceiver *ptrJirTransceiver = (JirTransceiver*) pvParameter;

	while(1)
	{
		ptrJirTransceiver->JirTransceiverLoop();

		esp_task_wdt_reset();
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}

}


void LightHandlerhandler (void *pvParameter)
{
	RMTClass *ptrRMTClass = (RMTClass *)pvParameter;

	while(1)

	{
		ptrRMTClass ->rmtService();
		vTaskDelay(10 / portTICK_PERIOD_MS);
		esp_task_wdt_reset();

	}

}

#include <iostream>
#include <string>

#include <ArduinoJson.h>



extern "C" void app_main()
{
	esp_err_t err = nvs_flash_init();
	if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	  ESP_ERROR_CHECK(nvs_flash_erase());
	  err = nvs_flash_init();
	}





	initiate();

	JJLOG.println("&&&&&&&&&&&&&&&&&&&&&&&when file read then ir fire crash device");




//	RTC.squareWave(SQWAVE_1_HZ);	//delay(5000);
//	RTC.squareWave(SQWAVE_NONE);


	// maintain the sequense

	#if DECODE_HASH	// Ignore messages with less than minimum on or off pulses.
		irrecv.setUnknownThreshold(objJirTransceiver.JkMinUnknownSize);
	#endif  // DECODE_HASH
		irrecv.enableIRIn();  // Start the receiver
	irsend.begin();


	objJirTransceiver.setInstance(&irrecv, &irsend);
	jobjFileOperation.getIRinstance(&irrecv);


	xTaskCreate(&JirTransceiver_handler, "IRHandler", 4048, (void*) &objJirTransceiver, 1, NULL);


//	IRContainer irData;
//	while (true)
//	{		esp_task_wdt_reset();
//  	vTaskDelay(10 / portTICK_PERIOD_MS);
//
//
//		irData = jobjFileOperation.jgetVectorFromFile	(
//				"/but/b1"  );
//		objJirTransceiver.SendIRFromIRContainer(&irData);
//
//		delay(50);
//
//		 irData = jobjFileOperation.jgetVectorFromFile	(
//				"/but/b2"  );
//		objJirTransceiver.SendIRFromIRContainer(&irData);
//
//		delay(50);
//
//		irData = jobjFileOperation.jgetVectorFromFile	(
//				"/but/b4"  );
//		objJirTransceiver.SendIRFromIRContainer(&irData);
//
//		delay(50);
//		irData = jobjFileOperation.jgetVectorFromFile	(
//				"/but/b5"  );
//		objJirTransceiver.SendIRFromIRContainer(&irData);
//		delay(50);
//
//	}




//
//	rgbVal myColor;
//	myColor.r = 255;
//	myColor.g = 255;
//	myColor.b = 255;
//
//	objRGB.ws2812_setColors(2, &myColor); //rgbVal
//




	device_info();

	objRGB.ws2812_init(5);//ws2812_init(WS2812_PIN);
	xTaskCreate(&LightHandlerhandler, "ws2812 rainbow demo", 4096, (void *) &objRGB, 10, NULL);


	objJdeviceFunctionality.func_stopFlow(0);

//	objJdeviceFunctionality.suraj;
//	objJdeviceFunctionality.mehual;

	INFO("Some issue given below");
	// rtc alarm some times not works
//	JJLOG.println("if device has no token, but mobile has than problem arise");
//	JJLOG.println("app prbably has 2 problems 1> without changes just save flow rpeate mode change value and nested flow value change to null");
//	JJLOG.println("in nested flow second flow started than repatability check for second flow not frist one");
//  // when excuting favo same time firing button device crash
	// many placess heap allocation given file operator get rid of that later


	JJLOG.println("main while loop started");
	pinMode(15, INPUT_PULLUP);
	JJLOG.println("connect gnd pin 15 to clear spiff");

	long someTime = millis();
	pinMode(interruptPin, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(interruptPin), handleInterrupt, FALLING);

	JJLOG.println("mainloop starting");


	irrecv.disableIRIn();
	httpd_handle_t jserver = NULL;
	CommunicationMode obj_comM;

	obj_comM.jwifi_init_softap_sta_both(&jserver);
	irrecv.enableIRIn();

	xTaskCreate(&JWebSocketsServer_handler, "jarusWebsocket", 8024, NULL, 1, NULL);
	objJdeviceFunctionality.test_function();


	JJLOG.println("alarm setting for 5 sec");			// testing alarm is working or not
	objJdeviceFunctionality.setAlarmAfterSec("5");






//
///*
//	device turn on
//	if (read config file)
//		get router config otherwise null
//
//	set both sta and ap mode
//
//	try to coonect router
//	also wait for stations to connect
//
//	if no body connect to ap -> disable ap mode
//	if no router find turn off staion mode
//*/
//
//




	objRGB.jRainbowStart(false);
	rgbVal rgb ;
//	rgb = {255,0,0};	objRGB.ws2812_setColors(2, &rgb);delay(1000);
//	rgb = {0,255,0};	objRGB.ws2812_setColors(2, &rgb);delay(1000);
//	rgb = {0,0,255};	objRGB.ws2812_setColors(2, &rgb);delay(1000);



//for (int jloop = 0; jloop< 100; jloop ++)
//{
//	rgb = {0,0,255};	objRGB.ws2812_setColors(2, &rgb, jloop );delay(100);
//	JJLOG.println(jloop);
//
//}


	int text = 1;
	while(1)
	  {


//
//		obj_JWebSocketsServer
//		cmdFromWebSocket
//		String send2App =  objJdeviceFunctionality.jsonDE(collectedJsonFromWebSocket.c_str());




		esp_task_wdt_reset();
	  	vTaskDelay(10 / portTICK_PERIOD_MS);

	  	if (flagForFLowExecution)
	  	{
	  		flagForFLowExecution = false;
	  		JJLOG.println("Interrupt Flag Resetting|Flow Starting");
	  		objJdeviceFunctionality.funcScheduleHandler();

	  	}
	  	if ((someTime + 2 * 60 * 1000) < millis())
	  	{
	  		someTime = millis();
	  		objJdeviceFunctionality.printDateTime(RTC.get());
	  	}

		if(interruptCounter>0)
		{

			portENTER_CRITICAL(&mux);
			interruptCounter--;
			portEXIT_CRITICAL(&mux);

			numberOfInterrupts++;
			JJLOG.print(String (numberOfInterrupts) + " [-------------------------------jarus:interrupt:alarm-------------------------------]");
			JJLOG.println();

		  if ( RTC.alarm(ALARM_1) )    // check alarm flag, clear it if set
		  {
			  JJLOG << millis() << " ALARM_1 ";
			  objJdeviceFunctionality.printDateTime(RTC.get());
			  JJLOG << endl;
			  flagForFLowExecution = true;

		  }

		}
		if ( ! digitalRead(15))
		{
			JJLOG.println("spiff formatting");
			jobjFileOperation.jformat();
			JJLOG.println("spiff formated");
		}

	  }







}
