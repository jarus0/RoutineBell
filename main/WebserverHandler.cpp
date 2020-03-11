/*
 * WebserverHandler.cpp
 *
 *  Created on: 07-Jan-2020
 *      Author: JARUS singh
 */

#include "WebserverHandler.h"

WebserverHandler::WebserverHandler() {
	// TODO Auto-generated constructor stub
}

WebserverHandler::~WebserverHandler() {
	// TODO Auto-generated destructor stub
}



httpd_handle_t WebserverHandler::start_webserver(void)
{
	INFO("msg");

	objJarusAccessories.generateRandom();
	JJLOG.println("Random number\t: " + String (objJarusAccessories.randNumber) );

	httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

	static httpd_uri_t handleinfo_uri = {};
	static httpd_uri_t handleColo_uri = {};
	static httpd_uri_t handleArgs_uri = {};
	static httpd_uri_t handlergba_uri = {};
	static httpd_uri_t handlergbb_uri = {};
	static httpd_uri_t handlergbc_uri = {};
	static httpd_uri_t handlergbd_uri = {};

	handleinfo_uri.uri = "/info";
	handleColo_uri.uri = "/getColors";
	handleArgs_uri.uri = "/auth";
	handlergba_uri.uri = "/viLightCode/1";
	handlergbb_uri.uri = "/viLightCode/2";
	handlergbc_uri.uri = "/viLightCode/3";
	handlergbd_uri.uri = "/viLightCode/4";

	handleinfo_uri.handler = &WebserverHandler::handleinfo_post_handler;
	handleColo_uri.handler = &WebserverHandler::getRang_post_handler;
	handleArgs_uri.handler = &WebserverHandler::handleArgs_post_handler;
	handlergba_uri.handler = &WebserverHandler::handlergba_post_handler;
	handlergbb_uri.handler = &WebserverHandler::handlergbb_post_handler;
	handlergbc_uri.handler = &WebserverHandler::handlergbc_post_handler;
	handlergbd_uri.handler = &WebserverHandler::handlergbd_post_handler;

	handleinfo_uri.method = HTTP_GET;
	handleColo_uri.method = HTTP_GET;
	handleArgs_uri.method = HTTP_GET;

	handlergba_uri.method = HTTP_GET;
	handlergbb_uri.method = HTTP_GET;
	handlergbc_uri.method = HTTP_GET;
	handlergbd_uri.method = HTTP_GET;

	handleinfo_uri.user_ctx = NULL;
	handleColo_uri.user_ctx = NULL;
	handleArgs_uri.user_ctx = NULL;
	handlergba_uri.user_ctx = NULL;
	handlergbb_uri.user_ctx = NULL;
	handlergbc_uri.user_ctx = NULL;
	handlergbd_uri.user_ctx = NULL;


    // Start the httpd server
    //ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    JJLOG.println("Starting server on port: " + String (config.server_port) );
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &handleinfo_uri);
        httpd_register_uri_handler(server, &handleArgs_uri);
        httpd_register_uri_handler(server, &handleColo_uri);


        httpd_register_uri_handler(server, &handlergba_uri);
        httpd_register_uri_handler(server, &handlergbb_uri);
        httpd_register_uri_handler(server, &handlergbc_uri);
        httpd_register_uri_handler(server, &handlergbd_uri);

        return server;
    }
    else {
    	JJLOG.println("Error starting server!");
    }
    return NULL;
}

void WebserverHandler::stop_webserver(httpd_handle_t server)
{
	INFO("msg");
	httpd_stop(server);// Stop the httpd server
}

esp_err_t WebserverHandler::handleinfo_post_handler(httpd_req_t *req)
{
	INFO("msg");
	objRGB.jRainbowStart(false);
	jStr fileContain = jobjFileOperation.jreadFile(	objJarusAccessories.fileInfo	);
	if (fileContain  == ""){
		jsonPair JdeviceInfo;

		JdeviceInfo["mdnsName"]			= "SmartRemote@" + objJarusAccessories.sstr_chipID; // str_chipID; //Put Sensor value
		JdeviceInfo["supportedAuth"] 	= "[0,1,2]";
		JdeviceInfo["deviceVersion"]	= objJarusAccessories.jhardwareVer;
		JdeviceInfo["firmwareVersion"] 	= objJarusAccessories.jfirmwareVer;
		JdeviceInfo["nickName"] 		= "";
		fileContain = objJarusAccessories.getJsonStr(&JdeviceInfo);
	}
	JJLOG.println( "Sending Info" + String (fileContain.c_str()) );
	httpd_resp_send(req, fileContain.c_str(), fileContain.size());
	return ESP_OK;
}

esp_err_t WebserverHandler::handlergba_post_handler(httpd_req_t *req){
	INFO("msg");
	vLightColor(0);
	jStr str_replyToServer = "JARUS";
	httpd_resp_send(req, str_replyToServer.c_str(), str_replyToServer.size());

	return ESP_OK;
}
esp_err_t WebserverHandler::handlergbb_post_handler(httpd_req_t *req){
	INFO("msg");
	vLightColor(1);
	jStr str_replyToServer = "JARUS";
	httpd_resp_send(req, str_replyToServer.c_str(), str_replyToServer.size());
	return ESP_OK;
}
esp_err_t WebserverHandler::handlergbc_post_handler(httpd_req_t *req){
	INFO("msg");
	vLightColor(2);
	jStr str_replyToServer = "JARUS";httpd_resp_send(req, str_replyToServer.c_str(), str_replyToServer.size());
	return ESP_OK;
}
esp_err_t WebserverHandler::handlergbd_post_handler(httpd_req_t *req){
	INFO("msg");
	vLightColor(3);
	jStr str_replyToServer = "JARUS";httpd_resp_send(req, str_replyToServer.c_str(), str_replyToServer.size());
	return ESP_OK;
}

esp_err_t WebserverHandler::handleArgs_post_handler(httpd_req_t *req)
{
	INFO("msg");

	//http://10.10.10.1/auth?methodType=0&code=6038&hardwareID=88:b4:a6:2b:f0:23&timestamp=1573198983
	queryInfo _queryInfo;
	char*  buf;
    size_t buf_len;
    //JJLOG.println("ok here its got3");
    buf_len = httpd_req_get_url_query_len(req) + 1;
    if (buf_len > 1) {
        buf = (char*) malloc(buf_len);
        if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
        	JJLOG.println("Found URL query =>" + String (buf) );
            char param[32];
            /* Get value of expected key from query string */
            if (httpd_query_key_value(buf, "methodType",param, sizeof(param)) == ESP_OK) 	{	_queryInfo.methodType = param; }
            if (httpd_query_key_value(buf, "code", 		param, sizeof(param)) == ESP_OK)	{	_queryInfo.code = param; }
            if (httpd_query_key_value(buf, "hardwareID",param, sizeof(param)) == ESP_OK) 	{	_queryInfo.hardwareID = param; }
            if (httpd_query_key_value(buf, "timeStamp", param, sizeof(param)) == ESP_OK)	{	_queryInfo.timeStamp = param; }
        }
        free(buf);
    }

    JJLOG.println("ok here its got4");

    objJarusAccessories.jprint("method\t: "		+ _queryInfo.methodType);
    objJarusAccessories.jprint("code\t: " 		+ _queryInfo.code);
    objJarusAccessories.jprint("hardwareID\t: " + _queryInfo.hardwareID);
    objJarusAccessories.jprint("timeStamp\t: " 	+ _queryInfo.timeStamp);
    objJarusAccessories.jprint("\n");

	jsonPair replyToServer;
	int userCount = -1;
	jStr fileContain = "";


	if (	_queryInfo.methodType 	== "" &&
			_queryInfo.code 		== "" &&
			_queryInfo.hardwareID	== "" &&
			_queryInfo.timeStamp	== ""
			)
	{
		JJLOG.println("argumentError");
		replyToServer["code"]		= String (argumentError).c_str();
		replyToServer["message"]	= "argumentError";
	}

	else if (	objJarusAccessories.randNumber == atoi( _queryInfo.code.c_str() )	)
	{
		JJLOG.println("CodeMatched");
		for (userCount = 0; userCount < 4; userCount++)
		{
			String _someUser = "/user/" + String (userCount);
			fileContain = jobjFileOperation.jreadFile(_someUser.c_str() );

			if (fileContain == "")
			{

				String strToken1 = "";
				char *letters = "abcdefghijklmnopqrstuvwxyz0123456789";
				for (int jloop = 0; jloop < 40; jloop++)
					strToken1 = strToken1 + letters [random(0, 36)];

				//static jStr strToken = objJarusAccessories.fortyRandomChar();
				jStr strToken = strToken1.c_str();
				_queryInfo.token = strToken;
				replyToServer["message"] = strToken;
				replyToServer["code"]    = "2"; //String(2).c_str();
				JJLOG.println("random String\t: " + String (strToken.c_str()) );

				if (userCount == 3) 											// 4th user
				{
					JJLOG.println("4th user saving info to user0 file");
					_queryInfo.userID = userCount;
					saveInfoToFile(&_queryInfo);
				}
				else															// new user
				{
					JJLOG.println("new user saving to file user/" + String (userCount) );
					_queryInfo.userID = String (userCount).toInt();
					saveInfoToFile(&_queryInfo);

				}
				break;
			}
			else if (_queryInfo.hardwareID == objJarusAccessories.getValueFromKey(	fileContain.c_str(), "hardwareID") )	// existing user
			{
				JJLOG.println(objJarusAccessories.getValueFromKey(	fileContain.c_str(), "hardwareID").c_str());
				replyToServer["code"] = String (ExistingUser).c_str();
				replyToServer["message"] = objJarusAccessories.getValueFromKey(	fileContain, "token");
				JJLOG.println("Existing user:- " + String (userCount));
				break;
			}
		}
		objJarusAccessories.currentUserToken = replyToServer["message"];
		JJLOG.println("user num:- " + String (userCount) ) ;

	}
	else
	{
		replyToServer["code"] = "3";
		replyToServer["message"] = "CodeIncorrect";
        JJLOG.println("Code is Incorrect");
	}

	String str_replyToServer = objJarusAccessories.func_getJson_str(&replyToServer);
	JJLOG.println("Sending to server" ) ;
	JJLOG.println(str_replyToServer ) ;

	httpd_resp_send(req, str_replyToServer.c_str(), str_replyToServer.length());
	return ESP_OK;
}

esp_err_t WebserverHandler::getRang_post_handler(httpd_req_t *req){

	objJarusAccessories.jprint("get random color func:rangPost");

	objJarusAccessories.colorMap["BLUE"] 	= "#0000FF";
	objJarusAccessories.colorMap["GREEN"] 	= "#00FF00";
	objJarusAccessories.colorMap["MAGENTA"] = "#FF00FF";
	objJarusAccessories.colorMap["ORANGE"] 	= "#FFA500";
	objJarusAccessories.colorMap["RED"] 	= "#FF0000";
	objJarusAccessories.colorMap["WHITE"] 	= "#FFFFFF";
	objJarusAccessories.colorMap["YELLOW"] 	= "#FFFF00";

	jStr str_replyToServer = objJarusAccessories.getJsonFromJP (&objJarusAccessories.colorMap);
	JJLOG.println("replyto server: -" + String (str_replyToServer.c_str()) );
	httpd_resp_send(
			req,
			str_replyToServer.c_str(),
			str_replyToServer.size()
		);

	return ESP_OK;
}

void WebserverHandler::vLightColor(int num)
{
	JJLOG.print("postion:random:color = " + String (num) + " " + String (objJarusAccessories.randomArray[num]) + " "  );
	rgbVal color;
	// future : replace with auto filing later using objJarusAccessories.colorMap
	switch (objJarusAccessories.randomArray[num])
	{
		case 1:	{color.num = 0x0000FF; JJLOG.println("BLUE");			break;}
		case 2:	{color.num = 0x00FF00; JJLOG.println("GREEN");			break;}
		case 3:	{color.num = 0xFF00FF; JJLOG.println("MAGENTA");		break;}
		case 4: {color.num = 0xFFA500; JJLOG.println("ORANGE"); 		break;}
		case 5:	{color.num = 0xFF0000; JJLOG.println("RED"); 			break;}
		case 6:	{color.num = 0xFFFFFF; JJLOG.println("WHITE"); 			break;}
		case 7:	{color.num = 0xFFFF00; JJLOG.println("YELLOW"); 		break;}
		default:{color.num = 0xFFFFFF; JJLOG.println("didnt match");	break;}
	}

	rgbVal rgb = {
			(uint8_t)((color.num  >> 16) & 0xFF),
			(uint8_t)((color.num  >> 8) & 0xFF),
			(uint8_t)((color.num 	) & 0xFF)
	};
	objRGB.ws2812_setColors(2, &rgb); //rgbVal
}

void WebserverHandler::saveInfoToFile(queryInfo *temp_queryInfo)
{

	JJLOG.println("we are in saving user to file: - ");
	JJLOG.println(temp_queryInfo->userID);

	jsonPair saveToFile;
	saveToFile["timeStamp"]	= temp_queryInfo->timeStamp;
	saveToFile["token"] 	= temp_queryInfo->token;
	saveToFile["methodType"]= temp_queryInfo->methodType;
	saveToFile["code"] 		= temp_queryInfo->code;
	saveToFile["hardwareID"]= temp_queryInfo->hardwareID;

	if (temp_queryInfo->userID == 3)
	{
		jobjFileOperation.jrenameFile("/user/0", "/user/1");
		jobjFileOperation.jrenameFile("/user/1", "/user/2");
		jobjFileOperation.jwriteFile(
				"/user/0",
				objJarusAccessories.func_getJson_str(&saveToFile).c_str());

	}
	else
	{
		String _someUser = "/user/" + String (temp_queryInfo->userID);
		jobjFileOperation.jwriteFile(
				_someUser.c_str(),
				objJarusAccessories.func_getJson_str(&saveToFile).c_str());
	}
}
