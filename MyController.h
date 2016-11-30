#pragma once
#include "Gliph.h"
#include "SimpleDrawDoc.h"
class MyController
{
public:
	MyController(void);
	MyController(CDC * pDC, CSimpleDrawDoc* pDoc);

	virtual ~MyController(void);

public:
	enum STATE{		        
		DRAW_LINE,
		DRAW_Rectangle,
		DRAW_RoundRect,
		DRAW_Ellipse,
		DRAW_SELECT
	};

protected:

	CDC   * m_pDC;
	CSimpleDrawDoc* m_pDoc;
	
	Gliph* pCurGliph;
	Gliph* prevGliph;
	Gliph* newGliph;
	CPoint m_ptStart,m_ptPrev,m_ptEnd;
	CPoint mousepointS, mousepointP, mousepointE;//用于select模式下记录鼠标坐标的
	int flag;//用于判断是移动(0)还是均匀缩放(1)还是非均匀缩放(2),
	int symb;//用于记录Glif数组当前选中的gliph的index
	int x1 = m_ptStart.x;
	int y1 = m_ptStart.y;
	int x2 = m_ptEnd.x;
	int y2 = m_ptEnd.y;
	int x3 = m_ptPrev.x;
	int y3 = m_ptPrev.x;
	int i;
	int Xoffset = mousepointE.x - mousepointS.x;
	int Yoffset = mousepointE.y - mousepointS.y;
	CPoint offset,prevoffset; // = mousepointE-mousepointS;???这样的offset不会更新？？
	STATE m_mode;
	int a;
public:
	void setDC(CDC * pDC){m_pDC = pDC;}
	CDC * getDC(){return m_pDC;}
	void setpDoc(CSimpleDrawDoc* pDoc) { m_pDoc = pDoc; }
	void setOpMode(STATE state){m_mode = state;}
	STATE getOpMode(){return m_mode;}

public:
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void showSelf(Gliph* ptGliph);
	void showHandle(Gliph* ptGliph);
	void hideHandle(Gliph* ptGliph);
	void showBoundingBox(Gliph* ptGliph);
	void hideBoundingBox(Gliph* ptGliph);
};
