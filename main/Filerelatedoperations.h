/*
 * Filerelatedoperations.h
 *
 *  Created on: 28-Dec-2019
 *      Author: suraj
 */

#ifndef MAIN_FILERELATEDOPERATIONS_H_
#define MAIN_FILERELATEDOPERATIONS_H_

#define FORMAT_SPIFFS_IF_FAILED true

#include "wasteGlobal.h"
#include "FS.h"
#include "SPIFFS.h"
#include <mutex>          // std::mutex

#include <IRrecv.h>

class File_related_operations {
public:
	File_related_operations();
	virtual ~File_related_operations();

	IRrecv *ptrIRrecv1;

	void getIRinstance(IRrecv *tempIRrecv);

	std::mutex multiFileAccessProtection;
	void jwriteFile(jStr path, jStr message);

	void jappendFile(jStr path, jStr message);

	void jsaveVectorToFile(jStr path, std::vector<uint16_t> *toSaveVector);
	std::vector<uint16_t> jgetVectorFromFile(jStr path);

	std::string jreadFile(jStr path);
	void jrenameFile(jStr path1, jStr path2);

	void jdeleteFile(jStr path);
	void jdeleteFolder(jStr path);
	void jformat();

	jsonNested jlistDir(jStr dirname, uint8_t levels);
	void jtestFileIO(jStr path);


	void takeActionONfolder();


};

#endif /* MAIN_FILERELATEDOPERATIONS_H_ */
