#include "std.h"

extern char day[15];
extern int d_total_money;

extern struct table {
	int m_cnt[10];	//메뉴별 주문량
	int active;	//테이블 활성키
} current_table[9];

extern struct menu {
	char m_name[10];	//메뉴이름
	int m_cost;	//가격
	int m_cnt;	//총 주문량
} menu[10];

void app_init()
{
	console_size_set(62, 45);
	day_input();
	today_file_load();
}

void app_run()
{
	char key;		//메뉴번호
	int current_table_cnt;
	while (1)
	{
		current_table_cnt = 0;
		console_size_set(40, 6);
		system("cls");
		print_menu();
		key = _getch();

		switch (key)
		{
		case '1':	title_run(); break;
		case '2':	setting_choice(); break;
		case '3':	
			for (int i = 0; i < 9;i++)
				if (current_table[i].active == 1)
					current_table_cnt++;
			if (current_table_cnt == 0)
			{
				save_data();
				return;
			}
			else
				alert_remain_table();
		}
	}
}

void app_exit()
{

}

void day_input()
{
	char temp[10];
	time_t timer = 0;
	struct tm t;

	printf("[1] day_init....");

	timer = time(NULL);	//현재 시각(초단위)를 timer에 대입
	localtime_s(&t, &timer);	//분리하여 구조체 대입

	_itoa_s((t.tm_year + 1900), temp,sizeof(temp), 10);
	strcat_s(day, sizeof(day), temp);

	if (t.tm_mon < 10)
	{
		strcat_s(day, sizeof(day), "0");
		_itoa_s(t.tm_mon + 1, temp, sizeof(temp), 10);
		strcat_s(day, sizeof(day), temp);
	}

	else
	{
		_itoa_s(t.tm_mon + 1, temp, sizeof(temp), 10);
		strcat_s(day, sizeof(day), temp);
	}
	

	if (t.tm_mday < 10)
	{
		strcat_s(day, sizeof(day), "0");
		_itoa_s(t.tm_mday, temp, sizeof(temp), 10);
		strcat_s(day, sizeof(day),temp);
	}

	else
	{
		_itoa_s(t.tm_mday, temp, sizeof(temp), 10);
		strcat_s(day, sizeof(day), temp);
	}

	printf(" ok\n");	

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("[SYSTEM] 현재 날짜 : %s\n", day);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

void print_menu()
{
	printf(" **************************************\n");
	printf(" * [1] 실시간 테이블 상황　　　　　　 *\n");
	printf(" * [2] 설정　　　　　　　　　　　　　 *\n");
	printf(" * [3] 종료　　　　　　　　　　　　　 *\n");
	printf(" **************************************\n");
}

void today_file_load()	//오늘의 총매출액 메뉴들하고 각 메뉴들의 판매량 로드
{
	FILE *f = 0;

	printf("[2] %s.dat_load....",day);
	strcat_s(day, sizeof(day), ".dat");
	fopen_s(&f, day, "rb");

	if(f == NULL)
	{
		printf(" fail : 파일이 존재하지 않습니다.\n");
		struct_first_set();

		printf("[2] %s_new_save....", day);
		fopen_s(&f, day, "wb");

		d_total_money = 0;

		fwrite(&d_total_money, sizeof(int), 1,f);
		fwrite(&menu, sizeof(menu), 10, f);

		fclose(f);

		printf(" ok\n");
		fopen_s(&f, day, "rb");
	}
	else
		printf(" processing\n");

	fread(&d_total_money, sizeof(int), 1, f);
	printf("[2] 금일의 총판매액을 로드했습니다. : 현재 %d원\n", d_total_money);

	fread(&menu, sizeof(menu), 1, f);
	printf("[2] 금일의 메뉴별 판매량을 로드했습니다.\n\n");
	for (int i = 0; i < 10; i++)
		printf("%20s의 판매량 : %3d\n", menu[i].m_name, menu[i].m_cnt);
	printf("\n[2] %s_load....", day);
	fclose(f);

	printf(" ok\n");

	printf("[3] menu.dat_load....");
	fopen_s(&f, "menu.dat", "rb");
	if (f == NULL)
	{
		printf(" fail : menu.dat파일이 존재하지 않습니다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] 설정에서 반드시 메뉴를 초기화 해야합니다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		fclose(f);
		printf(" ok\n");
	}

	printf("[4] table.dat_load....");
	fopen_s(&f, "table.dat", "rb");
	if (f == NULL)
	{
		printf(" fail : table.dat파일이 존재하지 않습니다.\n");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] 설정에서 반드시 테이블을 초기화 해야합니다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		fclose(f);
		printf(" ok\n");
	}

	printf("[5] current_table.dat_load....");
	fopen_s(&f, "current_table.dat", "rb");
	if (f == NULL)
	{
		printf(" fail\n");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] current_table.dat파일이 존재하지 않습니다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		for (int i = 0; i < 9; i++)
		{
			current_table[i].active = 0;
			for (int j = 0; j < 10; j++)
				current_table[i].m_cnt[j] = 0;
		}
		fopen_s(&f, "current_table.dat", "wb");
		fwrite(&current_table, sizeof(current_table), 1, f);
		fclose(f);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] current_table.dat파일을 생성하였습니다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		printf("[5] current_table.dat_load.... ok\n");
	}
	else
	{
		int current_table_cnt = 0;
		fread(&current_table, sizeof(current_table), 1, f);
		fclose(f);

		for (int i = 0; i < 9;i++)
			if (current_table[i].active == 1)
				current_table_cnt++;
		if (current_table_cnt == 0)
		{
			printf(" ok\n");
		}
		else
		{
			printf(" ok\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			printf("[SYSTEM] 이전 작업이 정상적으로 종료되지 않았습니다.\n");
			printf("[SYSTEM] 작업중이던 데이터를 \"실시간 테이블 상황\"에 복구하였습니다.\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		
	}
	system("pause");
}

void struct_first_set()
{
	struct menu {
		char m_name[10];	//메뉴이름
		int m_cost;	//가격
		int m_cnt;	//총 주문량
	} temp_menu[10];	//임시적 구조체

	FILE *f1 = 0;
	printf("[2] menu.dat_load....");
	fopen_s(&f1, "menu.dat", "rb");
	if (f1 == NULL)
	{
		printf(" fail : menu.dat파일이 존재하지 않습니다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] 설정에서 반드시 메뉴를 초기화 해야합니다.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		fread(&temp_menu, sizeof(menu), 1, f1);
		fclose(f1);
		printf(" ok\n");

		for (int i = 0; i < 10; i++)
		{
			printf("[2] 메뉴 : %10s -> ", menu[i].m_name);
			strcpy_s(menu[i].m_name, sizeof(menu[i].m_name), temp_menu[i].m_name);
			printf("%10s의 가격 : %6d ->", menu[i].m_name, menu[i].m_cost);
			menu[i].m_cost = temp_menu[i].m_cost;
			printf("%6d\n", menu[i].m_cost);
		}
	}
}

void alert_remain_table()
{
	printf(" ********************************\n");
	printf(" * 아직 운영중인 테이블이 있습니다.\n");
	printf(" * \"실시간 테이블 상황\" 메뉴에서\n");
	printf(" * 테이블을 정산후에 종료하십시오.\n");
	printf(" ********************************\n");
	system("pause");
}

void save_data()
{
	FILE *f = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 10; j++)
			current_table[i].m_cnt[j] = 0;
	}
	fopen_s(&f, "current_table.dat", "wb");
	fwrite(current_table, sizeof(current_table), 1, f);
	fclose(f);
}