// CLogin.cpp: 实现文件
//

#include "stdafx.h"
#include "SellSystem.h"
#include "CLogin.h"
#include "afxdialogex.h"
#include "Connect2Database.h"

// CLogin 对话框
#include "winsock2.h"
#include "mysql.h"
#pragma comment(lib,"libmysql.lib")
#include "global.h"
int user_flag = 0;//判断用户类别
int user_who;//判断用户是谁
CString user_name;
IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, m_Radio1);
	DDX_Control(pDX, IDC_RADIO2, m_Radio2);
	DDX_Control(pDX, IDC_RADIO3, m_Radio3);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnBnClickedButton1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLogin 消息处理程序


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Radio1.SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLogin::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//定义全局变量判断身份
	
	UpdateData(TRUE);
	MYSQL_RES *res;
	MYSQL_ROW row;
	Connect2Database con;
	MYSQL mysqlCon;
	mysqlCon = con.getconnect();
	if (m_user.IsEmpty() || m_pwd.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空!"), _T("用户登录信息"));
		return;
	}
	user_name = m_user;
	CString select_sql_by_user;
	if (m_Radio1.GetCheck() == 1) {
		select_sql_by_user.Format("select Username,Password,UserId from user_info where Username = \'%s\'", m_user);
		
		user_flag = 1;
	}
	else if(m_Radio2.GetCheck() == 1)
	{
		select_sql_by_user.Format("select Username,Password from user_seller where Username = \'%s\'", m_user);
		user_flag = 2;
	}
	else if (m_Radio3.GetCheck() == 1)
	{
		select_sql_by_user.Format("select Username,Password from user_admin where Username = \'%s\'", m_user);
		user_flag = 3;
	}
	int ress = mysql_query(&mysqlCon, (char*)(LPCSTR)select_sql_by_user);
	if (ress == 0) //检测查询成功
	{
		res = mysql_store_result(&mysqlCon);
		if (mysql_num_rows(res) == 0) //查询结果为空
		{
			MessageBox("用户不存在");
		}
		else
		{
			//判断登陆
			row = mysql_fetch_row(res);
			if (m_pwd == row[1])
			{
				user_who = _ttoi(row[2]);
				mysql_free_result(res);
				MessageBox("登录成功!");
				CDialog::OnOK();
			}
			else
			{
				MessageBox("密码错误!");
			}
		}


	}

	//mysql_close(&mysqlCon);//不能close好像有点问题
}


void CLogin::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//结束整个程序
	exit(0);
	CDialogEx::OnClose();
}


void CLogin::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			OnBnClickedButton1();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
