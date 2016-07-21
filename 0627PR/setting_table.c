#include "std.h"
// file추가  table.dat

FILE * ff = 0;

extern int table[9];		//테이블 번호의 활성유무

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
	printf(" [1] 테이블 활성화\n");
	printf(" [2] 활성화 테이블 확인\n");
	printf(" [3] 테이블 제거\n");
	printf(" [0] 뒤로가기\n");
	printf("************************************\n");
}

void table_check()
{
	printf("************************************\n");
	for (int i = 0; i < 9; i++)
	{
		if (table[i] == 1)
			printf("[%d]\t활성화\n",i);
		else
			printf("[%d]\t비활성화\n", i);
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
		printf("삭제 시킬 테이블 번호를 입력(0~8)\n");
		printf("['x'를 입력하면 종료합니다] : ");
		fflush(stdin);
		key1 = _getch();
		printf("************************************\n");
		if (key1 >= '0' && key1 < '9')
		{
			if (table[key1 - '0'] == 0)
			{
				printf("[%c] 테이블은 비활성화 상태입니다.\n", key1);
			}
			else
			{
				table[key1-'0'] = 0;
				fopen_s(&ff, "table.dat", "wb");
				fwrite(table, sizeof(table), 1, ff);
				fclose(ff);
				printf("[%c] 테이블이 비활성화 되었습니다.\n", key1);
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
		printf("활성화 시킬 테이블 번호를 입력(0~8)\n");
		printf("['x'를 입력하면 종료합니다] : ");
		fflush(stdin);
		key1 = _getch();
		printf("************************************\n");
		if (key1 >= '0' && key1 < '9')
		{
			if (table[key1-'0'] == 1)
			{
				printf("[%c]는 이미 활성화 되어있는 테이블입니다.\n", key1);
				system("pause");
				continue;
			}
			else
			{
				table[key1-'0'] = 1;
				fopen_s(&ff, "table.dat", "wb");
				fwrite(table, sizeof(table), 1, ff);
				fclose(ff);
				printf("[%c] 테이블이 활성화 되었습니다.\n", key1);
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
			printf("총 %d개의 테이블이 활성화 되었습니다.\n", cnt);
			return;
		}
	}
}