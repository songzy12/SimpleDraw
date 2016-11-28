// SimpleDrawView.cpp : CSimpleDrawView ���ʵ��
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
	// ��׼��ӡ����
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

// CSimpleDrawView ����/����

CSimpleDrawView::CSimpleDrawView()
{
	// TODO: �ڴ˴���ӹ������
//	m_mode = this->DRAW_SELECT;
}

CSimpleDrawView::~CSimpleDrawView()
{
}

BOOL CSimpleDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CSimpleDrawView ����

void CSimpleDrawView::OnDraw(CDC* pDC)
{
	CSimpleDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}
void CSimpleDrawView::OnInitialUpdate()
{
	CView::OnInitialUpdate();	
}


// CSimpleDrawView ��ӡ

BOOL CSimpleDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSimpleDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CSimpleDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CSimpleDrawView ���

#ifdef _DEBUG
void CSimpleDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CSimpleDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpleDrawDoc* CSimpleDrawView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpleDrawDoc)));
	return (CSimpleDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimpleDrawView ��Ϣ�������

void CSimpleDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC * pClientDC = (CClientDC *)this->GetDC();
	this->m_controller.setDC(pClientDC);

	this->m_controller.OnLButtonUp(nFlags,point);

	CView::OnLButtonUp(nFlags, point);
}

void CSimpleDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CClientDC * pClientDC = (CClientDC * )this->GetDC();
	this->m_controller.setDC(pClientDC);

	this->m_controller.OnMouseMove(nFlags,point);

	CView::OnMouseMove(nFlags, point);
}

void CSimpleDrawView::OnDrawLine()
{
	// TODO: �ڴ���������������
	this->m_controller.setOpMode(MyController::DRAW_LINE);
}

void CSimpleDrawView::OnUpdateDrawLine(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck( m_controller.getOpMode() == MyController::DRAW_LINE );	
}

void CSimpleDrawView::OnDrawRectangle()
{
	// TODO: �ڴ���������������
	this->m_controller.setOpMode(MyController::DRAW_Rectangle);
}


void CSimpleDrawView::OnUpdateDrawRectangle(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_Rectangle);
}


void CSimpleDrawView::OnDrawEllipse()
{
	// TODO: �ڴ���������������
	this->m_controller.setOpMode(MyController::DRAW_Ellipse);
}


void CSimpleDrawView::OnUpdateDrawEllipse(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_Ellipse);
}


void CSimpleDrawView::OnDrawRoundrect()
{
	// TODO: �ڴ���������������
	this->m_controller.setOpMode(MyController::DRAW_RoundRect);
}


void CSimpleDrawView::OnUpdateDrawRoundrect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_RoundRect);
}


void CSimpleDrawView::OnDrawSelect()
{
	// TODO: �ڴ���������������
	this->m_controller.setOpMode(MyController::DRAW_SELECT);

}



void CSimpleDrawView::OnUpdateDrawSelect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_controller.getOpMode() == MyController::DRAW_SELECT);

}
