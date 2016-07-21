#include "std.h"

char day[11];	//날짜
int d_total_money;	//총 판매액
int table[9];	//테이블 활성키

struct table {
	int m_cnt[10];	// 주문량
	int active;	//테이블 활성키
} current_table[9];

struct menu {
	char m_name[10];	//메뉴이름
	int m_cost;	//가격
	int m_cnt;	//총 주문량
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
