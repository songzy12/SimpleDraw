// SimpleDrawView.cpp : CSimpleDrawView 类的实现
//

#include "stdafx.h"
#include "SimpleDraw.h"

#include "SimpleDrawDoc.h"
#include "SimpleDrawView.h"
#include ".\simpledrawview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleDrawView

IMPLEMENT_DYNCREATE(CSimpleDrawView, CView)

BEGIN_MESSAGE_MAP(CSimpleDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	
	ON_COMMAND(ID_DRAW_LINE, OnDrawLine)
	ON_UPDATE_COMMAND_UI(ID_DRAW_LINE, OnUpdateDrawLine)
	ON_COMMAND(ID_DRAW_RECTANGLE, &CSimpleDrawView::OnDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CSimpleDrawView::OnUpdateDrawRectangle)
	ON_COMMAND(ID_DRAW_Ellipse, &CSimpleDrawView::OnDrawEllipse)
	ON_UPDATE_COMMAND_UI(ID_DRAW_Ellipse, &CSimpleDrawView::OnUpdateDrawEllipse)
	ON_COMMAND(ID_DRAW_RoundRect, &CSimpleDrawView::OnDrawRoundrect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RoundRect, &CSimpleDrawView::OnUpdateDrawRoundrect)	
	ON_COMMAND(ID_DRAW_SELECT, &CSimpleDrawView::OnDrawSelect)
	ON_UPDATE_COMMAND_UI(ID_DRAW_SELECT, &CSimpleDrawView::OnUpdateDrawSelect)
END_MESSAGE_MAP()

// CSimpleDrawView 构造/析构

CSimpleDrawView::CSimpleDrawView()
{
	// TODO: 在此处添加构造代码
//	m_mode = this->DRAW_SELECT;
}

CSimpleDrawView::~CSimpleDrawView()
{
}

BOOL CSimpleDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CSimpleDrawView 绘制

void CSimpleDrawView::OnDraw(CDC* pDC)
{
	CSimpleDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: 在此处为本机数据添加绘制代码
}
void CSimpleDrawView::OnInitialUpdate()
{
	CView::OnInitialUpdate();	
}


// CSimpleDrawView 打印

BOOL CSimpleDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSimpleDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CSimpleDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CSimpleDrawView 诊断

#ifdef _DEBUG
void CSimpleDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CSimpleDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpleDrawDoc* CSimpleDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleDrawDoc)));
	return (CSimpleDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimpleDrawView 消息处理程序

void CSimpleDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CSimpleDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	this->m_controller.setpDoc(pDoc);
	
	CClientDC * pClientDC = (CClientDC *)this->GetDC();
	this->m_controller.setDC(pClientDC);
	
	this->m_controller.OnLButtonDown(nFlags,point);
	

	CView::OnLButtonDown(nFlags, point);
}

void CSimpleDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC * pClientDC = (CClientDC *)this->GetDC();
	this->m_controller.setDC(pClientDC);

	this->m_controller.OnLButtonUp(nFlags,point);

	CView::OnLButtonUp(nFlags, point);
}

void CSimpleDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CClientDC * pClientDC = (CClientDC * )this->GetDC();
	this->m_controller.setDC(pClientDC);

	this->m_controller.OnMouseMove(nFlags,point);

	CView::OnMouseMove(nFlags, point);
}

void CSimpleDrawView::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	this->m_controller.setOpMode(MyController::DRAW_LINE);
}

void CSimpleDrawView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck( m_controller.getOpMode() == MyController::DRAW_LINE );	
}

void CSimpleDrawView::OnDrawRectangle()
{
	// TODO: 在此添加命令处理程序代码
	this->m_controller.setOpMode(MyController::DRAW_Rectangle);
}


void CSimpleDrawView::OnUpdateDrawRectangle(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_Rectangle);
}


void CSimpleDrawView::OnDrawEllipse()
{
	// TODO: 在此添加命令处理程序代码
	this->m_controller.setOpMode(MyController::DRAW_Ellipse);
}


void CSimpleDrawView::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_Ellipse);
}


void CSimpleDrawView::OnDrawRoundrect()
{
	// TODO: 在此添加命令处理程序代码
	this->m_controller.setOpMode(MyController::DRAW_RoundRect);
}


void CSimpleDrawView::OnUpdateDrawRoundrect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_RoundRect);
}


void CSimpleDrawView::OnDrawSelect()
{
	// TODO: 在此添加命令处理程序代码
	this->m_controller.setOpMode(MyController::DRAW_SELECT);

}



void CSimpleDrawView::OnUpdateDrawSelect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_SELECT);

}
