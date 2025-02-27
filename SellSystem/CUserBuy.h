#pragma once



// CUserBuy 窗体视图

class CUserBuy : public CFormView
{
	DECLARE_DYNCREATE(CUserBuy)

protected:
	CUserBuy();           // 动态创建所使用的受保护的构造函数
	virtual ~CUserBuy();

public:
	enum { IDD = DIALOG_BUY };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedButton1();
	CComboBox m_combo;
	int m_count;
	double m_price;
	afx_msg void OnSelchangeCombo1();
	int m_pnum;
	afx_msg void OnBnClickedButton3();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton4();
};