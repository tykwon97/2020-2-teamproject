#include "dataFunc.h"

int makeFile(char* fileName) {//filenName 인자는 반드시 xxx.txt형식일것!
	FILE* fp;
	fp = fopen(fileName, "r");
	if ((fp = fopen(fileName, "r")) == NULL) {
		fprintf(stderr, "Cannot open file.\n");
		return 1;
	}
	//char* a = "abcd";//test word
	//fputs(a, fp);
	fclose(fp);
	return 0;
}

int writeFile1(char* fileName, char* str) {
	//마스터 파일 저장용
	//filenName 인자는 반드시 xxx.txt형식일것!
	//기록하면 한 칸 띄워짐!!
	FILE* fp;
	char file_buff[100];
	sprintf_s(file_buff, sizeof(file_buff), "%s ", str);
	if ((fp = fopen(fileName, "a")) == NULL) {
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	fputs(file_buff, fp);
	fclose(fp);
	return 0;
}
int writeFile2(char fileName[], char* str) {
	//개인파일 저장용
	//filenName 인자는 반드시 xxx.txt형식일것!
	//기록하면 한 줄 띄워짐!!
	FILE* fp;
	char file_buff[100];
	sprintf_s(file_buff, sizeof(file_buff), "%s\n", str);
	if ((fp = fopen(fileName, "a")) == NULL) {
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	fputs(file_buff, fp);
	fclose(fp);
	return 0;
}

int writeFile3(char fileName[], char* str) {
	//개인파일 초기화 후 저장용 개인 파일 저장시 처음으로 실행
	//filenName 인자는 반드시 xxx.txt형식일것!
	//기록하면 한 줄 띄워짐!!
	FILE* fp;
	char file_buff[100];
	sprintf_s(file_buff, sizeof(file_buff), "%s\n", str);
	if ((fp = fopen(fileName, "w")) == NULL) {
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	fputs(file_buff, fp);
	fclose(fp);
	return 0;
}

int writeFile4(char* fileName, int disc) {
	//개인 파일 주소록 권한 저장용
	//filenName 인자는 반드시 xxx.txt형식일것!
	//기록하면 한 칸 띄워짐!!
	FILE* fp;
	char file_buff[100];
	sprintf_s(file_buff, sizeof(file_buff), "%d ", disc);
	if ((fp = fopen(fileName, "a")) == NULL) {
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	fputs(file_buff, fp);
	fclose(fp);
	return 0;
}

int writeFile5(char* fileName, char* str) {
	//개인 파일 주소록 정보식별자 저장용
	//filenName 인자는 반드시 xxx.txt형식일것!
	//기록하면 한 칸 띄워짐!!
	FILE* fp;
	char file_buff[100];
	sprintf_s(file_buff, sizeof(file_buff), "%s ", str);
	if ((fp = fopen(fileName, "a")) == NULL) {
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	fputs(file_buff, fp);
	fclose(fp);
	return 0;
}

int writeFile6(char* fileName, int num) {
	//개인 파일 선택정보 갯수 저장용
	//filenName 인자는 반드시 xxx.txt형식일것!
	//기록하면 한 줄 띄워짐!!
	FILE* fp;
	char file_buff[100];
	sprintf_s(file_buff, sizeof(file_buff), "%d\n", num);
	if ((fp = fopen(fileName, "a")) == NULL) {
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	fputs(file_buff, fp);
	fclose(fp);
	return 0;
}

void init(personalData* pd, int pernum) {
	//구조체 메모리 초기화
	//사이즈 설정 문자열 길이에 따라 변경 가능
	pd->id = (char*)malloc(sizeof(char) * 11);
	pd->password = (char*)malloc(sizeof(char) * 13);
	pd->name = (char*)malloc(sizeof(char) * 13);
	pd->phoneNum = (char*)malloc(sizeof(char) * 12);
	pd->address = (char*)malloc(sizeof(char) * 61);
	pd->birth = (char*)malloc(sizeof(char) * 11);
	pd->gender = (char*)malloc(sizeof(char) * 3);

	//데이터 개수 초기화
	pd->dataNum;

	//구조체 내부 포인터 초기화
	pd->address = NULL;
	pd->birth = NULL;
	pd->gender = NULL;
	pd->addressdisc = 0;
	pd->birthdisc = 0;
	pd->genderdisc = 0;

	pd->masterfileData = (char***)malloc(sizeof(char**) * pernum);
	for (int i = 0; i < pernum; i++) {
		pd->masterfileData[i] = (char**)malloc(sizeof(char*) * 4);
	}
	//makeFile("masterfile.txt");
}

int savePernum(int pernum) {
	FILE* fp;
	char file_buff[100];
	sprintf_s(file_buff, sizeof(file_buff), "%d\n", pernum);
	if ((fp = fopen("pernum.txt", "w")) == NULL) {
		fprintf(stderr, "Cannot open output file.\n");
		return 1;
	}
	fputs(file_buff, fp);
	fclose(fp);
	return 0;
}

int saveMasterData(personalData* pd) {
	//마스터 파일
	char* masterfile = "masterfile.txt";
	writeFile1(masterfile, pd->id);
	writeFile1(masterfile, pd->password);
	writeFile1(masterfile, pd->name);
	writeFile1(masterfile, pd->phoneNum);
	writeFile2(masterfile, "");
	return 0;
}
int savePersonalData(personalData* pd, adressList* adl) {
	//개인별 파일
	char personalfile[100];
	sprintf_s(personalfile, sizeof(personalfile), "%s.txt", pd->id);

	writeFile3(personalfile, pd->id);
	writeFile2(personalfile, pd->password);
	writeFile2(personalfile, pd->name);
	writeFile2(personalfile, pd->phoneNum);
	writeFile6(personalfile, pd->dataNum);

	if (pd->address != NULL) {
		writeFile5(personalfile, "address");
		writeFile4(personalfile, pd->addressdisc);
		writeFile2(personalfile, pd->address);
	}
	if (pd->gender != NULL) {
		writeFile5(personalfile, "gender");
		writeFile4(personalfile, pd->genderdisc);
		writeFile2(personalfile, pd->gender);
	}
	if (pd->birth != NULL) {
		writeFile5(personalfile, "birth");
		writeFile4(personalfile, pd->birthdisc);
		writeFile2(personalfile, pd->birth);
	}

	writeFile6(personalfile, pd->friendNum);


	for (int i = 0; i < pd->friendNum; i++) {
		writeFile5(personalfile, adl[i].textName);
		writeFile5(personalfile, adl[i].auth);
		writeFile2(personalfile, adl[i].nick);
	}
	return 0;
}

int readPernumData() {
	FILE* fp = NULL;
	int pernum;
	if ((fp = fopen("pernum.txt", "r")) == NULL) {
		fprintf(stderr, "Cannot open input file.\n");
		return -1;
	}
	char str[10];
	fscanf(fp, "%s", str);
	pernum = atoi(str);
	return pernum;
}

int readPersonalData(adressList* adl, personalData* pd, char* filename) {
	char textname[100];
	sprintf_s(textname, sizeof(textname), "%s.txt", filename);
	FILE* fp;
	if ((fp = fopen(textname, "r")) == NULL) {
		fprintf(stderr, "Cannot open input file.\n");
		return 1;
	}

	//필수정보
	char str1[100];
	fscanf(fp, "%s", str1);
	strcpy(pd->id, str1);
	char str2[100];
	fscanf(fp, "%s", str2);
	strcpy(pd->password, str2);
	char str3[100];
	fscanf(fp, "%s", str3);
	strcpy(pd->name, str3);
	char str4[100];
	fscanf(fp, "%s", str4);
	strcpy(pd->phoneNum, str4);
	int datanum = 1;
	fscanf(fp, "%d", &datanum);
	pd->dataNum = datanum;

	//선택정보
	int disk1;
	int disk2;
	int disk3;
	char str5[100];
	char str6[100];
	char str7[100];
	char str8[100];
	char str9[100];
	char str10[100];

	for (int i = 0; i < pd->dataNum; i++) {

		if (i == 0) {
			fscanf(fp, "%s", str5);
			if (strcmp(str5, "address") == 0) {
				fscanf(fp, "%d", &disk1);
				pd->addressdisc = disk1;
				fscanf(fp, "%s", str6);
				pd->address = (char*)malloc(sizeof(char) * 30);
				strcpy(pd->address, str6);
			}
			else if (strcmp(str5, "gender") == 0) {
				fscanf(fp, "%d", &disk2);
				pd->genderdisc = disk2;
				fscanf(fp, "%s", str8);
				pd->gender = (char*)malloc(sizeof(char) * 3);
				strcpy(pd->gender, str8);
			}
			else if (strcmp(str5, "birth") == 0) {
				fscanf(fp, "%d", &disk3);
				pd->birthdisc = disk3;
				fscanf(fp, "%s", str10);
				pd->birth = (char*)malloc(sizeof(char) * 10);
				strcpy(pd->birth, str10);
			}

		}
		else if (i == 1) {
			fscanf(fp, "%s", str7);
			if (strcmp(str7, "gender") == 0) {
				fscanf(fp, "%d", &disk2);
				pd->genderdisc = disk2;
				fscanf(fp, "%s", str8);
				pd->gender = (char*)malloc(sizeof(char) * 3);
				strcpy(pd->gender, str8);
			}
			else if (strcmp(str7, "birth") == 0) {
				fscanf(fp, "%d", &disk3);
				pd->birthdisc = disk3;
				fscanf(fp, "%s", str10);
				pd->birth = (char*)malloc(sizeof(char) * 10);
				strcpy(pd->birth, str10);
			}
		}
		else if (i == 2) {
			fscanf(fp, "%s", str9);
			if (strcmp(str9, "birth") == 0) {
				fscanf(fp, "%d", &disk3);
				pd->birthdisc = disk3;
				fscanf(fp, "%s", str10);
				pd->birth = (char*)malloc(sizeof(char) * 10);
				strcpy(pd->birth, str10);
			}
		}
	}
	int friendNum = 0;
	fscanf(fp, "%d\n", &friendNum);
	pd->friendNum = friendNum;

	// 구현중	

		//adl = (adressList*)malloc(sizeof(adressList) * pd->friendNum);	
	for (int i = 0; i < pd->friendNum; i++) {
		//adl[i] = malloc(sizeof(adressList));
		char str11[100];
		char str12[100];
		char str13[20];
		fscanf(fp, "%s", str11);
		fscanf(fp, "%s", str12);
		fscanf(fp, "%s", str13);
		//printf("%s\n", str13); 들어 갔어
		//adl[i].nick = str13;
		strcpy(adl[i].nick, str13);
	}

	//char str13[100];
	//fscanf(fp, "%s", str13);
	//strcpy(adl[1].nick, str13);
	//strcpy(adl[i].textName, str11);
	//strcpy(adl[i].auth, str12);
	fclose(fp);
	return 0;
}

int readMasterData(personalData* pd, int pernum) {
	char textname[100];
	FILE* fp = NULL;
	if ((fp = fopen("masterfile.txt", "r")) == NULL) {
		fprintf(stderr, "Cannot open input file.\n");
		return 1;
	}

	char buffer[100];

	for (int i = 0; i < pernum; i++) {
		for (int j = 0; j < 4; j++) {
			fscanf(fp, "%s", buffer);
			pd->masterfileData[i][j] = malloc(sizeof(char) * 100);
			strcpy(pd->masterfileData[i][j], buffer);
		}
	}

	fclose(fp);
	return 0;
}



