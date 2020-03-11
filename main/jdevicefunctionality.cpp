/*
 * suraj
 * jdevicefunctionality.cpp
 *
 *  Created on: 26-Dec-2019
 *      Author: suraj
 */

#include "jdevicefunctionality.h"

j_device_functionality::j_device_functionality() {

	FuncCollection["clearSSID"]	= &j_device_functionality::func_clearSSID;
	FuncCollection["saveSSID"] 	= &j_device_functionality::func_saveSSID;
	FuncCollection["setMode"]      = &j_device_functionality::func_setMode;;

	FuncCollection["clearFlow"]	= &j_device_functionality::func_clearFlow;
	FuncCollection["executeFlow"] 	= &j_device_functionality::func_executeFlow;
	FuncCollection["stopFlow"]     = &j_device_functionality::func_stopFlow;
	FuncCollection["saveFlow"]     = &j_device_functionality::func_saveFlow;

	FuncCollection["getFlow"] 		= &j_device_functionality::func_getFlow;
	FuncCollection["getFlows"]     = &j_device_functionality::func_getFlows;
	FuncCollection["nowFlow"]		= &j_device_functionality::func_nowFlow;
	FuncCollection["removeFlow"]	= &j_device_functionality::func_removeFlow;
	FuncCollection["removeFlows"]	= &j_device_functionality::func_removeFlows;
	FuncCollection["updateFlow"]	= &j_device_functionality::func_updateFlow;


	FuncCollection["getIRs"]		= &j_device_functionality::func_getIRs;
	FuncCollection["removeIR"]		= &j_device_functionality::func_removeIR;
	FuncCollection["saveIR"]		= &j_device_functionality::func_saveIR;
	FuncCollection["updateIR"]		= &j_device_functionality::func_updateIR;

	FuncCollection["getStatus"]	= &j_device_functionality::func_getStatus;
	FuncCollection["resetDevice"]	= &j_device_functionality::func_resetDevice ;
	FuncCollection["restartDevice"]= &j_device_functionality::func_restartDevice ;

	FuncCollection["saveFavorite"]	= &j_device_functionality::func_saveFavorite ;
	FuncCollection["saveFavorite"]	= &j_device_functionality::func_saveFavorite ;
	FuncCollection["executeFavorite"]	= &j_device_functionality::func_executeFavorite ;

	FuncCollection["removeFavorite"]	= &j_device_functionality::func_removeFavorite ;

	FuncCollection["clearFavorite"]	= &j_device_functionality::func_clearFavorite ;

	FuncCollection["getFavorite"]	= &j_device_functionality::func_getFavorite ;
	FuncCollection["getFavorites"]	= &j_device_functionality::func_getFavorites ;
	FuncCollection["clearFavorite"]	= &j_device_functionality::func_clearFavorite ;
	FuncCollection["getRecentFlow"]	= &j_device_functionality::func_getRecentFlow  ;

	FuncCollection["executeIR"]	= &j_device_functionality::func_executeIR;
	FuncCollection["clearIR"]	= &j_device_functionality::func_clearIR;
	FuncCollection["nickName"]	= &j_device_functionality::func_nickName ;


	FuncCollection["setNickname"]	= &j_device_functionality::func_setNickname;
	FuncCollection["lightStop"]	= &j_device_functionality::func_lightStop;
	FuncCollection["defaultLight"]	= &j_device_functionality::func_defaultLight;

}

j_device_functionality::~j_device_functionality(){
	// TODO Auto-generated destructor stub
}


int j_device_functionality::func_nickName (int x)
{
	INFO("msg");

	jStr nickName = mydata.c_str();

	JJLOG.println("warning what is deviceVersion");

	jsonPair infoReply;
	infoReply["mdnsName"] 			= "SmartRemote@" + objJarusAccessories.sstr_chipID; //Put Sensor value
	infoReply["supportedAuth"] 		= "[0,1,2]";
	infoReply["deviceVersion"] 		= "0.1";
	infoReply["firmwareVersion"] 	= objJarusAccessories.jfirmwareVer;
	infoReply["nickName"] 			= nickName ;

	jobjFileOperation.jwriteFile (
    		"/information",
			objJarusAccessories.getJsonFromJP(&infoReply) );

//    DynamicJsonDocument root(500);
//    root["mdnsName"] = "SmartRemote@" + objJarusAccessories.str_chipID; //Put Sensor value
//    root["supportedAuth"] = "[0,1,2]";
//    root["deviceVersion"] = "0.1";
//    root["firmwareVersion"] = objJarusAccessories.jfirmwareVer;
//	root["nickName"] = mydata;
//
//    String temp = "";
//    serializeJson(root, temp);
//    JJLOG.println(temp);
//
//    jobjFileOperation.jwriteFile ("/information", temp.c_str() );


	return jexecutionOK;

}

//
//int j_device_functionality::OperationOnfolder(jStr folderAddress, ptrFunc func)
//{
//	File root = SPIFFS.open(folderAddress.c_str());
//    if(!root && !root.isDirectory()){return -1;}
//    for (File file = root.openNextFile(); file; file = root.openNextFile())
//        if(!file.isDirectory())
//        	if(! (this->*func)(file.name()) ) break;
//
//    return 0;
//}

int j_device_functionality::JUOperationOnfolder(jStr folderName, jarusUnion *myUnion, ptrFuncU func)
{
	File root = SPIFFS.open( folderName.c_str() );
    if(!root && !root.isDirectory()){return -1;}
    for (File file = root.openNextFile(); file; file = root.openNextFile())
    {
    	myUnion->t1.completeFileDire = file.name();
    	if( !file.isDirectory() )
    	{
        	if(! (this->*func)( myUnion) ) break;
    	}
    }
    return 0;
}

int j_device_functionality::UActionDeleteSpecificFile(jarusUnion *myUnion)
{
	INFO("msg");
	JJLOG.print("In Folder Name: ");
	JJLOG.println( myUnion->t1.completeFileDire );

	JJLOG.print("Searching File Name ");
	JJLOG.println( myUnion->t1.somefilePart );
	jStr someShit = myUnion->t1.completeFileDire;
	if (someShit.find(	myUnion->t1.somefilePart ) > 0)
	{
		  JJLOG.print("file found: ");
		  JJLOG.println(myUnion->t1.completeFileDire);
		  jobjFileOperation.jdeleteFile( myUnion->t1.completeFileDire );
		  return 0;
	}
	return 1;
}
int j_device_functionality::someAction(jStr subFile)
{
//	JJLOG.print("printhing file name: - ");
//	JJLOG.println (subFile.c_str());
//	jobjFileOperation.jreadFile(subFile.c_str());
//
	return 1;
}

void j_device_functionality::testCall()
{
	//OperationOnfolder("/jarus", &j_device_functionality::someAction);
}

int j_device_functionality::indirectFuncCall(jStr function_name, int extra_argument)
{
	//INFO(function_name);
	//JJLOG.print("Function call initiating\t: ");
	//JJLOG.println(function_name.c_str());
	return (this->*FuncCollection[function_name])(extra_argument);
	return 0;
}

void j_device_functionality::test_function()
{
	INFO("Test funciton on connection");
	//jjjRGB->setMode(FX_MODE_RAINBOW_CYCLE);
}

String j_device_functionality::jsonDE(jStr str_receivedJson)
{
	//INFO("Future change with jarusJSON");

	ptr_receivedJson = new DynamicJsonDocument(500);
	_str_receivedJson = str_receivedJson.c_str();
	DeserializationError error = deserializeJson(*ptr_receivedJson, _str_receivedJson);
	if (error)
	{
		String issue = error.c_str();
		JJLOG.print(F("deserializeJson() failed: "));
		JJLOG.println(error.c_str());
	}

	id     = (*ptr_receivedJson)["id"].as<const char*>();
	mycmd  = (*ptr_receivedJson)["cmd"].as<const char*>();
	mydata = (*ptr_receivedJson)["data"].as<const char*>();

	d0 = (*ptr_receivedJson)["data"][0].as<const char*>();
	d1 = (*ptr_receivedJson)["data"][1].as<const char*>();
	d2 = (*ptr_receivedJson)["data"][2].as<const char*>();
	d3 = (*ptr_receivedJson)["data"][3].as<const char*>();

//
//	JJLOG.println("\nApp collected data decoding");
//	JJLOG.print("ID\t: ");		JJLOG.println(id);
//	JJLOG.print("mycmd\t: "); 	JJLOG.println(mycmd);
//	JJLOG.print("mydata\t: "); 	JJLOG.println(mydata);
//	JJLOG.print("d0\t: "); 		JJLOG.println(d0);
//	JJLOG.print("d1\t: "); 		JJLOG.println(d1);
//	JJLOG.print("d2\t: "); 		JJLOG.println(d2);
//	JJLOG.print("d3\t: ");		JJLOG.println(d3);
//	JJLOG.println("***end***\n");

	ptr_replyJson = new DynamicJsonDocument(1000);
	(*ptr_replyJson)["id"] = objJarusAccessories.str_chipID;
	(*ptr_replyJson)["ack"] = mycmd;

	objNestedJsonToReply.clear();
	int funcReturnValue  = -1;

	customMutez.lock();
	irrecv.disableIRIn();
	if (id == objJarusAccessories.str_chipID || id == "all")
	{
		 if (FuncCollection.count(mycmd.c_str())>0)
			 funcReturnValue  = (this->*FuncCollection[mycmd.c_str()]) (0);
			 //funcReturnValue = indirectFuncCall(mycmd.c_str(), 0);
		 else JJLOG.println("this feature not yet implemented");
	}
	customMutez.unlock();
	irrecv.enableIRIn();

	switch (funcReturnValue)
	{
	    case jexecutionOK:
	    {
			JJLOG.println("case\t: jexecutionOK");
			(*ptr_replyJson)["data"] = "ok";
	    }break;
	    case jexecutionOKwithData:
	    {
	    	JJLOG.println("case\t: jexecutionOKwithData");
	    	JsonArray data = (*ptr_replyJson).createNestedArray("data");
	    	 for (auto i = objNestedJsonToReply.begin(); i != objNestedJsonToReply.end(); ++i)
	    		 data.add((*i).c_str());

	    }break;

	    case jexecutionProblem:
	    {
	    	JJLOG.println("case\t: jexecutionProblem");
	    }break;
	    case jexecutionUndefine:
	    {
	    	JJLOG.println("case\t: jexecutionUndefine");
	    }break;
	    default:
	    	JJLOG.println("case\t: default");
	}

	String msg = "";
	serializeJson(*ptr_replyJson, msg);
	delete ptr_receivedJson;
	delete ptr_replyJson;
	return msg;
}

int j_device_functionality::func_getRecentFlow(int x)
{
	INFO("msg");

	jarusJSON jsonTemp  = objJarusAccessories.jgetJJSON( jobjFileOperation.jreadFile("/JcurrentFlow") );
	jStr currentFlowID = jsonTemp.vjsonPair["currentFlow"];

	//JJLOG.println("currentFlowID " + String (currentFlowID.c_str()));
	//objJarusAccessories.printjarusJSON(&jsonTemp);

	jsonTemp =  objJarusAccessories.jgetJJSON(
			jobjFileOperation.jreadFile(objJarusAccessories.recentFlow));

	//objJarusAccessories.printjarusJSON(&jsonTemp);

	jStr som1 = jsonTemp.vjsonPair["rece1"];
	jStr som2 = jsonTemp.vjsonPair["rece2"];
	jStr som3 = jsonTemp.vjsonPair["rece3"];

//	if (som1 != "" && currentFlowID != som1) objNestedJsonToReply.push_back(som1.c_str());
	if (som2 != "" && currentFlowID != som2) objNestedJsonToReply.push_back(som2.c_str());
	if (som3 != "" && currentFlowID != som3) objNestedJsonToReply.push_back(som3.c_str());

	JJLOG.println("Recent flowList " +
			String (som1.c_str()) + " " +
			String (som2.c_str())+ " " +
			String (som3.c_str()));

	return jexecutionOKwithData;
}

int j_device_functionality::func_clearSSID(int x)
{
	INFO("msg");
	jobjFileOperation.jdeleteFile(objJarusAccessories.fileConfig);
	return jexecutionOK;
}

int j_device_functionality::func_saveSSID(int x)
{
	INFO("msg");
    JJLOG.println("New config...");
    JJLOG.println("ssid:- " + d0 );	//ssid
    JJLOG.println("pass:- " + d1 );	//pass

    jobjFileOperation.jwriteFile(objJarusAccessories.fileConfig, _str_receivedJson);

	return jexecutionOK;
}

int j_device_functionality::func_setMode(int x)
{
	INFO("msg");
    JJLOG.println(F("Router Mode..."));
    JJLOG.println(d1);
    JJLOG.println(d2);





	jStr fileConfigContain =  jobjFileOperation.jreadFile(objJarusAccessories.fileConfig);
	jarusJSON temp =  objJarusAccessories.jgetJJSON( fileConfigContain );

//	int FlowPosition  = 2 + atoi( temp.vjsonPair["counter"].c_str() );
//	jStr currentFlowName  = temp.vjsonPair["currentFlow"];


    jobjFileOperation.jwriteFile(objJarusAccessories.fileConfig, _str_receivedJson);

    DynamicJsonDocument  conFig(300);
    DeserializationError error = deserializeJson(conFig, _str_receivedJson);
    if (error) {
      JJLOG.print(F("deserializeJson() failed: "));
      JJLOG.println(error.c_str());
    }


	String newssid = conFig["data"][0];
	String newpass = conFig["data"][1];



    if (newssid != "")
    {
        WiFi.disconnect();
        WiFi.softAPdisconnect();
        WiFi.mode(WIFI_OFF);


      if (d0 == "sta")
      {

		WiFi.begin(newssid.c_str(), newpass.c_str());
		JJLOG.print(F("IP: "));
		JJLOG.println(WiFi.localIP());
      }
      else
      {
        WiFi.mode(WIFI_AP);
        IPAddress apIP(10, 10, 10, 1);
        IPAddress netMsk(255, 255, 255, 0);
        WiFi.softAPConfig(apIP, apIP, netMsk);

        String temp = "SmartRemote@" + objJarusAccessories.str_chipID;

        char ssidtemp[20];
        temp.toCharArray(ssidtemp, 20);
        WiFi.softAP(ssidtemp, "smartremote");


        JJLOG.print(F("AP IP : "));
        JJLOG.println(WiFi.softAPIP());
      }
    }

    //(*ptr_replyJson)["data"] = "ok";
	return 1;

}

int j_device_functionality::func_clearFlow(int x)
{
	INFO("msg");

	jobjFileOperation.jdeleteFolder("/flow");
    jobjFileOperation.jdeleteFolder("/flowN");
	return jexecutionOK;
}

int j_device_functionality::func_executeFlow(int x)
{
	//Jmutex.lock();
	INFO("msg");

	jStr flowID;
	if (x == 5) 	flowID = wasteElemt;
	else 			flowID = mydata.c_str();

	JJLOG.println("Current Flow " + String (flowID .c_str() ));


	// Future task : this is not good way
	jarusJSON temp =  objJarusAccessories.jgetJJSON(
			jobjFileOperation.jreadFile("/flow/" + flowID));
	if (temp.vjsonPair.size() == 0) {
		JJLOG.println("issue found, undefine flowID");
		func_stopFlow(0);//		stoppingFlowFunc();
	}
	if ( temp.vjsonPair["flow_light"] == "Off" )
	{
		func_lightStop(0);
	}
	else if (temp.vjsonPair["flow_light"] == "Rainbow")
	{
		int inte = String ( temp.vjsonPair["intensity"].c_str() ) .toInt()  ;
		objRGB.setIntensity( inte );
		objRGB.jRainbowStart(true);
	}
	else
	{
		objRGB.jRainbowStart(false);
		setLightColor(&(temp.vjsonPair["flow_light"]), &(temp.vjsonPair["intensity"]));
	}

	saveCurrentTime();	 //saving flow becasue nowFlow call initiate now and want to now elaped time
	savoFlowStatusToFile(0, flowID); // recent related also handler by this which is not working yet
	//Jmutex.unlock();

	return jexecutionOK;
}

int j_device_functionality::func_stopFlow(int x)
{
	INFO("msg");

	//stoppingFlowFunc();

	func_lightStop(0);
	flagForFLowExecution = false;
	jobjFileOperation.jwriteFile(objJarusAccessories.FlowTimeStoring, "jarus");
	jobjFileOperation.jwriteFile(objJarusAccessories.JcurrentFlow, "jarus");
	RTC.squareWave(SQWAVE_NONE);
	RTC.alarmInterrupt(ALARM_1, false);     //disable Alarm2


	return jexecutionOK;
}

int j_device_functionality::func_getFlow(int x)
{
	INFO("msg");

	// future task : change with deseriloier functuion
	DynamicJsonDocument  temp_doc(500);
	DeserializationError error = deserializeJson(
			temp_doc,
			jobjFileOperation.jreadFile(	String ("/flow/" + mydata).c_str()	)
		);
	if (error)
	{
	  JJLOG.print(F("deserializeJson() failed: "));
	  JJLOG.println(error.c_str());
	}
	(*ptr_replyJson)["flow_light"] = temp_doc["flow_light"];
	(*ptr_replyJson)["intensity"] = temp_doc["intensity"];
	for (int jloop = 0; true; jloop++)
	{
		String text = temp_doc["data"][jloop];
		if (text == "null") break;
		objNestedJsonToReply.push_back(text.c_str());
	}

	return jexecutionOKwithData;
}

int j_device_functionality::func_getFlows(int x)
{
	INFO("msg");

//	OperationOnfolder("/flowN", &j_device_functionality::ActionGetName);

    jStr buttonFolder = "/flowN";
	jStr toSearch = buttonFolder + "/";

	JJLOG.println("Searching for " + String (toSearch.c_str() ) );
	jsonNested listOfFiles = jobjFileOperation.jlistDir (buttonFolder, 1);
	for(auto buttonPath : listOfFiles )
	{
		if (buttonPath.find(toSearch) == 0 )
		{
			buttonPath.erase(buttonPath.find(buttonFolder), 1+ buttonFolder.length());
			objNestedJsonToReply.push_back( buttonPath  );
			JJLOG.println(buttonPath.c_str());
		}
	}

	return jexecutionOKwithData;
}

int j_device_functionality::func_nowFlow(int x){
	INFO("msg");
	//irrecv.disableIRIn();

	// replying 3 things from this file [flowID, currentActionPostion, elapedTime] first 2 get by current file, 3 third by reading and calculateing

	jarusJSON temp =  objJarusAccessories.jgetJJSON(
			jobjFileOperation.jreadFile("/JcurrentFlow") );

	// 2 added because app want absolute postion
	int FlowPosition  = 2 + atoi( temp.vjsonPair["counter"].c_str() );
	jStr currentFlowName  = temp.vjsonPair["currentFlow"];

	objNestedJsonToReply.push_back( currentFlowName );
	objNestedJsonToReply.push_back( String (FlowPosition).c_str() );

	jStr flowFileContain = jobjFileOperation.jreadFile(objJarusAccessories.FlowTimeStoring);
	if ( flowFileContain == "jarus" || flowFileContain == "")
	{
		JJLOG.println("No Flow Running Replying Zero");
		objNestedJsonToReply.push_back( "0" );
	}
	else
	{
		//JJLOG.println("does here is problem1below printing");
		temp = objJarusAccessories.jgetJJSON(	flowFileContain		);
		//objJarusAccessories.printjarusJSON(&temp );
		//JJLOG.println("does here is problem2");

		time_t currentTime;
		int elapsTime = -1;

		while ( elapsTime <= 0)
		{

			JJLOG.println("Collecting time from RTC");

			while (true)	// only jarus know what he has done here
			{

				esp_task_wdt_reset();
				vTaskDelay(10 / portTICK_PERIOD_MS);

				//JJLOG.println("does here is problem4");
				currentTime = RTC.get(); delay(200);
				if (RTC.get() == currentTime)
				{
					break;
				}
			}
			//JJLOG.println("does here is problem5");
			//currentTime = RTC.get();	delay(200);
			timeStore rtctime;

			rtctime._day  = (day(currentTime));
			rtctime._hour = (hour(currentTime));
			rtctime._min  = (minute(currentTime));
			rtctime._sec  = (second(currentTime));
			printTimeStore(rtctime);

			int diffDD = rtctime._day 	- atoi(  temp.vjsonPair["dd"].c_str() );
			int diffHH = rtctime._hour 	- atoi(  temp.vjsonPair["hh"].c_str() );;
			int diffMM = rtctime._min 	- atoi(  temp.vjsonPair["mm"].c_str() );;
			int diffSS = rtctime._sec 	- atoi(  temp.vjsonPair["ss"].c_str() );;

			elapsTime =
					diffDD * 60*60*24	+
					diffHH * 60*60		+
					diffMM * 60			+
					diffSS * 1			;

			JJLOG.println("Elapsed time\t: "+ String (elapsTime) + " Sec");

//			JJLOG.print("Saved RTC Time\t: ");
//			JJLOG.print(temp.vjsonPair["dd"].c_str()); 	JJLOG.print( " " );
//			JJLOG.print(temp.vjsonPair["hh"].c_str());	JJLOG.print( ":" );
//			JJLOG.print(temp.vjsonPair["mm"].c_str());	JJLOG.print( ":" );
//			JJLOG.print(temp.vjsonPair["ss"].c_str());	JJLOG.println( );

			JJLOG.print ("Diff Time\t: ");
			JJLOG.print(diffDD); 	JJLOG.print( " " );
			JJLOG.print(diffHH);	JJLOG.print( ":" );
			JJLOG.print(diffMM);	JJLOG.print( ":" );
			JJLOG.print(diffSS);	JJLOG.println( );

		}


		objNestedJsonToReply.push_back( String (elapsTime).c_str() );
	}

	//irrecv.enableIRIn();
	return jexecutionOKwithData;
}
int j_device_functionality::func_removeFlow(int x)
{
	INFO("msg");

	jStr buttonFolder = "/flowN";
	jStr buttonID = mydata.c_str();

	jobjFileOperation.jdeleteFile( "/flow/" + buttonID );

	jStr toSearch =
		buttonFolder +
		"/" +
		buttonID  +
		",";

	JJLOG.println("Searching for " + String (toSearch.c_str() ) );
	jsonNested listOfFiles = jobjFileOperation.jlistDir (buttonFolder, 1);
	for(auto buttonPath : listOfFiles )
	{
		if (buttonPath.find(toSearch) == 0 )
			jobjFileOperation.jdeleteFile(buttonPath);
	}

    return jexecutionOK;
}
int j_device_functionality::func_removeFlows(int x)
{
	INFO("msg");

	// future task you could replce this with that common list serch delete method
	for (int jloop = 0; true; jloop++)
	{
	    String myStr = (*ptr_receivedJson)["data"][jloop].as<const char*>();
	    if (myStr == "") break;
	    jobjFileOperation.jdeleteFile(	String ("/flow/" + myStr).c_str()	);

		jarusUnion tempUnion {"jarus", myStr.c_str()};
		JUOperationOnfolder(
				"/flowN",											// folder name
				&tempUnion ,					// temp vari, str if match delete
				&j_device_functionality::UActionDeleteSpecificFile	// action name
		);
	}

	return jexecutionOK;
}
int j_device_functionality::func_updateFlow(int x)
{

	INFO("msg");
    JJLOG.println("Edit flow");

    jStr buttonFolder = "/flowN";
	jStr buttonID = d0.c_str();
	jStr buttonName = d2.c_str();

	jStr toSearch =
		buttonFolder +
		"/" +
		buttonID  +
		",";

	JJLOG.println("Searching for " + String (toSearch.c_str() ) );
	jsonNested listOfFiles = jobjFileOperation.jlistDir (buttonFolder, 1);
	for(auto buttonPath : listOfFiles )
	{
		if (buttonPath.find(toSearch) == 0 )
			jobjFileOperation.jdeleteFile(buttonPath);
	}

    jobjFileOperation.jwriteFile (
    		"/flowN/" + buttonID + "," + buttonName,
    		"jarus");

    jobjFileOperation.jwriteFile (
    		"/flow/" + buttonID,
			_str_receivedJson);

	return jexecutionOK;
}


void j_device_functionality::eraseSubStr(std::string & mainStr, const std::string & toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);

	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}

int j_device_functionality::func_getIRs(int x)
{
	INFO("msg");

	jStr buttonFolder = "/butN";
	jsonNested listOfFiles = jobjFileOperation.jlistDir (buttonFolder, 1);

	JJLOG.println("adding to list");
	for(auto buttonPath : listOfFiles )
	{
		buttonPath.erase(buttonPath.find(buttonFolder), 1+ buttonFolder.length());
		objNestedJsonToReply.push_back(	buttonPath );

		JJLOG.println(buttonPath.c_str());
	}
	JJLOG.println("list over");
	return jexecutionOKwithData;

}
int j_device_functionality::ActionGetName(jStr subFile)
{
	INFO("msg");
	// future modification needed (1 data same name can problem, remove use of below string)
	String someText1 = subFile.c_str();
	//subFile.find_last_of("/");
	someText1.remove(0, 1+subFile.find_last_of("/"));

	objNestedJsonToReply.push_back(someText1.c_str());

	JJLOG.println(someText1);
	return 1;

}
int j_device_functionality::ActionDeleteAll(jStr subFile)
{

	INFO("msg");
	jobjFileOperation.jdeleteFile(subFile);
	return 1;
}

int j_device_functionality::ActionDeleteSpecificFile(jStr subFile)
{
	JJLOG.print("searching for contain");
	JJLOG.println(mydata.c_str());

	if (subFile.find(mydata.c_str()) > 0)
	{
		  JJLOG.print("file found");
		  JJLOG.println(subFile.c_str());
		  jobjFileOperation.jdeleteFile(subFile);
		  return 0;
	}
	return 1;
}

//
//int j_device_functionality::UActionRenameSpecificFile(jarusUnion myUnion)
//{
//	//int some = myUnion.soneFunNum;
////	JJLOG.print("searching for contain");
////	JJLOG.println(mydata.c_str());
////
////	if (subFile.find(mydata.c_str()) > 0)
////	{
////		  JJLOG.print("file found");
////		  JJLOG.println(subFile.c_str());
////		  jobjFileOperation.jdeleteFile(subFile);
////		  return 0;
////	}
//	return 1;
//}



int j_device_functionality::func_removeIR(int x)
{
	INFO("msg");
	jStr buttonFolder = "/butN";
	jStr buttonID = mydata.c_str();

	jobjFileOperation.jdeleteFile( "/but/" + buttonID );

	jStr toSearch =
		buttonFolder +
		"/" +
		buttonID  +
		",";

	JJLOG.println("Searching for " + String (toSearch.c_str() ) );
	jsonNested listOfFiles = jobjFileOperation.jlistDir (buttonFolder, 1);
	for(auto buttonPath : listOfFiles )
	{
		if (buttonPath.find(toSearch) == 0 )
			jobjFileOperation.jdeleteFile(buttonPath);
	}
	return jexecutionOK;
}

int j_device_functionality::func_saveIR(int x)
{
	INFO("msg");
	JJLOG.println("update button");

	IRContainer collectedIRvector = objJirTransceiver.getIRData();
	//objJirTransceiver.printIRvectorData(&collectedIRvector);

	jobjFileOperation.jsaveVectorToFile(
			String ("/but/" + d0).c_str(), 	//d0 = buttonId
			&collectedIRvector
		);
	jobjFileOperation.jwriteFile(String ("/butN/" + d0 + "," + d1) .c_str(), // d1 buttonName
			"jarus"
		);

    return jexecutionOK;
}



int j_device_functionality::ActionRenameSpecificFile(jStr subFile){
	INFO("msg");
	JJLOG.println("Searching for contain " + String (d0.c_str()));
	JJLOG.println("rename to " + String (d1.c_str()));

	jStr someRando = d0.c_str();
	if (subFile.find(someRando) > 0)
	{
		JJLOG.println("d0 and subfile");
		JJLOG.println(d0);
		JJLOG.println(subFile.c_str());

		// future modificaiton use jrenameFile file operation bye
		JJLOG.println("file Founded, deleting then creating with new name");
		//jobjFileOperation.jrenameFile()
		jobjFileOperation.jdeleteFile(subFile);
		jobjFileOperation.jwriteFile(String ("/butN/" + d0 + "," + d1).c_str(), // d1 buttonName
				"jarus"
				);
		return 0;
	}
	return 1;

}
int j_device_functionality::func_updateIR(int x)
{
	INFO("msg");
    JJLOG.println("renaming button");

	jStr buttonFolder = "/butN";

	jStr buttonID = d0.c_str();
	jStr renameTo = d1.c_str();

	jStr toSearch =
		buttonFolder +
		"/" +
		buttonID  +
		",";

	jStr newName =
			toSearch +
			renameTo ;

	JJLOG.println("Searching for contain " + String (toSearch.c_str()) );
	JJLOG.println("Renaming to " + String (newName.c_str()) );

	jsonNested listOfFiles = jobjFileOperation.jlistDir (buttonFolder, 1);
	for(auto buttonPath : listOfFiles )
	{
		JJLOG.println(buttonPath.c_str());
		JJLOG.println(toSearch.c_str());
		JJLOG.println(buttonPath.find(toSearch));

		if (buttonPath.find(toSearch) == 0 )
		{
			JJLOG.println("match found : " + String (buttonPath .c_str() ));

			jobjFileOperation.jrenameFile (
					buttonPath,
					newName
				);

		    break;
		}

	}
	return jexecutionOK;
}

int j_device_functionality::func_getStatus (int x){
	INFO("msg");			// esp8266 also reply nothing future
	return jexecutionOK;
}

int j_device_functionality::func_resetDevice (int x){
	INFO("msg");
    JJLOG.println("\n\nWait while formatting...");
    jobjFileOperation.jformat();

	return jexecutionOK;
}

int j_device_functionality::func_restartDevice (int x){
	INFO("msg");
	JJLOG.println("Restarting...");
    String msg = "";
    JJLOG.println("need to think later");
    serializeJson(	*ptr_replyJson, msg);

    ESP.restart();
	return 1;

}

int j_device_functionality::func_saveFavorite (int x){
	INFO("msg");
    JJLOG.println("Button Added");

    jStr favoPos = d0.c_str();
    jStr BuFaID  = d1.c_str();

    jStr str = jobjFileOperation.jreadFile(favoFile);
    jarusJSON somePai = objJarusAccessories.jgetJJSON(str);

    somePai.vjsonPair[favoPos] = BuFaID;

	jobjFileOperation.jwriteFile (favoFile,
			objJarusAccessories.func_getJson_str(&somePai.vjsonPair).c_str());

    return jexecutionOK;

}

int j_device_functionality::func_executeFavorite (int x){
	INFO("msg");
	//Jmutex.lock();

	jStr favPos = mydata.c_str();

    jarusJSON somePai = objJarusAccessories.jgetJJSON(
    		jobjFileOperation.jreadFile(favoFile));

	for(auto lfavoPos : somePai.vjsonPair )
	{
		if (lfavoPos.first == favPos)
		{
			jStr actionId = lfavoPos.second;
			JJLOG.println("Favourite match found: " + String (actionId.c_str()));
			if (actionId.at(0) == 'f') {
				JJLOG.println("log1");
				saveCurrentTime();
				JJLOG.println("log2");
				wasteElemt = actionId;
				JJLOG.println("log3" + String (wasteElemt .c_str()));
				JJLOG.println("log4");
				//JJLOG.println("From Favorite:calling function:actionId " + mydata);
				func_executeFlow(5);		// handler by same funciton
			}
			else if (actionId.at(0) == 'b') {
				mydata = String (actionId.c_str() );
				JJLOG.println("From Favorite:calling function:actionId " + mydata);
				func_executeIR(0);
			}

			break;
		}
	}
	//Jmutex.unlock();
	return jexecutionOK;

}

int j_device_functionality::func_removeFavorite (int x){
	INFO("msg");


	JJLOG.println("DONT know HOw to delete from app UI");

	jStr favPos = mydata.c_str();
	//int pos = 0;
	jStr str = jobjFileOperation.jreadFile(favoFile);
    jarusJSON somePai = objJarusAccessories.jgetJJSON(str);

    somePai.vjsonPair.erase(favPos );
	jobjFileOperation.jwriteFile (favoFile,
			objJarusAccessories.func_getJson_str(&somePai.vjsonPair).c_str());




	return jexecutionOK;
}

int j_device_functionality::func_getFavorite (int x){

	INFO("msg");

	JJLOG.println("dont know what to do : func_getFavorites is there alredy");

	return jexecutionOKwithData;
}

int j_device_functionality::func_clearFavorite (int x)
{
	INFO("msg");
	jobjFileOperation.jdeleteFile( favoFile	);
    return jexecutionOK;
}

int j_device_functionality::func_getFavorites (int x)
{
	INFO("msg");

	jarusJSON somePai = objJarusAccessories.jgetJJSON(
			jobjFileOperation.jreadFile(favoFile));

	for (auto p : somePai.vjsonPair) {
		objNestedJsonToReply.push_back (p.first);
		objNestedJsonToReply.push_back (p.second);
	}

    return jexecutionOKwithData;
}

int j_device_functionality::func_setNickname(int x)
{
	INFO("msg");

	jsonPair saveDeviceInfo;
	saveDeviceInfo["mdnsName"] = "SmartRemote@" + objJarusAccessories.sstr_chipID;
	saveDeviceInfo["supportedAuth"] = "[0,1,2]";;
	saveDeviceInfo["deviceVersion"] = objJarusAccessories.jhardwareVer;
	saveDeviceInfo["firmwareVersion"] = objJarusAccessories.jfirmwareVer;
	saveDeviceInfo["nickName"] = mydata.c_str();

	jobjFileOperation.jwriteFile ("/information",
			objJarusAccessories.func_getJson_str(&saveDeviceInfo).c_str());

	return jexecutionOK;

}

int j_device_functionality::func_defaultLight(int x)
{
	INFO("msg");
	jStr intensity = d1.c_str();
	jStr rgbColor  = d0.c_str();

	//func_lightStop(0);
	objRGB.jRainbowStart(false);

	JJLOG.print("intensity:rgbColor>");
	JJLOG.print(intensity .c_str());JJLOG.print (" ");
	JJLOG.println(rgbColor .c_str());

	setLightColor(&rgbColor, &intensity);
	return jexecutionOK;
}

void j_device_functionality::setLightColor(jStr *rgbColor, jStr * intensity)
{
	//objRGB.jRainbowStart(false);

	std::vector<int> rgvVec;  //rgvVec.resize(3);
	std::stringstream strStream(*rgbColor);

	for (int i; strStream >> i;) {
		rgvVec.push_back(i);
		if (strStream.peek() == ',')
			strStream.ignore();
	}

	JJLOG.println("RGB printhing");
	for (std::size_t i = 0; i < rgvVec.size(); i++)
		JJLOG.println(rgvVec[i]);
	JJLOG.println("printhing end");

	rgbVal rgb = {
				(uint8_t)rgvVec[0],
				(uint8_t)rgvVec[1],
				(uint8_t)rgvVec[2]
		};


	int inte = String (intensity->c_str()).toInt();
	objRGB.ws2812_setColors(2, &rgb,  inte);

}

void j_device_functionality::setLightColor(int x, int y, int z)
{
//	jjjRGB->stop();
//	jjjRGB->setMode(FX_MODE_STATIC);
//	jjjRGB->setColor(
//			x,
//			y,
//			z);
//	jjjRGB->show();
//	jjjRGB->start();
//	jjjRGB->service();

}

int j_device_functionality::func_lightStop(int x)
{

	INFO("msg");

	objRGB.jRainbowStart(false);
	rgbVal rgb = {0,0,0};
	objRGB.ws2812_setColors(2, &rgb, 0);

	return jexecutionOK;

}


void j_device_functionality::rgbCallBack()
{

	//if (RGBFLAg ){jjjRGB ->service(); // problem see it later
	//JJLOG.println("ok this is calling ");}
}

int j_device_functionality::func_getBackup(int x)
{
	INFO("msg");
    JJLOG.println("Sending Backup file...");
/*    dmode.detach();       // Daily mode
    rmode.detach();       // Random mode
    tmode.detach();       // Temp mode
    sec.detach();
    String temp =     "";
    String filename = "/but/" + mydata;
    if (SPIFFS.exists(filename)) {
      temp = readline(filename);
    }
    webSocket.broadcastTXT(temp);
*/
    //(*ptr_replyJson)["data"] = "ok";
	return 1;

}
int j_device_functionality::func_restoreBackup(int x)
{
	INFO("msg");
    JJLOG.println("Restoring...");
/*    restore_flag = 1;
    dmode.detach();       // Daily mode
    rmode.detach();       // Random mode
    tmode.detach();       // Temp mode
    sec.detach();
    buttonId = d0;
    buttonName = d1;
*/
    //(*ptr_replyJson)["data"] = "ok";
	return 1;

}

int j_device_functionality::func_saveFlow(int x)
{
	INFO("msg");
	jStr folderName = "/flow/";
	jStr flowID 	= d0.c_str();
	jStr flowName 	= d2.c_str();

    jobjFileOperation.jwriteFile(
    		folderName + flowID,
			_str_receivedJson.c_str()
			);
    jobjFileOperation.jwriteFile(
    		"/flowN/" + flowID + "," + flowName,
    		"jarus"
		);
    return jexecutionOK;
}

int j_device_functionality::func_clearIR(int x)
{
	INFO("msg");
	jobjFileOperation.jdeleteFolder("/but");
	jobjFileOperation.jdeleteFolder("/butN");
	return jexecutionOK;
}

int j_device_functionality::func_executeIR(int x)
{
	INFO("msg");

	jStr buttonID = mydata.c_str();

	JJLOG.println("Transmit button" + String (buttonID.c_str()) );
	IRContainer irData = jobjFileOperation.jgetVectorFromFile	(
			"/but/" + buttonID );
	objJirTransceiver.SendIRFromIRContainer(&irData);

	return jexecutionOK;
}

int j_device_functionality::func_getSSID(int x)
{
	INFO("msg");


	jarusJSON temp = objJarusAccessories.jgetJJSON(
			jobjFileOperation.jreadFile(objJarusAccessories.fileConfig));

	objJarusAccessories.printjarusJSON(&temp);


	if (temp.vjsonNested.size() > 0)
	{
		objNestedJsonToReply.push_back(temp.vjsonNested[0]);
		objNestedJsonToReply.push_back(temp.vjsonNested[1]);
	}

	return jexecutionOKwithData;

}



void j_device_functionality::savoFlowStatusToFile(int count, jStr flowID)
{
	INFO("msg");

	jsonPair tempJsonPair;
	tempJsonPair["currentFlow"]  = flowID;
	tempJsonPair["counter"]      = String (count).c_str();
	jobjFileOperation.jwriteFile(
			objJarusAccessories.JcurrentFlow,
			objJarusAccessories.getJsonStr(&tempJsonPair)
	  );

	if (count == 0)
	{

		JJLOG.println ("This is new Flow:Writing to File");
		//JJLOG.println ("Their is problem if nested flow is given");

		// give somekind of parralar access protection later
		jarusJSON temp = objJarusAccessories.jgetJJSON(
				jobjFileOperation.jreadFile(objJarusAccessories.recentFlow));

		bool doesItSameFlow = (flowID  == temp.vjsonPair["rece3"]) ? true : false;
		if ( doesItSameFlow )
		{
			JJLOG.println("Same flow executing again, no change in recent file");
		}
		else
		{




//			if ( temp.vjsonPair["flow_light"] == "Off" )
//			{
//				func_lightStop(0);
//				JJLOG.println("Flow Light Stop");
//			}
//			else if (temp.vjsonPair["flow_light"] == "Rainbow")
//			{
//				int inte = String ( temp.vjsonPair["intensity"].c_str() ) .toInt()  ;
//				objRGB.setIntensity( inte );
//				objRGB.jRainbowStart(true);
//				JJLOG.println("Flow Rainbow Start");
//			}
//			else
//			{
//				objRGB.jRainbowStart(false);
//				setLightColor(&(temp.vjsonPair["flow_light"]), &(temp.vjsonPair["intensity"]));
//				JJLOG.println("Flow Light Stop");
//			}



			JJLOG.println( "This is different flow changing sequnce" );

			jsonPair tempPair;
			tempPair["rece1"] =	temp.vjsonPair["rece2"];
			tempPair["rece2"] =	temp.vjsonPair["rece3"];
			tempPair["rece3"] = flowID;

			jobjFileOperation.jwriteFile(
					objJarusAccessories.recentFlow,
					objJarusAccessories.getJsonStr(&tempPair)
				);

		}
		flagForFLowExecution = true; // bad way : future task : make a funcion call here make it independented
	}

}

void j_device_functionality::setAlarmAfterSec(jStr seconds)
{

//	JJLOG.println("time default setting for 10 second count down started");
//	seconds = "10";



	// default values
	RTC.setAlarm(ALM1_MATCH_DATE, 0, 0, 0, 1);
	RTC.setAlarm(ALM2_MATCH_DATE, 0, 0, 0, 1);
	RTC.alarm(ALARM_1);
	RTC.alarm(ALARM_2);
	RTC.alarmInterrupt(ALARM_1, false);
	RTC.alarmInterrupt(ALARM_2, false);
	RTC.squareWave(SQWAVE_NONE);		    //RTC.set(compileTime());


	if (seconds == "-1")
	{
		JJLOG.println("RTC Alarm Setting after " + String (seconds.c_str() ) + " Second" );
	}



	//RTC.alarmInterrupt(ALARM_1, true);

	time_t _currentTime;
	while (true)	// only jarus know what he has done here
	{
		_currentTime = RTC.get(); delay(300);
		if (RTC.get() == _currentTime)
		{
			break;
		}
	}
	saveCurrentTime(_currentTime);	 //saving flow becasue nowFlow call initiate now and want to now elaped time


	timeStore alarmDelay = ConvertSectoDay(String ( seconds.c_str() ).toInt());	//setTime(int hr,int min,int sec,int dy, int mnth, int yr);

	// future make alarm for days, weeks, months
	timeStore tempAlarmTime;
	tempAlarmTime._day		= /*HERE COMES XX	*/  + day		(_currentTime);
	tempAlarmTime._sec		=	alarmDelay._sec		+ second	(_currentTime);
	tempAlarmTime._min		=	alarmDelay._min		+ minute	(_currentTime) + (tempAlarmTime._sec/60);
	tempAlarmTime._hour		=	alarmDelay._hour	+ hour		(_currentTime) + (tempAlarmTime._min/60);
	tempAlarmTime._min		%= 60;
	tempAlarmTime._sec 		%= 60;


	JJLOG.print ("Alarm Time DDHHMMSS : ");

	JJLOG.print (tempAlarmTime._day);	JJLOG.print (" ");
	JJLOG.print (tempAlarmTime._hour);	JJLOG.print (":");
	JJLOG.print (tempAlarmTime._min);	JJLOG.print (":");
	JJLOG.print (tempAlarmTime._sec);	JJLOG.println();

	RTC.setAlarm(
		ALM1_MATCH_DATE,		// type of alarm future : can be improve this but chale bhai nasa mate thodik chee
		tempAlarmTime._sec,
		tempAlarmTime._min,
		tempAlarmTime._hour,
		tempAlarmTime._day
	);

	RTC.alarmInterrupt(ALARM_1, true);
	delay(100);
}


// wasted 3-4 hour to make a recursive funtion esp32 doesnt have enhoufgh call stack so doent work : done waste anext time
// probabaly other reason , file reading with mutex lock didnt check
void j_device_functionality::funcScheduleHandler()
{
	INFO("msg");

	for (int jloop = 0; true; jloop++)
	{
		JJLOG.println("Loop Counter\t: " + String (jloop) );
		jarusJSON temp =  objJarusAccessories.jgetJJSON(
				jobjFileOperation.jreadFile("/JcurrentFlow"));

		if (temp.vjsonPair.size() == 0) {func_stopFlow(0); break;}

		int jcounter = atoi( temp.vjsonPair["counter"].c_str() );
		jStr currentFlowStr = temp.vjsonPair["currentFlow"];

		temp =  objJarusAccessories.jgetJJSON(
				jobjFileOperation.jreadFile("/flow/" + currentFlowStr));

		if (temp.vjsonPair.size() == 0) {func_stopFlow(0); break;}









		// this indicates last element in flow [here some tricky thing, vector size is normal count but jcounter is programmer count]
		if ( temp.vjsonNested.size() == 3 + jcounter )
		{
		  int repateOrNOT =  String ( temp.vjsonNested[1].c_str() ).toInt();
		  if (1 == repateOrNOT)
		  {
			  JJLOG.println("Repeatable Flow : Same Flow starting again");
			  //func_stopFlow(0);
			  savoFlowStatusToFile(0, currentFlowStr );


			  // NEED TO DECSCUSS THIS SECSTION

				if ( temp.vjsonPair["flow_light"] == "Off" )
				{
					func_lightStop(0);
					JJLOG.println("Flow Light Stop");
				}
				else if (temp.vjsonPair["flow_light"] == "Rainbow")
				{
					int inte = String ( temp.vjsonPair["intensity"].c_str() ) .toInt()  ;
					objRGB.setIntensity( inte );
					objRGB.jRainbowStart(true);
					JJLOG.println("Flow Rainbow Start");
				}
				else
				{
					objRGB.jRainbowStart(false);
					setLightColor(&(temp.vjsonPair["flow_light"]), &(temp.vjsonPair["intensity"]));
					JJLOG.println("Flow Light Stop");
				}


		  }
		  else
		  {

			  JJLOG.println("Not Repeatable Flow : Ending Scheduled");
			  func_stopFlow(0); 	//stoppingFlowFunc();

		  }
		  break;
		}

		jStr currentFlowActionID = temp.vjsonNested[3 + jcounter];
		JJLOG.println("currentFlowActionID >>>>>>>>>>>>>>>>>"+ String (currentFlowActionID.c_str()));











	  if (currentFlowActionID.at(0)  == 'b' )
	  {
		JJLOG.println("transmitting button From action");
		IRContainer irData = jobjFileOperation.jgetVectorFromFile	(
				"/but/" + currentFlowActionID);

		objJirTransceiver.SendIRFromIRContainer(&irData);

		savoFlowStatusToFile( jcounter + 1, currentFlowStr );
		continue;

	  }
	  else if ( currentFlowActionID.at(0) == 'f' )
		{
			if (currentFlowActionID == "flow")
			{
				savoFlowStatusToFile(jcounter + 1, currentFlowStr);
				JJLOG.println("waste thing done here modify its later");
				continue;
			}
			else
			{
				JJLOG.println("nested saving attaching second flow");
				savoFlowStatusToFile(0, currentFlowActionID);




				// NEED TO DECSCUSS THIS SECSTION
				if ( temp.vjsonPair["flow_light"] == "Off" )
				{
					func_lightStop(0);
					JJLOG.println("Flow Light Stop");
				}
				else if (temp.vjsonPair["flow_light"] == "Rainbow")
				{
					int inte = String ( temp.vjsonPair["intensity"].c_str() ) .toInt()  ;
					objRGB.setIntensity( inte );
					objRGB.jRainbowStart(true);
					JJLOG.println("Flow Rainbow Start");
				}
				else
				{
					objRGB.jRainbowStart(false);
					setLightColor(&(temp.vjsonPair["flow_light"]), &(temp.vjsonPair["intensity"]));
					JJLOG.println("Flow Light Stop");
				}


				break;
			}
		}
	  else if (	 String ( currentFlowActionID.c_str() ).toInt()  )		// this is alarm
	  {
		savoFlowStatusToFile(jcounter + 1, currentFlowStr);
		setAlarmAfterSec(currentFlowActionID);
		break;
	  }
	  else
	  {
		JJLOG.println("Schedule finished");
		func_stopFlow(0); //stoppingFlowFunc();

		break;
	  }
	}
}



timeStore j_device_functionality::ConvertSectoDay(long n)
{
	INFO("msg");
	timeStore timeVari;
	timeVari._day = n / (24 * 3600);
	n = fmodl(n, (24 * 3600));	timeVari._hour = n / 3600;
	n = fmodl(n, 3600);			timeVari._min = n / 60 ;
	n = fmodl(n, 60);			timeVari._sec = n;
    return timeVari;
}

void j_device_functionality::saveCurrentTime(time_t _currentTime )
{
	INFO("msg");
	//time_t _currentTime;
	if (_currentTime == 0)
	{
		while (true)	// only jarus know what he has done here
		{
			_currentTime = RTC.get(); delay(200);
			if (RTC.get() == _currentTime)	break;
		}
	}
	jsonPair timeJsonPair;
	timeJsonPair["dd"] = String (day(_currentTime))		.c_str();
	timeJsonPair["hh"] = String (hour(_currentTime))	.c_str();
	timeJsonPair["mm"] = String (minute(_currentTime))	.c_str();
	timeJsonPair["ss"] = String (second(_currentTime))	.c_str();

	jobjFileOperation.jwriteFile(
			objJarusAccessories.FlowTimeStoring,
			objJarusAccessories.getJsonStr(&timeJsonPair)
		);
}
void j_device_functionality::printTimeStore(timeStore timeVari)
{
	JJLOG.print ("RTC Time DDHHMMSS:");
	JJLOG.print(String (timeVari._day)); 	JJLOG.print( " " );
	JJLOG.print(String (timeVari._hour));	JJLOG.print( ":" );
	JJLOG.print(String (timeVari._min));	JJLOG.print( ":" );
	JJLOG.print(String (timeVari._sec));	JJLOG.println( );
}


void j_device_functionality::printDateTime(time_t t)
{
	JJLOG.print ("current time\t: ");
    JJLOG << ((day(t)<10) ? "0" : "") << _DEC(day(t));
    JJLOG << monthShortStr(month(t)) << _DEC(year(t)) << ' ';
    JJLOG << ((hour(t)<10) ? "0" : "") << _DEC(hour(t)) << ':';
    JJLOG << ((minute(t)<10) ? "0" : "") << _DEC(minute(t)) << ':';
    JJLOG << ((second(t)<10) ? "0" : "") << _DEC(second(t));
    JJLOG.println();
}

// function to return the compile date and time as a time_t value
time_t j_device_functionality::compileTime()
{
    const time_t FUDGE(10);    //fudge factor to allow for upload time, etc. (seconds, YMMV)
    const char *compDate = __DATE__, *compTime = __TIME__, *months = "JanFebMarAprMayJunJulAugSepOctNovDec";
    char compMon[3], *m;

    strncpy(compMon, compDate, 3);
    compMon[3] = '\0';
    m = strstr(months, compMon);

    tmElements_t tm;
    tm.Month = ((m - months) / 3 + 1);
    tm.Day = atoi(compDate + 4);
    tm.Year = atoi(compDate + 7) - 1970;
    tm.Hour = atoi(compTime);
    tm.Minute = atoi(compTime + 3);
    tm.Second = atoi(compTime + 6);

    time_t t = makeTime(tm);
    return t + FUDGE;        //add fudge factor to allow for compile time
}
