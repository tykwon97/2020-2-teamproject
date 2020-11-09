#define _CRT_SECURE_NO_WARNINGS
#include "personalData.h"
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>

int makeFile(char* fileName);

int writeFile1(char* fileName, char* str);
int writeFile2(char fileName[], char* str);
int writeFile3(char fileName[], char* str);
int writeFile4(char* fileName, int disc);
int writeFile5(char* fileName, char* str);
int writeFile6(char* fileName, int num);

void init(personalData* pd, int pernum);

int savePernum(int pernum);
int saveMasterData(personalData* pd);
int savePersonalData(personalData* pd, adressList* adl);

int readPernumData();
int readPersonalData(adressList* adl, personalData* pd, char* filename);
int readMasterData(personalData* pd, int pernum);