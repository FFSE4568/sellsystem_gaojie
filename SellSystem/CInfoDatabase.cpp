#include "stdafx.h"
#include "CInfoDatabase.h"


CInfoDatabase::CInfoDatabase()
{
}


CInfoDatabase::~CInfoDatabase()
{
}
void CInfoDatabase::charToDouble(const char* ch, double& res)
{
	sscanf(ch, "%lf", &res);
}

void CInfoDatabase::ReadDocline()
{
	msg tmp;//�����Ʒ��Ϣ�ṹ��
	MYSQL_RES *res;
	MYSQL_ROW row;
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();

	CString select_sql_by_product;
	select_sql_by_product.Format("SELECT C_Name,C_Price,ware_Count  from commodity,warehouse WHERE commodity.C_Id=warehouse.C_Id");
	mysql_query(&mysqlCon, "set names utf8");
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)select_sql_by_product);
	if (ress == 0)
	{
		//MessageBox("���ҳɹ�");
		res = mysql_store_result(&mysqlCon);
		if (mysql_num_rows(res) == 0) //��ѯ���Ϊ��
		{
			MessageBox(NULL,"��ʾ��Ϣ","�̼���ʱ����Ʒ����\n",0);
		}
		else
		{
			char szBuffer[1024];
			//CString wszString;
			while (row = mysql_fetch_row(res))
			{
				sprintf(szBuffer, "%s", row[0]);
				int wcsLen = MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), NULL, 0);
				wchar_t* wszString = new wchar_t[wcsLen + 1];
				MultiByteToWideChar(CP_UTF8, 0, szBuffer, strlen(szBuffer), wszString, wcsLen);
				wszString[wcsLen] = '\0';
				WideCharToMultiByte(CP_ACP, 0, wszString, -1,tmp.name, sizeof(tmp.name), NULL, NULL);//����Ʒ���ָ�ֵ���ṹ��
				//MessageBox(NULL, "sfs", (CString)tmp.name, 0);
				double tmp_price;
				charToDouble(row[1], tmp_price);
				tmp.price = tmp_price;//����Ʒ�ļ۸�ֵ���ṹ��
				//��渳ֵ
				char tmp_num[20];
				sprintf(tmp_num, "%s", row[2]);
				tmp.num=atoi(tmp_num);//����Ʒ�Ŀ�渳ֵ���ṹ��
				//��ӽ�����
				ls.push_back(tmp);
				//MessageBox((CString)wszString);
				delete wszString;
			}
		}
	}
}
