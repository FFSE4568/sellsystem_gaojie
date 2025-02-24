#pragma once


// CAddC 对话框

class CAddC : public CFormView
{
	DECLARE_DYNCREATE(CAddC)

protected:
	CAddC();           // 动态创建所使用的受保护的构造函数
	virtual ~CAddC();

public:
	enum { IDD = DIALOG_ADDC };
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
	CComboBox m_combo;
	CString m_Iprice;
	int m_Inum;
	double m_Oprice;
	afx_msg void OnBnClickedButton1();
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	CString m_name;
//	CEdit m_IPrice;
	double m_IPrice;
	int m_warecount;
	double m_CPrice;
	afx_msg void OnBnClickedButton4();
};
