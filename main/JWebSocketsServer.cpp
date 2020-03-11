/*
 * JWebSocketsServer.cpp
 *
 *  Created on: 16-Jan-2020
 *      Author: suraj
 */

#include "JWebSocketsServer.h"

JWebSocketsServer::JWebSocketsServer() {
	// TODO Auto-generated constructor stub
	JJLOG.println("JWebSocketsServer constructor");
	//jwebsocketFlag = false;
}

JWebSocketsServer::~JWebSocketsServer() {
	// TODO Auto-generated destructor stub
}

//
//j_device_functionality* JWebSocketsServer::functionalityInstance()
//{
//	return &objJdeviceFunctionality;
//}

void JWebSocketsServer::jwebSocketInit()
{
	JJLOG.println("jwebSocketInit");
	static const char * headerkeys[] = { "cookie" };
	static size_t headerKeyCount = sizeof(headerkeys) / sizeof(char*);
	JwebSocket.onValidateHttpHeader(validateHttpHeader, headerkeys, headerKeyCount);
	JwebSocket.begin();
	JwebSocket.onEvent(jwebSocketEvent);
}

void JWebSocketsServer::jwebSocketLoop()
{
	JwebSocket.loop();
}


void JWebSocketsServer::jwebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
	//JJLOG.println("jwebSocketEvent happen");
	//INFO("Socket Event");
    switch(type) {
        case WStype_DISCONNECTED:
        {
            JJLOG.printf("[%u] Disconnected!\n", num);
            //if (!ptr_j_device_functionality)	ptr_j_device_functionality = NULL;
            break;
        }
        case WStype_CONNECTED:
		{


			IPAddress ip = JwebSocket.remoteIP(num);
			JJLOG.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
			objJdeviceFunctionality.test_function();

			JJLOG.printf("%s", payload);
			JJLOG.println();
			replyDeviceInfo(&num);
			//JJLOG.println( "FreeHeap:- " + String (ESP.getFreeHeap())	);

		}
		break;
        case WStype_TEXT:
        {

            irrecv.disableIRIn();


        	String collectedJsonFromWebSocket = String((char*)payload);
			JJLOG.println("App\t: "+	collectedJsonFromWebSocket);
			cmdFromWebSocket = collectedJsonFromWebSocket.c_str();
			String send2App =  objJdeviceFunctionality.jsonDE(collectedJsonFromWebSocket.c_str());

			//INFO(send2App.c_str());
			JJLOG.println("send2App\t: "  + String (send2App.c_str()) );
			webSocketReplyToAPP(&num, send2App);
			irrecv.enableIRIn();



            break;
        }
        case WStype_BIN:
        {
            JJLOG.printf("[%u] get binary length: %u\n", num, length);
            hexdump(payload, length);

            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
           }
		case WStype_ERROR:{break;}
		case WStype_FRAGMENT_TEXT_START:{break;}
		case WStype_FRAGMENT_BIN_START:{break;}
		case WStype_FRAGMENT:{break;}
		case WStype_FRAGMENT_FIN:{break;}
		case WStype_PING:{break;}
		case WStype_PONG:{break;}
			break;
    }

}


void JWebSocketsServer::hexdump(const void *mem, uint32_t len, uint8_t cols) {
	INFO("msg");
	const uint8_t* src = (const uint8_t*) mem;
	JJLOG.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t)src, len, len);
	for(uint32_t i = 0; i < len; i++) {
		if(i % cols == 0) {
			JJLOG.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t)src, i);
		}
		JJLOG.printf("%02X ", *src);
		src++;
	}
	JJLOG.printf("\n");
}

void JWebSocketsServer::replyDeviceInfo(uint8_t *_num)
{
	INFO("msg");
	jsonPair temp_json;

	temp_json["id"]			 = objJarusAccessories.sstr_chipID;
	temp_json["mDNS"] 		 = "ESP/" + objJarusAccessories.sstr_chipID;
	temp_json["supAuth"] 	 = "Light/QR/Barcode";
	temp_json["appVer"] 	 = objJarusAccessories.jappVer;
	temp_json["firmwareVer"] = objJarusAccessories.jfirmwareVer;
	temp_json["hardwareVer"] = objJarusAccessories.jhardwareVer;

	webSocketReplyToAPP(_num, objJarusAccessories.func_getJson_str(&temp_json));

}

void JWebSocketsServer::webSocketReplyToAPP(uint8_t *tempNum, String SendText)
{
	INFO("msg");
	JwebSocket.sendTXT( *tempNum, SendText.c_str());
}



bool JWebSocketsServer::isCookieValid(String rawCookieHeaderValue)
{
	INFO("msg");

	JJLOG.println("Token\t: " + String (objJarusAccessories.currentUserToken.c_str()));

  if (rawCookieHeaderValue.indexOf("token") != -1) {
    String sessionIdStr = rawCookieHeaderValue.substring(rawCookieHeaderValue.indexOf("token") + 6);
    jStr someSessionIdStr =sessionIdStr.c_str();
    if (someSessionIdStr == objJarusAccessories.currentUserToken)
    {
    	return true;
    }
    else
    {
    	JJLOG.println("Token is not correct");
    	return false;
    }
    JJLOG.print("sessionIdStr :" + String (sessionIdStr.c_str()) );
  }

  return false;
}

bool JWebSocketsServer::validateHttpHeader(String headerName, String headerValue) {
  bool valid = true;
  if (headerName.equalsIgnoreCase("cookie"))
  {
    valid = isCookieValid(headerValue);
  }
  return valid;

}





