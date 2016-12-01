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

	int flag;//用于判断是移动(0)还是均匀缩放(1)还是非均匀缩放(2),
	int symb;//用于记录Glif数组当前选中的gliph的index	

    CPoint prevMousePt;//用于select模式下记录鼠标坐标的
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
