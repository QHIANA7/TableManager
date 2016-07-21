#include "std.h"
// file�߰�  table.dat

FILE * ff = 0;

extern int table[9];		//���̺� ��ȣ�� Ȱ������

void table_setting()
{
	int key1;

	console_size_set(40, 20);
	
	wake_table_file();

	while (1)
	{
		system("cls");
		table_check();
		table_print();
		fflush(stdin);
		key1 = _getch();

		switch (key1)
		{
		case '1': table_choice(); break;
		case '2': table_check(); break;
		case '3': table_delete(); break;
		case '0': system("cls"); return;
		}
		system("pause");
	}
}

void wake_table_file()
{
	fopen_s(&ff, "table.dat", "rb");
	if (ff == NULL)
	{
		fopen_s(&ff, "table.dat", "wb");
		fwrite(table, sizeof(table), 1, ff);
		fclose(ff);
	}

	else
	{
		fread(table, sizeof(table), 1, ff);
		fclose(ff);
	}
}

void table_print()
{
	printf("************************************\n");
	printf(" [1] ���̺� Ȱ��ȭ\n");
	printf(" [2] Ȱ��ȭ ���̺� Ȯ��\n");
	printf(" [3] ���̺� ����\n");
	printf(" [0] �ڷΰ���\n");
	printf("************************************\n");
}

void table_check()
{
	printf("************************************\n");
	for (int i = 0; i < 9; i++)
	{
		if (table[i] == 1)
			printf("[%d]\tȰ��ȭ\n",i);
		else
			printf("[%d]\t��Ȱ��ȭ\n", i);
	}
	printf("************************************\n");
}

void table_delete()
{
	char key1;

	while (1)
	{
		system("cls");
		table_check();
		printf("************************************\n");
		printf("���� ��ų ���̺� ��ȣ�� �Է�(0~8)\n");
		printf("['x'�� �Է��ϸ� �����մϴ�] : ");
		fflush(stdin);
		key1 = _getch();
		printf("************************************\n");
		if (key1 >= '0' && key1 < '9')
		{
			if (table[key1 - '0'] == 0)
			{
				printf("[%c] ���̺��� ��Ȱ��ȭ �����Դϴ�.\n", key1);
			}
			else
			{
				table[key1-'0'] = 0;
				fopen_s(&ff, "table.dat", "wb");
				fwrite(table, sizeof(table), 1, ff);
				fclose(ff);
				printf("[%c] ���̺��� ��Ȱ��ȭ �Ǿ����ϴ�.\n", key1);
			}
		}
		else if (key1 == 'x' || key1 == 'X')
			return;
		system("pause");
	}
}

void table_choice()
{
	char key1;
	int cnt=0;
	
	
	while (1)
	{
		system("cls");
		table_check();
		printf("************************************\n");
		printf("Ȱ��ȭ ��ų ���̺� ��ȣ�� �Է�(0~8)\n");
		printf("['x'�� �Է��ϸ� �����մϴ�] : ");
		fflush(stdin);
		key1 = _getch();
		printf("************************************\n");
		if (key1 >= '0' && key1 < '9')
		{
			if (table[key1-'0'] == 1)
			{
				printf("[%c]�� �̹� Ȱ��ȭ �Ǿ��ִ� ���̺��Դϴ�.\n", key1);
				system("pause");
				continue;
			}
			else
			{
				table[key1-'0'] = 1;
				fopen_s(&ff, "table.dat", "wb");
				fwrite(table, sizeof(table), 1, ff);
				fclose(ff);
				printf("[%c] ���̺��� Ȱ��ȭ �Ǿ����ϴ�.\n", key1);
				system("pause");
			}
		}
		else if (key1 == 'x' || key1 == 'X')
		{
			for (int i = 0; i < sizeof(table); i++)
			{
				if (table[i] == 1)
					cnt++;
			}
			printf("�� %d���� ���̺��� Ȱ��ȭ �Ǿ����ϴ�.\n", cnt);
			return;
		}
	}
}