#include "contact.h"

void menu()
{
	printf("***********************************\n");
	printf("****     1.add     2.delete     ***\n");
	printf("****     3.modify  4.search     ***\n");
	printf("****     5.show    6.sort       ***\n");
	printf("****     0.exit                 ***\n");
	printf("***********************************\n");
}

int main()
{
	int input = 0;
	Contact con = { 0 };
	InitContact(&con);
	do
	{
		menu();
		printf("请选择:>");
		int ret = scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&con);
			break;
		case DELETE:
			DeleteContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case SHOW:
			ShowContact(&con);
			break;
		case SORT:
			SortContact(&con, 0, con.last - 1);
			break;
		case EXIT:
			SaveContact(&con);
			DestoryContact(&con);
			printf("退出成功\n");
			break;
		default:
			printf("请输入正确的数字\n");
			break;
		}
	} while (input);
	return 0;
}