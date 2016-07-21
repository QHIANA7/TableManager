#include "std.h"

char day[11];	//��¥
int d_total_money;	//�� �Ǹž�
int table[9];	//���̺� Ȱ��Ű

struct table {
	int m_cnt[10];	// �ֹ���
	int active;	//���̺� Ȱ��Ű
} current_table[9];

struct menu {
	char m_name[10];	//�޴��̸�
	int m_cost;	//����
	int m_cnt;	//�� �ֹ���
} menu[10];

int main()
{
	app_init();
	app_run();
	app_exit();
	return 0;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void console_size_set(int cols, int lines)
{
	char str[30] = "mode con: cols=";
	char temp[10];

	_itoa_s(cols, temp, sizeof(temp), 10);
	strcat_s(str, sizeof(str), temp);
	strcat_s(str, sizeof(str), " lines=");
	_itoa_s(lines, temp, sizeof(temp), 10);
	strcat_s(str, sizeof(str), temp);

	system(str);
}
