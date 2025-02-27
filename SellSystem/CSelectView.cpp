// CSelectView.cpp: 实现文件
//

#include "stdafx.h"
#include "SellSystem.h"
#include "CSelectView.h"
#include "MainFrm.h"
extern int user_flag;
// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序


void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	if (user_flag == 1)
	{
		HICON icon_user = AfxGetApp()->LoadIcon(IDI_ICON_USER);
		HICON icon_buy = AfxGetApp()->LoadIcon(IDI_ICON_BUY);
		m_imageList.Create(50, 50, ILC_COLOR32, 2, 2);
		//
		m_imageList.Add(icon_user);
		m_imageList.Add(icon_buy);
		//
		m_treeCtrl = &GetTreeCtrl();
		m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);
		m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("买东西"), 1, 1, NULL);
	}
	else if (user_flag == 2)
	{
		HICON icon_user = AfxGetApp()->LoadIcon(IDI_ICON_USER);
		HICON icon_deal = AfxGetApp()->LoadIcon(IDI_ICON_DEAL);
		m_imageList.Create(50, 50, ILC_COLOR32, 2, 2);
		//
		m_imageList.Add(icon_user);
		m_imageList.Add(icon_deal);
		//
		m_treeCtrl = &GetTreeCtrl();
		m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);
		m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("订单处理"), 1, 1, NULL);
	}
	else if (user_flag == 3)
	{
		HICON icon_user = AfxGetApp()->LoadIcon(IDI_ICON_USER);
		HICON icon_deal = AfxGetApp()->LoadIcon(IDI_ICON_GOODS);
		m_imageList.Create(50, 50, ILC_COLOR32, 2, 2);
		//
		m_imageList.Add(icon_user);
		m_imageList.Add(icon_deal);
		//
		m_treeCtrl = &GetTreeCtrl();
		m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);
		m_treeCtrl->InsertItem(TEXT("个人信息"), 0, 0, NULL);
		m_treeCtrl->InsertItem(TEXT("进货"), 1, 1, NULL);
	}
}


void CSelectView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取当前节点选中的内容
	HTREEITEM item = m_treeCtrl->GetSelectedItem();

	//获取选中项的文本内容CTreeCtrl::GetItemText
	CString str = m_treeCtrl->GetItemText(item);
	//MessageBox(str);
	if (user_flag == 1)
	{
		if (str == TEXT("个人信息"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
		}
		else if (str == TEXT("买东西"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
		}
	}
	else if (user_flag == 2)
	{
		if (str == TEXT("个人信息"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
		}
		else if (str == TEXT("订单处理"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
		}
	}
	else if (user_flag == 3)
	{
		if (str == TEXT("个人信息"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
		}
		else if (str == TEXT("进货"))
		{
			::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
		}
	}
}
