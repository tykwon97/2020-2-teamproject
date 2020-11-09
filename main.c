#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "dataFunc.h"
#define STR_SIZE 100
#define MEMBER_SIZE 100

//���� ���� �Լ�
void clearInputBuffer() {
	while (getchar() != '\n');
}

//�ѱ������Ͽ� ���ڿ� ���� ���ϴ� �Լ�
int GetStringLength(const char* string) {
	int count = 0;
	while (*string) {
		if (*string >> 7) {
			string++;
		}
		string++;
		count++;
	}
	return count;
}

//����� �Է� �����ϰ� �޴� �Լ� ���ϰ� 0�Ͻ� �ùٸ� �Է�, 1�Ͻ� �ùٸ��� ���� �Է�
int get_char_input(char input[], int* input_length) {
	int length = 0;
	char c;
	int i = 0;
	int flag = 0;
	while (1) {
		if (i > STR_SIZE - 1) {
			flag = 1;
			break;
		}
		scanf("%c", &c);
		if (c == '\n') {
			flag = 2;
			break;
		}
		else {
			input[i] = c;
			i++;
		}
	}
	if (flag == 1) {
		i = 0;
		clearInputBuffer();
		return 1;
	}
	else if (flag == 2) {
		if (i == 0) {
			return 1;
		}
		input[i] = '\0';
		length = strlen(input);
		*input_length = length;
		return 0;
	}
}

//�̸� �����˻� �Լ� ���ϰ� 0�Ͻ� �ùٸ� �Է�, 1�Ͻ� �ùٸ��� ���� �Է�
int check_name(char* name) {
	int flag = 0;
	int name_arr_length = strlen(name);
	int real_name_length = GetStringLength(name);
	if (real_name_length > 6 || real_name_length < 2) {
		flag = 1;
	}
	else {
		for (int i = 0; i < name_arr_length; i++) {
			char check = name[i];
			if (check >> 7) {
				continue;
			}
			else if (isdigit(check) != 0) {
				continue;
			}
			else if (isalpha(check) != 0) {
				continue;
			}
			else {
				flag = 1;
				break;
			}
		}
	}
	return flag;
}

//������ �����Ϳ��� ��ȭ��ȣ ã�� �Լ�
char* seekCharPhone(char*** masterFileData, char* phone_num, int pernum) {
	int seekpoint_phone_num;
	for (int i = 0; i < pernum; i++) {
		if (strcmp(masterFileData[i][3], phone_num) == 0) {
			seekpoint_phone_num = i;
			return masterFileData[seekpoint_phone_num][3];
		}
	}
	return NULL;
}

//��ȭ��ȣ �����˻� �Լ� ���ϰ� 0�Ͻ� �ùٸ� �Է�, 1�Ͻ� �ùٸ��� ���� �Է�, 2�Ͻ� �ߺ�
int check_phone_num(char* phone_num, char*** masterfileData, int pernum) {
	int flag = 0;
	int phone_num_arr_length = strlen(phone_num);
	int real_phone_num_length = GetStringLength(phone_num);
	if ((real_phone_num_length == 13 || real_phone_num_length == 11) != 1) {
		flag = 1;
	}
	else {
		for (int i = 0; i < 3; i++) {
			char check = phone_num[i];
			if (i == 0 || i == 2) {
				if (phone_num[i] == '0') {
					continue;
				}
				else {
					flag = 1;
					break;
				}

			}
			else if (i == 1) {
				if (phone_num[i] == '1') {
					continue;
				}
				else {
					flag = 1;
					break;
				}
			}
		}
		if (flag != 1) {
			if (phone_num_arr_length == 13) {
				if (phone_num[3] == '-' && phone_num[8] == '-') {
					for (int i = 0; i < phone_num_arr_length; i++) {
						if (i == 3 || i == 8)continue;
						char check = phone_num[i];
						if (check >> 7) {
							flag = 1;
							break;
						}
						else if (isdigit(check) != 0) {
							continue;
						}
						else {
							flag = 1;
							break;
						}
					}
					char temp_phone_num[12];
					int j = 0;
					for (int i = 0; i < phone_num_arr_length; i++) {
						if (i == 3 || i == 8) {
							continue;
						}
						else {
							temp_phone_num[j] = phone_num[i];
							j++;
						}
					}
					temp_phone_num[11] = '\0';
					if (seekCharPhone(masterfileData, temp_phone_num, pernum) != NULL) {
						flag = 2;
					}
				}
				else {
					flag = 1;
				}
			}
			else if (phone_num_arr_length == 11) {
				for (int i = 0; i < phone_num_arr_length; i++) {
					char check = phone_num[i];
					if (check >> 7) {
						flag = 1;
						break;
					}
					else if (isdigit(check) != 0) {
						continue;
					}
					else {
						flag = 1;
						break;
					}
				}
				if (seekCharPhone(masterfileData, phone_num, pernum) != NULL) {
					flag = 2;
				}
			}
		}
	}
	return flag;
}

//������� �����˻� �Լ� ���ϰ� 0�Ͻ� �ùٸ� �Է�, 1�Ͻ� �ùٸ��� ���� �Է�, 2�Ͻ� 2020-01-23 ������ �Է�
int check_birth(char* birthday) {
	int flag = 0;
	int birthday_flag = 0;
	char temp_birthday[7];
	int birthday_arr_length = strlen(birthday);
	int real_birthday_length = GetStringLength(birthday);
	if (!(real_birthday_length == 6 || real_birthday_length == 10)) {
		flag = 1;
	}
	else {
		if (real_birthday_length == 6) {
			birthday_flag = 1;
			for (int i = 0; i < birthday_arr_length; i++) {
				char check = birthday[i];
				if (check >> 7) {
					flag = 1;
					break;
				}
				else if (isdigit(check) != 0) {
					continue;
				}
				else {
					flag = 1;
					break;
				}
			}

			if (!(birthday[2] == '0' || birthday[2] == '1')) {
				flag = 1;
			}
			else {
				if (birthday[2] == '0') {
					if (birthday[3] == '0') {
						flag = 1;
					}
				}
				else if (birthday[2] == '1') {
					if (!(birthday[3] == '0' || birthday[3] == '1' || birthday[3] == '2')) {
						flag = 1;
					}
				}
			}

			if (!(birthday[4] == '0' || birthday[4] == '1' || birthday[4] == '2' || birthday[4] == '3')) {
				flag = 1;
			}
			else {
				if (birthday[4] == '0') {
					if (birthday[5] == '0') {
						flag = 1;
					}
				}
				else if (birthday[4] == '3') {
					if (birthday[2] == '0' && birthday[3] == '2') {
						flag = 1;
					}
					else {
						char thirtyone[] = "0123578";
						char check_day = birthday[5];
						char check_month = birthday[3];
						if (check_day == '1') {
							char* p;
							p = strchr(thirtyone, check_month);
							if (p == NULL) {
								flag = 1;
							}
						}
					}
				}
			}

			if (birthday[2] == '0' && birthday[3] == '2') {
				char temp_year[3];
				strncpy(temp_year, birthday, 2);
				int check_year = atoi(temp_year);
				if (check_year > 20) {
					char year[5] = "19";
					strcat(year, temp_year);
					int real_year = atoi(year);
					if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
						if (birthday[4] == '2' && birthday[5] == '9') {
							flag = 1;
						}
					}
				}
				else {
					char year[5] = "20";
					strcat(year, temp_year);
					int real_year = atoi(year);
					if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
						if (birthday[4] == '2' && birthday[5] == '9') {
							flag = 1;
						}
					}
				}
			}
		}
		else if (real_birthday_length == 10) {
			birthday_flag = 2;
			flag = 2;
			if (!(birthday[4] == '-' && birthday[7] == '-')) {
				flag = 1;
			}
			else {
				for (int i = 0; i < birthday_arr_length; i++) {
					if (i == 4 || i == 7)continue;
					char check = birthday[i];
					if (check >> 7) {
						flag = 1;
						break;
					}
					else if (isdigit(check) != 0) {
						continue;
					}
					else {
						flag = 1;
						break;
					}
				}
				char year_check[5];
				strncpy(year_check, birthday, 4);
				year_check[4] = '\0';
				int a = atoi(year_check);
				if (a < 1921 || a > 2020) {
					flag = 1;
				}
				int j = 2;
				for (int i = 0; i < 7; i++) {
					if (birthday[j] == '-') {
						i--;
					}
					else {
						temp_birthday[i] = birthday[j];
					}
					j++;
				}
				temp_birthday[6] = '\0';
				if (!(temp_birthday[2] == '0' || temp_birthday[2] == '1')) {
					flag = 1;
				}
				else {
					if (temp_birthday[2] == '0') {
						if (temp_birthday[3] == '0') {
							flag = 1;
						}
					}
					else if (temp_birthday[2] == '1') {
						if (!(temp_birthday[3] == '0' || temp_birthday[3] == '1' || temp_birthday[3] == '2')) {
							flag = 1;
						}
					}
				}

				if (!(temp_birthday[4] == '0' || temp_birthday[4] == '1' || temp_birthday[4] == '2' || temp_birthday[4] == '3')) {
					flag = 1;
				}
				else {
					if (temp_birthday[4] == '0') {
						if (temp_birthday[5] == '0') {
							flag = 1;
						}
					}
					else if (temp_birthday[4] == '3') {
						if (temp_birthday[2] == '0' && temp_birthday[3] == '2') {
							flag = 1;
						}
						else {
							char thirtyone[] = "0123578";
							char check_day = temp_birthday[5];
							char check_month = temp_birthday[3];
							if (check_day == '1') {
								char* p;
								p = strchr(thirtyone, check_month);
								if (p == NULL) {
									flag = 1;
								}
							}
						}
					}
				}

				if (temp_birthday[2] == '0' && temp_birthday[3] == '2') {
					char temp_year[3];
					strncpy(temp_year, temp_birthday, 2);
					int check_year = atoi(temp_year);
					if (check_year > 20) {
						char year[5] = "19";
						strcat(year, temp_year);
						int real_year = atoi(year);
						if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
							if (temp_birthday[4] == '2' && temp_birthday[5] == '9') {
								flag = 1;
							}
						}
					}
					else {
						char year[5] = "20";
						strcat(year, temp_year);
						int real_year = atoi(year);
						if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
							if (temp_birthday[4] == '2' && temp_birthday[5] == '9') {
								flag = 1;
							}
						}
					}
				}
			}
		}
	}
	return flag;
}

//���� �����˻� �Լ� ���ϰ� 1�Ͻ� �ùٸ��� ���� �Է�, 2�Ͻ� ����, 3�Ͻ� ����
int check_gender(char* gender) {
	int flag = 0;
	int real_gender_length = GetStringLength(gender);
	if (!(real_gender_length == 1 || real_gender_length == 2)) {
		flag = 1;
	}
	else {

		if (strcmp(gender, "��") == 0 || strcmp(gender, "����") == 0 || strcmp(gender, "����") == 0) {
			flag = 2;
		}
		else if (strcmp(gender, "��") == 0 || strcmp(gender, "����") == 0 || strcmp(gender, "����") == 0) {
			flag = 3;
		}
		else {
			flag = 1;
		}

	}
	return flag;
}

//�ּ� �����˻� �Լ� ���ϰ� 0�Ͻ� �ùٸ� �Է�, 1�Ͻ� �ùٸ��� ���� �Է�
int check_address(char* address) {
	int flag = 0;
	int real_address_length = GetStringLength(address);
	if (real_address_length < 2 || real_address_length > 30) {
		flag = 1;
	}
	else {
		for (int i = 0; i < strlen(address); i++) {
			char check = address[i];
			if (check >> 7) {
				continue;
			}
			else if (isalnum(check)) {
				continue;
			}
			else if (check == ' ') {
				continue;
			}
			else {
				flag = 1;
				break;
			}
		}
	}
	return flag;
}

//������ �����Ϳ��� ���̵� ã�� �Լ�
char* seekCharId(char*** masterFileData, char* id, int pernum) {
	int seekpoint_id;
	for (int i = 0; i < pernum; i++) {
		if (strcmp(masterFileData[i][0], id) == 0) {
			seekpoint_id = i;
			return masterFileData[seekpoint_id][0];
		}
	}
	return NULL;
}

//������ �����Ϳ��� ��й�ȣ ã�� �Լ�
char* seekCharPw(char*** masterFileData, char* pw, int pernum) {
	int seekpoint_pw;
	for (int i = 0; i < pernum; i++) {
		if (strcmp(masterFileData[i][1], pw) == 0) {
			seekpoint_pw = i;
			return masterFileData[seekpoint_pw][1];
		}
	}
	return NULL;
}

void del_space(char temp[], char arr[]) {
	for (int i = 0; i < strlen(arr); i++) {
		char check = arr[i];
		if (check >> 7) {
			temp[i] = check;
		}
		else if (arr[i] == ' ') {
			temp[i] = '-';
		}
		else {
			temp[i] = check;
		}
	}
	temp[strlen(arr)] = '\0';
}

char* DeleteSpace(char s[]) {

	char* str = (char*)malloc(sizeof(s));

	int i, k = 0;

	for (i = 0; i < strlen(s); i++) {
		if (s[i] != ' ') {
			str[k++] = s[i];
		}
	}
	str[k] = '\0';

	return str;

}

void make_print_address(char temp[], char* address) {
	for (int i = 0; i < strlen(address); i++) {
		char check = address[i];
		if (check >> 7) {
			temp[i] = check;
		}
		else if (address[i] == '-') {
			temp[i] = ' ';
		}
		else {
			temp[i] = check;
		}
	}
	temp[strlen(address)] = '\0';
}

int main(void) {
	system("mode con: cols=90 lines=40");
	int pernum;
	if (readPernumData() == -1) {
		pernum = 0;
		savePernum(pernum);
	}
	while (1) {
		pernum = readPernumData();
		system("cls");
		printf(" ���� �ּҷ�\n");
		printf("----------------\n");
		printf(" 1) �α���\n");
		printf(" 2) ȸ������\n");
		printf(" 3) ���α׷� ����\n");
		printf("----------------\n");
		printf("�޴��� �����ϼ��� > ");
		char menu_temp[STR_SIZE];
		char* menu;
		int menu_arr_length = 0;
		int menu_check = get_char_input(menu_temp, &menu_arr_length);
		if (menu_check != 0) {
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
			Sleep(1000);
			continue;
		}
		else {
			menu = (char*)malloc(sizeof(char) * (menu_arr_length + 1));
			strcpy(menu, menu_temp);
			int real_menu_length = GetStringLength(menu);
			if (real_menu_length != 1) {
				printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
				Sleep(1000);
				continue;
			}
			else {
				//�α��� ����
				if (strcmp(menu, "1") == 0) {
					if (pernum == 0) {
						printf("���Ե� ȸ���� �������� �ʾ� �α����� �� �� �����ϴ�.\n");
						Sleep(1000);
						continue;
					}
					int login_flag = 0;
					char in_id_temp[STR_SIZE];
					char* in_id;
					int in_id_arr_length = 0;
					while (1) {
						personalData login;
						init(&login, pernum);
						readMasterData(&login, pernum);
						system("cls");
						printf("----------------------------------------------------------------------\n");
						printf("���̵�� 6�� �̻� 10�� ������ �θ��� �ҹ��ڿ� ���ڷ� �����Ǿ�� �մϴ�.\n");
						printf("��й�ȣ�� 8�� �̻� 12�� ������ �θ��ڿ� ���ڷ� �����Ǿ�� �մϴ�.\n");
						printf("----------------------------------------------------------------------\n");
						printf("������ ���̵�� ��й�ȣ�� �Է����ּ���.\n");
						printf("���̵� > ");
						int in_id_check = get_char_input(in_id_temp, &in_id_arr_length);
						if (in_id_check != 0) {
							printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
							Sleep(1000);
							continue;
						}
						else {
							printf("��й�ȣ > ");
							char in_pw_temp[STR_SIZE];
							char* in_pw;
							int in_pw_arr_length = 0;
							int in_pw_check = get_char_input(in_pw_temp, &in_pw_arr_length);
							if (in_pw_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
								Sleep(1000);
								continue;
							}
							else {
								in_id = (char*)malloc(sizeof(char) * (in_id_arr_length + 1));
								strcpy(in_id, in_id_temp);
								in_pw = (char*)malloc(sizeof(char) * (in_pw_arr_length + 1));
								strcpy(in_pw, in_pw_temp);
								if (seekCharId(login.masterfileData, in_id, pernum) == NULL) {
									printf("�������� �ʴ� ���̵��Դϴ�.\n");
									Sleep(1000);
									while (1) {
										system("cls");
										printf("-------------------------------------\n");
										printf("1) �α��� ȭ������ ���ư��ϴ�\n");
										printf("2) ���α׷� ����ȭ������ ���ư��ϴ�.\n");
										printf("-------------------------------------\n");
										printf("�޴� > ");
										char menu_temp[STR_SIZE];
										char* menu;
										int menu_arr_length = 0;
										int menu_check = get_char_input(menu_temp, &menu_arr_length);
										if (menu_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											menu = (char*)malloc(sizeof(char) * (menu_arr_length + 1));
											strcpy(menu, menu_temp);
											if (strcmp(menu, "1") == 0) {
												login_flag = 1;
												break;
											}
											else if (strcmp(menu, "2") == 0) {
												login_flag = 3;
												break;
											}
											else {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
										}
									}
								}
								else if (strcmp(in_id, seekCharId(login.masterfileData, in_id, pernum)) == 0) {
									if (seekCharPw(login.masterfileData, in_pw, pernum) == NULL) {
										printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
										Sleep(1000);
										while (1) {
											system("cls");
											printf("-------------------------------------\n");
											printf("1) �α��� ȭ������ ���ư��ϴ�\n");
											printf("2) ���α׷� ����ȭ������ ���ư��ϴ�.\n");
											printf("-------------------------------------\n");
											printf("�޴� > ");
											char menu_temp[STR_SIZE];
											char* menu;
											int menu_arr_length = 0;
											int menu_check = get_char_input(menu_temp, &menu_arr_length);
											if (menu_check != 0) {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {
												menu = (char*)malloc(sizeof(char) * (menu_arr_length + 1));
												strcpy(menu, menu_temp);
												if (strcmp(menu, "1") == 0) {
													login_flag = 1;
													break;
												}
												else if (strcmp(menu, "2") == 0) {
													login_flag = 3;
													break;
												}
												else {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
											}
										}
									}
									else if (strcmp(in_pw, seekCharPw(login.masterfileData, in_pw, pernum)) == 0) {
										login_flag = 0;
									}
								}
							}
						}
						if (login_flag == 1) {
							continue;
						}
						else {
							break;
						}
					}
					if (login_flag == 0) {
						//�α��� ����
						char* user_id = in_id;
						personalData user;
						adressList user_adl[MEMBER_SIZE];
						init(&user, pernum);
						readMasterData(&user, pernum);
						readPersonalData(user_adl, &user, user_id);
						int user_masterfile_idx = 0;
						for (int i = 0; i < pernum; i++) {
							if (strcmp(user.id, user.masterfileData[i][0]) == 0) {
								user_masterfile_idx = i;
								break;
							}
						}
						system("cls");
						printf("----------------------------------\n");
						printf("  �ݰ����ϴ� %s ȸ����!\n", user.name);
						printf("----------------------------------\n");
						Sleep(1000);
						while (1) {
							system("cls");
							printf("\n��ɾ�(\'\'�����ϰ� �Է�) \t ���� \n\n");
							printf("\'search\' or \'s\' \t\t ȸ���� �˻��մϴ�. \n");
							printf("\'show\' or \'sh\' \t\t\t �ڽ��� �ּҷ��� �����ݴϴ�. \n");
							printf("\'change\' or \'c\' \t\t �ڽ��� ������ �����մϴ�. \n");
							printf("\'quit\' or \'q\' \t\t\t �α׾ƿ� �մϴ�. \n\n");
							printf("%s \'s PhoneBook > ", user.name);
							char main_menu_temp[STR_SIZE];
							char* main_menu;
							int main_menu_arr_length = 0;
							int main_menu_check = get_char_input(main_menu_temp, &main_menu_arr_length);
							if (main_menu_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								main_menu = (char*)malloc(sizeof(char) * (main_menu_arr_length + 1));
								strcpy(main_menu, main_menu_temp);
								int real_main_menu_length = GetStringLength(main_menu);
								//�˻�
								if (strcmp(main_menu, "search") == 0 || strcmp(main_menu, "s") == 0) {
									while (1) {
										system("cls");
										printf("\n�� ���α׷��� ȸ���� �˻��� �� �ֽ��ϴ�\n");
										printf("\n��ɾ�(\'\'�����ϰ� �Է�) \t ���� \n\n");
										printf("\'name\' \'�˻�����\' \t\t �̸��� �̿��ؼ� ȸ���� �˻��մϴ�.\n");
										printf("\'phone\' \'�˻�����\' \t\t ��ȭ��ȣ�� �̿��ؼ� ȸ���� �˻��մϴ�.\n");
										printf("\'back\' \t\t\t\t ����ȭ������ ���ư��ϴ�.\n");
										printf("ex) name ȫ�浿   phone 010-1234-5678\n\n");
										printf("�˻� > ");
										char search_temp[STR_SIZE];
										char* search = NULL;
										int search_arr_length = 0;
										int flag = 0;
										int search_check = get_char_input(search_temp, &search_arr_length);
										if (search_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											search = (char*)malloc(sizeof(char) * (search_arr_length + 1));
											strcpy(search, search_temp);
											int real_search_length = GetStringLength(search);
											char* t1 = strtok(search, " ");
											char* factor = strtok(NULL, " ");
											if (strcmp(t1, "back") == 0) {
												printf("����ȭ������ ���ư��ϴ�.");
												Sleep(1000);
												break;
											}
											if (factor == NULL) {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											if (strcmp(t1, "name") == 0) {
												char* search_name = factor;
												int search_name_arr_length = strlen(search_name);
												int real_search_name_length = GetStringLength(search_name);
												if (real_search_name_length > 6) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													flag = 2;
												}

											}
											else if (strcmp(t1, "phone") == 0) {
												char* search_phone_num = factor;
												int search_phone_num_arr_length = strlen(search_phone_num);
												int real_search_phone_num_length = GetStringLength(search_phone_num);
												if (real_search_phone_num_length > 13) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													flag = 3;
												}
											}
											else {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}

											if (flag == 2 || flag == 3) {
												char* search_text = factor;
												int search_flag = 0;
												while (1) {
													system("cls");
													printf("------------------------------\n");
													if (flag == 2) {
														printf("name %s > \n", search_text);
													}
													else if (flag == 3) {
														printf("phone %s > \n", search_text);
													}
													printf("------------------------------\n");
													int search_member_num = 0;
													int* search_member_num_arr;
													search_member_num_arr = (int*)malloc(sizeof(int) * pernum);
													int i = 0;
													for (i = 0; i < pernum; i++) {
														if (!(strstr(user.masterfileData[i][2], search_text) == NULL && strstr(user.masterfileData[i][3], search_text) == NULL)) {
															if (strcmp(user.id, user.masterfileData[i][0]) == 0) {
																continue;
															}
															search_flag = 1;
															search_member_num_arr[search_member_num] = i;
															search_member_num++;
															printf("%d  %s  %s\n", search_member_num, user.masterfileData[i][2], user.masterfileData[i][3]);
														}
														else {
															continue;
														}
													}

													if (search_flag == 0) {
														printf("�˻������ �������� �ʽ��ϴ�.\n");
														printf("------------------------------\n");
														Sleep(1000);
														break;
													}
													printf("------------------------------\n");
													printf("�����ϰ� ���� ȸ���� �տ� ������ ��ȣ�� �Է��ϼ��� > ");
													char member_num_temp[STR_SIZE];
													char* member_num;
													int member_num_arr_length = 0;
													int member_num_check = get_char_input(member_num_temp, &member_num_arr_length);
													if (member_num_check != 0) {
														printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
													else {
														member_num = (char*)malloc(sizeof(char) * (member_num_arr_length + 1));
														strcpy(member_num, member_num_temp);
														int real_member_num_length = GetStringLength(member_num);
														int member_flag = 0;
														for (int i = 0; i < member_num_arr_length; i++) {
															char check = member_num[i];
															if (check >> 7) {
																member_flag = 1;
																break;
															}
															else if (isdigit(check) != 0) {
																continue;
															}
															else {
																member_flag = 1;
																break;
															}
														}
														if (member_flag == 1) {
															printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
															Sleep(1000);
															continue;
														}
														else {
															int real_member_num = atoi(member_num);
															if (real_member_num > search_member_num || real_member_num < 1) {
																printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
																Sleep(1000);
																continue;
															}
															else {
																real_member_num = real_member_num - 1;
																int select_member_num = search_member_num_arr[real_member_num];
																if (select_member_num == user_masterfile_idx) {
																	printf("�ڽſ� ���ؼ� ����� �������� �ʽ��ϴ�.");
																	Sleep(1000);
																	break;

																}
																char* select_member_id = user.masterfileData[select_member_num][0];
																char* select_member_name = user.masterfileData[select_member_num][2];
																while (1) {
																	system("cls");
																	printf("\n");
																	printf("��ɾ�(\'\'�����ϰ� �Է�) \t ���� \n\n");
																	printf("\'add\' or \'a\' \t\t\t �ڽ��� ����ó�� �߰��մϴ�. \n");
																	printf("\'delete\' or \'d\' \t\t �ڽ��� ����ó���� �����մϴ�. \n");
																	printf("\'show\' or \'s\' \t\t\t ȸ���� �ڼ��� ������ �����ݴϴ�. \n");
																	printf("\'permission\' or \'pe\' \t\t ȸ���� ������ �����մϴ�. \n");
																	printf("\'nickname\' or \'n\' \t\t ȸ���� �г����� ����/�����մϴ�. \n");
																	printf("\'back\' or \'b\' \t\t\t ����ȭ������ ���ư��ϴ�. \n\n");
																	printf("%s\'s PhoneBook > ", user.name);
																	char sub_menu_temp[STR_SIZE];
																	char* sub_menu;
																	int sub_menu_arr_length = 0;
																	int sub_menu_check = get_char_input(sub_menu_temp, &sub_menu_arr_length);
																	if (sub_menu_check != 0) {
																		printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
																		Sleep(1000);
																		continue;
																	}
																	else {
																		sub_menu = (char*)malloc(sizeof(char) * (sub_menu_arr_length + 1));
																		strcpy(sub_menu, sub_menu_temp);
																		int real_sub_menu_length = GetStringLength(sub_menu);
																		//�����ּҷϿ� ȸ�� �߰�
																		if (strcmp(sub_menu, "add") == 0 || strcmp(sub_menu, "a") == 0) {

																			if (user.friendNum == 100) {
																				printf("���̻� �����ּҷϿ� ȸ���� �߰��� �� �����ϴ�.");
																				Sleep(1000);
																				continue;
																			}
																			int adl_flag = 0;
																			for (int i = 0; i < user.friendNum; i++) {
																				if (strcmp(select_member_id, user_adl[i].textName) == 0) {
																					adl_flag = 1;
																					break;
																				}
																			}
																			if (adl_flag == 1) {
																				printf("�̹� �����ּҷϿ� �����ϴ� ȸ���Դϴ�.");
																				Sleep(1000);
																				continue;
																			}
																			else {
																				strcpy(user_adl[user.friendNum].textName, select_member_id);
																				strcpy(user_adl[user.friendNum].auth, "x");
																				strcpy(user_adl[user.friendNum].nick, "\0");
																				user.friendNum++;
																				printf("���������� �����ּҷϿ� ȸ���� �߰��Ͽ����ϴ�.");
																				Sleep(1000);
																				continue;
																			}
																		}
																		//�����ּҷϿ� ȸ������
																		else if (strcmp(sub_menu, "delete") == 0 || strcmp(sub_menu, "d") == 0) {
																			if (user.friendNum == 0) {
																				printf("���̻� �����ּҷϿ� ������ ȸ���� �������� �ʽ��ϴ�.");
																				Sleep(1000);
																				continue;
																			}
																			int adl_flag = 0;
																			int idx = 0;
																			for (int i = 0; i < user.friendNum; i++) {
																				if (strcmp(select_member_id, user_adl[i].textName) == 0) {
																					idx = i;
																					adl_flag = 1;
																					break;
																				}
																			}
																			if (adl_flag == 1) {
																				memmove(user_adl + idx, user_adl + idx + 1, sizeof(adressList));
																				user.friendNum--;
																				printf("���������� �����ּҷϿ��� ȸ���� �����Ͽ����ϴ�.");
																				Sleep(1000);
																				continue;
																			}
																			else {
																				printf("�����ּҷϿ� �������� �ʴ� ȸ���Դϴ�.");
																				Sleep(1000);
																				continue;
																			}

																		}
																		//������ ȸ���� ���� ����
																		else if (strcmp(sub_menu, "show") == 0 || strcmp(sub_menu, "s") == 0) {
																			personalData select_memeber;
																			adressList select_member_adl[MEMBER_SIZE];
																			init(&select_memeber, pernum);
																			readPersonalData(select_member_adl, &select_memeber, select_member_id);
																			int idx = 0;
																			int adl_flag = 0;
																			for (int i = 0; i < select_memeber.friendNum; i++) {
																				if (strcmp(user.id, select_member_adl[i].textName) == 0) {
																					adl_flag = 1;
																					idx = i;
																					break;
																				}
																			}
																			if (adl_flag == 1) {
																				system("cls");
																				printf("\n���� �ּҷϿ� �߰��Ǿ� �ִ� ȸ���Դϴ�.\n");
																				printf("\n�̸�: %s\n", select_memeber.name);
																				printf("��ȭ��ȣ: %s\n", select_memeber.phoneNum);
																				if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																					printf("����: O\n");
																				}
																				else {
																					printf("����: X\n");
																				}
																				if (select_memeber.birthdisc == 3) {
																					printf("�������: %s\n", select_memeber.birth);
																				}
																				else if (select_memeber.birthdisc == 2) {
																					if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																						printf("�������: %s\n", select_memeber.birth);
																					}
																					else {
																						printf("�������: X\n");
																					}
																				}
																				else {
																					printf("�������: X\n");
																				}

																				if (select_memeber.genderdisc == 3) {
																					printf("����: %s\n", select_memeber.gender);
																				}
																				else if (select_memeber.genderdisc == 2) {
																					if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																						printf("����: %s\n", select_memeber.gender);
																					}
																					else {
																						printf("����: X\n");
																					}
																				}
																				else {
																					printf("����: X\n");
																				}

																				if (select_memeber.addressdisc == 3) {
																					char temp_add[STR_SIZE];
																					make_print_address(temp_add, select_memeber.address);
																					printf("�ּ�: %s\n", temp_add);
																				}
																				else if (select_memeber.addressdisc == 2) {
																					if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																						char temp_add[STR_SIZE];
																						make_print_address(temp_add, select_memeber.address);
																						printf("�ּ�: %s\n", temp_add);
																					}
																					else {
																						printf("�ּ�: X\n");
																					}
																				}
																				else {
																					printf("�ּ�: X\n");
																				}

																				if (strlen(select_member_adl[idx].nick) != 0) {
																					printf("�г���: %s\n", select_member_adl[idx].nick);
																				}
																				else {
																					printf("�г���: X\n");
																				}
																				printf("Ű �Է½� ģ������ ȭ������ ���ư��ϴ�. >");
																				char show_menu_temp[STR_SIZE];
																				char* show_menu;
																				int show_menu_arr_length = 0;
																				int show_menu_check = get_char_input(show_menu_temp, &show_menu_arr_length);
																				if (show_menu_check == 0 || show_menu_check == 1) {
																					printf("ģ������ ȭ������ ���ư��ϴ�.");
																					Sleep(1000);
																					continue;
																				}
																			}
																			else {
																				system("cls");
																				printf("\n���� �ּҷϿ� ���� ȸ���Դϴ�.\n");
																				printf("\n�̸�: %s\n", select_memeber.name);
																				printf("��ȭ��ȣ: %s\n", select_memeber.phoneNum);
																				if (select_memeber.birthdisc == 3) {
																					printf("�������: %s\n", select_memeber.birth);
																				}
																				else {
																					printf("�������: X\n");
																				}
																				if (select_memeber.genderdisc == 3) {
																					printf("����: %s\n", select_memeber.gender);
																				}
																				else {
																					printf("����: X\n");
																				}
																				if (select_memeber.addressdisc == 3) {
																					char temp_add[STR_SIZE];
																					make_print_address(temp_add, select_memeber.address);
																					printf("�ּ�: %s\n", temp_add);
																				}
																				else {
																					printf("�ּ�: X\n");
																				}
																				printf("Ű �Է½� ģ������ ȭ������ ���ư��ϴ�. >");
																				char show_menu_temp[STR_SIZE];
																				char* show_menu;
																				int show_menu_arr_length = 0;
																				int show_menu_check = get_char_input(show_menu_temp, &show_menu_arr_length);
																				if (show_menu_check == 0 || show_menu_check == 1) {
																					printf("ģ������ ȭ������ ���ư��ϴ�.");
																					Sleep(1000);
																					continue;
																				}
																			}

																		}
																		//���ο��� ����
																		else if (strcmp(sub_menu, "permission") == 0 || strcmp(sub_menu, "pe") == 0) {
																			int adl_flag = 0;
																			int idx = 0;
																			for (int i = 0; i < user.friendNum; i++) {
																				if (strcmp(select_member_id, user_adl[i].textName) == 0) {
																					adl_flag = 1;
																					idx = i;
																					break;
																				}
																			}
																			if (adl_flag == 1) {
																				int permit_flag = 0;
																				if (strcmp(user_adl[idx].auth, "x") == 0) {
																					permit_flag = 1;
																				}
																				else if (strcmp(user_adl[idx].auth, "o") == 0) {
																					permit_flag = 2;
																				}

																				if (permit_flag == 1) {
																					strcpy(user_adl[idx].auth, "o");
																					printf("������ ȸ������ ������ �� �� �ִ� ������ �ο��մϴ�.");
																					Sleep(1000);
																					continue;
																				}
																				else if (permit_flag == 2) {
																					strcpy(user_adl[idx].auth, "x");
																					printf("������ ȸ������ ������ �� �� �ִ� ������ �����մϴ�.");
																					Sleep(1000);
																					continue;
																				}
																			}
																			else {
																				printf("�ּҷϿ� �������� �ʴ� ȸ���Դϴ�. �ּҷϿ� ���� �߰����ּ���.");
																				Sleep(1000);
																				continue;
																			}
																		}
																		//�г��� ����
																		else if (strcmp(sub_menu, "nickname") == 0 || strcmp(sub_menu, "n") == 0) {
																			int adl_flag = 0;
																			int idx = 0;
																			char nickname_temp[STR_SIZE];
																			char* nickname = NULL;
																			int nickname_arr_length = 0;
																			for (int i = 0; i < user.friendNum; i++) {
																				if (strcmp(select_member_id, user_adl[i].textName) == 0) {
																					adl_flag = 1;
																					idx = i;
																					break;
																				}
																			}
																			if (adl_flag == 1) {
																				while (1) {
																					system("cls");
																					if (strlen(user_adl[idx].nick) == 0) {
																						printf("�г����� �����մϴ�.\n");
																						printf("�г����� 1�� �̻�, 5�� �����̸� �θ��ڿ� �ѱ�, ���ڷ� �����Ǿ�� �մϴ�\n");
																						printf("�г��� > ");
																					}
																					else {
																						printf("�г����� �̹� �����մϴ�. �г����� �����մϴ�.\n");
																						printf("���� �г����� %s �Դϴ�.\n", user_adl[idx].nick);
																						printf("�г����� 1�� �̻�, 5�� �����̸� �θ��ڿ� �ѱ�, ���ڷ� �����Ǿ�� �մϴ�\n");
																						printf("�г��� > ");
																					}
																					int nickname_check = get_char_input(nickname_temp, &nickname_arr_length);
																					if (nickname_check != 0) {
																						printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
																						Sleep(1000);
																						continue;
																					}
																					else {
																						nickname = (char*)malloc(sizeof(char) * (nickname_arr_length + 1));
																						strcpy(nickname, nickname_temp);
																						int real_nickname_length = GetStringLength(nickname);
																						if (real_nickname_length > 5 || real_nickname_length < 1) {
																							printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
																							Sleep(1000);
																							continue;
																						}
																						else {
																							for (int i = 0; i < nickname_arr_length; i++) {
																								char check = nickname[i];
																								if (check >> 7) {
																									continue;
																								}
																								else if (isdigit(check) != 0) {
																									continue;
																								}
																								else if (isalpha(check) != 0) {
																									continue;
																								}
																								else {
																									flag = 1;
																									break;
																								}
																							}
																							if (flag == 1) {
																								printf("���Ŀ� ��߳��� �г����Դϴ�. �ٽ� �Է����ּ���.\n");
																								Sleep(1000);
																								continue;
																							}
																							else {
																								strcpy(user_adl[idx].nick, nickname);
																								printf("�г��� �����Ϸ�.\n");
																								Sleep(1000);
																								break;
																							}
																						}
																					}
																				}
																			}
																			else {
																				printf("�ּҷϿ� �������� �ʴ� ȸ���Դϴ�. �ּҷϿ� ���� �߰����ּ���.");
																				Sleep(1000);
																				continue;
																			}

																		}
																		//����ȭ������ ����
																		else if (strcmp(sub_menu, "back") == 0 || strcmp(sub_menu, "b") == 0) {
																			printf("����ȭ������ ���ư��ϴ�");
																			Sleep(1000);
																			break;
																		}
																		else {
																			printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
																			Sleep(1000);
																			continue;
																		}
																	}
																	break;
																}
															}
														}

													}
													break;
												}
											}
										}
										break;
									}
								}
								//���� �ּҷ� ���
								else if (strcmp(main_menu, "show") == 0 || strcmp(main_menu, "sh") == 0) {
									if (user.friendNum == 0) {
										printf("���� �����ּҷϿ� �߰��� ȸ���� �������� �ʽ��ϴ�.");
										Sleep(1000);
										continue;
									}
									while (1) {
										system("cls");
										printf("%s`s PhoneBook -----------------------------------------------------\n", user.name);
										for (int i = 0; i < user.friendNum; i++) {
											char* mem_id = user_adl[i].textName;
											int mem_flag = 0;
											personalData mem;
											adressList mem_adl[MEMBER_SIZE];
											init(&mem, pernum);
											readPersonalData(mem_adl, &mem, mem_id);
											for (int j = 0; j < mem.friendNum; j++) {
												if (strcmp(user.id, mem_adl[j].textName) == 0) {
													if (strcmp(mem_adl[j].auth, "o") == 0) {
														mem_flag = 1;
														break;
													}
												}
											}
											printf("�̸�: %s\n", mem.name);
											printf("��ȭ��ȣ: %s\n", mem.phoneNum);
											if (mem.birthdisc == 3) {
												printf("�������: %s\n", mem.birth);
											}
											else if (mem.birthdisc == 2) {
												if (mem_flag == 1) {
													printf("�������: %s\n", mem.birth);
												}
												else {
													printf("�������: X\n");
												}
											}
											else {
												printf("�������: X\n");
											}

											if (mem.genderdisc == 3) {
												printf("����: %s\n", mem.gender);
											}
											else if (mem.genderdisc == 2) {
												if (mem_flag == 1) {
													printf("����: %s\n", mem.gender);
												}
												else {
													printf("����: X\n");
												}
											}
											else {
												printf("����: X\n");
											}

											if (mem.addressdisc == 3) {
												printf("�ּ�: %s\n", mem.address);
											}
											else if (mem.addressdisc == 2) {
												if (mem_flag == 1) {
													printf("�ּ�: %s\n", mem.address);
												}
												else {
													printf("�ּ�: X\n");
												}
											}
											else {
												printf("�ּ�: X\n");
											}
											if (strlen(user_adl[i].nick) == 0) {
												printf("�г���: X\n");
											}
											else {
												printf("�г���: %s\n", user_adl[i].nick);
											}
											printf("\n");
										}
										printf("---------------------------------------------------------------------\n");
										printf("Ű �Է½�  ����ȭ������ ���ư��ϴ�. >");
										char phone_book_menu_temp[STR_SIZE];
										char* phone_book_menu;
										int phone_book_menu_arr_length = 0;
										int phone_book_menu_check = get_char_input(phone_book_menu_temp, &phone_book_menu_arr_length);
										if (phone_book_menu_check == 0 || phone_book_menu_check == 1) {
											printf("���� ȭ������ ���ư��ϴ�.");
											Sleep(1000);
											break;
										}
									}

								}
								//������������
								else if (strcmp(main_menu, "change") == 0 || strcmp(main_menu, "c") == 0) {
									while (1) {
										system("cls");
										printf("\n <��������>\n");
										printf("�̸�: %s\n", user.name);
										printf("��ȭ��ȣ: %s\n", user.phoneNum);
										if (user.birthdisc == 0) {
											printf("�������: X\n");
										}
										else if (user.birthdisc == 1) {
											printf("�������: %s <�����>\n", user.birth);
										}
										else if (user.birthdisc == 2) {
											printf("�������: %s <���ð���>\n", user.birth);
										}
										else if (user.birthdisc == 3) {
											printf("�������: %s <��ü����>\n", user.birth);
										}
										else {
											printf("�������: X\n");
										}

										if (user.genderdisc == 0) {
											printf("����: X\n");
										}
										else if (user.genderdisc == 1) {
											printf("����: %s <�����>\n", user.gender);
										}
										else if (user.genderdisc == 2) {
											printf("����: %s <���ð���>\n", user.gender);
										}
										else if (user.genderdisc == 3) {
											printf("����: %s <��ü����>\n", user.gender);
										}
										else {
											printf("����: X\n");
										}

										if (user.addressdisc == 0) {
											printf("�ּ�: X\n");
										}
										else if (user.addressdisc == 1) {
											char temp_add[STR_SIZE];
											make_print_address(temp_add, user.address);
											printf("�ּ�: %s  <�����>\n", temp_add);
										}
										else if (user.addressdisc == 2) {
											char temp_add[STR_SIZE];
											make_print_address(temp_add, user.address);
											printf("�ּ�: %s  <���ð���>\n", temp_add);
										}
										else if (user.addressdisc == 3) {
											char temp_add[STR_SIZE];
											make_print_address(temp_add, user.address);
											printf("�ּ�: %s  <��ü����>\n", temp_add);
										}
										else {
											printf("�ּ�: X\n");
										}
										printf("\n��ɾ�(\'\'�����ϰ� �Է�) \t ���� \n\n");
										printf("\'name\' \'����\' \t\t ���� �̸��� \'����\'�� �����մϴ�.\n");
										printf("\'phone\' \'����\' \t\t ���� ��ȭ��ȣ�� \'����\'�� �����մϴ�.\n");
										printf("\'birth\' \'����\' \t\t ���� ��������� \'����\'�� �����մϴ�.\n");
										printf("\'gender\' \'����\' \t ���� ������ \'����\'�� �����մϴ�.\n");
										printf("\'address\' \'����\' \t ���� �ּҸ� \'����\'�� �����մϴ�.\n");
										printf("\'back\'  \t\t ����ȭ������ ���ư��ϴ�. \n\n");
										printf("���� ��ɾ�� �������������� �����ϴ� ��ɾ�� \'����\'�� �Ʒ��� ���� �ǹ̸� �����ϴ�.\n\n");
										printf("\'1\' : �����   \'2\' : ���ð���   \'3\' : ��ü����\n\n");
										printf("\'birthauth\' \'����\' \t\t ��������� ���������� �����մϴ�.\n");
										printf("\'genderauth\' \'����\' \t\t ������ ���������� �����մϴ�.\n");
										printf("\'addressauth\' \'����\' \t\t �ּ��� ���������� �����մϴ�.\n\n");
										printf(" %s\'s PhoneBook > ", user.name);
										char sub_menu_temp[STR_SIZE];
										char* sub_menu;
										int sub_menu_arr_length = 0;
										int sub_menu_check = get_char_input(sub_menu_temp, &sub_menu_arr_length);
										if (sub_menu_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											sub_menu = (char*)malloc(sizeof(char) * (sub_menu_arr_length + 1));
											strcpy(sub_menu, sub_menu_temp);
											int real_sub_menu_length = GetStringLength(sub_menu);
											char temp_sub_menu[STR_SIZE];
											strcpy(temp_sub_menu, sub_menu);
											char* t1 = strtok(sub_menu, " ");
											char* factor = strtok(NULL, " ");
											if (strcmp(sub_menu, "back") == 0) {
												printf("�������������� �����մϴ�.");
												Sleep(1000);
												break;
											}
											if (factor == NULL) {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											if (strcmp(t1, "name") == 0) {
												int factor_name_check = check_name(factor);
												if (factor_name_check == 1) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													strcpy(user.name, factor);
													strcpy(user.masterfileData[user_masterfile_idx][0], factor);
													printf("�̸��� �����Ͽ����ϴ�.");
													Sleep(1000);
													continue;
												}
											}
											else if (strcmp(t1, "phone") == 0) {
												int factor_phone_num_check = check_phone_num(factor, user.masterfileData, pernum);
												if (factor_phone_num_check == 1) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else if (factor_phone_num_check == 2) {
													printf("�̹� �����ϴ� ��ȣ�Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													int factor_phone_num_length = strlen(factor);
													if (factor_phone_num_length == 11) {
														strcpy(user.phoneNum, factor);
														strcpy(user.masterfileData[user_masterfile_idx][3], factor);
														printf("��ȭ��ȣ�� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (factor_phone_num_length == 13) {
														char temp_phone_num[12];
														int j = 0;
														for (int i = 0; i < factor_phone_num_length; i++) {
															if (i == 3 || i == 8) {
																continue;
															}
															else {
																temp_phone_num[j] = factor[i];
																j++;
															}
														}
														temp_phone_num[11] = '\0';
														strcpy(user.phoneNum, temp_phone_num);
														strcpy(user.masterfileData[user_masterfile_idx][3], temp_phone_num);
														printf("��ȭ��ȣ�� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "birth") == 0) {
												int factor_birth_check = check_birth(factor);
												if (factor_birth_check == 1) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													if (user.birthdisc == 0) {
														user.birth = (char*)malloc(sizeof(char) * 10);
														user.birthdisc = 1;
														strcpy(user.birth, factor);
														user.dataNum++;
														printf("��������� �Է��Ͽ����ϴ�. �������������� ������� �����˴ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (factor_birth_check == 2) {
														char temp_birthday[7];
														int j = 2;
														for (int i = 0; i < 7; i++) {
															if (factor[j] == '-') {
																i--;
															}
															else {
																temp_birthday[i] = factor[j];
															}
															j++;
														}
														temp_birthday[6] = '\0';
														strcpy(user.birth, temp_birthday);
														printf("��������� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else {
														strcpy(user.birth, factor);
														printf("��������� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "gender") == 0) {
												int factor_gender_check = check_gender(factor);
												if (factor_gender_check == 1) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													if (user.genderdisc == 0) {
														user.gender = (char*)malloc(sizeof(char) * 3);
														user.genderdisc = 1;
														if (factor_gender_check == 2) {
															strcpy(user.gender, "����");
														}
														else if (factor_gender_check == 3) {
															strcpy(user.gender, "����");
														}
														user.dataNum++;
														printf("������ �Է��Ͽ����ϴ�. �������������� ������� �����˴ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (factor_gender_check == 2) {
														strcpy(user.gender, "����");
														printf("������ �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (factor_gender_check == 3) {
														strcpy(user.gender, "����");
														printf("������ �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "address") == 0) {
												char temp_arr[STR_SIZE];
												int i = 0;
												for (i = 0; i < strlen(temp_sub_menu); i++) {
													if (temp_sub_menu[i] == ' ') {
														break;
													}
												}
												int k = 0;
												for (int j = i + 1; j < strlen(temp_sub_menu); j++) {
													temp_arr[k] = temp_sub_menu[j];
													k++;
												}
												temp_arr[k] = '\0';
												int factor_address_check = check_address(temp_arr);
												if (factor_address_check == 1) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													char temp_add[STR_SIZE];
													del_space(temp_add, temp_arr);
													if (user.addressdisc == 0) {
														user.address = (char*)malloc(sizeof(char) * 61);
														user.addressdisc = 1;
														strcpy(user.address, temp_add);
														user.dataNum++;
														printf("�ּҸ� �Է��Ͽ����ϴ�. �������������� ������� �����˴ϴ�.");
														Sleep(1000);
														continue;
													}
													else {
														strcpy(user.address, temp_add);
														printf("�ּҸ� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "birthauth") == 0) {
												if (user.birthdisc == 0) {
													printf("��������� �Էµ��� �ʾҽ��ϴ�. ���� ��������� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													if (strcmp(factor, "1") == 0) {
														user.birthdisc = 1;
														printf("��������� ������� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "2") == 0) {
														user.birthdisc = 2;
														printf("��������� ���ð����� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "3") == 0) {
														user.birthdisc = 3;
														printf("��������� ��ü������ �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else {
														printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "genderauth") == 0) {
												if (user.genderdisc == 0) {
													printf("������ �Էµ��� �ʾҽ��ϴ�. ���� ������ �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													if (strcmp(factor, "1") == 0) {
														user.genderdisc = 1;
														printf("������ ������� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "2") == 0) {
														user.genderdisc = 2;
														printf("������ ���ð����� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "3") == 0) {
														user.genderdisc = 3;
														printf("������ ��ü������ �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else {
														printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "addressauth") == 0) {
												if (user.addressdisc == 0) {
													printf("�ּҰ� �Էµ��� �ʾҽ��ϴ�. ���� �ּҸ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													if (strcmp(factor, "1") == 0) {
														user.addressdisc = 1;
														printf("�ּҸ� ������� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "2") == 0) {
														user.addressdisc = 2;
														printf("�ּҸ� ���ð����� �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "3") == 0) {
														user.addressdisc = 3;
														printf("�ּҸ� ��ü������ �����Ͽ����ϴ�.");
														Sleep(1000);
														continue;
													}
													else {
														printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
												}
											}
											else {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
										}
									}
								}
								//���α׷� ����
								else if (strcmp(main_menu, "quit") == 0 || strcmp(main_menu, "q") == 0) {
									printf("�α׾ƿ� �մϴ�.");
									login_flag = 3;
									savePersonalData(&user, user_adl);
									Sleep(1000);
									break;
								}
								else {
									printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
									Sleep(1000);
									continue;
								}
							}
						}
					}
					if (login_flag == 3) {
						continue;
					}
				}
				//ȸ������ ����
				else if (strcmp(menu, "2") == 0) {
					while (1) {
						personalData join;
						adressList join_adl[MEMBER_SIZE];
						init(&join, pernum);
						readMasterData(&join, pernum);
						int datanum = 0;
						//���̵� ����
						while (1) {
							//���̵� ����
							char id_temp[STR_SIZE];
							char* id = NULL;
							int id_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("����Ͻ� ���̵� �Է����ּ���.\n");
							printf("���̵�� 6�� �̻� 10�� ������ �θ��� �ҹ��ڿ� ���ڷ� �����Ǿ�� �մϴ�.\n");
							printf("���̵� > ");
							int id_check = get_char_input(id_temp, &id_arr_length);
							if (id_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								id = (char*)malloc(sizeof(char) * (id_arr_length + 1));
								strcpy(id, id_temp);
								int real_id_length = GetStringLength(id);
								if (real_id_length > 10 || real_id_length < 6) {
									printf("���̵��� ���̰� ��Ģ�� ����˴ϴ�. �ٽ� �Է����ּ���");
									Sleep(1000);
									continue;
								}
								else {
									int alphabet = 0;
									int num = 0;
									if (seekCharId(join.masterfileData, id, pernum) != NULL) {
										flag = 2;
									}
									for (int i = 0; i < id_arr_length; i++) {
										char check = id[i];
										if (check >> 7) {
											flag = 1;
										}
										else if (isalpha(check) != 0) {
											if (islower(check) != 0) {
												alphabet++;
												continue;
											}
											else {
												flag = 1;
											}
										}
										else if (isdigit(check) != 0) {
											num++;
											continue;
										}
										else {
											flag = 1;
										}
									}
									if ((flag == 1) || (num == 0) || (alphabet == 0)) {
										printf("���Ŀ� ��߳��� ���̵��Դϴ�. �ٽ� �Է����ּ���.\n");
										Sleep(1000);
										continue;
									}
									else if (flag == 2) {
										printf("�̹� �����ϴ� ���̵��Դϴ�. �ٽ� �Է����ּ���.\n");
										Sleep(1000);
										continue;
									}
									else {
										join.id = id;
										printf("���̵� �����Ϸ�!");
										Sleep(1000);
										break;
									}
								}
							}

						}
						//��й�ȣ ����
						while (1) {
							//��й�ȣ ����
							char pw_temp[STR_SIZE];
							char* pw = NULL;
							int pw_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("����Ͻ� ��й�ȣ�� �Է����ּ���.\n");
							printf("��й�ȣ�� 8�� �̻� 12�� ������ �θ��ڿ� ���ڷ� �����Ǿ�� �մϴ�.\n");
							printf("��й�ȣ > ");
							int pw_check = get_char_input(pw_temp, &pw_arr_length);
							if (pw_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								pw = (char*)malloc(sizeof(char) * (pw_arr_length + 1));
								strcpy(pw, pw_temp);
								int real_pw_length = GetStringLength(pw);
								if (real_pw_length > 12 || real_pw_length < 8) {
									printf("��й�ȣ�� ���̰� ��Ģ�� ����˴ϴ�. �ٽ� �Է����ּ���");
									Sleep(1000);
									continue;
								}
								else {
									int alphabet = 0;
									int num = 0;
									for (int i = 0; i < pw_arr_length; i++) {
										char check = pw[i];
										if (check >> 7) {
											flag = 1;
										}
										else if (isalpha(check) != 0) {
											alphabet++;
											continue;
										}
										else if (isdigit(check) != 0) {
											num++;
											continue;
										}
										else {
											flag = 1;
										}
									}
									if ((flag == 1) || (num == 0) || (alphabet == 0)) {
										printf("���Ŀ� ��߳��� ��й�ȣ�Դϴ�. �ٽ� �Է����ּ���.\n");
										Sleep(1000);
										continue;
									}
									else {
										while (1) {
											system("cls");
											printf("��й�ȣ�� �����մϴ�\n");
											printf("��й�ȣ�� 8�� �̻� 12�� ������ �θ��ڿ� ���ڷ� �����Ǿ�� �մϴ�.\n");
											printf("��й�ȣ > %s\n", pw);
											printf(" * �������� ��й�ȣ �Դϴ�!\n");
											printf("��й�ȣ 2�� Ȯ�� > ");
											char check_pw_temp[STR_SIZE];
											char* check_pw = NULL;
											int check_pw_arr_length = 0;
											int flag = 0;
											int check_pw_check = get_char_input(check_pw_temp, &check_pw_arr_length);
											if (pw_check != 0) {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {
												check_pw = (char*)malloc(sizeof(char) * (check_pw_arr_length + 1));
												strcpy(check_pw, check_pw_temp);
												if (strcmp(pw, check_pw) == 0) {
													join.password = pw;
													printf("��й�ȣ �����Ϸ�!");
													Sleep(1000);
													break;
												}
												else {
													printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
											}
										}
									}
									break;
								}
							}
						}
						//�̸� �Է�
						while (1) {
							//�̸��Է�
							char name_temp[STR_SIZE];
							char* name = NULL;
							int name_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("����Ͻ� �̸��� �Է����ּ���.\n");
							printf("�̸��� 2�� �̻� 6�� �����Դϴ�.\n");
							printf("�̸� > ");
							int name_check = get_char_input(name_temp, &name_arr_length);
							if (name_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								name = (char*)malloc(sizeof(char) * (name_arr_length + 1));
								strcpy(name, name_temp);
								int real_name_length = GetStringLength(name);
								if (real_name_length > 6 || real_name_length < 2) {
									printf("�̸��� ���̰� ��Ģ�� ����˴ϴ�. �ٽ� �Է����ּ���");
									Sleep(1000);
									continue;
								}
								else {
									for (int i = 0; i < name_arr_length; i++) {
										char check = name[i];
										if (check >> 7) {
											continue;
										}
										else if (isdigit(check) != 0) {
											continue;
										}
										else if (isalpha(check) != 0) {
											continue;
										}
										else {
											flag = 1;
											break;
										}
									}
								}
								if (flag == 1) {
									printf("���Ŀ� ��߳��� �̸��Դϴ�. �ٽ� �Է����ּ���.\n");
									Sleep(1000);
									continue;
								}
								else {
									join.name = name;
									printf("�̸� �����Ϸ�!");
									Sleep(1000);
									break;
								}
							}
						}
						//��ȭ��ȣ �Է�
						while (1) {
							//��ȭ��ȣ �Է�
							char phone_num_temp[STR_SIZE];
							char* phone_num = NULL;
							int phone_num_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("����Ͻ� ��ȭ��ȣ�� �Է����ּ���.\n");
							printf("���� �Է��Ͻô� ��ȭ��ȣ�� �� ���α׷��� ȸ������ �����Ǵ� ��ȭ��ȣ�Դϴ�.\n");
							printf("ex) 010-1234-7688, 01012347688\n");
							printf("��ȭ��ȣ > ");
							int phone_num_check = get_char_input(phone_num_temp, &phone_num_arr_length);
							if (phone_num_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								phone_num = (char*)malloc(sizeof(char) * (phone_num_arr_length + 1));
								strcpy(phone_num, phone_num_temp);
								int real_phone_num_length = GetStringLength(phone_num);
								if ((real_phone_num_length == 13 || real_phone_num_length == 11) != 1) {
									printf("��ȭ��ȣ�� ���̰� ��Ģ�� ����˴ϴ�. �ٽ� �Է����ּ���");
									Sleep(1000);
									continue;
								}
								else {
									for (int i = 0; i < 3; i++) {
										char check = phone_num[i];
										if (i == 0 || i == 2) {
											if (phone_num[i] == '0') {
												continue;
											}
											else {
												flag = 1;
												break;
											}

										}
										else if (i == 1) {
											if (phone_num[i] == '1') {
												continue;
											}
											else {
												flag = 1;
												break;
											}
										}
									}
									if (flag != 1) {
										if (phone_num_arr_length == 13) {
											if (phone_num[3] == '-' && phone_num[8] == '-') {
												for (int i = 0; i < phone_num_arr_length; i++) {
													if (i == 3 || i == 8)continue;
													char check = phone_num[i];
													if (check >> 7) {
														flag = 1;
														break;
													}
													else if (isdigit(check) != 0) {
														continue;
													}
													else {
														flag = 1;
														break;
													}
												}
												char temp_phone_num[12];
												int j = 0;
												for (int i = 0; i < phone_num_arr_length; i++) {
													if (i == 3 || i == 8) {
														continue;
													}
													else {
														temp_phone_num[j] = phone_num[i];
														j++;
													}
												}
												temp_phone_num[11] = '\0';
												if (seekCharPhone(join.masterfileData, temp_phone_num, pernum) != NULL) {
													flag = 2;
												}
											}
											else {
												flag = 1;
											}
										}
										else if (phone_num_arr_length == 11) {
											for (int i = 0; i < phone_num_arr_length; i++) {
												char check = phone_num[i];
												if (check >> 7) {
													flag = 1;
													break;
												}
												else if (isdigit(check) != 0) {
													continue;
												}
												else {
													flag = 1;
													break;
												}
											}
											if (seekCharPhone(join.masterfileData, phone_num, pernum) != NULL) {
												flag = 2;
											}
										}
									}
									if (flag == 1) {
										printf("���Ŀ� ��߳��� ��ȭ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n");
										Sleep(1000);
										continue;
									}
									else if (flag == 2) {
										printf("�̹� �����ϴ� ��ȭ��ȣ�Դϴ�. �ٽ� �Է����ּ���.\n");
										Sleep(1000);
										continue;
									}
									else {
										if (phone_num_arr_length == 11) {
											join.phoneNum = phone_num;
											printf("��ȭ��ȣ �����Ϸ�!");
											Sleep(1000);
											break;
										}
										else if (phone_num_arr_length == 13) {
											char temp_phone_num[12];
											int j = 0;
											for (int i = 0; i < phone_num_arr_length; i++) {
												if (i == 3 || i == 8) {
													continue;
												}
												else {
													temp_phone_num[j] = phone_num[i];
													j++;
												}
											}
											temp_phone_num[11] = '\0';
											join.phoneNum = temp_phone_num;
											printf("��ȭ��ȣ �����Ϸ�!");
											Sleep(1000);
											break;
										}
									}
								}
							}
						}
						//������� �Է�
						while (1) {
							//������� �Է�
							char birthday_temp[STR_SIZE];
							char* birthday;
							char temp_birthday[7];
							int birthday_arr_length = 0;
							int flag = 0;
							int birthday_flag = 0;
							system("cls");
							printf("��������Է� ���θ� �����մϴ�\n");
							printf(" 1) ������� �Է�\n");
							printf(" 2) ������� �Է� X\n");
							printf(" �Է¿��� > ");
							char birthday_menu_temp[STR_SIZE];
							char* birthday_menu;
							int birthday_menu_arr_length = 0;
							int birthday_menu_check = get_char_input(birthday_menu_temp, &birthday_menu_arr_length);
							if (birthday_menu_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								birthday_menu = (char*)malloc(sizeof(char) * (birthday_menu_arr_length + 1));
								strcpy(birthday_menu, birthday_menu_temp);
								int real_birthday_menu_length = GetStringLength(birthday_menu);
								if (real_birthday_menu_length != 1) {
									printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
									Sleep(1000);
									continue;
								}
								else {
									for (int i = 0; i < birthday_menu_arr_length; i++) {
										char check = birthday_menu[i];
										if (check >> 7) {
											flag = 1;
											break;
										}
										else if (birthday_menu[i] == '2') {
											flag = 2;
											break;
										}
										else if (birthday_menu[i] == '1') {
											flag = 0;
											break;
										}
										else {
											flag = 1;
											break;
										}
									}
								}
								if (flag == 1) {
									printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
									Sleep(1000);
									continue;
								}
								else if (flag == 2) {
									join.birthdisc = 0;
									printf("������� �Է��� �ǳʶٰڽ��ϴ�.");
									Sleep(1000);
									break;
								}
								else if (flag == 0) {
									while (1) {
										system("cls");
										printf("��������� �Է��ϼ���\n");
										printf("ex) 990123   1999-01-23\n");
										printf("������� >");
										int birthday_check = get_char_input(birthday_temp, &birthday_arr_length);
										if (birthday_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											birthday = (char*)malloc(sizeof(char) * (birthday_arr_length + 1));
											strcpy(birthday, birthday_temp);
											int real_birthday_length = GetStringLength(birthday);
											if (!(real_birthday_length == 6 || real_birthday_length == 10)) {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {
												if (real_birthday_length == 6) {
													birthday_flag = 1;
													for (int i = 0; i < birthday_arr_length; i++) {
														char check = birthday[i];
														if (check >> 7) {
															flag = 1;
															break;
														}
														else if (isdigit(check) != 0) {
															continue;
														}
														else {
															flag = 1;
															break;
														}
													}

													if (!(birthday[2] == '0' || birthday[2] == '1')) {
														flag = 1;
													}
													else {
														if (birthday[2] == '0') {
															if (birthday[3] == '0') {
																flag = 1;
															}
														}
														else if (birthday[2] == '1') {
															if (!(birthday[3] == '0' || birthday[3] == '1' || birthday[3] == '2')) {
																flag = 1;
															}
														}
													}

													if (!(birthday[4] == '0' || birthday[4] == '1' || birthday[4] == '2' || birthday[4] == '3')) {
														flag = 1;
													}
													else {
														if (birthday[4] == '0') {
															if (birthday[5] == '0') {
																flag = 1;
															}
														}
														else if (birthday[4] == '3') {
															if (birthday[2] == '0' && birthday[3] == '2') {
																flag = 1;
															}
															else {
																char thirtyone[] = "0123578";
																char check_day = birthday[5];
																char check_month = birthday[3];
																if (check_day == '1') {
																	char* p;
																	p = strchr(thirtyone, check_month);
																	if (p == NULL) {
																		flag = 1;
																	}
																}
															}
														}
													}

													if (birthday[2] == '0' && birthday[3] == '2') {
														char temp_year[3];
														strncpy(temp_year, birthday, 2);
														int check_year = atoi(temp_year);
														if (check_year > 20) {
															char year[5] = "19";
															strcat(year, temp_year);
															int real_year = atoi(year);
															if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
																if (birthday[4] == '2' && birthday[5] == '9') {
																	flag = 1;
																}
															}
														}
														else {
															char year[5] = "20";
															strcat(year, temp_year);
															int real_year = atoi(year);
															if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
																if (birthday[4] == '2' && birthday[5] == '9') {
																	flag = 1;
																}
															}
														}
													}
												}
												else if (real_birthday_length == 10) {
													birthday_flag = 2;
													if (!(birthday[4] == '-' && birthday[7] == '-')) {
														flag = 1;
													}
													else {
														for (int i = 0; i < birthday_arr_length; i++) {
															if (i == 4 || i == 7)continue;
															char check = birthday[i];
															if (check >> 7) {
																flag = 1;
																break;
															}
															else if (isdigit(check) != 0) {
																continue;
															}
															else {
																flag = 1;
																break;
															}
														}
														char year_check[5];
														strncpy(year_check, birthday, 4);
														year_check[4] = '\0';
														int a = atoi(year_check);
														if (a < 1921 || a > 2020) {
															flag = 1;
														}
														int j = 2;
														for (int i = 0; i < 7; i++) {
															if (birthday[j] == '-') {
																i--;
															}
															else {
																temp_birthday[i] = birthday[j];
															}
															j++;
														}
														temp_birthday[6] = '\0';
														if (!(temp_birthday[2] == '0' || temp_birthday[2] == '1')) {
															flag = 1;
														}
														else {
															if (temp_birthday[2] == '0') {
																if (temp_birthday[3] == '0') {
																	flag = 1;
																}
															}
															else if (temp_birthday[2] == '1') {
																if (!(temp_birthday[3] == '0' || temp_birthday[3] == '1' || temp_birthday[3] == '2')) {
																	flag = 1;
																}
															}
														}

														if (!(temp_birthday[4] == '0' || temp_birthday[4] == '1' || temp_birthday[4] == '2' || temp_birthday[4] == '3')) {
															flag = 1;
														}
														else {
															if (temp_birthday[4] == '0') {
																if (temp_birthday[5] == '0') {
																	flag = 1;
																}
															}
															else if (temp_birthday[4] == '3') {
																if (temp_birthday[2] == '0' && temp_birthday[3] == '2') {
																	flag = 1;
																}
																else {
																	char thirtyone[] = "0123578";
																	char check_day = temp_birthday[5];
																	char check_month = temp_birthday[3];
																	if (check_day == '1') {
																		char* p;
																		p = strchr(thirtyone, check_month);
																		if (p == NULL) {
																			flag = 1;
																		}
																	}
																}
															}
														}

														if (temp_birthday[2] == '0' && temp_birthday[3] == '2') {
															char temp_year[3];
															strncpy(temp_year, temp_birthday, 2);
															int check_year = atoi(temp_year);
															if (check_year > 20) {
																char year[5] = "19";
																strcat(year, temp_year);
																int real_year = atoi(year);
																if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
																	if (temp_birthday[4] == '2' && temp_birthday[5] == '9') {
																		flag = 1;
																	}
																}
															}
															else {
																char year[5] = "20";
																strcat(year, temp_year);
																int real_year = atoi(year);
																if (!(((real_year % 4 == 0) && (real_year % 100 != 0)) || (real_year % 400 == 0))) {
																	if (temp_birthday[4] == '2' && temp_birthday[5] == '9') {
																		flag = 1;
																	}
																}
															}
														}
													}
												}
											}
										}
										if (flag == 1) {
											flag = 0;
											birthday_flag = 0;
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											if (birthday_flag == 1) {
												join.birth = birthday;
											}
											else if (birthday_flag == 2) {
												join.birth = temp_birthday;
											}
											datanum++;
											printf("������� �Է� �Ϸ�!");
											Sleep(1000);
											break;
										}
									}
									while (1) {
										char permission_menu_temp[STR_SIZE];
										char* permission_menu;
										int permission_menu_arr_length = 0;
										system("cls");
										printf("��������� �����Ͻðڽ��ϱ�?\n");
										printf(" 1) ��ü����\n");
										printf(" 2) ������ �ο��� ������Ը� ����\n");
										printf(" 3) �����\n");
										printf("�������� > ");
										int permission_menu_check = get_char_input(permission_menu_temp, &permission_menu_arr_length);
										if (permission_menu_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											permission_menu = (char*)malloc(sizeof(char) * (permission_menu_arr_length + 1));
											strcpy(permission_menu, permission_menu_temp);
											int real_permission_menu_length = GetStringLength(permission_menu);
											if (real_permission_menu_length != 1) {
												printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {
												for (int i = 0; i < permission_menu_arr_length; i++) {
													char check = permission_menu[i];
													if (check >> 7) {
														printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
													else if (permission_menu[i] == '1') {
														printf("��������� ��ü�����մϴ�.");
														join.birthdisc = 3;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '2') {
														printf("��������� ������ �ο��� ������Ը� �����մϴ�.");
														join.birthdisc = 2;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '3') {
														printf("��������� ������մϴ�.");
														join.birthdisc = 1;
														Sleep(1000);
														break;
													}
													else {
														printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
												}
											}
										}
										break;
									}
								}
							}
							break;
						}
						//���� �Է�
						while (1) {
							//���� �Է�
							char gender_temp[STR_SIZE];
							char* gender = NULL;
							int gender_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("�����Է� ���θ� �����մϴ�\n");
							printf(" 1) ���� �Է�\n");
							printf(" 2) ���� �Է� X\n");
							printf(" �Է¿��� > ");
							char gender_menu_temp[STR_SIZE];
							char* gender_menu;
							int gender_menu_arr_length = 0;
							int gender_menu_check = get_char_input(gender_menu_temp, &gender_menu_arr_length);
							if (gender_menu_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								gender_menu = (char*)malloc(sizeof(char) * (gender_menu_arr_length + 1));
								strcpy(gender_menu, gender_menu_temp);
								int real_gender_menu_length = GetStringLength(gender_menu);
								if (real_gender_menu_length != 1) {
									printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
									Sleep(1000);
									continue;
								}
								else {
									for (int i = 0; i < gender_menu_arr_length; i++) {
										char check = gender_menu[i];
										if (check >> 7) {
											flag = 1;
											break;
										}
										else if (gender_menu[i] == '2') {
											flag = 2;
											break;
										}
										else if (gender_menu[i] == '1') {
											flag = 0;
											break;
										}
										else {
											flag = 1;
											break;
										}
									}
								}
								if (flag == 1) {
									printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
									Sleep(1000);
									continue;
								}
								else if (flag == 2) {
									join.genderdisc = 0;
									printf("���� �Է��� �ǳʶٰڽ��ϴ�.");
									Sleep(1000);
									break;
								}
								else if (flag == 0) {
									while (1) {
										system("cls");
										printf("������ �Է��ϼ���\n");
										printf("ex) ��, ��   ����, ����   ����, ����\n");
										printf("���� >");
										int gender_check = get_char_input(gender_temp, &gender_arr_length);
										if (gender_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											gender = (char*)malloc(sizeof(char) * (gender_arr_length + 1));
											strcpy(gender, gender_temp);
											int real_gender_length = GetStringLength(gender);
											if (!(real_gender_length == 1 || real_gender_length == 2)) {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {

												if (strcmp(gender, "��") == 0 || strcmp(gender, "����") == 0 || strcmp(gender, "����") == 0) {
													gender = "����";
													join.gender = gender;
													datanum++;
													printf("������ �������� �����Ͽ����ϴ�");
													Sleep(1000);
													break;
												}
												else if (strcmp(gender, "��") == 0 || strcmp(gender, "����") == 0 || strcmp(gender, "����") == 0) {
													gender = "����";
													join.gender = gender;
													datanum++;
													printf("������ �������� �����Ͽ����ϴ�");
													Sleep(1000);
													break;
												}
												else {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}

											}
										}
									}
									while (1) {
										char permission_menu_temp[STR_SIZE];
										char* permission_menu;
										int permission_menu_arr_length = 0;
										system("cls");
										printf("������ �����Ͻðڽ��ϱ�?\n");
										printf(" 1) ��ü����\n");
										printf(" 2) ������ �ο��� ������Ը� ����\n");
										printf(" 3) �����\n");
										printf("�������� > ");
										int permission_menu_check = get_char_input(permission_menu_temp, &permission_menu_arr_length);
										if (permission_menu_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											permission_menu = (char*)malloc(sizeof(char) * (permission_menu_arr_length + 1));
											strcpy(permission_menu, permission_menu_temp);
											int real_permission_menu_length = GetStringLength(permission_menu);
											if (real_permission_menu_length != 1) {
												printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {
												for (int i = 0; i < permission_menu_arr_length; i++) {
													char check = permission_menu[i];
													if (check >> 7) {
														printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
													else if (permission_menu[i] == '1') {
														printf("������ ��ü�����մϴ�.");
														join.genderdisc = 3;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '2') {
														printf("������ ������ �ο��� ������Ը� �����մϴ�.");
														join.genderdisc = 2;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '3') {
														printf("������ ������մϴ�.");
														join.genderdisc = 1;
														Sleep(1000);
														break;
													}
													else {
														printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
												}
											}
										}
										break;
									}

								}
								break;
							}
							break;
						}
						//�ּ� �Է�
						while (1) {
							char address_temp[STR_SIZE];
							char* address = NULL;
							int address_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("�ּ��Է� ���θ� �����մϴ�\n");
							printf(" 1) �ּ� �Է�\n");
							printf(" 2) �ּ� �Է� X\n");
							printf(" �Է¿��� > ");
							char address_menu_temp[STR_SIZE];
							char* address_menu;
							int address_menu_arr_length = 0;
							int address_menu_check = get_char_input(address_menu_temp, &address_menu_arr_length);
							if (address_menu_check != 0) {
								printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
								Sleep(1000);
								continue;
							}
							else {
								address_menu = (char*)malloc(sizeof(char) * (address_menu_arr_length + 1));
								strcpy(address_menu, address_menu_temp);
								int real_address_menu_length = GetStringLength(address_menu);
								if (real_address_menu_length != 1) {
									printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
									Sleep(1000);
									continue;
								}
								else {
									for (int i = 0; i < address_menu_arr_length; i++) {
										char check = address_menu[i];
										if (check >> 7) {
											flag = 1;
											break;
										}
										else if (address_menu[i] == '2') {
											flag = 2;
											break;
										}
										else if (address_menu[i] == '1') {
											flag = 0;
											break;
										}
										else {
											flag = 1;
											break;
										}
									}
								}
								if (flag == 1) {
									printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
									Sleep(1000);
									continue;
								}
								else if (flag == 2) {
									join.addressdisc = 0;
									printf("�ּ� �Է��� �ǳʶٰڽ��ϴ�.");
									Sleep(1000);
									break;
								}
								else {
									while (1) {
										system("cls");
										printf("�ּҸ� �Է��ϼ���\n");
										printf("�ּ� >");
										int address_check = get_char_input(address_temp, &address_arr_length);
										if (address_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											address = (char*)malloc(sizeof(char) * (address_arr_length + 1));
											strcpy(address, address_temp);
											int real_address_length = GetStringLength(address);
											if (real_address_length < 2 || real_address_length > 30) {
												printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {
												int add_flag = 0;
												for (int i = 0; i < address_arr_length; i++) {
													char check = address[i];
													if (check >> 7) {
														continue;
													}
													else if (isalnum(check)) {
														continue;
													}
													else if (check == ' ') {
														continue;
													}
													else {
														add_flag = 1;
														break;
													}
												}
												if (add_flag == 1) {
													printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
													Sleep(1000);
													continue;
												}
												else {
													char temp_add[STR_SIZE];
													del_space(temp_add, address_temp);
													join.address = temp_add;
													datanum++;
													printf("�ּ� �Է¿Ϸ�!\n");
													Sleep(1000);
													break;
												}
											}
										}
									}
									while (1) {
										char permission_menu_temp[STR_SIZE];
										char* permission_menu;
										int permission_menu_arr_length = 0;
										system("cls");
										printf("�ּҸ� �����Ͻðڽ��ϱ�?\n");
										printf(" 1) ��ü����\n");
										printf(" 2) ������ �ο��� ������Ը� ����\n");
										printf(" 3) �����\n");
										printf("�������� > ");
										int permission_menu_check = get_char_input(permission_menu_temp, &permission_menu_arr_length);
										if (permission_menu_check != 0) {
											printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
											Sleep(1000);
											continue;
										}
										else {
											permission_menu = (char*)malloc(sizeof(char) * (permission_menu_arr_length + 1));
											strcpy(permission_menu, permission_menu_temp);
											int real_permission_menu_length = GetStringLength(permission_menu);
											if (real_permission_menu_length != 1) {
												printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
												Sleep(1000);
												continue;
											}
											else {
												for (int i = 0; i < permission_menu_arr_length; i++) {
													char check = permission_menu[i];
													if (check >> 7) {
														printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
													else if (permission_menu[i] == '1') {
														printf("�ּҸ� ��ü�����մϴ�.");
														join.addressdisc = 3;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '2') {
														printf("�ּҸ� ������ �ο��� ������Ը� �����մϴ�.");
														join.addressdisc = 2;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '3') {
														printf("�ּҸ� ������մϴ�.");
														join.addressdisc = 1;
														Sleep(1000);
														break;
													}
													else {
														printf("�߸��� �޴��Դϴ�. �ٽ� �Է����ּ���.");
														Sleep(1000);
														continue;
													}
												}
											}
										}
										break;
									}
								}
							}
							break;
						}
						join.dataNum = datanum;
						join.friendNum = 0;
						pernum++;
						savePernum(pernum);
						saveMasterData(&join);
						savePersonalData(&join, join_adl);
						break;
					}
					continue;
				}
				//���α׷� ����
				else if (strcmp(menu, "3") == 0) {
					printf("���α׷��� �����մϴ�.");
					Sleep(1000);
					break;
				}
				else {
					printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.");
					Sleep(1000);
					continue;
				}

			}
			break;
		}
	}
	printf("\n�Ϸ�!");
}

