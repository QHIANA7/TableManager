#include "std.h"

void setting_choice()
{
	char key;		//�޴�

	

	while (1)
	{	
		setting_printmenu();

		key = _getch();

		switch (key)
		{
		case '1': table_setting(); break;			//���̺� �߰� & ����
		case '2': setting_menu_choice(); break;			//�޴� & ���� ����
		case '0': return;
		}
	}
}

void setting_printmenu()
{
	console_size_set(40, 6);
	printf(" **************************************\n");
	printf(" * [1] ���̺� �߰� & ���š����������� *\n");
	printf(" * [2] �޴� & ���� ������������������ *\n");
	printf(" * [0] �ڷΰ��⡡�������������������� *\n");
	printf(" **************************************\n");
}