#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "dataFunc.h"
#define STR_SIZE 100
#define MEMBER_SIZE 100

//버퍼 비우는 함수
void clearInputBuffer() {
	while (getchar() != '\n');
}

//한글포함하여 문자열 길이 구하는 함수
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

//사용자 입력 안전하게 받는 함수 리턴값 0일시 올바른 입력, 1일시 올바르지 않은 입력
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

//이름 문법검사 함수 리턴값 0일시 올바른 입력, 1일시 올바르지 않은 입력
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

//마스터 데이터에서 전화번호 찾는 함수
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

//전화번호 문법검사 함수 리턴값 0일시 올바른 입력, 1일시 올바르지 않은 입력, 2일시 중복
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

//생년월일 문법검사 함수 리턴값 0일시 올바른 입력, 1일시 올바르지 않은 입력, 2일시 2020-01-23 형식의 입력
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

//성별 문법검사 함수 리턴값 1일시 올바르지 않은 입력, 2일시 남성, 3일시 여성
int check_gender(char* gender) {
	int flag = 0;
	int real_gender_length = GetStringLength(gender);
	if (!(real_gender_length == 1 || real_gender_length == 2)) {
		flag = 1;
	}
	else {

		if (strcmp(gender, "남") == 0 || strcmp(gender, "남자") == 0 || strcmp(gender, "남성") == 0) {
			flag = 2;
		}
		else if (strcmp(gender, "여") == 0 || strcmp(gender, "여자") == 0 || strcmp(gender, "여성") == 0) {
			flag = 3;
		}
		else {
			flag = 1;
		}

	}
	return flag;
}

//주소 문법검사 함수 리턴값 0일시 올바른 입력, 1일시 올바르지 않은 입력
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

//마스터 데이터에서 아이디 찾는 함수
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

//마스터 데이터에서 비밀번호 찾는 함수
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
		printf(" 개인 주소록\n");
		printf("----------------\n");
		printf(" 1) 로그인\n");
		printf(" 2) 회원가입\n");
		printf(" 3) 프로그램 종료\n");
		printf("----------------\n");
		printf("메뉴를 선택하세요 > ");
		char menu_temp[STR_SIZE];
		char* menu;
		int menu_arr_length = 0;
		int menu_check = get_char_input(menu_temp, &menu_arr_length);
		if (menu_check != 0) {
			printf("잘못된 입력입니다. 다시 입력해주세요.");
			Sleep(1000);
			continue;
		}
		else {
			menu = (char*)malloc(sizeof(char) * (menu_arr_length + 1));
			strcpy(menu, menu_temp);
			int real_menu_length = GetStringLength(menu);
			if (real_menu_length != 1) {
				printf("잘못된 입력입니다. 다시 입력해주세요.");
				Sleep(1000);
				continue;
			}
			else {
				//로그인 시작
				if (strcmp(menu, "1") == 0) {
					if (pernum == 0) {
						printf("가입된 회원이 존재하지 않아 로그인을 할 수 없습니다.\n");
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
						printf("아이디는 6자 이상 10자 이하의 로마자 소문자와 숫자로 구성되어야 합니다.\n");
						printf("비밀번호는 8자 이상 12자 이하의 로마자와 숫자로 구성되어야 합니다.\n");
						printf("----------------------------------------------------------------------\n");
						printf("본인의 아이디와 비밀번호를 입력해주세요.\n");
						printf("아이디 > ");
						int in_id_check = get_char_input(in_id_temp, &in_id_arr_length);
						if (in_id_check != 0) {
							printf("잘못된 입력입니다. 다시 입력해주세요.\n");
							Sleep(1000);
							continue;
						}
						else {
							printf("비밀번호 > ");
							char in_pw_temp[STR_SIZE];
							char* in_pw;
							int in_pw_arr_length = 0;
							int in_pw_check = get_char_input(in_pw_temp, &in_pw_arr_length);
							if (in_pw_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.\n");
								Sleep(1000);
								continue;
							}
							else {
								in_id = (char*)malloc(sizeof(char) * (in_id_arr_length + 1));
								strcpy(in_id, in_id_temp);
								in_pw = (char*)malloc(sizeof(char) * (in_pw_arr_length + 1));
								strcpy(in_pw, in_pw_temp);
								if (seekCharId(login.masterfileData, in_id, pernum) == NULL) {
									printf("존재하지 않는 아이디입니다.\n");
									Sleep(1000);
									while (1) {
										system("cls");
										printf("-------------------------------------\n");
										printf("1) 로그인 화면으로 돌아갑니다\n");
										printf("2) 프로그램 시작화면으로 돌아갑니다.\n");
										printf("-------------------------------------\n");
										printf("메뉴 > ");
										char menu_temp[STR_SIZE];
										char* menu;
										int menu_arr_length = 0;
										int menu_check = get_char_input(menu_temp, &menu_arr_length);
										if (menu_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
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
												printf("잘못된 입력입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
										}
									}
								}
								else if (strcmp(in_id, seekCharId(login.masterfileData, in_id, pernum)) == 0) {
									if (seekCharPw(login.masterfileData, in_pw, pernum) == NULL) {
										printf("비밀번호가 일치하지 않습니다.\n");
										Sleep(1000);
										while (1) {
											system("cls");
											printf("-------------------------------------\n");
											printf("1) 로그인 화면으로 돌아갑니다\n");
											printf("2) 프로그램 시작화면으로 돌아갑니다.\n");
											printf("-------------------------------------\n");
											printf("메뉴 > ");
											char menu_temp[STR_SIZE];
											char* menu;
											int menu_arr_length = 0;
											int menu_check = get_char_input(menu_temp, &menu_arr_length);
											if (menu_check != 0) {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
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
													printf("잘못된 입력입니다. 다시 입력해주세요.");
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
						//로그인 성공
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
						printf("  반갑습니다 %s 회원님!\n", user.name);
						printf("----------------------------------\n");
						Sleep(1000);
						while (1) {
							system("cls");
							printf("\n명령어(\'\'제외하고 입력) \t 설명 \n\n");
							printf("\'search\' or \'s\' \t\t 회원을 검색합니다. \n");
							printf("\'show\' or \'sh\' \t\t\t 자신의 주소록을 보여줍니다. \n");
							printf("\'change\' or \'c\' \t\t 자신의 정보를 변경합니다. \n");
							printf("\'quit\' or \'q\' \t\t\t 로그아웃 합니다. \n\n");
							printf("%s \'s PhoneBook > ", user.name);
							char main_menu_temp[STR_SIZE];
							char* main_menu;
							int main_menu_arr_length = 0;
							int main_menu_check = get_char_input(main_menu_temp, &main_menu_arr_length);
							if (main_menu_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								main_menu = (char*)malloc(sizeof(char) * (main_menu_arr_length + 1));
								strcpy(main_menu, main_menu_temp);
								int real_main_menu_length = GetStringLength(main_menu);
								//검색
								if (strcmp(main_menu, "search") == 0 || strcmp(main_menu, "s") == 0) {
									while (1) {
										system("cls");
										printf("\n이 프로그램의 회원을 검색할 수 있습니다\n");
										printf("\n명령어(\'\'제외하고 입력) \t 설명 \n\n");
										printf("\'name\' \'검색인자\' \t\t 이름을 이용해서 회원을 검색합니다.\n");
										printf("\'phone\' \'검색인자\' \t\t 전화번호를 이용해서 회원을 검색합니다.\n");
										printf("\'back\' \t\t\t\t 메인화면으로 돌아갑니다.\n");
										printf("ex) name 홍길동   phone 010-1234-5678\n\n");
										printf("검색 > ");
										char search_temp[STR_SIZE];
										char* search = NULL;
										int search_arr_length = 0;
										int flag = 0;
										int search_check = get_char_input(search_temp, &search_arr_length);
										if (search_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
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
												printf("메인화면으로 돌아갑니다.");
												Sleep(1000);
												break;
											}
											if (factor == NULL) {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
											if (strcmp(t1, "name") == 0) {
												char* search_name = factor;
												int search_name_arr_length = strlen(search_name);
												int real_search_name_length = GetStringLength(search_name);
												if (real_search_name_length > 6) {
													printf("잘못된 입력입니다. 다시 입력해주세요.");
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
													printf("잘못된 입력입니다. 다시 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													flag = 3;
												}
											}
											else {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
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
														printf("검색결과가 존재하지 않습니다.\n");
														printf("------------------------------\n");
														Sleep(1000);
														break;
													}
													printf("------------------------------\n");
													printf("선택하고 싶은 회원의 앞에 적혀진 번호를 입력하세요 > ");
													char member_num_temp[STR_SIZE];
													char* member_num;
													int member_num_arr_length = 0;
													int member_num_check = get_char_input(member_num_temp, &member_num_arr_length);
													if (member_num_check != 0) {
														printf("잘못된 입력입니다. 다시 입력해주세요.");
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
															printf("잘못된 입력입니다. 다시 입력해주세요.");
															Sleep(1000);
															continue;
														}
														else {
															int real_member_num = atoi(member_num);
															if (real_member_num > search_member_num || real_member_num < 1) {
																printf("잘못된 입력입니다. 다시 입력해주세요.");
																Sleep(1000);
																continue;
															}
															else {
																real_member_num = real_member_num - 1;
																int select_member_num = search_member_num_arr[real_member_num];
																if (select_member_num == user_masterfile_idx) {
																	printf("자신에 대해서 기능을 제공하지 않습니다.");
																	Sleep(1000);
																	break;

																}
																char* select_member_id = user.masterfileData[select_member_num][0];
																char* select_member_name = user.masterfileData[select_member_num][2];
																while (1) {
																	system("cls");
																	printf("\n");
																	printf("명령어(\'\'제외하고 입력) \t 설명 \n\n");
																	printf("\'add\' or \'a\' \t\t\t 자신의 연락처에 추가합니다. \n");
																	printf("\'delete\' or \'d\' \t\t 자신의 연락처에서 삭제합니다. \n");
																	printf("\'show\' or \'s\' \t\t\t 회원의 자세한 정보를 보여줍니다. \n");
																	printf("\'permission\' or \'pe\' \t\t 회원의 권한을 수정합니다. \n");
																	printf("\'nickname\' or \'n\' \t\t 회원의 닉네임을 설정/수정합니다. \n");
																	printf("\'back\' or \'b\' \t\t\t 메인화면으로 돌아갑니다. \n\n");
																	printf("%s\'s PhoneBook > ", user.name);
																	char sub_menu_temp[STR_SIZE];
																	char* sub_menu;
																	int sub_menu_arr_length = 0;
																	int sub_menu_check = get_char_input(sub_menu_temp, &sub_menu_arr_length);
																	if (sub_menu_check != 0) {
																		printf("잘못된 입력입니다. 다시 입력해주세요.");
																		Sleep(1000);
																		continue;
																	}
																	else {
																		sub_menu = (char*)malloc(sizeof(char) * (sub_menu_arr_length + 1));
																		strcpy(sub_menu, sub_menu_temp);
																		int real_sub_menu_length = GetStringLength(sub_menu);
																		//개인주소록에 회원 추가
																		if (strcmp(sub_menu, "add") == 0 || strcmp(sub_menu, "a") == 0) {

																			if (user.friendNum == 100) {
																				printf("더이상 개인주소록에 회원을 추가할 수 없습니다.");
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
																				printf("이미 개인주소록에 존재하는 회원입니다.");
																				Sleep(1000);
																				continue;
																			}
																			else {
																				strcpy(user_adl[user.friendNum].textName, select_member_id);
																				strcpy(user_adl[user.friendNum].auth, "x");
																				strcpy(user_adl[user.friendNum].nick, "\0");
																				user.friendNum++;
																				printf("성공적으로 개인주소록에 회원을 추가하였습니다.");
																				Sleep(1000);
																				continue;
																			}
																		}
																		//개인주소록에 회원삭제
																		else if (strcmp(sub_menu, "delete") == 0 || strcmp(sub_menu, "d") == 0) {
																			if (user.friendNum == 0) {
																				printf("더이상 개인주소록에 삭제할 회원이 존재하지 않습니다.");
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
																				printf("성공적으로 개인주소록에서 회원을 삭제하였습니다.");
																				Sleep(1000);
																				continue;
																			}
																			else {
																				printf("개인주소록에 존재하지 않는 회원입니다.");
																				Sleep(1000);
																				continue;
																			}

																		}
																		//선택한 회원의 정보 보기
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
																				printf("\n현재 주소록에 추가되어 있는 회원입니다.\n");
																				printf("\n이름: %s\n", select_memeber.name);
																				printf("전화번호: %s\n", select_memeber.phoneNum);
																				if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																					printf("권한: O\n");
																				}
																				else {
																					printf("권한: X\n");
																				}
																				if (select_memeber.birthdisc == 3) {
																					printf("생년월일: %s\n", select_memeber.birth);
																				}
																				else if (select_memeber.birthdisc == 2) {
																					if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																						printf("생년월일: %s\n", select_memeber.birth);
																					}
																					else {
																						printf("생년월일: X\n");
																					}
																				}
																				else {
																					printf("생년월일: X\n");
																				}

																				if (select_memeber.genderdisc == 3) {
																					printf("성별: %s\n", select_memeber.gender);
																				}
																				else if (select_memeber.genderdisc == 2) {
																					if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																						printf("성별: %s\n", select_memeber.gender);
																					}
																					else {
																						printf("성별: X\n");
																					}
																				}
																				else {
																					printf("성별: X\n");
																				}

																				if (select_memeber.addressdisc == 3) {
																					char temp_add[STR_SIZE];
																					make_print_address(temp_add, select_memeber.address);
																					printf("주소: %s\n", temp_add);
																				}
																				else if (select_memeber.addressdisc == 2) {
																					if (strcmp(select_member_adl[idx].auth, "o") == 0) {
																						char temp_add[STR_SIZE];
																						make_print_address(temp_add, select_memeber.address);
																						printf("주소: %s\n", temp_add);
																					}
																					else {
																						printf("주소: X\n");
																					}
																				}
																				else {
																					printf("주소: X\n");
																				}

																				if (strlen(select_member_adl[idx].nick) != 0) {
																					printf("닉네임: %s\n", select_member_adl[idx].nick);
																				}
																				else {
																					printf("닉네임: X\n");
																				}
																				printf("키 입력시 친구설정 화면으로 돌아갑니다. >");
																				char show_menu_temp[STR_SIZE];
																				char* show_menu;
																				int show_menu_arr_length = 0;
																				int show_menu_check = get_char_input(show_menu_temp, &show_menu_arr_length);
																				if (show_menu_check == 0 || show_menu_check == 1) {
																					printf("친구설정 화면으로 돌아갑니다.");
																					Sleep(1000);
																					continue;
																				}
																			}
																			else {
																				system("cls");
																				printf("\n현재 주소록에 없는 회원입니다.\n");
																				printf("\n이름: %s\n", select_memeber.name);
																				printf("전화번호: %s\n", select_memeber.phoneNum);
																				if (select_memeber.birthdisc == 3) {
																					printf("생년월일: %s\n", select_memeber.birth);
																				}
																				else {
																					printf("생년월일: X\n");
																				}
																				if (select_memeber.genderdisc == 3) {
																					printf("성별: %s\n", select_memeber.gender);
																				}
																				else {
																					printf("성별: X\n");
																				}
																				if (select_memeber.addressdisc == 3) {
																					char temp_add[STR_SIZE];
																					make_print_address(temp_add, select_memeber.address);
																					printf("주소: %s\n", temp_add);
																				}
																				else {
																					printf("주소: X\n");
																				}
																				printf("키 입력시 친구설정 화면으로 돌아갑니다. >");
																				char show_menu_temp[STR_SIZE];
																				char* show_menu;
																				int show_menu_arr_length = 0;
																				int show_menu_check = get_char_input(show_menu_temp, &show_menu_arr_length);
																				if (show_menu_check == 0 || show_menu_check == 1) {
																					printf("친구설정 화면으로 돌아갑니다.");
																					Sleep(1000);
																					continue;
																				}
																			}

																		}
																		//승인여부 변경
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
																					printf("선택한 회원에게 정보를 볼 수 있는 권한을 부여합니다.");
																					Sleep(1000);
																					continue;
																				}
																				else if (permit_flag == 2) {
																					strcpy(user_adl[idx].auth, "x");
																					printf("선택한 회원에게 정보를 볼 수 있는 권한을 삭제합니다.");
																					Sleep(1000);
																					continue;
																				}
																			}
																			else {
																				printf("주소록에 존재하지 않는 회원입니다. 주소록에 먼저 추가해주세요.");
																				Sleep(1000);
																				continue;
																			}
																		}
																		//닉네임 설정
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
																						printf("닉네임을 설정합니다.\n");
																						printf("닉네임은 1자 이상, 5자 이하이며 로마자와 한글, 숫자로 구성되어야 합니다\n");
																						printf("닉네임 > ");
																					}
																					else {
																						printf("닉네임이 이미 존재합니다. 닉네임을 수정합니다.\n");
																						printf("현재 닉네임은 %s 입니다.\n", user_adl[idx].nick);
																						printf("닉네임은 1자 이상, 5자 이하이며 로마자와 한글, 숫자로 구성되어야 합니다\n");
																						printf("닉네임 > ");
																					}
																					int nickname_check = get_char_input(nickname_temp, &nickname_arr_length);
																					if (nickname_check != 0) {
																						printf("잘못된 입력입니다. 다시 입력해주세요.");
																						Sleep(1000);
																						continue;
																					}
																					else {
																						nickname = (char*)malloc(sizeof(char) * (nickname_arr_length + 1));
																						strcpy(nickname, nickname_temp);
																						int real_nickname_length = GetStringLength(nickname);
																						if (real_nickname_length > 5 || real_nickname_length < 1) {
																							printf("잘못된 입력입니다. 다시 입력해주세요.");
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
																								printf("형식에 어긋나는 닉네임입니다. 다시 입력해주세요.\n");
																								Sleep(1000);
																								continue;
																							}
																							else {
																								strcpy(user_adl[idx].nick, nickname);
																								printf("닉네임 설정완료.\n");
																								Sleep(1000);
																								break;
																							}
																						}
																					}
																				}
																			}
																			else {
																				printf("주소록에 존재하지 않는 회원입니다. 주소록에 먼저 추가해주세요.");
																				Sleep(1000);
																				continue;
																			}

																		}
																		//메인화면으로 복귀
																		else if (strcmp(sub_menu, "back") == 0 || strcmp(sub_menu, "b") == 0) {
																			printf("메인화면으로 돌아갑니다");
																			Sleep(1000);
																			break;
																		}
																		else {
																			printf("잘못된 입력입니다. 다시 입력해주세요.");
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
								//개인 주소록 출력
								else if (strcmp(main_menu, "show") == 0 || strcmp(main_menu, "sh") == 0) {
									if (user.friendNum == 0) {
										printf("현재 개인주소록에 추가된 회원이 존재하지 않습니다.");
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
											printf("이름: %s\n", mem.name);
											printf("전화번호: %s\n", mem.phoneNum);
											if (mem.birthdisc == 3) {
												printf("생년월일: %s\n", mem.birth);
											}
											else if (mem.birthdisc == 2) {
												if (mem_flag == 1) {
													printf("생년월일: %s\n", mem.birth);
												}
												else {
													printf("생년월일: X\n");
												}
											}
											else {
												printf("생년월일: X\n");
											}

											if (mem.genderdisc == 3) {
												printf("성별: %s\n", mem.gender);
											}
											else if (mem.genderdisc == 2) {
												if (mem_flag == 1) {
													printf("성별: %s\n", mem.gender);
												}
												else {
													printf("성별: X\n");
												}
											}
											else {
												printf("성별: X\n");
											}

											if (mem.addressdisc == 3) {
												printf("주소: %s\n", mem.address);
											}
											else if (mem.addressdisc == 2) {
												if (mem_flag == 1) {
													printf("주소: %s\n", mem.address);
												}
												else {
													printf("주소: X\n");
												}
											}
											else {
												printf("주소: X\n");
											}
											if (strlen(user_adl[i].nick) == 0) {
												printf("닉네임: X\n");
											}
											else {
												printf("닉네임: %s\n", user_adl[i].nick);
											}
											printf("\n");
										}
										printf("---------------------------------------------------------------------\n");
										printf("키 입력시  메인화면으로 돌아갑니다. >");
										char phone_book_menu_temp[STR_SIZE];
										char* phone_book_menu;
										int phone_book_menu_arr_length = 0;
										int phone_book_menu_check = get_char_input(phone_book_menu_temp, &phone_book_menu_arr_length);
										if (phone_book_menu_check == 0 || phone_book_menu_check == 1) {
											printf("메인 화면으로 돌아갑니다.");
											Sleep(1000);
											break;
										}
									}

								}
								//개인정보변경
								else if (strcmp(main_menu, "change") == 0 || strcmp(main_menu, "c") == 0) {
									while (1) {
										system("cls");
										printf("\n <개인정보>\n");
										printf("이름: %s\n", user.name);
										printf("전화번호: %s\n", user.phoneNum);
										if (user.birthdisc == 0) {
											printf("생년월일: X\n");
										}
										else if (user.birthdisc == 1) {
											printf("생년월일: %s <비공개>\n", user.birth);
										}
										else if (user.birthdisc == 2) {
											printf("생년월일: %s <선택공개>\n", user.birth);
										}
										else if (user.birthdisc == 3) {
											printf("생년월일: %s <전체공개>\n", user.birth);
										}
										else {
											printf("생년월일: X\n");
										}

										if (user.genderdisc == 0) {
											printf("성별: X\n");
										}
										else if (user.genderdisc == 1) {
											printf("성별: %s <비공개>\n", user.gender);
										}
										else if (user.genderdisc == 2) {
											printf("성별: %s <선택공개>\n", user.gender);
										}
										else if (user.genderdisc == 3) {
											printf("성별: %s <전체공개>\n", user.gender);
										}
										else {
											printf("성별: X\n");
										}

										if (user.addressdisc == 0) {
											printf("주소: X\n");
										}
										else if (user.addressdisc == 1) {
											char temp_add[STR_SIZE];
											make_print_address(temp_add, user.address);
											printf("주소: %s  <비공개>\n", temp_add);
										}
										else if (user.addressdisc == 2) {
											char temp_add[STR_SIZE];
											make_print_address(temp_add, user.address);
											printf("주소: %s  <선택공개>\n", temp_add);
										}
										else if (user.addressdisc == 3) {
											char temp_add[STR_SIZE];
											make_print_address(temp_add, user.address);
											printf("주소: %s  <전체공개>\n", temp_add);
										}
										else {
											printf("주소: X\n");
										}
										printf("\n명령어(\'\'제외하고 입력) \t 설명 \n\n");
										printf("\'name\' \'인자\' \t\t 현재 이름을 \'인자\'로 변경합니다.\n");
										printf("\'phone\' \'인자\' \t\t 현재 전화번호를 \'인자\'로 변경합니다.\n");
										printf("\'birth\' \'인자\' \t\t 현재 생년월일을 \'인자\'로 변경합니다.\n");
										printf("\'gender\' \'인자\' \t 현재 성별을 \'인자\'로 변경합니다.\n");
										printf("\'address\' \'인자\' \t 현재 주소를 \'인자\'로 변경합니다.\n");
										printf("\'back\'  \t\t 메인화면으로 돌아갑니다. \n\n");
										printf("밑의 명령어는 정보공개범위를 설정하는 명령어로 \'인자\'는 아래와 같은 의미를 같습니다.\n\n");
										printf("\'1\' : 비공개   \'2\' : 선택공개   \'3\' : 전체공개\n\n");
										printf("\'birthauth\' \'인자\' \t\t 생년월일의 공개범위를 변경합니다.\n");
										printf("\'genderauth\' \'인자\' \t\t 성별의 공개범위를 변경합니다.\n");
										printf("\'addressauth\' \'인자\' \t\t 주소의 공개범위를 변경합니다.\n\n");
										printf(" %s\'s PhoneBook > ", user.name);
										char sub_menu_temp[STR_SIZE];
										char* sub_menu;
										int sub_menu_arr_length = 0;
										int sub_menu_check = get_char_input(sub_menu_temp, &sub_menu_arr_length);
										if (sub_menu_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
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
												printf("개인정보변경을 종료합니다.");
												Sleep(1000);
												break;
											}
											if (factor == NULL) {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
											if (strcmp(t1, "name") == 0) {
												int factor_name_check = check_name(factor);
												if (factor_name_check == 1) {
													printf("잘못된 입력입니다. 다시 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													strcpy(user.name, factor);
													strcpy(user.masterfileData[user_masterfile_idx][0], factor);
													printf("이름을 변경하였습니다.");
													Sleep(1000);
													continue;
												}
											}
											else if (strcmp(t1, "phone") == 0) {
												int factor_phone_num_check = check_phone_num(factor, user.masterfileData, pernum);
												if (factor_phone_num_check == 1) {
													printf("잘못된 입력입니다. 다시 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else if (factor_phone_num_check == 2) {
													printf("이미 존재하는 번호입니다. 다시 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													int factor_phone_num_length = strlen(factor);
													if (factor_phone_num_length == 11) {
														strcpy(user.phoneNum, factor);
														strcpy(user.masterfileData[user_masterfile_idx][3], factor);
														printf("전화번호를 변경하였습니다.");
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
														printf("전화번호를 변경하였습니다.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "birth") == 0) {
												int factor_birth_check = check_birth(factor);
												if (factor_birth_check == 1) {
													printf("잘못된 입력입니다. 다시 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													if (user.birthdisc == 0) {
														user.birth = (char*)malloc(sizeof(char) * 10);
														user.birthdisc = 1;
														strcpy(user.birth, factor);
														user.dataNum++;
														printf("생년월일을 입력하였습니다. 정보공개범위는 비공개로 설정됩니다.");
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
														printf("생년월일을 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else {
														strcpy(user.birth, factor);
														printf("생년월일을 변경하였습니다.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "gender") == 0) {
												int factor_gender_check = check_gender(factor);
												if (factor_gender_check == 1) {
													printf("잘못된 입력입니다. 다시 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													if (user.genderdisc == 0) {
														user.gender = (char*)malloc(sizeof(char) * 3);
														user.genderdisc = 1;
														if (factor_gender_check == 2) {
															strcpy(user.gender, "남성");
														}
														else if (factor_gender_check == 3) {
															strcpy(user.gender, "여성");
														}
														user.dataNum++;
														printf("성별을 입력하였습니다. 정보공개범위는 비공개로 설정됩니다.");
														Sleep(1000);
														continue;
													}
													else if (factor_gender_check == 2) {
														strcpy(user.gender, "남성");
														printf("성별을 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else if (factor_gender_check == 3) {
														strcpy(user.gender, "여성");
														printf("성별을 변경하였습니다.");
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
													printf("잘못된 입력입니다. 다시 입력해주세요.");
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
														printf("주소를 입력하였습니다. 정보공개범위는 비공개로 설정됩니다.");
														Sleep(1000);
														continue;
													}
													else {
														strcpy(user.address, temp_add);
														printf("주소를 변경하였습니다.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "birthauth") == 0) {
												if (user.birthdisc == 0) {
													printf("생년월일이 입력되지 않았습니다. 먼저 생년월일을 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													if (strcmp(factor, "1") == 0) {
														user.birthdisc = 1;
														printf("생년월일을 비공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "2") == 0) {
														user.birthdisc = 2;
														printf("생년월일을 선택공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "3") == 0) {
														user.birthdisc = 3;
														printf("생년월일을 전체공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else {
														printf("잘못된 입력입니다. 다시 입력해주세요.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "genderauth") == 0) {
												if (user.genderdisc == 0) {
													printf("성별이 입력되지 않았습니다. 먼저 성별을 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													if (strcmp(factor, "1") == 0) {
														user.genderdisc = 1;
														printf("성별을 비공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "2") == 0) {
														user.genderdisc = 2;
														printf("성별을 선택공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "3") == 0) {
														user.genderdisc = 3;
														printf("성별을 전체공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else {
														printf("잘못된 입력입니다. 다시 입력해주세요.");
														Sleep(1000);
														continue;
													}
												}
											}
											else if (strcmp(t1, "addressauth") == 0) {
												if (user.addressdisc == 0) {
													printf("주소가 입력되지 않았습니다. 먼저 주소를 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													if (strcmp(factor, "1") == 0) {
														user.addressdisc = 1;
														printf("주소를 비공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "2") == 0) {
														user.addressdisc = 2;
														printf("주소를 선택공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else if (strcmp(factor, "3") == 0) {
														user.addressdisc = 3;
														printf("주소를 전체공개로 변경하였습니다.");
														Sleep(1000);
														continue;
													}
													else {
														printf("잘못된 입력입니다. 다시 입력해주세요.");
														Sleep(1000);
														continue;
													}
												}
											}
											else {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
										}
									}
								}
								//프로그램 종료
								else if (strcmp(main_menu, "quit") == 0 || strcmp(main_menu, "q") == 0) {
									printf("로그아웃 합니다.");
									login_flag = 3;
									savePersonalData(&user, user_adl);
									Sleep(1000);
									break;
								}
								else {
									printf("잘못된 입력입니다. 다시 입력해주세요.");
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
				//회원가입 시작
				else if (strcmp(menu, "2") == 0) {
					while (1) {
						personalData join;
						adressList join_adl[MEMBER_SIZE];
						init(&join, pernum);
						readMasterData(&join, pernum);
						int datanum = 0;
						//아이디 생성
						while (1) {
							//아이디 생성
							char id_temp[STR_SIZE];
							char* id = NULL;
							int id_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("사용하실 아이디를 입력해주세요.\n");
							printf("아이디는 6자 이상 10자 이하의 로마자 소문자와 숫자로 구성되어야 합니다.\n");
							printf("아이디 > ");
							int id_check = get_char_input(id_temp, &id_arr_length);
							if (id_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								id = (char*)malloc(sizeof(char) * (id_arr_length + 1));
								strcpy(id, id_temp);
								int real_id_length = GetStringLength(id);
								if (real_id_length > 10 || real_id_length < 6) {
									printf("아이디의 길이가 규칙에 위배됩니다. 다시 입력해주세요");
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
										printf("형식에 어긋나는 아이디입니다. 다시 입력해주세요.\n");
										Sleep(1000);
										continue;
									}
									else if (flag == 2) {
										printf("이미 존재하는 아이디입니다. 다시 입력해주세요.\n");
										Sleep(1000);
										continue;
									}
									else {
										join.id = id;
										printf("아이디 생성완료!");
										Sleep(1000);
										break;
									}
								}
							}

						}
						//비밀번호 생성
						while (1) {
							//비밀번호 생성
							char pw_temp[STR_SIZE];
							char* pw = NULL;
							int pw_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("사용하실 비밀번호를 입력해주세요.\n");
							printf("비밀번호는 8자 이상 12자 이하의 로마자와 숫자로 구성되어야 합니다.\n");
							printf("비밀번호 > ");
							int pw_check = get_char_input(pw_temp, &pw_arr_length);
							if (pw_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								pw = (char*)malloc(sizeof(char) * (pw_arr_length + 1));
								strcpy(pw, pw_temp);
								int real_pw_length = GetStringLength(pw);
								if (real_pw_length > 12 || real_pw_length < 8) {
									printf("비밀번호의 길이가 규칙에 위배됩니다. 다시 입력해주세요");
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
										printf("형식에 어긋나는 비밀번호입니다. 다시 입력해주세요.\n");
										Sleep(1000);
										continue;
									}
									else {
										while (1) {
											system("cls");
											printf("비밀번호를 생성합니다\n");
											printf("비밀번호는 8자 이상 12자 이하의 로마자와 숫자로 구성되어야 합니다.\n");
											printf("비밀번호 > %s\n", pw);
											printf(" * 정상적인 비밀번호 입니다!\n");
											printf("비밀번호 2차 확인 > ");
											char check_pw_temp[STR_SIZE];
											char* check_pw = NULL;
											int check_pw_arr_length = 0;
											int flag = 0;
											int check_pw_check = get_char_input(check_pw_temp, &check_pw_arr_length);
											if (pw_check != 0) {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
											else {
												check_pw = (char*)malloc(sizeof(char) * (check_pw_arr_length + 1));
												strcpy(check_pw, check_pw_temp);
												if (strcmp(pw, check_pw) == 0) {
													join.password = pw;
													printf("비밀번호 생성완료!");
													Sleep(1000);
													break;
												}
												else {
													printf("비밀번호가 일치하지 않습니다. 다시 입력해주세요.");
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
						//이름 입력
						while (1) {
							//이름입력
							char name_temp[STR_SIZE];
							char* name = NULL;
							int name_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("사용하실 이름을 입력해주세요.\n");
							printf("이름은 2자 이상 6자 이하입니다.\n");
							printf("이름 > ");
							int name_check = get_char_input(name_temp, &name_arr_length);
							if (name_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								name = (char*)malloc(sizeof(char) * (name_arr_length + 1));
								strcpy(name, name_temp);
								int real_name_length = GetStringLength(name);
								if (real_name_length > 6 || real_name_length < 2) {
									printf("이름의 길이가 규칙에 위배됩니다. 다시 입력해주세요");
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
									printf("형식에 어긋나는 이름입니다. 다시 입력해주세요.\n");
									Sleep(1000);
									continue;
								}
								else {
									join.name = name;
									printf("이름 생성완료!");
									Sleep(1000);
									break;
								}
							}
						}
						//전화번호 입력
						while (1) {
							//전화번호 입력
							char phone_num_temp[STR_SIZE];
							char* phone_num = NULL;
							int phone_num_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("사용하실 전화번호를 입력해주세요.\n");
							printf("현재 입력하시는 전화번호는 이 프로그램의 회원에게 공개되는 전화번호입니다.\n");
							printf("ex) 010-1234-7688, 01012347688\n");
							printf("전화번호 > ");
							int phone_num_check = get_char_input(phone_num_temp, &phone_num_arr_length);
							if (phone_num_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								phone_num = (char*)malloc(sizeof(char) * (phone_num_arr_length + 1));
								strcpy(phone_num, phone_num_temp);
								int real_phone_num_length = GetStringLength(phone_num);
								if ((real_phone_num_length == 13 || real_phone_num_length == 11) != 1) {
									printf("전화번호의 길이가 규칙에 위배됩니다. 다시 입력해주세요");
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
										printf("형식에 어긋나는 전화번호입니다. 다시 입력해주세요.\n");
										Sleep(1000);
										continue;
									}
									else if (flag == 2) {
										printf("이미 존재하는 전화번호입니다. 다시 입력해주세요.\n");
										Sleep(1000);
										continue;
									}
									else {
										if (phone_num_arr_length == 11) {
											join.phoneNum = phone_num;
											printf("전화번호 생성완료!");
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
											printf("전화번호 생성완료!");
											Sleep(1000);
											break;
										}
									}
								}
							}
						}
						//생년월일 입력
						while (1) {
							//생년월일 입력
							char birthday_temp[STR_SIZE];
							char* birthday;
							char temp_birthday[7];
							int birthday_arr_length = 0;
							int flag = 0;
							int birthday_flag = 0;
							system("cls");
							printf("생년월일입력 여부를 선택합니다\n");
							printf(" 1) 생년월일 입력\n");
							printf(" 2) 생년월일 입력 X\n");
							printf(" 입력여부 > ");
							char birthday_menu_temp[STR_SIZE];
							char* birthday_menu;
							int birthday_menu_arr_length = 0;
							int birthday_menu_check = get_char_input(birthday_menu_temp, &birthday_menu_arr_length);
							if (birthday_menu_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								birthday_menu = (char*)malloc(sizeof(char) * (birthday_menu_arr_length + 1));
								strcpy(birthday_menu, birthday_menu_temp);
								int real_birthday_menu_length = GetStringLength(birthday_menu);
								if (real_birthday_menu_length != 1) {
									printf("잘못된 입력입니다. 다시 입력해주세요.");
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
									printf("잘못된 입력입니다. 다시 입력해주세요.");
									Sleep(1000);
									continue;
								}
								else if (flag == 2) {
									join.birthdisc = 0;
									printf("생년월일 입력을 건너뛰겠습니다.");
									Sleep(1000);
									break;
								}
								else if (flag == 0) {
									while (1) {
										system("cls");
										printf("생년월일을 입력하세요\n");
										printf("ex) 990123   1999-01-23\n");
										printf("생년월일 >");
										int birthday_check = get_char_input(birthday_temp, &birthday_arr_length);
										if (birthday_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
											Sleep(1000);
											continue;
										}
										else {
											birthday = (char*)malloc(sizeof(char) * (birthday_arr_length + 1));
											strcpy(birthday, birthday_temp);
											int real_birthday_length = GetStringLength(birthday);
											if (!(real_birthday_length == 6 || real_birthday_length == 10)) {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
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
											printf("잘못된 입력입니다. 다시 입력해주세요.");
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
											printf("생년월일 입력 완료!");
											Sleep(1000);
											break;
										}
									}
									while (1) {
										char permission_menu_temp[STR_SIZE];
										char* permission_menu;
										int permission_menu_arr_length = 0;
										system("cls");
										printf("생년월일을 공개하시겠습니까?\n");
										printf(" 1) 전체공개\n");
										printf(" 2) 권한을 부여한 사람에게만 공개\n");
										printf(" 3) 비공개\n");
										printf("공개여부 > ");
										int permission_menu_check = get_char_input(permission_menu_temp, &permission_menu_arr_length);
										if (permission_menu_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
											Sleep(1000);
											continue;
										}
										else {
											permission_menu = (char*)malloc(sizeof(char) * (permission_menu_arr_length + 1));
											strcpy(permission_menu, permission_menu_temp);
											int real_permission_menu_length = GetStringLength(permission_menu);
											if (real_permission_menu_length != 1) {
												printf("잘못된 메뉴입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
											else {
												for (int i = 0; i < permission_menu_arr_length; i++) {
													char check = permission_menu[i];
													if (check >> 7) {
														printf("잘못된 메뉴입니다. 다시 입력해주세요.");
														Sleep(1000);
														continue;
													}
													else if (permission_menu[i] == '1') {
														printf("생년월일을 전체공개합니다.");
														join.birthdisc = 3;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '2') {
														printf("생년월일을 권한을 부여한 사람에게만 공개합니다.");
														join.birthdisc = 2;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '3') {
														printf("생년월일을 비공개합니다.");
														join.birthdisc = 1;
														Sleep(1000);
														break;
													}
													else {
														printf("잘못된 입력입니다. 다시 입력해주세요.");
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
						//성별 입력
						while (1) {
							//성별 입력
							char gender_temp[STR_SIZE];
							char* gender = NULL;
							int gender_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("성별입력 여부를 선택합니다\n");
							printf(" 1) 성별 입력\n");
							printf(" 2) 성별 입력 X\n");
							printf(" 입력여부 > ");
							char gender_menu_temp[STR_SIZE];
							char* gender_menu;
							int gender_menu_arr_length = 0;
							int gender_menu_check = get_char_input(gender_menu_temp, &gender_menu_arr_length);
							if (gender_menu_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								gender_menu = (char*)malloc(sizeof(char) * (gender_menu_arr_length + 1));
								strcpy(gender_menu, gender_menu_temp);
								int real_gender_menu_length = GetStringLength(gender_menu);
								if (real_gender_menu_length != 1) {
									printf("잘못된 입력입니다. 다시 입력해주세요.");
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
									printf("잘못된 입력입니다. 다시 입력해주세요.");
									Sleep(1000);
									continue;
								}
								else if (flag == 2) {
									join.genderdisc = 0;
									printf("성별 입력을 건너뛰겠습니다.");
									Sleep(1000);
									break;
								}
								else if (flag == 0) {
									while (1) {
										system("cls");
										printf("성별을 입력하세요\n");
										printf("ex) 남, 여   남자, 여자   남성, 여성\n");
										printf("성별 >");
										int gender_check = get_char_input(gender_temp, &gender_arr_length);
										if (gender_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
											Sleep(1000);
											continue;
										}
										else {
											gender = (char*)malloc(sizeof(char) * (gender_arr_length + 1));
											strcpy(gender, gender_temp);
											int real_gender_length = GetStringLength(gender);
											if (!(real_gender_length == 1 || real_gender_length == 2)) {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
											else {

												if (strcmp(gender, "남") == 0 || strcmp(gender, "남자") == 0 || strcmp(gender, "남성") == 0) {
													gender = "남성";
													join.gender = gender;
													datanum++;
													printf("성별을 남성으로 선택하였습니다");
													Sleep(1000);
													break;
												}
												else if (strcmp(gender, "여") == 0 || strcmp(gender, "여자") == 0 || strcmp(gender, "여성") == 0) {
													gender = "여성";
													join.gender = gender;
													datanum++;
													printf("성별을 여성으로 선택하였습니다");
													Sleep(1000);
													break;
												}
												else {
													printf("잘못된 입력입니다. 다시 입력해주세요.");
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
										printf("성별을 공개하시겠습니까?\n");
										printf(" 1) 전체공개\n");
										printf(" 2) 권한을 부여한 사람에게만 공개\n");
										printf(" 3) 비공개\n");
										printf("공개여부 > ");
										int permission_menu_check = get_char_input(permission_menu_temp, &permission_menu_arr_length);
										if (permission_menu_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
											Sleep(1000);
											continue;
										}
										else {
											permission_menu = (char*)malloc(sizeof(char) * (permission_menu_arr_length + 1));
											strcpy(permission_menu, permission_menu_temp);
											int real_permission_menu_length = GetStringLength(permission_menu);
											if (real_permission_menu_length != 1) {
												printf("잘못된 메뉴입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
											else {
												for (int i = 0; i < permission_menu_arr_length; i++) {
													char check = permission_menu[i];
													if (check >> 7) {
														printf("잘못된 메뉴입니다. 다시 입력해주세요.");
														Sleep(1000);
														continue;
													}
													else if (permission_menu[i] == '1') {
														printf("성별을 전체공개합니다.");
														join.genderdisc = 3;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '2') {
														printf("성별을 권한을 부여한 사람에게만 공개합니다.");
														join.genderdisc = 2;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '3') {
														printf("성별을 비공개합니다.");
														join.genderdisc = 1;
														Sleep(1000);
														break;
													}
													else {
														printf("잘못된 입력입니다. 다시 입력해주세요.");
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
						//주소 입력
						while (1) {
							char address_temp[STR_SIZE];
							char* address = NULL;
							int address_arr_length = 0;
							int flag = 0;
							system("cls");
							printf("주소입력 여부를 선택합니다\n");
							printf(" 1) 주소 입력\n");
							printf(" 2) 주소 입력 X\n");
							printf(" 입력여부 > ");
							char address_menu_temp[STR_SIZE];
							char* address_menu;
							int address_menu_arr_length = 0;
							int address_menu_check = get_char_input(address_menu_temp, &address_menu_arr_length);
							if (address_menu_check != 0) {
								printf("잘못된 입력입니다. 다시 입력해주세요.");
								Sleep(1000);
								continue;
							}
							else {
								address_menu = (char*)malloc(sizeof(char) * (address_menu_arr_length + 1));
								strcpy(address_menu, address_menu_temp);
								int real_address_menu_length = GetStringLength(address_menu);
								if (real_address_menu_length != 1) {
									printf("잘못된 메뉴입니다. 다시 입력해주세요.");
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
									printf("잘못된 메뉴입니다. 다시 입력해주세요.");
									Sleep(1000);
									continue;
								}
								else if (flag == 2) {
									join.addressdisc = 0;
									printf("주소 입력을 건너뛰겠습니다.");
									Sleep(1000);
									break;
								}
								else {
									while (1) {
										system("cls");
										printf("주소를 입력하세요\n");
										printf("주소 >");
										int address_check = get_char_input(address_temp, &address_arr_length);
										if (address_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
											Sleep(1000);
											continue;
										}
										else {
											address = (char*)malloc(sizeof(char) * (address_arr_length + 1));
											strcpy(address, address_temp);
											int real_address_length = GetStringLength(address);
											if (real_address_length < 2 || real_address_length > 30) {
												printf("잘못된 입력입니다. 다시 입력해주세요.");
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
													printf("잘못된 입력입니다. 다시 입력해주세요.");
													Sleep(1000);
													continue;
												}
												else {
													char temp_add[STR_SIZE];
													del_space(temp_add, address_temp);
													join.address = temp_add;
													datanum++;
													printf("주소 입력완료!\n");
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
										printf("주소를 공개하시겠습니까?\n");
										printf(" 1) 전체공개\n");
										printf(" 2) 권한을 부여한 사람에게만 공개\n");
										printf(" 3) 비공개\n");
										printf("공개여부 > ");
										int permission_menu_check = get_char_input(permission_menu_temp, &permission_menu_arr_length);
										if (permission_menu_check != 0) {
											printf("잘못된 입력입니다. 다시 입력해주세요.");
											Sleep(1000);
											continue;
										}
										else {
											permission_menu = (char*)malloc(sizeof(char) * (permission_menu_arr_length + 1));
											strcpy(permission_menu, permission_menu_temp);
											int real_permission_menu_length = GetStringLength(permission_menu);
											if (real_permission_menu_length != 1) {
												printf("잘못된 메뉴입니다. 다시 입력해주세요.");
												Sleep(1000);
												continue;
											}
											else {
												for (int i = 0; i < permission_menu_arr_length; i++) {
													char check = permission_menu[i];
													if (check >> 7) {
														printf("잘못된 메뉴입니다. 다시 입력해주세요.");
														Sleep(1000);
														continue;
													}
													else if (permission_menu[i] == '1') {
														printf("주소를 전체공개합니다.");
														join.addressdisc = 3;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '2') {
														printf("주소를 권한을 부여한 사람에게만 공개합니다.");
														join.addressdisc = 2;
														Sleep(1000);
														break;
													}
													else if (permission_menu[i] == '3') {
														printf("주소를 비공개합니다.");
														join.addressdisc = 1;
														Sleep(1000);
														break;
													}
													else {
														printf("잘못된 메뉴입니다. 다시 입력해주세요.");
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
				//프로그램 종료
				else if (strcmp(menu, "3") == 0) {
					printf("프로그램을 종료합니다.");
					Sleep(1000);
					break;
				}
				else {
					printf("잘못된 입력입니다. 다시 입력해주세요.");
					Sleep(1000);
					continue;
				}

			}
			break;
		}
	}
	printf("\n완료!");
}

