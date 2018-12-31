#include "stdafx.h"
#include "SellSystem.h"
#include "CUserBuy.h"
#include "mysql.h"
#include "Connect2Database.h"
#include "CInfoDatabase.h"
//CUserBuy
IMPLEMENT_DYNCREATE(CUserBuy, CFormView);
CUserBuy::CUserBuy()
	:CFormView(CUserBuy::IDD)
	, m_count(0)
	, m_price(0)
	, m_pnum(0)
{
}


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
}
BEGIN_MESSAGE_MAP(CUserBuy, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CUserBuy::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CUserBuy::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserBuy::OnBnClickedButton3)
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
	m_combo.SetCurSel(0);

}

void CUserBuy::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_pnum <= 0)
	{
		MessageBox("购买的数量需要大于0!");
	}
	if (m_pnum > m_count)
	{
		MessageBox("购买的数量不能大于库存量!");
	}
	
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
