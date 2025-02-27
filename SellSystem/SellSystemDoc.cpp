
// SellSystemDoc.cpp: CSellSystemDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SellSystem.h"
#endif

#include "SellSystemDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern int user_flag;

// CSellSystemDoc

IMPLEMENT_DYNCREATE(CSellSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CSellSystemDoc, CDocument)
END_MESSAGE_MAP()


// CSellSystemDoc 构造/析构

CSellSystemDoc::CSellSystemDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CSellSystemDoc::~CSellSystemDoc()
{
}

BOOL CSellSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	if (user_flag == 1)
	{	
		//设置软件标题
		SetTitle(TEXT("销售管理系统--买家版"));
	}
	else if (user_flag == 2)
	{
		SetTitle(TEXT("销售管理系统--销售员版"));
	}
	else if (user_flag == 3)
	{
		SetTitle(TEXT("销售管理系统--管理员版"));
	}
	return TRUE;
}




// CSellSystemDoc 序列化

void CSellSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSellSystemDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSellSystemDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSellSystemDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSellSystemDoc 诊断

#ifdef _DEBUG
void CSellSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSellSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSellSystemDoc 命令
