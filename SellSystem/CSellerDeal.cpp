// CSellerDeal.cpp: 实现文件
//

#include "stdafx.h"
#include "SellSystem.h"
#include "CSellerDeal.h"
#include "afxdialogex.h"
#include "CInfoDatabase.h"

// CSellerDeal 对话框

IMPLEMENT_DYNCREATE(CSellerDeal, CFormView);
CSellerDeal::CSellerDeal()
	:CFormView(CSellerDeal::IDD)
	, m_username(_T(""))
	, m_totalprice(0)
{
}
CSellerDeal::~CSellerDeal()
{
}
void CSellerDeal::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_totalprice);
	DDX_Control(pDX, IDC_LIST2, m_list);
}
BEGIN_MESSAGE_MAP(CSellerDeal, CFormView)

	ON_BN_CLICKED(IDC_BUTTON1, &CSellerDeal::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellerDeal::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()
// CUserBuy 诊断

#ifdef _DEBUG
void CSellerDeal::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellerDeal::Dump(CDumpContext& dc) const
{
	CSellerDeal::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellerDeal 消息处理程序


void CSellerDeal::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	//MessageBox(name);
}




void CSellerDeal::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	((CEdit*)m_combo.GetWindow(GW_CHILD))->SetReadOnly();
	//初始化下拉框
	CInfoDatabase data;
	//把商品读入data对象中
	data.ReadInfo_Order();

	for (list<ordersystem>::iterator it = data.order.begin(); it != data.order.end(); it++)
	{
		m_combo.AddString(CString(it->Order_Id));
		
	}
	//设置初始化的商品
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

	//初始化list信息
	LONG styles;
	styles = GetWindowLong(m_list.m_hWnd, GWL_STYLE);
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, styles | LVS_REPORT);
	CString str[] = { _T("序号"),_T("商品名字"),_T("购买个数"),_T("总价格") };
	for (int i = 0; i < 4; i++)
	{
		m_list.InsertColumn(i, str[i], LVCFMT_LEFT, 90, -1);
	}
}


void CSellerDeal::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoDatabase data;
	data.ReadInfo_Order();
	for (list<ordersystem>::iterator it = data.order.begin(); it != data.order.end(); it++)
	{
		if ((CString)it->Order_Id == name)
		{
			m_username = it->Username;
			m_totalprice = it->Order_Totalprice;
			UpdateData(FALSE);
		}
	}
}
