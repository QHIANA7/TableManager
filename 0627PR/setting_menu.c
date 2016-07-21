#include "std.h"
// file추가  menu.dat

extern int d_total_money;
extern char day[15];
extern struct menu {
	char m_name[10];	//메뉴이름
	int m_cost;	//가격
	int m_cnt;	//총 주문량
} menu[10];

FILE *f = 0;

void setting_menu_choice()
{
	int key;

	while (1)
	{
		wake_menu_file();
		console_size_set(35, 30);
		setting_menu_selectall();
		print_setting_menu();
		fflush(stdin);
		key = _getch();

		switch (key)
		{
		case '1': setting_menu_selectall();	break;
		case '2': setting_menu_update();	break;
		case '3': setting_menu_delete();	break;
		case '0': system("cls"); return;
		}
		system("pause");
	}
	
}

void wake_menu_file()
{	
	fopen_s(&f, "menu.dat", "rb");
	if (f == NULL)
	{
		fopen_s(&f, "menu.dat", "wb");
		fwrite(&menu, sizeof(menu), 1, f);
		fclose(f);
	}
	else
	{
		fread(&menu, sizeof(menu), 1, f);
		fclose(f);
	}
}

void setting_menu_selectall()
{
	printf("**********************************\n");
	printf("*        메뉴 & 가격 설정        *\n");
	printf("**********************************\n");
	printf("\t메뉴\t\t가격\n");
	printf("==================================\n");
	for (int i = 0; i < 10; i++)
	{
		printf(" [%d]\t%s\t\t%d\n", i, menu[i].m_name, menu[i].m_cost);
	}
	printf("==================================\n");
}

void print_setting_menu()
{
	printf("**********************************\n");
	printf(" [1] 확인\n");
	printf(" [2] 수정\n");
	printf(" [3] 삭제\n");
	printf(" [0] 뒤로가기\n");
	printf("**********************************\n");
}

void setting_menu_update()
{
	char key;
	char name[10];
	int cost;

	while (1)
	{
		printf("0~9 번호 입력 (완료시 ""x""입력) : ");
		key = _getch();
		if (key == 'x' || key == 'X') { printf("\n"); break; }
		else if (key >= '0' && key < '10')
		{
			printf("\n[%c] 메뉴와 가격을 입력하세요 : ", key);
			scanf_s("%s %d", name, (unsigned int)sizeof(name), &cost);
			strcpy_s(menu[key-'0'].m_name, sizeof(menu[key-'0'].m_name), name);
			menu[key - '0'].m_cost = cost;
			menu[key - '0'].m_cnt = 0;
			system("cls");
			setting_menu_selectall();
			fopen_s(&f, "menu.dat", "wb");
			fwrite(&menu, sizeof(menu), 1, f);
			fclose(f);
			fopen_s(&f, day, "wb");
			fwrite(&d_total_money, sizeof(int), 1, f);
			fwrite(&menu, sizeof(menu), 1, f);
			fclose(f);
		}
		else
		{
			printf("잘못누르셨습니다.\n"); continue;
		}
	}
}

void setting_menu_delete()
{
	char key;

	while (1)
	{
		printf("0~9 번호 입력 (완료시 ""x""입력) : ");
		key = _getch();
		if (key == 'x' || key == 'X') { printf("\n"); break; }
		else if (key >= '0' && key < '10')
		{
			strcpy_s(menu[key-'0'].m_name, sizeof(menu[key-'0'].m_name), "");
			menu[key - '0'].m_cost = 0;
			menu[key - '0'].m_cnt = 0;
			system("cls");
			setting_menu_selectall();
			fopen_s(&f, "menu.dat", "wb");
			fwrite(&menu, sizeof(menu), 1, f);
			fclose(f);
			fopen_s(&f, day, "wb");
			fwrite(&d_total_money, sizeof(int), 1, f);
			fwrite(&menu, sizeof(menu), 1, f);
			fclose(f);
		}
		else
		{
			printf("잘못누르셨습니다.\n"); continue;
		}
	}
}