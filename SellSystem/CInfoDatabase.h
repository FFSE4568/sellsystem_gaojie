#pragma once
#include "mysql.h"
#include "Connect2Database.h"

#include <iostream>
#include <list>
#include <string>
using namespace std;
struct msg
{
	int id;//��Ʒ�ı��
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
struct ordersystem//������Ϣ��
{
	char Username[40];//��������������;
	char Order_Id[20];
	int Cu_Id;
	char Order_Date[20];
	int Order_Status;
	double Order_Totalprice;
};
class CInfoDatabase
{
public:
	CInfoDatabase();
	~CInfoDatabase();
	void charToDouble(const char* ch, double& res);

	void ReadDocline();

	list<msg> ls;//�洢��Ʒ����
	list<ordersystem> order;//������Ϣ
	void ReadInfo_Order();
};

