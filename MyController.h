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
	CPoint mousepointS, mousepointP, mousepointE;//����selectģʽ�¼�¼��������
	int flag;//�����ж����ƶ�(0)���Ǿ�������(1)���ǷǾ�������(2),
	int symb;//���ڼ�¼Glif���鵱ǰѡ�е�gliph��index
	int x1 = m_ptStart.x;
	int y1 = m_ptStart.y;
	int x2 = m_ptEnd.x;
	int y2 = m_ptEnd.y;
	int x3 = m_ptPrev.x;
	int y3 = m_ptPrev.x;
	int i;
	int Xoffset = mousepointE.x - mousepointS.x;
	int Yoffset = mousepointE.y - mousepointS.y;
	CPoint offset,prevoffset; // = mousepointE-mousepointS;???������offset������£���
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
