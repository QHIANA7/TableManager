#include "std.h"

extern char day[15];
extern int d_total_money;

extern struct table {
	int m_cnt[10];	//�޴��� �ֹ���
	int active;	//���̺� Ȱ��Ű
} current_table[9];

extern struct menu {
	char m_name[10];	//�޴��̸�
	int m_cost;	//����
	int m_cnt;	//�� �ֹ���
} menu[10];

void app_init()
{
	console_size_set(62, 45);
	day_input();
	today_file_load();
}

void app_run()
{
	char key;		//�޴���ȣ
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

	timer = time(NULL);	//���� �ð�(�ʴ���)�� timer�� ����
	localtime_s(&t, &timer);	//�и��Ͽ� ����ü ����

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
	printf("[SYSTEM] ���� ��¥ : %s\n", day);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

void print_menu()
{
	printf(" **************************************\n");
	printf(" * [1] �ǽð� ���̺� ��Ȳ������������ *\n");
	printf(" * [2] ������������������������������ *\n");
	printf(" * [3] ���ᡡ������������������������ *\n");
	printf(" **************************************\n");
}

void today_file_load()	//������ �Ѹ���� �޴����ϰ� �� �޴����� �Ǹŷ� �ε�
{
	FILE *f = 0;

	printf("[2] %s.dat_load....",day);
	strcat_s(day, sizeof(day), ".dat");
	fopen_s(&f, day, "rb");

	if(f == NULL)
	{
		printf(" fail : ������ �������� �ʽ��ϴ�.\n");
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
	printf("[2] ������ ���Ǹž��� �ε��߽��ϴ�. : ���� %d��\n", d_total_money);

	fread(&menu, sizeof(menu), 1, f);
	printf("[2] ������ �޴��� �Ǹŷ��� �ε��߽��ϴ�.\n\n");
	for (int i = 0; i < 10; i++)
		printf("%20s�� �Ǹŷ� : %3d\n", menu[i].m_name, menu[i].m_cnt);
	printf("\n[2] %s_load....", day);
	fclose(f);

	printf(" ok\n");

	printf("[3] menu.dat_load....");
	fopen_s(&f, "menu.dat", "rb");
	if (f == NULL)
	{
		printf(" fail : menu.dat������ �������� �ʽ��ϴ�.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] �������� �ݵ�� �޴��� �ʱ�ȭ �ؾ��մϴ�.\n");
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
		printf(" fail : table.dat������ �������� �ʽ��ϴ�.\n");

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] �������� �ݵ�� ���̺��� �ʱ�ȭ �ؾ��մϴ�.\n");
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
		printf("[SYSTEM] current_table.dat������ �������� �ʽ��ϴ�.\n");
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
		printf("[SYSTEM] current_table.dat������ �����Ͽ����ϴ�.\n");
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
			printf("[SYSTEM] ���� �۾��� ���������� ������� �ʾҽ��ϴ�.\n");
			printf("[SYSTEM] �۾����̴� �����͸� \"�ǽð� ���̺� ��Ȳ\"�� �����Ͽ����ϴ�.\n");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		
	}
	system("pause");
}

void struct_first_set()
{
	struct menu {
		char m_name[10];	//�޴��̸�
		int m_cost;	//����
		int m_cnt;	//�� �ֹ���
	} temp_menu[10];	//�ӽ��� ����ü

	FILE *f1 = 0;
	printf("[2] menu.dat_load....");
	fopen_s(&f1, "menu.dat", "rb");
	if (f1 == NULL)
	{
		printf(" fail : menu.dat������ �������� �ʽ��ϴ�.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("[SYSTEM] �������� �ݵ�� �޴��� �ʱ�ȭ �ؾ��մϴ�.\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else
	{
		fread(&temp_menu, sizeof(menu), 1, f1);
		fclose(f1);
		printf(" ok\n");

		for (int i = 0; i < 10; i++)
		{
			printf("[2] �޴� : %10s -> ", menu[i].m_name);
			strcpy_s(menu[i].m_name, sizeof(menu[i].m_name), temp_menu[i].m_name);
			printf("%10s�� ���� : %6d ->", menu[i].m_name, menu[i].m_cost);
			menu[i].m_cost = temp_menu[i].m_cost;
			printf("%6d\n", menu[i].m_cost);
		}
	}
}

void alert_remain_table()
{
	printf(" ********************************\n");
	printf(" * ���� ����� ���̺��� �ֽ��ϴ�.\n");
	printf(" * \"�ǽð� ���̺� ��Ȳ\" �޴�����\n");
	printf(" * ���̺��� �����Ŀ� �����Ͻʽÿ�.\n");
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