#include "std.h"
// file�߰�  menu.dat

extern int d_total_money;
extern char day[15];
extern struct menu {
	char m_name[10];	//�޴��̸�
	int m_cost;	//����
	int m_cnt;	//�� �ֹ���
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
	printf("*        �޴� & ���� ����        *\n");
	printf("**********************************\n");
	printf("\t�޴�\t\t����\n");
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
	printf(" [1] Ȯ��\n");
	printf(" [2] ����\n");
	printf(" [3] ����\n");
	printf(" [0] �ڷΰ���\n");
	printf("**********************************\n");
}

void setting_menu_update()
{
	char key;
	char name[10];
	int cost;

	while (1)
	{
		printf("0~9 ��ȣ �Է� (�Ϸ�� ""x""�Է�) : ");
		key = _getch();
		if (key == 'x' || key == 'X') { printf("\n"); break; }
		else if (key >= '0' && key < '10')
		{
			printf("\n[%c] �޴��� ������ �Է��ϼ��� : ", key);
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
			printf("�߸������̽��ϴ�.\n"); continue;
		}
	}
}

void setting_menu_delete()
{
	char key;

	while (1)
	{
		printf("0~9 ��ȣ �Է� (�Ϸ�� ""x""�Է�) : ");
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
			printf("�߸������̽��ϴ�.\n"); continue;
		}
	}
}