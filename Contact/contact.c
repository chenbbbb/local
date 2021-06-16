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
			printf("���ݳɹ�\n");
		}
	}
}


void AddContact(Contact* pc)
{
	CheckCapacity(pc);
	int ret = 0;
	printf("����������:>");
	ret = scanf("%s", pc->data[pc->last].name);
	printf("����������:>");
	ret = scanf("%d", &(pc->data[pc->last].age));
	printf("�������Ա�:>");
	ret = scanf("%s", pc->data[pc->last].sex);
	printf("������绰:>");
	ret = scanf("%s", pc->data[pc->last].tele);
	printf("�������ַ:>");
	ret = scanf("%s", pc->data[pc->last].addr);
	pc->last++;
}

void ShowContact(Contact* pc)
{
	if (pc->last == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
		return;
	}
	printf("\t%s\t%s\t%s\t%s\t%s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	printf("��������Ҫɾ���˵�����:>");
	char name[MAX_NAME];
	int ret = scanf("%s", name);
	int pos = FindName(pc, name);
	if (pos == -1)
	{
		printf("��Ҫɾ�����˲�����\n");
	}
	else
	{
		memmove(pc->data + pos, pc->data + pos + 1, (pc->last - pos - 1) * sizeof(PeoInfo));
		pc->last--;
		printf("ɾ���ɹ�\n");
	}
}

void SearchContact(const Contact* pc)
{
	printf("������Ҫ�����˵�����:>");
	char name[MAX_NAME];
	int ret = scanf("%s", name);
	int pos = FindName(pc, name);
	if (pos == -1)
	{
		printf("��Ҫ���ҵ��˲�����\n");
	}
	else
	{
		printf("\t%s\t%s\t%s\t%s\t%s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	printf("������Ҫ�޸���Ϣ��������:>");
	char name[MAX_NAME];
	int ret = scanf("%s", name);
	int pos = FindName(pc, name);
	if (pos == -1)
	{
		printf("��Ҫ�޸ĵ��˲�����\n");

	}
	else
	{
		printf("����������:>");
		ret = scanf("%s", pc->data[pos].name);
		printf("����������:>");
		ret = scanf("%d", &(pc->data[pos].age));
		printf("�������Ա�:>");
		ret = scanf("%s", pc->data[pos].sex);
		printf("������绰:>");
		ret = scanf("%s", pc->data[pos].tele);
		printf("�������ַ:>");
		ret = scanf("%s", pc->data[pos].addr);
		printf("�޸ĳɹ�\n");
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