// CAddC.cpp: 实现文件
//

#include "stdafx.h"
#include "SellSystem.h"
#include "CAddC.h"
#include "afxdialogex.h"
#include "CInfoDatabase.h"

// CAddC 对话框

IMPLEMENT_DYNCREATE(CAddC, CFormView);

CAddC::CAddC()
	:CFormView(CAddC::IDD)
	, m_Iprice(_T(""))
	, m_Inum(0)
	, m_Oprice(0)
	, m_name(_T(""))
	, m_IPrice(0)
	, m_warecount(0)
	, m_CPrice(0)
{
}

CAddC::~CAddC()
{
}

void CAddC::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_Iprice);
	DDX_Text(pDX, IDC_EDIT2, m_Inum);
	DDX_Text(pDX, IDC_EDIT5, m_Oprice);
	DDX_Text(pDX, IDC_EDIT3, m_name);
	//  DDX_Control(pDX, IDC_EDIT4, m_IPrice);
	DDX_Text(pDX, IDC_EDIT4, m_IPrice);
	DDX_Text(pDX, IDC_EDIT6, m_warecount);
	DDX_Text(pDX, IDC_EDIT7, m_CPrice);
}


BEGIN_MESSAGE_MAP(CAddC, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CAddC::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddC::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddC::OnBnClickedButton4)
END_MESSAGE_MAP()

#ifdef _DEBUG
void CAddC::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddC::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
// CAddC 消息处理程序


void CAddC::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_Inum <= 0)
	{
		MessageBox("添加的个数需大于零");
	}
	else if (m_Inum > 0)
	{
		int result_add_number = 0;
		int C_id;
		int index = m_combo.GetCurSel();
		CString name;
		m_combo.GetLBText(index, name);
		CInfoDatabase data;
		data.ReadDocline();
		for (list<msg>::iterator it = data.ls.begin(); it != data.ls.end(); it++)
		{
			if ((CString)it->name == name)
			{
				result_add_number = it->num;
				C_id = it->id;
				break;
			}
		}
		result_add_number += m_Inum;
		MYSQL mysqlCon;
		Connect2Database con;
		mysqlCon = con.getconnect();
		CString update_Ware_Count;
		CString update_C_Price;
		update_C_Price.Format("UPDATE commodity SET C_Price=%lf WHERE C_Id=%d",m_Oprice,C_id);
		update_Ware_Count.Format("UPDATE warehouse SET Ware_Count=%d WHERE C_Id=%d",result_add_number,C_id);
		int ress=mysql_query(&mysqlCon,(char*)(LPCSTR)update_Ware_Count);
		int ress1 = mysql_query(&mysqlCon,(char*)(LPCSTR)update_C_Price);
		if (ress == 0 && ress1==0)
		{
			MessageBox("更新库存成功!");
		}
		else
		{
			MessageBox("连接数据库失败!");
		}

	}
}


void CAddC::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	((CEdit*)m_combo.GetWindow(GW_CHILD))->SetReadOnly();
	//初始化下拉框
	CInfoDatabase data;
	//把商品读入data对象中
	data.ReadDocline();

	for (list<msg>::iterator it = data.ls.begin(); it != data.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name));
	}
	//设置初始化的商品
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}


void CAddC::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoDatabase data;
	data.ReadDocline();
	for (list<msg>::iterator it = data.ls.begin(); it != data.ls.end(); it++)
	{
		if ((CString)it->name == name)
		{
			m_Oprice = it->price;
			CString tmp;
			tmp.Format("%lf",it->IPrice);
			m_Iprice = tmp;
			UpdateData(FALSE);
		}
	}
}


void CAddC::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_name.IsEmpty())
	{
		MessageBox("输入的商品名字不能为空!");
	}
	else if (m_IPrice <= 0 || isdigit(m_IPrice))
	{
		MessageBox("输入的商品的进价不正确");
	}
	else if (m_warecount <= 0 || isdigit(m_warecount))
	{
		MessageBox("输入的商品的个数不正确");
	}
	else if (m_CPrice <= 0 || isdigit(m_CPrice))
	{
		MessageBox("输入的商品的单价不正确");
	}
	else
	{
		MYSQL mysqlCon;
		Connect2Database con;
		mysqlCon = con.getconnect();
		MYSQL_RES *res;
		MYSQL_ROW row;
		int max_C_id;
		CString sql_get_max_id;
		sql_get_max_id.Format("SELECT MAX(C_Id) FROM commodity");
		mysql_query(&mysqlCon, "set names utf8");
		int ress = mysql_query(&mysqlCon, (char *)(LPCSTR)sql_get_max_id);
		if (ress == 0)
		{
			res = mysql_store_result(&mysqlCon);
			if (mysql_num_rows(res) == 0)
			{
				MessageBox("当前无商品再仓库中");
				max_C_id = 1;
			}
			else
			{
				char tmpnum[20];
				row = mysql_fetch_row(res);
				sprintf(tmpnum, "%s", row[0]);
				max_C_id = atoi(tmpnum) + 1;
			}
		}
		else
		{
			MessageBox("查找C_Id访问数据库失败");
		}
		CString insert_commodity;
		CString insert_warehouse;
		insert_commodity.Format("INSERT INTO commodity VALUES(%d,\'%s\',%lf,%lf)",max_C_id,m_name,m_IPrice,m_CPrice);

		char tmp_insert_commodity[255];
		char szBuffer[1024];
		sprintf(szBuffer, "%s", (char *)(LPCSTR)insert_commodity);
		int wcsLen = MultiByteToWideChar(CP_ACP, 0, szBuffer, strlen(szBuffer), NULL, 0);
		wchar_t* wszString = new wchar_t[wcsLen + 1];
		MultiByteToWideChar(CP_ACP, 0, szBuffer, strlen(szBuffer), wszString, wcsLen);
		wszString[wcsLen] = '\0';
		WideCharToMultiByte(CP_UTF8, 0, wszString, -1, tmp_insert_commodity, sizeof(tmp_insert_commodity), NULL, NULL);//将商品名字赋值给结构体


		insert_warehouse.Format("INSERT INTO warehouse VALUES(1,%d,%d)", max_C_id, m_warecount);
		int ress1 = mysql_query(&mysqlCon,(char *)(LPCSTR)tmp_insert_commodity);
		int ress2 = mysql_query(&mysqlCon, (char*)(LPCSTR)insert_warehouse);
		if (ress1 == 0 && ress2 == 0)
		{
			MessageBox("添加成功");

		}
		else
		{
			MessageBox("添加失败");
		}
	}
}
