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
		DRAW_RECTANGLE,
		DRAW_ROUNDRECT,
		DRAW_ELLIPSE,
		DRAW_SELECT
	};

protected:

	CDC   * m_pDC;
	CSimpleDrawDoc* m_pDoc;
	
	Gliph* pCurGliph;
	Gliph* pPrevGliph;
	Gliph* pNewGliph;

	int flag;//�����ж����ƶ�(0)���Ǿ�������(1)���ǷǾ�������(2),
	int symb;//���ڼ�¼Glif���鵱ǰѡ�е�gliph��index	

    CPoint prevMousePt;//����selectģʽ�¼�¼��������
	CPoint prevOffset;
	CPoint prevOffset1, prevOffset2;

	STATE mMode;
	int mHandle;

public:
	void setDC(CDC * pDC){m_pDC = pDC;}
	CDC * getDC(){return m_pDC;}
	void setpDoc(CSimpleDrawDoc* pDoc) { m_pDoc = pDoc; }
	void setOpMode(STATE state){mMode = state;}
	STATE getOpMode(){return mMode;}

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
