#include "stdafx.h"
#include "SellSystem.h"
#include "CUserBuy.h"
#include "mysql.h"
#include "Connect2Database.h"
#include "CInfoDatabase.h"
#include "CLogin.h"
//CUserBuy
IMPLEMENT_DYNCREATE(CUserBuy, CFormView);
CUserBuy::CUserBuy()
	:CFormView(CUserBuy::IDD)
	, m_count(0)
	, m_price(0)
	, m_pnum(0)
{
}
extern int user_who;
int index_listctrl = 0;
CInfoDatabase insertinfo;
int sqlcount = 0;//定义添加条数
CUserBuy::~CUserBuy()
{
}
void CUserBuy::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_count);
	DDX_Text(pDX, IDC_EDIT2, m_price);
	DDX_Text(pDX, IDC_EDIT5, m_pnum);
	DDX_Control(pDX, IDC_LIST1, m_list);
}
BEGIN_MESSAGE_MAP(CUserBuy, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CUserBuy::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUserBuy::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserBuy::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CUserBuy::OnBnClickedButton4)
END_MESSAGE_MAP()
// CUserBuy 诊断

#ifdef _DEBUG
void CUserBuy::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserBuy::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserBuy 消息处理程序
void CUserBuy::OnInitialUpdate()
{
	CFormView::OnInitialUpdate(); 
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
	OnSelchangeCombo1();
	

	//初始化list信息
	LONG styles;
	styles = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	SetWindowLong(m_list.m_hWnd, GWL_STYLE,styles|LVS_REPORT);
	CString str[] = { _T("序号"),_T("商品名字"),_T("购买个数"),_T("总价格") };
	for (int i = 0; i < 4; i++)
	{
		m_list.InsertColumn(i,str[i],LVCFMT_LEFT,90,-1);
	}

}

void CUserBuy::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	msg tmp;
	UpdateData(TRUE);
	if (m_pnum <= 0)
	{
		MessageBox("购买的数量需要大于0!");
	}
	else if (m_pnum > m_count)
	{
		MessageBox("购买的数量不能大于库存量!");
	}
	else
	{
		CString str;
		str.Format("%d", index_listctrl);
		m_list.InsertItem(index_listctrl, str);

		int index = m_combo.GetCurSel();
		CString name;
		m_combo.GetLBText(index, name);
		m_list.SetItemText(index_listctrl, 1, name);

		CInfoDatabase data;
		data.ReadDocline();
		for (list<msg>::iterator it = data.ls.begin(); it != data.ls.end(); it++)
		{
			if ((CString)it->name == name)
			{
				tmp.id = it->id;
			}
		}


		name.Format("%d",m_pnum);
		m_list.SetItemText(index_listctrl, 2, name);
		tmp.pnum = m_pnum;
		double total_price = m_pnum * m_price;
		name.Format("%lf", total_price);
		m_list.SetItemText(index_listctrl++, 3, name);
		tmp.totalprice = total_price;
		insertinfo.ls.push_back(tmp);
	}
	sqlcount++;
	
}


void CUserBuy::OnSelchangeCombo1()
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
			m_price = it->price;
			m_count = it->num;
			UpdateData(FALSE);
		}
	}
}


void CUserBuy::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_combo.ResetContent();
	CInfoDatabase data;
	//把商品读入data对象中
	data.ReadDocline();

	for (list<msg>::iterator it = data.ls.begin(); it != data.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name));
	}
	m_combo.SetCurSel(0);
}


void CUserBuy::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取系统的当前时间设置为当前的Orderid（年＋月+天+小时+分钟+秒数）
	CTime orderid = CTime::GetCurrentTime();
	CString CStr_orderid = orderid.Format(_T("%Y%m%d%H%M%S"));
	CStringA  tmp;
	tmp = CStr_orderid;
	char *pp = tmp.GetBuffer();

	MYSQL_RES *res;
	MYSQL_ROW row;
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();
	CString sql_insert;
	CTime time = CTime::GetCurrentTime();
	CString date=time.Format(_T("%Y-%m-%d"));
	//MessageBox(date);
	CStringA tmp_date = date;
	char *real_date = tmp_date.GetBuffer();
	sql_insert.Format("insert into ordersystem(Order_Id,Cu_Id,Order_Date,Order_Status) values('%s',%d,'%s',%d)",pp,user_who,real_date,0);
	//MessageBox(sql_insert);
	//定义要执行的sql语句的list
	list<char *> sql;
	int flagtoinsert = 0;//判断每一步的插入数据库单条数据是否成功
	double totalprice=0;

	for (list<msg>::iterator it = insertinfo.ls.begin(); it != insertinfo.ls.end(); it++)
	{
		char sqltmp[255];
		sprintf(sqltmp, "INSERT INTO outsystem(Order_Id,C_Id,Out_Count,Out_Total) values('%s',%d,%d,%lf)", pp,it->id, it->pnum, it->totalprice);
		sql.push_back(sqltmp);
		//MessageBox(sqltmp);
		int ress_all = mysql_query(&mysqlCon,(LPCSTR)sqltmp);
		if (ress_all != 0)
		{
			flagtoinsert = 1;
		}
		totalprice += it->totalprice;
	}
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)sql_insert);
	char str_totalprice[255];
	sprintf(str_totalprice, "UPDATE ordersystem set Order_Totalprice =\'%lf\' WHERE Order_Id=\'%s\'", totalprice,pp);
	int res_totalprice = mysql_query(&mysqlCon, (LPCSTR)str_totalprice);
	if (ress == 0 && flagtoinsert==0 && res_totalprice==0)
	{
		CString MsgtoUser;
		MsgtoUser.Format("您的订单总价格为%lf,请尽快付款", totalprice);
		MessageBox(MsgtoUser);
		MessageBox("订单已经提交等待系统处理");
	}
	else
	{
		MessageBox("购买失败");
	}
}
