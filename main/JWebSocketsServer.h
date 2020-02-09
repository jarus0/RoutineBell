/*
 * JWebSocketsServer.h
 *
 *  Created on: 16-Jan-2020
 *      Author: suraj
 */

#ifndef MAIN_JWEBSOCKETSSERVER_H_
#define MAIN_JWEBSOCKETSSERVER_H_

#include <Arduino.h>
#include "jglobal.h"

#include "jdevicefunctionality.h"
static j_device_functionality objJdeviceFunctionality; // future : static declaration really ,change it most important


#include <WebSocketsServer.h>
static WebSocketsServer JwebSocket = WebSocketsServer(81);

class JWebSocketsServer {
public:
	JWebSocketsServer();
	virtual ~JWebSocketsServer();

	//static String collectedJsonFromWebSocket;
	static jsonPair colorMap;
	//static j_device_functionality* functionalityInstance();
	static void hexdump(const void *mem, uint32_t len, uint8_t cols = 16);

	static void jwebSocketInit();
	static void jwebSocketLoop();
	//static String replyWebSocketDeviceInfo(uint8_t *_num);
	static void replyDeviceInfo(uint8_t *_num);

	static void webSocketReplyToAPP(uint8_t *tempNum, String SendText);

private:
	static void jwebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

	static bool isCookieValid(String rawCookieHeaderValue);
	static bool validateHttpHeader(String headerName, String headerValue);


};


#endif /* MAIN_JWEBSOCKETSSERVER_H_ */
//bool JWebSocketsServer::jwebsocketFlag = false;
