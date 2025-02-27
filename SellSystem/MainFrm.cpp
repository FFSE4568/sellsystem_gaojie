
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "SellSystem.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CUserDlg.h"
#include "CUserBuy.h"
#include "CSellerDeal.h"
#include "CAddC.h"


// CMainFrame
extern int user_flag;
#include "CSelectView.h"
#include "CDisplayView.h"

//为了判断类别
#include "CLogin.h"
extern int user_flag;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconA(IDI_ICON_MAIN));//设置软件图标

	MoveWindow(0, 0, 1000, 700);
	CenterWindow();
	
	CTime time = CTime::GetCurrentTime();//获取系统当前时间
	CString currentTime = time.Format("%Y-%m-%d");
	
	SetTitle(currentTime);//设置右侧标题
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序






BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	//静态拆分窗口一行俩列
	m_spliter.CreateStatic(this, 1, 2);


	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView),CSize(200,500),pContext);

	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext   Context;
	if (user_flag == 1)
	{
		if (wParam == NM_A)
		{
			//MessageBox(TEXT("个人信息界面挂载！"));
			//挂载界面
			Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
			m_spliter.DeleteView(0, 1);
			m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
			CUserDlg *pNewView = (CUserDlg *)m_spliter.GetPane(0, 1);
			m_spliter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_spliter.SetActivePane(0, 1);
		}
		else if (wParam == NM_B)
		{
			//MessageBox(TEXT("22222"));
			//挂载界面
			Context.m_pNewViewClass = RUNTIME_CLASS(CUserBuy);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
			m_spliter.DeleteView(0, 1);
			m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserBuy), CSize(600, 500), &Context);
			CUserBuy *pNewView = (CUserBuy *)m_spliter.GetPane(0, 1);
			m_spliter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_spliter.SetActivePane(0, 1);
		}
	}
	else if (user_flag == 2)
	{
		if (wParam == NM_A)
		{
			//MessageBox(TEXT("个人信息界面挂载！"));
			//挂载界面
			Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
			m_spliter.DeleteView(0, 1);
			m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
			CUserDlg *pNewView = (CUserDlg *)m_spliter.GetPane(0, 1);
			m_spliter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_spliter.SetActivePane(0, 1);
		}
		else if (wParam == NM_B)
		{
			//MessageBox(TEXT("22222"));
			//挂载界面
			Context.m_pNewViewClass = RUNTIME_CLASS(CSellerDeal);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
			m_spliter.DeleteView(0, 1);
			m_spliter.CreateView(0, 1, RUNTIME_CLASS(CSellerDeal), CSize(600, 500), &Context);
			CSellerDeal *pNewView = (CSellerDeal *)m_spliter.GetPane(0, 1);
			m_spliter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_spliter.SetActivePane(0, 1);
		}
	}
	else if (user_flag == 3)
	{
		if (wParam == NM_A)
		{
			//MessageBox(TEXT("个人信息界面挂载！"));
			//挂载界面
			Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
			m_spliter.DeleteView(0, 1);
			m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
			CUserDlg *pNewView = (CUserDlg *)m_spliter.GetPane(0, 1);
			m_spliter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_spliter.SetActivePane(0, 1);
		}
		else if (wParam == NM_B)
		{
			//MessageBox(TEXT("22222"));
			//挂载界面
			Context.m_pNewViewClass = RUNTIME_CLASS(CAddC);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
			m_spliter.DeleteView(0, 1);
			m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAddC), CSize(600, 500), &Context);
			CAddC *pNewView = (CAddC *)m_spliter.GetPane(0, 1);
			m_spliter.RecalcLayout();
			pNewView->OnInitialUpdate();
			m_spliter.SetActivePane(0, 1);
		}
	}
	return 0;
}

