/*
 * JarusAccessories.cpp
 *
 *  Created on: 28-Dec-2019
 *      Author: suraj
 */

#include "JarusAccessories.h"

JarusAccessories::JarusAccessories() {
	// TODO Auto-generated constructor stub

	uint64_t _macAddress = ESP.getEfuseMac();
	uint64_t _macAddressTrunc = _macAddress << 40;

	uint64_t _chipID = _macAddress;// replace it later

	//uint64_t _chipID = _macAddressTrunc >> 40;
	//JJLOGesp_efuse_mac_get_default
	//str_chipID = "esp32JARUS";
	//str_chipID = "30JARUS";
	//str_chipID = String (int64String(_chipID, HEX));


	uint64_t macAddressTrunc = ESP.getEfuseMac() << 40;
	uint32_t chipID = macAddressTrunc >> 40;

	str_chipID = "7654321";
	//str_chipID = String (chipID).c_str();
	sstr_chipID = str_chipID.c_str();
	DeviceName  = "SmartRemoteJ@" + sstr_chipID;


}

JarusAccessories::~JarusAccessories() {
	// TODO Auto-generated destructor stub
}


template<typename T>
std::string JarusAccessories::toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}


String JarusAccessories::func_getJson_str(jsonPair *jjson, jsonNested *nestedJson){
	DynamicJsonDocument _tempDoc(1000);
	for (std::map<std::string, std::string>::iterator it=jjson->begin(); it!= jjson->end(); ++it)
		_tempDoc[it->first.c_str()] = it->second.c_str();

	JsonArray _nestedDocData = _tempDoc.createNestedArray("data");

	for (std::vector<std::string>::iterator it = nestedJson->begin() ; it != nestedJson->end(); ++it)
		_nestedDocData.add ( (*it).c_str() );

	String str_temp; serializeJson(_tempDoc, str_temp);
	//JJLOG.println("Prepared json:- " + str_temp);
	return str_temp;
}

jStr JarusAccessories::getJsonStr(jsonPair *jjson){
	DynamicJsonDocument _tempDoc(1000);
	for (std::map<std::string, std::string>::iterator it=jjson->begin(); it!= jjson->end(); ++it)
		_tempDoc[it->first.c_str()] = it->second.c_str();

	String str_temp;
	serializeJson(_tempDoc, str_temp);
	return str_temp.c_str();
}

String JarusAccessories::func_getJson_str(jsonPair *jjson){
	DynamicJsonDocument _tempDoc(1000);
	for (std::map<std::string, std::string>::iterator it=jjson->begin(); it!= jjson->end(); ++it)
		_tempDoc[it->first.c_str()] = it->second.c_str();

	String str_temp; serializeJson(_tempDoc, str_temp);
	//JJLOG.println("Prepared json:- " + str_temp);
	return str_temp;

}
jStr JarusAccessories::getJsonFromJP(jsonPair *jjson){
	DynamicJsonDocument _tempDoc(1000);
	for (std::map<std::string, std::string>::iterator it=jjson->begin(); it!= jjson->end(); ++it)
		_tempDoc[it->first.c_str()] = it->second.c_str();

	String str_temp; serializeJson(_tempDoc, str_temp);
	//JJLOG.println("Prepared json:- " + str_temp);
	return str_temp.c_str();

}

//inline jStr JarusAccessories::fortyRandomChar()
//{
//	String strToken = "";
//	char *letters = "abcdefghijklmnopqrstuvwxyz0123456789";
//	for (int jloop = 0; jloop < 40; jloop++)
//		strToken = strToken + letters [random(0, 36)];
//	return strToken.c_str();
//}


jarusJSON JarusAccessories::jgetJJSON(jStr jsonStr)
{
	jarusJSON temp;
	DynamicJsonDocument doc(1024);
	deserializeJson(doc, jsonStr);
	JsonObject obj = doc.as<JsonObject>(); // useless converaion if you know why

	for (JsonPair p : obj) {
		if ( strcmp (p.key().c_str() , "data") == 0 )
			for( const auto& value : obj["data"].as<JsonArray>() )
				temp.vjsonNested.push_back(value.as<char*>());
		else
			temp.vjsonPair[p.key().c_str()] = p.value().as<const char*>();
	}

	return temp;
}


jStr JarusAccessories::getValueFromKey(jStr argJson, jStr argKey) {
	jarusJSON temp = jgetJJSON (argJson);

	if (temp.vjsonPair.count(argKey) > 0 /*== temp.vjsonPair.end()*/)
	{
		JJLOG.print( "MAP : " );
		JJLOG.print( argKey.c_str() );
		JJLOG.print( " : " );
		JJLOG.println( temp.vjsonPair[argKey].c_str() );
		return temp.vjsonPair[argKey];
	}
	else
	{
		return "";
	}
}


void JarusAccessories::printjarusJSON(jarusJSON *temp)
{
	JJLOG.println("[Printing key:pair]");
	for(auto elem : temp->vjsonPair)
		JJLOG.println(
				String (elem.first.c_str()) +"\t:\t"+
				String (elem.second.c_str()));

	if (temp->vjsonNested.size() != 0)
	{
		JJLOG.print ("jsonNested Printing\t: ");
		for (auto i: temp->vjsonNested)
			JJLOG.print ( String(i.c_str()) + " ");
		JJLOG.println("");
	}
}

void JarusAccessories::generateRandom()
{
	randNumber = 0;
	genrateRepeat:
	for (int i = 0; i < 4; i++)
		randomArray[i] = random(1, 8);
	if (randomArray[0] == randomArray[1] || randomArray[1] == randomArray[2] || randomArray[2] == randomArray[3])
		goto genrateRepeat;

	for (int j = 0; j < 4; j++)
	{
		randNumber *= 10;
		randNumber += randomArray[j];
	}
}

void JarusAccessories::jprint(jStr sText)
{
	JJLOG.println(sText.c_str());
}


String JarusAccessories::getValueBySplit(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
String JarusAccessories::getCurrentFileName(String FullFileAddress)
{
  for (int myloop = 0; myloop < 20; myloop++ )
  {
    if (getValueBySplit(FullFileAddress, (char)47, myloop).equals("") && (myloop != 0) )
    {
      return getValueBySplit(FullFileAddress, (char)47, myloop-1);
    }
  }
  return "-1";
}

void JarusAccessories::info(jStr StrFile, jStr Strline, jStr Strfunc, jStr StrMsg)
//void JarusAccessories::info(jStr StrDate, jStr StrTime, jStr StrFile, jStr Strline, jStr Strfunc, jStr StrMsg)
{

	jsonPair fileInfo;

//	fileInfo["date"] = StrDate;
//	fileInfo["time"] = StrTime;
	fileInfo["file"] = getCurrentFileName(StrFile.c_str()).c_str();
	fileInfo["line"] = Strline;
	fileInfo["func"] = Strfunc;
	//fileInfo["line"] = StrArg;
	fileInfo["msg"] = StrMsg;
	fileInfo["heap"] = String (esp_get_free_heap_size()).c_str();

	//Serial.println(ESP.getFreeHeap());
	//JJLOG.println(String (esp_get_free_heap_size()).c_str());

	JJLOG.print("Jlog\t: ");
	JJLOG.println (getJsonStr(&fileInfo).c_str());

}


