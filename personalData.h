#pragma once

typedef struct personalData {
	char* id;
	char* password;
	char* name;
	char* phoneNum;
	int dataNum;
	char* address;
	char* birth;
	char* gender;

	//선택정보 승인여부, 전체 공개공개면 3, 개인 공개면 2, 비공개면 1
	int addressdisc;
	int birthdisc;
	int genderdisc;

	int friendNum;//친구수는 실제 친구수 보다 1 크게 만들어짐

	char*** masterfileData;

}personalData;

typedef struct adressList {// 배열 형식으로 선언
	char textName[30];
	char auth[30];
	char nick[30];

}adressList;

