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

	//�������� ���ο���, ��ü ���������� 3, ���� ������ 2, ������� 1
	int addressdisc;
	int birthdisc;
	int genderdisc;

	int friendNum;//ģ������ ���� ģ���� ���� 1 ũ�� �������

	char*** masterfileData;

}personalData;

typedef struct adressList {// �迭 �������� ����
	char textName[30];
	char auth[30];
	char nick[30];

}adressList;

