#pragma once
#include "mysql.h"
#include "Connect2Database.h"

#include <iostream>
#include <list>
#include <string>
using namespace std;
struct msg
{
	int id;
	char name[255];
	double price;
	int num;//���
	int pnum;//����ĸ���
	double totalprice;//������Ϣ�ܼ۸�

};
struct msg_order//Ϊ��д�����ݿ�
{
	char name[255];
	
};
class CInfoDatabase
{
public:
	CInfoDatabase();
	~CInfoDatabase();
	void charToDouble(const char* ch, double& res);

	void ReadDocline();

	list<msg> ls;//�洢��Ʒ����
};

