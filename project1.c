#include<stdio.h>
#include<string.h>

int search2(char* filename, char word[256])
{
	char line[100];//������ ���� �� ����� �ӽ� ����
	FILE* fp = fopen(filename, "r"); //�б���� ����, ���� �����͸� ��ȯ
	while (fgets(line, 100, fp))//.txt���� ���ڿ��� ����
	{
		if (strstr(line, word))
		{
			printf("%s", line);//������ ���� ���
		}
	}
	fclose(fp);//���� ������ �ݱ�
	return 0;
}
void search1(void)
{
	char* filename = ("C:/2020/��������������Ʈ2/������Ʈ/�ּҷ�.txt");
	char word[256];
	char s1[8] = "<phone> ";
	char s2[7] = "<name> ";
	char name[256] = "";
	char phone[256] = "";
	while (1)
	{
		printf("\n��ȭ��ȣ �˻� : <phone> + ���� + ��ȭ��ȣ \n");
		printf("�̸� �˻�     : <name>  + ���� + �̸� \n");
		printf("�˻��� ������ �� ��Ģ�� �°� �Է��ϼ��� : ");
		gets_s(word, 256);//������� �Է¹޴´�.

		if (strncmp(s1, word, 6) == 0)//phone�ΰ��
		{
			if (word[7] != ' ')//������ ������ ���� ���
			{
				printf("������ ����ؼ� �Է��ϼ���\n\n");
				continue;
			}
			for (int i = 8; i < 256; i++)
			{
				phone[i - 8] = word[i];
				if (word[i] == '\0')
					break;
			}
			//��ȣ ��Ģ �˻� �߰��ؾߵ�
			search2(filename, phone);
			break;
		}
		if (strncmp(s2, word, 5) == 0)//name�� ���
		{
			if (word[6] != ' ')//������ ������ ���� ���
			{
				printf("������ ����ؼ� �Է��ϼ���\n\n");
				continue;
			}
			for (int i = 7; i < 256; i++)
			{
				name[i - 7] = word[i];
				if (word[i] == '\0')
					break;
			}
			//�̸� ��Ģ �˻� �߰��ؾߵ�
			search2(filename, name);
			break;
		}
		printf("�߸� �Է��߽��ϴ�.\n\n");
	}
}

void show(void)
{
	char* filename = ("C:/2020/��������������Ʈ2/������Ʈ/�ּҷ�.txt");//���� �ּҷ�
	char line[100];//������ ���� �� ����� �ӽ� ����
	FILE* fp = fopen(filename, "r"); //�б���� ����, ���� �����͸� ��ȯ
	while (fgets(line, 100, fp))//.txt���� ���ڿ��� ����
	{
			printf("%s", line);//������ ���� ���
	}
	printf("\n");
	fclose(fp);//���� ������ �ݱ�

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
		printf("\n��ȭ��ȣ ����	: <phone> + ���� + ��ȭ��ȣ \n");//�ڼ��� ������ �����ؾߵ�
		printf("�̸� ����       : <name>  + ���� + �̸� \n");
		printf("���� ����       : <birth> + ���� + ��ȭ��ȣ \n");
		printf("���� ����       : <gender>  + ���� + �̸� \n");
		printf("�ڷ� ����       : <back>  + ���� + �̸� \n");
		printf("�˻��� ������ �� ��Ģ�� �°� �Է��ϼ��� : ");
		gets_s(word, 256);//������� �Է¹޴´�.

		if (strncmp(s1, word, 6) == 0)//phone�ΰ��
		{
			if (word[7] != ' ')//������ ������ ���� ���
			{
				printf("������ ����ؼ� �Է��ϼ���\n\n");
				continue;
			}

			for (int i = 8; i < 256; i++)
			{
				phone[i - 8] = word[i];
				if (word[i] == '\0')
					break;
			}
			//��ȣ ��Ģ �˻� �߰��ؾߵ�
			//search2(filename, phone);
			break;
		}

		else if (strncmp(s2, word, 5) == 0)//name�� ���
		{
			if (word[6] != ' ')//������ ������ ���� ���
			{
				printf("������ ����ؼ� �Է��ϼ���\n\n");
				continue;
			}
			for (int i = 7; i < 256; i++)
			{
				name[i - 7] = word[i];
				if (word[i] == '\0')
					break;
			}
			//�̸� ��Ģ �˻� �߰��ؾߵ�
			//search2(filename, name);
			break;
		}
		else if (strncmp(s3, word, 6) == 0)//birth�� ���
		{
			if (word[7] != ' ')//������ ������ ���� ���
			{
				printf("������ ����ؼ� �Է��ϼ���\n\n");
				continue;
			}
			for (int i = 8; i < 256; i++)
			{
				name[i - 8] = word[i];
				if (word[i] == '\0')
					break;
			}
			//�̸� ��Ģ �˻� �߰��ؾߵ�
			//search2(filename, name);
			break;
		}
		else if (strncmp(s4, word, 7) == 0)//gender�� ���
		{
			if (word[8] != ' ')//������ ������ ���� ���
			{
				printf("������ ����ؼ� �Է��ϼ���\n\n");
				continue;
			}
			for (int i = 9; i < 256; i++)
			{
				name[i - 9] = word[i];
				if (word[i] == '\0')
					break;
			}
			//�̸� ��Ģ �˻� �߰��ؾߵ�
			//search2(filename, name);
			break;
		}
		else if (strncmp(s5, word, 5) == 0)//back�� ���
		{
			if (word[6] != ' ')//������ ������ ���� ���
			{
				printf("������ ����ؼ� �Է��ϼ���\n\n");
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
			printf("�߸� �Է��߽��ϴ�.\n\n");
		}
	}
	return 0;

}

int main(void) 
{
	char menu[7]="";//menu ���� �迭

	//�� ������Ʈ
	printf("��ɾ�(''�����ϰ� �Է�) \t ���� \n\n");
	printf("'search' or 's' \t\t ���� ȸ���� �˻��մϴ�. \n");
	printf("'show' or 'sh' \t\t\t �ڽ��� �ּҷ��� �����ݴϴ�. \n");
	printf("'change' or 'c' \t\t �ڽ��� ������ �����մϴ�. \n");
	printf("'quit' or 'q' \t\t\t ���α׷��� �����մϴ�. \n");
	
	while (1)
	{
		printf("name's phone book : ");
		scanf("%s", menu);
		getchar();//���� ����
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
			printf("�߸� �Է��߽��ϴ�.\n\n");
		}
	}
}

