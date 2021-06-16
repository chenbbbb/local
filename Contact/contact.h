/*
* 
* 
* 
* ��ǰ�汾��1.0
* ��    �ߣ��±�
* ������ڣ�2021��6��12�� 
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

//��ʼ��ͨѶ¼
void InitContact(Contact* pc);

//ΪͨѶ¼������Ϣ
void AddContact(Contact* pc);

//�鿴ͨѶ¼
void ShowContact(Contact* pc);

//ɾ��ͨѶ¼��Ϣ
void DeleteContact(Contact* pc);

//����ͨѶ¼
void SearchContact(const Contact* pc);

//�޸�ͨѶ¼��ĳ���˵���Ϣ
void ModifyContact(Contact* pc);

//����������ͨѶ¼����
void SortContact(Contact* pc, int left, int right);

//����Ϣ���浽�ļ���
void SaveContact(Contact* pc);

//�ݻ�ͨѶ¼���ͷ��ڴ�
void DestoryContact(Contact* pc);

//�����ļ��е���Ϣ��ͨѶ¼
void LoadContact(Contact* pc);

#endif