/*
* 
* 
* 
* 当前版本：1.0
* 作    者：陈兵
* 完成日期：2021年6月12日 
* 
* 
*/

//#pragma once
#ifndef CONTACT_H
#define CONTACT_H

#define _CRT_SECURE_NO_WARNINGS 1

#define DEFAULT_SZ 3
#define MAX_NAME 20
#define MAX_SEX 4
#define MAX_TELE 20
#define MAX_ADDR 40

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum
{
	EXIT,
	ADD,
	DELETE,
	MODIFY,
	SEARCH,
	SHOW,
	SORT
};

typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
} PeoInfo;

typedef struct Contact
{
	PeoInfo* data;
	int last;
	int size;
} Contact;

//初始化通讯录
void InitContact(Contact* pc);

//为通讯录增加信息
void AddContact(Contact* pc);

//查看通讯录
void ShowContact(Contact* pc);

//删除通讯录信息
void DeleteContact(Contact* pc);

//查找通讯录
void SearchContact(const Contact* pc);

//修改通讯录中某个人的信息
void ModifyContact(Contact* pc);

//按照姓名给通讯录排序
void SortContact(Contact* pc, int left, int right);

//把信息储存到文件中
void SaveContact(Contact* pc);

//摧毁通讯录，释放内存
void DestoryContact(Contact* pc);

//加载文件中的信息到通讯录
void LoadContact(Contact* pc);

#endif