#pragma once


// CSellerDeal 对话框

class CSellerDeal : public CFormView
{
	DECLARE_DYNCREATE(CSellerDeal)

protected:
	CSellerDeal();           // 动态创建所使用的受保护的构造函数
	virtual ~CSellerDeal();

public:
	enum { IDD = DIALOG_DEAL };
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
	afx_msg void OnBnClickedButton1();
	CComboBox m_combo;
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	CString m_username;
	double m_totalprice;
	CListCtrl m_list;
	afx_msg void OnBnClickedButton2();
	void getInfoCommodity();
	CButton m_button2;
	CButton m_button1;
};
