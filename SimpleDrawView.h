// SimpleDrawView.h : CSimpleDrawView ��Ľӿ�
//


#pragma once

#include "MyController.h"

class CSimpleDrawView : public CView
{
protected: // �������л�����
	CSimpleDrawView();
	//CSimpleDrawView();
	DECLARE_DYNCREATE(CSimpleDrawView)

// ����
public:
	CSimpleDrawDoc* GetDocument() const;
		
protected:
	MyController m_controller;
	
	
// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSimpleDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI *pCmdUI);

protected:
//	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnDrawRectangle();
	afx_msg void OnUpdateDrawRectangle(CCmdUI *pCmdUI);
	afx_msg void OnDrawEllipse();
	afx_msg void OnUpdateDrawEllipse(CCmdUI *pCmdUI);
	afx_msg void OnDrawRoundrect();
	afx_msg void OnUpdateDrawRoundrect(CCmdUI *pCmdUI);
	afx_msg void OnDrawSelect();
	afx_msg void OnUpdateDrawSelect(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // SimpleDrawView.cpp �ĵ��԰汾
inline CSimpleDrawDoc* CSimpleDrawView::GetDocument() const
   { return reinterpret_cast<CSimpleDrawDoc*>(m_pDocument); }
#endif

