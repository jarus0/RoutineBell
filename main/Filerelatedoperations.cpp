/*
 * Filerelatedoperations.cpp
 *
 *  Created on: 28-Dec-2019
 *      Author: suraj
 */

#include "Filerelatedoperations.h"

File_related_operations::File_related_operations() {

/*
    this take dynamic memoty allocation nuit class construction on;ly intistile staic vartiblaes
    https://github.com/espressif/arduino-esp32/issues/831
    if(!SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED))
    {
    	JJLOG.println("SPIFFS Mount Failed");
    }
    else
    {
    	JJLOG.println("SPIFFS Mount succesful");
    }
*/
}

File_related_operations::~File_related_operations() {
	// TODO Auto-generated destructor stub
}


void File_related_operations::getIRinstance(IRrecv *tempIRrecv)
{
	ptrIRrecv1 = tempIRrecv;
}

void File_related_operations::jwriteFile(jStr temp_path, jStr temp_message){
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();
	const char *path = temp_path.c_str();
	const char *message = temp_message.c_str();

    JJLOG.print("Writing file\t: " + String (temp_path.c_str()));

    File file = SPIFFS.open(path, FILE_WRITE);
    if(file){
        if( file.print(message) )
        	JJLOG.println(" |File written :- " + String (temp_message.c_str()) );
        else
        	JJLOG.println(" |File write failed");
    }
    else
    	JJLOG.println("- failed to open file for writing");
    file.close();
    GlobalMutexLU.unlock();
    ptrIRrecv1->enableIRIn();
}

void File_related_operations::jappendFile(jStr temp_path, jStr temp_message){

	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();
	const char *path = temp_path.c_str();
	const char *message = temp_message.c_str();

	JJLOG.printf("Appending to file: %s\r\n", path);

    File file = SPIFFS.open(path, FILE_APPEND);
    if(!file){
        JJLOG.println("- failed to open file for appending");
        file.close();
        GlobalMutexLU.unlock();
        return;
    }
    if(file.print(message))
    	JJLOG.println("- message appended");
    else
    	JJLOG.println("- append failed");
    file.close();
    GlobalMutexLU.unlock();
    ptrIRrecv1->enableIRIn();
}

void File_related_operations::jsaveVectorToFile(jStr path, std::vector<uint16_t> *toSaveVector)
{
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();

    JJLOG.println("vector saving " + String (path.c_str()) );

    File file = SPIFFS.open(path.c_str(), FILE_WRITE);
    if(file){
    	for (auto it = toSaveVector->begin(); it != toSaveVector->end(); ++it){
    		if(	!file.print(*it) ){JJLOG.println("file appending failed");break;}
    		if(	!file.print(',') ){JJLOG.println("file appending failed");break;}
    	}
    }
    else
    	JJLOG.println("- failed to open file for writing");
	file.close();
	JJLOG.println("vector written to file");
	GlobalMutexLU.unlock();
	ptrIRrecv1->enableIRIn();
}
std::vector<uint16_t> File_related_operations::jgetVectorFromFile(jStr path)
{
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();
	JJLOG.printf("vector reading from file:-> %s\r\n", path.c_str());

	std::vector<uint16_t> IRvector;

	File file = SPIFFS.open(path.c_str(), "r");

	if(file && !file.isDirectory()){
	    String tempStr;
		while (file.available())
		{
			char tempChar = (char)file.read();
			if (tempChar == ',')
			{
			  IRvector.push_back((uint16_t) tempStr.toInt());
			  tempStr = "";
			}
			else
				tempStr += tempChar;
		}


    }
	else
		JJLOG.println("- failed to open file for reading");
	file.close();
	GlobalMutexLU.unlock();
	ptrIRrecv1->enableIRIn();
	return IRvector;
}

void File_related_operations::jrenameFile(jStr temp_path1, jStr temp_path2){
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();
	const char *path1 = temp_path1.c_str();
	const char *path2 = temp_path2.c_str();
    JJLOG.printf("Renaming file %s to %s\r\n", path1, path2);

    if (SPIFFS.rename(path1, path2))
    	JJLOG.println("- file renamed");
    else
    	JJLOG.println("- rename failed");
    GlobalMutexLU.unlock();
    ptrIRrecv1->enableIRIn();
}

void File_related_operations::jdeleteFile(jStr temp_path){
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();
    const char *path = temp_path.c_str();

    JJLOG.print("Deleting "+ String (path));

	if( SPIFFS.remove(path) )
		JJLOG.println(" deleted");
	else
		JJLOG.println(" can't delete");
    GlobalMutexLU.unlock();
    ptrIRrecv1->enableIRIn();
}
void File_related_operations::jdeleteFolder(jStr temp_path){
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();

    File root = SPIFFS.open(temp_path.c_str());
    if(root && root.isDirectory())
    {
    	JJLOG.println("deleting folder\t: " + String (root.name()) );
    	for (	File file = root.openNextFile();
    			file;
    			file = root.openNextFile())
    	{

			if(!file.isDirectory())
			{
				JJLOG.print("deleting file\t: "+ String (file.name()));
				if( SPIFFS.remove(file.name()) ) JJLOG.println(" deleted");
				else JJLOG.println(" can't delete");
			}
			else
			{
				JJLOG.print("deleting folder\t: "+ String (file.name()));
				if( SPIFFS.remove(file.name()) ) JJLOG.println(" deleted");
				else JJLOG.println(" can't delete");
			}
			file.close();
    	}
    }
    root.close();
    GlobalMutexLU.unlock();
    ptrIRrecv1->enableIRIn();
}

jsonNested File_related_operations::jlistDir(jStr temp_dirname, uint8_t levels)
{
	ptrIRrecv1->disableIRIn();
	// future some patiya is here solve in future
	jsonNested temp;
	GlobalMutexLU.lock();
	const char *dirname = temp_dirname.c_str();

    JJLOG.printf("Listing directory: %s\r\n", dirname);

    File root = SPIFFS.open(dirname);
    if(!root){
        JJLOG.println("- failed to open directory");
        GlobalMutexLU.unlock();
        return temp;
    }
    if(!root.isDirectory()){
        JJLOG.println(" - not a directory");
        GlobalMutexLU.unlock();
        return temp;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            JJLOG.print("  DIR : ");
            JJLOG.println(file.name());
            if(levels){
            	jlistDir(file.name(), levels -1);
            }
        } else {
        	temp.push_back(file.name());
            JJLOG.print("  FILE: ");
            JJLOG.print(file.name());
            JJLOG.print("\tSIZE: ");
            JJLOG.println(file.size());
        }
        file = root.openNextFile();
    }
    GlobalMutexLU.unlock();
    ptrIRrecv1->enableIRIn();
    return temp;
}

jStr File_related_operations::jreadFile(jStr temp_path)
{
	GlobalMutexLU.lock();
	ptrIRrecv1->disableIRIn();
	jStr returnStr = "";
	//JJLOG.println("one issue is here see it later");

	const char *path = temp_path.c_str();


    JJLOG.print("File[" + String (temp_path.c_str()) );
    File file = SPIFFS.open(path);
    if(file && !file.isDirectory())
    {
    	//returnStr = file.readBytesUntil('\n');

        while(file.available())
        	returnStr += (char) file.read();
        JJLOG.println("]Contain:- " + String (returnStr.c_str()) );
    }
    else
    {

    	JJLOG.println("- failed to open file for reading");
    	//break;
    }

    file.close();


    ptrIRrecv1->enableIRIn();
    GlobalMutexLU.unlock();
    return returnStr;

}

void File_related_operations::jtestFileIO(jStr temp_path)
{
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();
	const char *path = temp_path.c_str();
    JJLOG.printf("Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = SPIFFS.open(path, FILE_WRITE);
    if(!file){
        JJLOG.println("- failed to open file for writing");
        GlobalMutexLU.unlock();
        return;
    }

    size_t i;
    JJLOG.print("- writing" );
    uint32_t start = millis();
    for(i=0; i<2048; i++){
        if ((i & 0x001F) == 0x001F){
          JJLOG.print(".");
        }
        file.write(buf, 512);
    }
    JJLOG.println("");
    uint32_t end = millis() - start;
    JJLOG.printf(" - %u bytes written in %u ms\r\n", 2048 * 512, end);
    file.close();

    file = SPIFFS.open(path);
    start = millis();
    end = start;
    i = 0;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        JJLOG.print("- reading" );
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F){
              JJLOG.print(".");
            }
            len -= toRead;
        }
        JJLOG.println("");
        end = millis() - start;
        JJLOG.printf("- %u bytes read in %u ms\r\n", flen, end);
        file.close();
    } else {
        JJLOG.println("- failed to open file for reading");
    }
    GlobalMutexLU.unlock();
    ptrIRrecv1->enableIRIn();
}

void File_related_operations::jformat()
{
	ptrIRrecv1->disableIRIn();
	GlobalMutexLU.lock();
	if (SPIFFS.format())
		JJLOG.println("\n\nSuccess format");
	else
		JJLOG.println("\n\nError format");
	GlobalMutexLU.unlock();
	ptrIRrecv1->enableIRIn();
}
