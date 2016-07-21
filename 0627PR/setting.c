#include "std.h"

void setting_choice()
{
	char key;		//메뉴

	

	while (1)
	{	
		setting_printmenu();

		key = _getch();

		switch (key)
		{
		case '1': table_setting(); break;			//테이블 추가 & 제거
		case '2': setting_menu_choice(); break;			//메뉴 & 가격 설정
		case '0': return;
		}
	}
}

void setting_printmenu()
{
	console_size_set(40, 6);
	printf(" **************************************\n");
	printf(" * [1] 테이블 추가 & 제거　　　　　　 *\n");
	printf(" * [2] 메뉴 & 가격 설정　　　　　　　 *\n");
	printf(" * [0] 뒤로가기　　　　　　　　　　　 *\n");
	printf(" **************************************\n");
}