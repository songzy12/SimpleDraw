// SimpleDrawView.h : CSimpleDrawView 类的接口
//


#pragma once

#include "MyController.h"

class CSimpleDrawView : public CView
{
protected: // 仅从序列化创建
	CSimpleDrawView();
	//CSimpleDrawView();
	DECLARE_DYNCREATE(CSimpleDrawView)

// 属性
public:
	CSimpleDrawDoc* GetDocument() const;
		
protected:
	MyController m_controller;
	
	
// 操作
public:

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSimpleDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // SimpleDrawView.cpp 的调试版本
inline CSimpleDrawDoc* CSimpleDrawView::GetDocument() const
   { return reinterpret_cast<CSimpleDrawDoc*>(m_pDocument); }
#endif

