/*
 * jdevicefunctionality.h
 *
 *  Created on: 26-Dec-2019
 *      Author: suraj
 */

#ifndef JDEVICEFUNCTIONALITY_H_
#define JDEVICEFUNCTIONALITY_H_

#include "jglobal.h"
#include <stdio.h>
#include <iostream>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "esp_task_wdt.h"

#include <mutex>          // std::mutex
struct timeStore
{
	int _day;
	int _hour;
	int _min;
	int _sec;
};



enum returnType
{
	jexecutionOK,
	jexecutionOKwithData,
	jexecutionProblem,
	jexecutionUndefine
};


union jarusUnion{

	//const char *fileName;
	struct type1  // for delete specific file
	{
		const char *completeFileDire;
		const char *somefilePart;
	} t1;

} ;


class j_device_functionality {
public:
	j_device_functionality();
	virtual ~j_device_functionality();

	std::mutex customMutez;           // dont know but later think about it


	timeStore timeVari;
	jarusUnion abc;
	jStr wasteElemt;

//	union jarusUnion abcs;
//	abcs.t1.
//	abc.folderName = suraj;

	bool RGBFLAg = false;

	typedef int (j_device_functionality::* ptr_func)(int);
	std::map<jStr, ptr_func> FuncCollection;

	DynamicJsonDocument *ptr_receivedJson ;
	DynamicJsonDocument *ptr_replyJson;


	// future : bad way to do
	//DynamicJsonDocument  heapAllocatedJson(500);
	DynamicJsonDocument  *ptrheapAllocatedJson;
	DeserializationError *ptrError;
	//some123 someWasterVarib;

	jStr _str_receivedJson;
	jStr _reply_json;

	jStr favoFile = "/favoFile";

	jsonNested objNestedJsonToReply;

	//objJarusAccessories.str_chipID;

	String _flowNow;
	String _id_flow;
	String _flow_time ;

	String id, mycmd, mydata;
	String d0, d1, d2, d3;

	//String firmwareVer = "temporary";
	int x = 0;


	int indirectFuncCall(jStr function_name, int extra_argument);
	String jsonDE(jStr json);

	int someChange = 9;

	void test_function();
	int func_getSSID (int x);
	int func_clearSSID(int x);
	int func_saveSSID(int x);
	int func_setNickname(int x);	// not supported yet	// save it in file
	int func_nickName (int x);

	int func_setMode(int x);	// not supported yet

	// worked
	int func_saveFlow (int x);
	int func_clearFlow(int x);
	int func_executeFlow(int x); // think little later today
	int func_stopFlow(int x);
	int func_getFlow(int x);	// ya its working now and man nahi hai to update with JJseriliser
	int func_nowFlow(int x);	// not supported yet
	int func_removeFlow(int x); // checking that
	int func_updateFlow(int x);
	int func_removeFlows(int x);
	int func_getFlows(int x);	// current working but need to change with univeral funciton

	// tested working fine
	int func_getIRs(int x);
	int func_removeIR(int x);
	int func_saveIR(int x);
	int func_updateIR(int x);
	int func_clearIR (int x);
	int func_executeIR (int x);

	int func_getStatus (int x);
	int func_resetDevice (int x);
	int func_restartDevice (int x);		// ok need to see

	// ok but flow must test first
	int func_saveFavorite (int x);
	int func_executeFavorite (int x);
	int func_removeFavorite (int x);
	int func_getFavorite (int x);
	int func_getFavorites (int x);		//putting patiya here
	int func_clearFavorite (int x);

	int func_defaultLight (int x);
	int func_lightStop (int x);

	int func_getBackup (int x);		// this 3 are super tough type
	int func_restoreBackup (int x);
	int func_getRecentFlow (int x);


	typedef int (j_device_functionality::*ptrFunc)(jStr subFile);
	//int OperationOnfolder(jStr folderAddress, ptrFunc func);

	typedef int (j_device_functionality::*ptrFuncU)(jarusUnion *myUnion);
	int JUOperationOnfolder(jStr folderName, jarusUnion *myUnion, ptrFuncU func);

	// replce with union architecure
	int ActionGetName(jStr subFile);
	int ActionDeleteAll(jStr subFile);
	int ActionDeleteSpecificFile(jStr insideFilesDireS);
	int ActionRenameSpecificFile(jStr subFile);

	int UActionDeleteSpecificFile(jarusUnion *myUnion); // t1 type// folder name , file conataon to delete

	int someAction(jStr subFile);

	void testCall();

	void eraseSubStr(std::string & mainStr, const std::string & toErase);

	void rgbCallBack();

	//void jSetAlarm();


	void setLightColor(jStr *rgbColor, jStr *intensity);
	void setLightColor(int x, int y, int z);

	void funcScheduleHandler();
	void setAlarmAfterSec(jStr seconds);
	void saveCurrentTime(time_t _currentTime = 0);

	void savoFlowStatusToFile(int count, jStr flowID);
	inline timeStore ConvertSectoDay(long n);

	void printTimeStore(timeStore timeVari);
	void printDateTime(time_t t);
	time_t compileTime();

	int suraj= 5;
private :
	int mehual;
};

#endif /* JDEVICEFUNCTIONALITY_H_ */
