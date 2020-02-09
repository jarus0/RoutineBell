/*
 * WebserverHandler.h
 *
 *  Created on: 07-Jan-2020
 *      Author: suraj
 */

#ifndef MAIN_WEBSERVERHANDLER_H_
#define MAIN_WEBSERVERHANDLER_H_

#include <Arduino.h>
#include <esp_wifi.h>
#include <esp_event_loop.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>

#include <esp_http_server.h>

#include <stdlib.h>
#include "jglobal.h"

//#include "JWebSocketsServer.h"
//extern JWebSocketsServer obj_JWebSocketsServer;
//JWebSocketsServer obj_JWebSocketsServer;




//websocket headers



static const char *TAG="APP";


class WebserverHandler {
public:
	WebserverHandler();
	virtual ~WebserverHandler();



	// lots of use of static keyword is not good idea, future task : https://isocpp.org/wiki/faq/pointers-to-members
	// event handler is static function that why all need
	static int randomArray[4];
	//static int _num;

	struct queryInfo
	{
		jStr methodType;
		jStr code;
		jStr hardwareID;
		jStr timeStamp;
		jStr token;
		int userID;
	};
	enum replyFlag
	{

		argumentError = 0,
		ExistingUser = 1,
		OverLoadUser = 2,
		CodeIncorrect = 3	// code is incorrect
	};

	static httpd_handle_t start_webserver(void);
	static void stop_webserver(httpd_handle_t server);

	static esp_err_t handlergba_post_handler(httpd_req_t *req);
	static esp_err_t handlergbb_post_handler(httpd_req_t *req);
	static esp_err_t handlergbc_post_handler(httpd_req_t *req);
	static esp_err_t handlergbd_post_handler(httpd_req_t *req);

	static esp_err_t handleinfo_post_handler(httpd_req_t *req);
	static esp_err_t getRang_post_handler(httpd_req_t *req);
	static esp_err_t handleArgs_post_handler(httpd_req_t *req);

	static void vLightColor(int num);
	static void saveInfoToFile(queryInfo *temp_queryInfo);


//	static void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
//	static void websocketLoop (void *pvParameter);

};

#endif /* MAIN_WEBSERVERHANDLER_H_ */
