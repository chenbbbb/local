#include "contact.h"

void InitContact(Contact* pc)
{
	pc->data = (PeoInfo*)malloc(DEFAULT_SZ * sizeof(PeoInfo));
	pc->size = DEFAULT_SZ;
	pc->last = 0;
	LoadContact(pc);
}

void CheckCapacity(Contact* pc);

void LoadContact(Contact* pc)
{
	PeoInfo tmp = { 0 };
	FILE* pf = fopen("contact.dat", "rb");
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	while (fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		CheckCapacity(pc);
		pc->data[pc->last] = tmp;
		pc->last++;
	}
	fclose(pf);
	pf = NULL;
}

void CheckCapacity(Contact* pc)
{
	if (pc->last == pc->size)
	{
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->size + 2) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->size = pc->size + 2;
			printf("扩容成功\n");
		}
	}
}


void AddContact(Contact* pc)
{
	CheckCapacity(pc);
	int ret = 0;
	printf("请输入姓名:>");
	ret = scanf("%s", pc->data[pc->last].name);
	printf("请输入年龄:>");
	ret = scanf("%d", &(pc->data[pc->last].age));
	printf("请输入性别:>");
	ret = scanf("%s", pc->data[pc->last].sex);
	printf("请输入电话:>");
	ret = scanf("%s", pc->data[pc->last].tele);
	printf("请输入地址:>");
	ret = scanf("%s", pc->data[pc->last].addr);
	pc->last++;
}

void ShowContact(Contact* pc)
{
	if (pc->last == 0)
	{
		printf("通讯录为空\n");
		return;
	}
	printf("\t%s\t%s\t%s\t%s\t%s\n", "姓名", "年龄", "性别", "电话", "地址");
	int i = 0;
	for (i = 0; i < pc->last; i++)
	{
		printf("\t%s\t%d\t%s\t%s\t%s\n",
			pc->data[i].name,
			pc->data[i].age,
			pc->data[i].sex,
			pc->data[i].tele,
			pc->data[i].addr);

	}
}

static int FindName(const Contact* pc, const char* name)
{
	int i = 0;
	for (i = 0; i < pc->last; i++)
	{
		if (0 == strcmp(name, pc->data[i].name))
		{
			return i;
		}
	}
	return -1;
}

void DeleteContact(Contact* pc)
{
	printf("请输入你要删除人的姓名:>");
	char name[MAX_NAME];
	int ret = scanf("%s", name);
	int pos = FindName(pc, name);
	if (pos == -1)
	{
		printf("你要删除的人不存在\n");
	}
	else
	{
		memmove(pc->data + pos, pc->data + pos + 1, (pc->last - pos - 1) * sizeof(PeoInfo));
		pc->last--;
		printf("删除成功\n");
	}
}

void SearchContact(const Contact* pc)
{
	printf("请输入要查找人的姓名:>");
	char name[MAX_NAME];
	int ret = scanf("%s", name);
	int pos = FindName(pc, name);
	if (pos == -1)
	{
		printf("你要查找的人不存在\n");
	}
	else
	{
		printf("\t%s\t%s\t%s\t%s\t%s\n", "姓名", "年龄", "性别", "电话", "地址");
		printf("\t%s\t%d\t%s\t%s\t%s\n",
			pc->data[pos].name,
			pc->data[pos].age,
			pc->data[pos].sex,
			pc->data[pos].tele,
			pc->data[pos].addr);
	}
}

void ModifyContact(Contact* pc)
{
	printf("请输入要修改信息的人姓名:>");
	char name[MAX_NAME];
	int ret = scanf("%s", name);
	int pos = FindName(pc, name);
	if (pos == -1)
	{
		printf("你要修改的人不存在\n");

	}
	else
	{
		printf("请输入姓名:>");
		ret = scanf("%s", pc->data[pos].name);
		printf("请输入年龄:>");
		ret = scanf("%d", &(pc->data[pos].age));
		printf("请输入性别:>");
		ret = scanf("%s", pc->data[pos].sex);
		printf("请输入电话:>");
		ret = scanf("%s", pc->data[pos].tele);
		printf("请输入地址:>");
		ret = scanf("%s", pc->data[pos].addr);
		printf("修改成功\n");
	}
}

static void swap(PeoInfo* px, PeoInfo* py)
{
	PeoInfo tmp = *px;
	*px = *py;
	*py = tmp;
}

void SortContact(Contact* pc, int left, int right)
{
	int i, tail;
	if (left >= right)
	{
		return;
	}
	swap(pc->data + left, pc->data + (left+right)/2);
	tail = left;
	for (i = left + 1; i <= right; i++)
	{
		if (strcmp(pc->data[i].name, pc->data[left].name) < 0)
		{
			swap(pc->data + ++tail, pc->data + i);
		}
	}
	swap(pc->data + left, pc->data + tail);
	SortContact(pc, left, tail - 1);
	SortContact(pc, tail + 1, right);
}

void SaveContact(Contact* pc)
{
	FILE* pf = fopen("contact.dat", "wb");
	int i = 0;
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}
	for (i = 0; i < pc->last; i++)
	{
		fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);

	}
	fclose(pf);
	pf = NULL;
}

void DestoryContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
}