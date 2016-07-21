#include "std.h"

extern char day[15];

extern struct menu {
	char m_name[10];	//메뉴이름
	int m_cost;	//가격
	int m_cnt;	//총 주문량
} menu[10];

extern int d_total_money;

extern struct table {
	int m_cnt[10];	// 주문량
	int active;	//테이블 활성키
} current_table[9];

extern int table[9];

int cnt[9][10];		//테이블 /메뉴별 주문량

void title_init()
{

	console_size_set(133, 42);
	title_display();
	title_load_table();
	is_current_table();

}

void title_run()
{
	title_init();
	
	char key;		//메뉴번호
	while (1)
	{
		key = _getch();

		switch (key)
		{
		case '1':	title_order(); break;
		case '2':	title_pay(); break;
		case '0':	save_current_table(); return;
		}
	}
}

void title_exit()
{

}

void title_load_table()
{
	FILE *f = 0;
	fopen_s(&f, "table.dat", "rb");
	if (f == NULL)
	{
		title_menubar_clear();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf(" [SYSTEM] table.dat 파일이 존재하지않습니다. 설정에서 초기화 해야합니다.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(2, 39); system("pause");
		title_menubar_clear();
		title_menubar_main();
	}
	else
	{
		fread(table, sizeof(table), 1, f);
		fclose(f);
	}

	for (int i = 1; i < 10; i++)
	{
		int x, y;

		if (i > 6)
		{
			x = i - 6;
			y = 2;
		}
		else if (i > 3)
		{
			x = i - 3;
			y = 1;
		}
		else
		{
			x = i;
			y = 0;
		}

			gotoxy(6 + (44 * (x - 1)), 1 + (12 * y));
			if (table[i-1] == 1)
				printf("활성");
			else
				printf("비활성");
	}
	gotoxy(129, 38);
}

void title_load_menu()
{

}

void title_display()
{
	for (int i = 0; i < 3; i++)
	{
		printf("┌─┬──────────────────┐┌─┬──────────────────┐┌─┬──────────────────┐\n");
		printf("│%02d│　　　　　　　　　　　　　　　　　　││%02d│　　　　　　　　　　　　　　　　　　││%02d│　　　　　　　　　　　　　　　　　　│\n", (3 * i) + 1, (3 * i) + 2, (3 * i) + 3);
		printf("├─┘　　　　　　　　　　　　　　　　　　│├─┘　　　　　　　　　　　　　　　　　　│├─┘　　　　　　　　　　　　　　　　　　│\n");
		for (int j = 0; j < 8; j++)
			printf("│　　　　　　　　　　　　　　　　　　　　││　　　　　　　　　　　　　　　　　　　　││　　　　　　　　　　　　　　　　　　　　│\n");
		printf("└────────────────────┘└────────────────────┘└────────────────────┘\n");
	}

	printf("┌────────────────────────────────────────────────────────────────┐\n");
	for (int j = 0; j < 3; j++)
		printf("│　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　│\n");
	printf("└────────────────────────────────────────────────────────────────┘\n");

	title_menubar_main();
}

void title_order()
{
	char table_key;
	title_menubar_clear();
	printf("테이블 번호를 입력하세요 : ");

	table_key = _getch();
	if ((49 <= table_key) && (57 >= table_key) && (table[table_key - 49] == 0))
	{
		title_menubar_clear();
		title_menubar_main();
		gotoxy(2, 37);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("\t\t\t\t\t   [SYSTEM] 해당 테이블은 비활성화 되있습니다.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(129, 38);
		return;
	}
	else
	{
		int menu_num = menu_display();
		title_menubar_clear();
		int order_cnt = order_cnt_display(menu_num);
		cnt[table_key - 49][menu_num] += order_cnt;
		if (cnt[table_key - 49][menu_num] == 0)
		{
			title_menubar_clear();
			printf("주문이 취소되었습니다.		");
			system("pause");
			title_menubar_clear();
			title_menubar_main();
			return;
		}
		title_menubar_clear();
		show_order_to_title(table_key - 48, menu_num);
		title_menubar_clear();
		current_table[table_key - 49].active = 1;	//테이블 활성화
		current_table[table_key - 49].m_cnt[menu_num] = cnt[table_key - 49][menu_num];
		save_current_table();
		title_menubar_clear();
		title_menubar_main();
		gotoxy(2, 37);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("\t\t\t\t\t[SYSTEM] %d 번 테이블에 %10s %2d개 주문완료", table_key - 48, menu[menu_num].m_name, order_cnt);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(129, 38);
		
	}
}

void title_pay()
{
	char table_key;
	char key;
	title_menubar_clear();
	printf("테이블 번호를 입력하세요 : ");

	table_key = _getch();

	if ((49 <= table_key) && (57 >= table_key) && (current_table[table_key - 49].active == 0))
	{
		title_menubar_clear();
		title_menubar_main();
		gotoxy(2, 37);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		printf("\t\t\t\t[SYSTEM] 해당 테이블은 비활성화 되있거나 주문이 없는 상태입니다.");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(129, 38);
		return;
	}
	else
	{
		title_menubar_clear();
		printf("%d번 테이블을 정산하시겠습니까? (1 : 정산, 0 : 취소)", table_key - 48);
		key = _getch();
		if (key == 48)
		{
			title_menubar_clear();
			title_menubar_main();
			return;
		}
		else if (key == 49)
		{
			int total_payment = 0;
			for (int i = 0; i < 10; i++)
			{
				total_payment += (cnt[table_key - 49][i] * menu[i].m_cost);
				menu[i].m_cnt += cnt[table_key - 49][i];
			}
			title_menubar_clear();
			printf("총 %8d 원의 금액을 정산하였습니다.		", total_payment);
			
			d_total_money += total_payment;

			current_table[table_key - 49].active = 0;
			for (int j = 0; j < 10; j++)
				current_table[table_key - 49].m_cnt[j] = 0;
			save_current_table();
			save_current_data();

			for (int i = 0; i < 10; i++)
			{
				cnt[table_key - 49][i] = 0;	//계산완료 후 초기화
			}

			show_pay_to_title(table_key - 48);

			system("pause");

			title_menubar_clear();
			title_menubar_main();
		}

	}
}

void title_menubar_clear()
{
	gotoxy(2, 37);
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	gotoxy(2, 38);
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	gotoxy(2, 39);
	printf("　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　");
	gotoxy(2, 38);
}

void title_menubar_main()
{
	gotoxy(2, 38);
	printf("[1] 주문        [2] 정산        [0]복귀");
	gotoxy(129, 38);
}

int menu_display()
{
	char menu_key;
	gotoxy(2, 37);
	for (int i = 0;i < 10; i++)
	{
		printf("[%d] %-10s ", i,menu[i].m_name);
		if((i+1)%5 == 0)
			gotoxy(2, 37+((i+1)/5));
	}
	printf("주문할 메뉴번호를 입력하세요 : ");
	menu_key = _getch();

	return menu_key - 48;
}

int order_cnt_display(int menu_num)
{
	char key;
	int order_cnt = 0;

	while (1)
	{
		title_menubar_clear();
		gotoxy(2, 37);
		printf("주문량 0 : 주문취소");
		gotoxy(2, 38);
		printf("%s의 주문량을 조절하세요(1 : 감소, 2: 증가, 3 : 결정) : %d", menu[menu_num].m_name, order_cnt);
		key = _getch();
		if (key == 51)
			break;
		else if (key == 49)
			order_cnt--;
		else if (key == 50)
			order_cnt++;

		if (order_cnt < 0)
			order_cnt = 0;
		if(order_cnt>50)
			order_cnt = 50;
	}

	return order_cnt;
}

void show_order_to_title(int t, int m)	//테이블 번호, 메뉴번호
{
		int x, y;

		if (t > 6)
		{
			x = t - 6;
			y = 2;
		}
		else if (t > 3)
		{
			x = t - 3;
			y = 1;
		}
		else
		{
			x = t;
			y = 0;
		}

		gotoxy(27 + (44 * (x - 1)), 1 + (12 * y) + m);
			printf("%10s : %2d",menu[m].m_name, cnt[t-1][m]);
	gotoxy(129, 38);
}

void save_current_data()
{
	FILE *f = 0;
	fopen_s(&f, day, "wb");
	fwrite(&d_total_money, sizeof(int), 1, f);
	fwrite(&menu, sizeof(menu), 1, f);
	fclose(f);
}

void show_pay_to_title(int t)
{
	int x, y;

	if (t > 6)
	{
		x = t - 6;
		y = 2;
	}
	else if (t > 3)
	{
		x = t - 3;
		y = 1;
	}
	else
	{
		x = t;
		y = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		gotoxy(27 + (44 * (x - 1)), 1 + (12 * y) + i);
		printf("%10s   %2s","","");
	}
	gotoxy(2, 39);
}

void is_current_table()
{
	FILE *f = 0;
	fopen_s(&f, "current_table.dat", "rb");
	fread(current_table, sizeof(current_table), 1, f);
	fclose(f);

	for (int i = 1; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			if (current_table[i-1].active == 1)
			{
				int x, y;

				if (i > 6)
				{
					x = i - 6;
					y = 2;
				}
				else if (i > 3)
				{
					x = i - 3;
					y = 1;
				}
				else
				{
					x = i;
					y = 0;
				}

				gotoxy(27 + (44 * (x - 1)), 1 + (12 * y) + j);
				if (current_table[i - 1].m_cnt[j] > 0)
				{
					printf("%10s : %2d", menu[j].m_name, current_table[i - 1].m_cnt[j]);
					cnt[i - 1][j] = current_table[i - 1].m_cnt[j];
				}
			}
		}
	gotoxy(129, 38);
}

void save_current_table()
{
	FILE *f = 0;
	fopen_s(&f, "current_table.dat", "wb");
	fwrite(current_table, sizeof(current_table), 1, f);
	fclose(f);
}