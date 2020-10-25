#include<stdio.h>
#include<string.h>

int search2(char* filename, char word[256])
{
	char line[100];//파일을 읽을 때 사용할 임시 공간
	FILE* fp = fopen(filename, "r"); //읽기모드로 열기, 파일 포인터를 변환
	while (fgets(line, 100, fp))//.txt에서 문자열을 읽음
	{
		if (strstr(line, word))
		{
			printf("%s", line);//파일의 내용 출력
		}
	}
	fclose(fp);//파일 포인터 닫기
	return 0;
}
void search1(void)
{
	char* filename = ("C:/2020/전공기초프로젝트2/프로젝트/주소록.txt");
	char word[256];
	char s1[8] = "<phone> ";
	char s2[7] = "<name> ";
	char name[256] = "";
	char phone[256] = "";
	while (1)
	{
		printf("\n전화번호 검색 : <phone> + 공백 + 전화번호 \n");
		printf("이름 검색     : <name>  + 공백 + 이름 \n");
		printf("검색할 정보를 위 규칙에 맞게 입력하세요 : ");
		gets_s(word, 256);//공백까지 입력받는다.

		if (strncmp(s1, word, 6) == 0)//phone인경우
		{
			if (word[7] != ' ')//공백이 사용되지 않은 경우
			{
				printf("공백을 사용해서 입력하세요\n\n");
				continue;
			}
			for (int i = 8; i < 256; i++)
			{
				phone[i - 8] = word[i];
				if (word[i] == '\0')
					break;
			}
			//번호 규칙 검사 추가해야됨
			search2(filename, phone);
			break;
		}
		if (strncmp(s2, word, 5) == 0)//name인 경우
		{
			if (word[6] != ' ')//공백이 사용되지 않은 경우
			{
				printf("공백을 사용해서 입력하세요\n\n");
				continue;
			}
			for (int i = 7; i < 256; i++)
			{
				name[i - 7] = word[i];
				if (word[i] == '\0')
					break;
			}
			//이름 규칙 검사 추가해야됨
			search2(filename, name);
			break;
		}
		printf("잘못 입력했습니다.\n\n");
	}
}

void show(void)
{
	char* filename = ("C:/2020/전공기초프로젝트2/프로젝트/주소록.txt");//개인 주소록
	char line[100];//파일을 읽을 때 사용할 임시 공간
	FILE* fp = fopen(filename, "r"); //읽기모드로 열기, 파일 포인터를 변환
	while (fgets(line, 100, fp))//.txt에서 문자열을 읽음
	{
			printf("%s", line);//파일의 내용 출력
	}
	printf("\n");
	fclose(fp);//파일 포인터 닫기

}

void change(void)
{
	char word[256];
	char s1[8] = "<phone> ";
	char s2[7] = "<name> ";
	char s3[8] = "<birth> ";
	char s4[9] = "<gender> ";
	char s5[7] = "<back> ";
	char name[256] = "";
	char phone[256] = "";
	char birth[256] = "";
	char gender[256] = "";
	char back[256] = "";
	while (1)
	{
		printf("\n전화번호 변경	: <phone> + 공백 + 전화번호 \n");//자세한 정보는 변경해야됨
		printf("이름 변경       : <name>  + 공백 + 이름 \n");
		printf("생일 변경       : <birth> + 공백 + 전화번호 \n");
		printf("성별 변경       : <gender>  + 공백 + 이름 \n");
		printf("뒤로 가기       : <back>  + 공백 + 이름 \n");
		printf("검색할 정보를 위 규칙에 맞게 입력하세요 : ");
		gets_s(word, 256);//공백까지 입력받는다.

		if (strncmp(s1, word, 6) == 0)//phone인경우
		{
			if (word[7] != ' ')//공백이 사용되지 않은 경우
			{
				printf("공백을 사용해서 입력하세요\n\n");
				continue;
			}

			for (int i = 8; i < 256; i++)
			{
				phone[i - 8] = word[i];
				if (word[i] == '\0')
					break;
			}
			//번호 규칙 검사 추가해야됨
			//search2(filename, phone);
			break;
		}

		else if (strncmp(s2, word, 5) == 0)//name인 경우
		{
			if (word[6] != ' ')//공백이 사용되지 않은 경우
			{
				printf("공백을 사용해서 입력하세요\n\n");
				continue;
			}
			for (int i = 7; i < 256; i++)
			{
				name[i - 7] = word[i];
				if (word[i] == '\0')
					break;
			}
			//이름 규칙 검사 추가해야됨
			//search2(filename, name);
			break;
		}
		else if (strncmp(s3, word, 6) == 0)//birth인 경우
		{
			if (word[7] != ' ')//공백이 사용되지 않은 경우
			{
				printf("공백을 사용해서 입력하세요\n\n");
				continue;
			}
			for (int i = 8; i < 256; i++)
			{
				name[i - 8] = word[i];
				if (word[i] == '\0')
					break;
			}
			//이름 규칙 검사 추가해야됨
			//search2(filename, name);
			break;
		}
		else if (strncmp(s4, word, 7) == 0)//gender인 경우
		{
			if (word[8] != ' ')//공백이 사용되지 않은 경우
			{
				printf("공백을 사용해서 입력하세요\n\n");
				continue;
			}
			for (int i = 9; i < 256; i++)
			{
				name[i - 9] = word[i];
				if (word[i] == '\0')
					break;
			}
			//이름 규칙 검사 추가해야됨
			//search2(filename, name);
			break;
		}
		else if (strncmp(s5, word, 5) == 0)//back인 경우
		{
			if (word[6] != ' ')//공백이 사용되지 않은 경우
			{
				printf("공백을 사용해서 입력하세요\n\n");
				continue;
			}
			for (int i = 7; i < 256; i++)
			{
				name[i - 7] = word[i];
				if (word[i] == '\0')
					break;
			}
			break;
		}
		else
		{
			printf("잘못 입력했습니다.\n\n");
		}
	}
	return 0;

}

int main(void) 
{
	char menu[7]="";//menu 선택 배열

	//주 프롬프트
	printf("명령어(''제외하고 입력) \t 설명 \n\n");
	printf("'search' or 's' \t\t 다음 회원을 검색합니다. \n");
	printf("'show' or 'sh' \t\t\t 자신의 주소록을 보여줍니다. \n");
	printf("'change' or 'c' \t\t 자신의 정보를 변경합니다. \n");
	printf("'quit' or 'q' \t\t\t 프로그램을 종료합니다. \n");
	
	while (1)
	{
		printf("name's phone book : ");
		scanf("%s", menu);
		getchar();//공백 제거
		if (strcmp(menu, "quit") == 0 || strcmp(menu, "q") == 0)
			break;
		else if (strcmp(menu, "search") == 0 || strcmp(menu, "s") == 0)
			search1();
		else if (strcmp(menu, "show") == 0 || strcmp(menu, "sh") == 0)
			show();
		else if (strcmp(menu, "change") == 0 || strcmp(menu, "c") == 0)
			change();
		else
		{
			printf("잘못 입력했습니다.\n\n");
		}
	}
}

