/*
 * JarusAccessories.h
 *
 *  Created on: 29-Jan-2020
 *      Author: suraj
 */

#ifndef MAIN_JARUSACCESSORIES_H_
#define MAIN_JARUSACCESSORIES_H_
//#define INFO(MSG) info(__FILE__, __LINE__, __func__, __VA_ARGS__, MSG)
#define INFO(MSG) objJarusAccessories.info(__FILE__, (String (__LINE__)).c_str(), __func__, MSG );
//#define INFO(MSG) objJarusAccessories.info(__DATE__, __TIME__, __FILE__, (String (__LINE__)).c_str(), __func__, MSG);

#include "wasteGlobal.h"

#include <Esp.h>
#include <Int64String.h>
#include <ArduinoJson.h>
#include <sstream>

#include <WebSocketsServer.h>

struct jarusJSON
{
	jsonPair	vjsonPair;
	jsonNested	vjsonNested;
};


class JarusAccessories {
public:
	JarusAccessories();
	virtual ~JarusAccessories();



	jStr currentUserToken = "jarus";		// if this is blank than problem create
	bool rgbBhutickFalg = true;
	jsonPair colorMap;

	String str_chipID; // find through constructor according to device
	jStr sstr_chipID;
	jStr DeviceName;

	jStr jappVer = "0.1";
	jStr jfirmwareVer = "1.0";
	jStr jhardwareVer = "1.0";

	jStr fileConfig	= "/config.json";
//	jStr fileMode	= "/mode.json";
//	jStr timeNow	= "/time.json";

	jStr fileInfo = "/information";
	jStr recentFlow = "/recentFlow";
	jStr JcurrentFlow = "/JcurrentFlow";
	jStr FlowTimeStoring = "/FlowTimeStoring";

	//future modification needed
	int randNumber = 0;
	int randomArray[4] = {};

	bool savingIRflag = false;


	jarusJSON jgetJJSON(jStr jsonStr);
	void printjarusJSON(jarusJSON *temp);

	jStr getJsonStr(jsonPair *jjson);
	String func_getJson_str(jsonPair *json);

	jStr getJsonFromJP(jsonPair *json);
	String func_getJson_str(jsonPair *json, jsonNested *nestedJson);	// overload funtion

	jStr getValueFromKey(jStr temp_json, jStr key);
	void generateRandom();


	void jprint(jStr sText);	//change with template <typename T>	void jPrint(T toPri);

	String getCurrentFileName(String FullFileAddress);
	void info(jStr StrFile, jStr Strline, jStr Strfunc, jStr StrMsg);
	//void info(jStr StrDate, jStr StrTime, jStr StrFile, jStr Strline, jStr Strfunc, jStr StrMsg);
	//void info(__DATE__, __TIME__, __FILE__, (String (__LINE__)).c_str(), __func__, MSG);


	template<typename T>
	std::string toString(const T& value);

	//static inline jStr fortyRandomChar();

private:
	String getValueBySplit(String data, char separator, int index);

};

#endif /* MAIN_JARUSACCESSORIES_H_ */



/*https://github.com/PaulStoffregen/TimeAlarms
not using this because : continoue scaningn is needed for this

esp32 internal rtc not using becasue > bad accuracy
esp32 external rtc not uding > yes this can be better option but in deep sleep or power off condition or configuring is not easy so leaving this option also



https://github.com/PaulStoffregen/Time
this is good library


esp32 external crystal time accuracy
esp32 32khz external crystal in deep sleep accuracy
esp32 internal clock

https://www.esp32.com/viewtopic.php?t=3715
https://esp32.com/viewtopic.php?t=1175
https://github.com/espressif/arduino-esp32/issues/1225
https://esp32.com/viewtopic.php?t=9227

https://www.esp32.com/viewtopic.php?t=5391
https://www.reddit.com/r/esp32/comments/9v22bj/esp32_rtc_external_crystal_vs_internal_rc_clock/
https://forum.pycom.io/topic/3162/use-of-rtc-with-xtal-and-deepsleep
https://github.com/espressif/arduino-esp32/issues/1225
https://forum.pycom.io/topic/1069/accuracy-of-rtc/7
https://www.esp32.com/viewtopic.php?t=5391
https://github.com/espressif/arduino-esp32/issues/892
 *
 */
