
// SellSystemView.cpp: CSellSystemView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SellSystem.h"
#endif

#include "SellSystemDoc.h"
#include "SellSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSellSystemView

IMPLEMENT_DYNCREATE(CSellSystemView, CView)

BEGIN_MESSAGE_MAP(CSellSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSellSystemView 构造/析构

CSellSystemView::CSellSystemView() noexcept
{
	// TODO: 在此处添加构造代码

}

CSellSystemView::~CSellSystemView()
{
}

BOOL CSellSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSellSystemView 绘图

void CSellSystemView::OnDraw(CDC* /*pDC*/)
{
	CSellSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CSellSystemView 打印

BOOL CSellSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSellSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSellSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CSellSystemView 诊断

#ifdef _DEBUG
void CSellSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CSellSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSellSystemDoc* CSellSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSellSystemDoc)));
	return (CSellSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CSellSystemView 消息处理程序
