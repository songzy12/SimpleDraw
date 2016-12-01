#include "StdAfx.h"
#include ".\mycontroller.h"
#include <fstream>

MyController::MyController(void)
{
	mMode = DRAW_SELECT;
	flag = -1;
	symb = -1;
}

MyController::MyController(CDC * pDC, CSimpleDrawDoc* pDoc)
{
    mMode = DRAW_SELECT;
	this->m_pDC = pDC;
	this->m_pDoc = pDoc;
	flag = -1;
	symb = -1;
}

MyController::~MyController(void)
{
}

void MyController::showSelf(Gliph* ptGliph)
{
	ptGliph->drawSelf(m_pDC);
}

void MyController::showHandle(Gliph* ptgliph)
{
    ptgliph->drawHandle(m_pDC);
}

void MyController::hideHandle(Gliph* ptgliph) {
	m_pDC->SetROP2(R2_NOT);
	m_pDC->SelectStockObject(NULL_BRUSH);
	showHandle(ptgliph);
}

void MyController::showBoundingBox(Gliph* ptGliph)
{
    ptGliph->drawBoundingBox(m_pDC);
}

void MyController::hideBoundingBox(Gliph* ptGliph) {
	m_pDC->SetROP2(R2_NOT);
	m_pDC->SelectStockObject(NULL_BRUSH);
	showBoundingBox(ptGliph);
}

void MyController::OnLButtonDown(UINT nFlags, CPoint point)
{
	mousePtS = point;
	
	if (mMode != MyController::DRAW_SELECT)
	{
        Gliph::TYPE type = static_cast<Gliph::TYPE> (mMode);
		pCurGliph = new Gliph(type, mousePtS, point);
		m_pDoc->addGliph(pCurGliph);
		showHandle(pCurGliph);
	}
	else
	{
		if (flag != -1)
			return;
		mousePtS = point;

		int count = m_pDoc->m_GliphList.GetCount();
		
		for (int i = 0; i < count; i++)
		{
			pCurGliph = m_pDoc->getGliphAt(i);
            mHandle = pCurGliph->handleSelected(point);
			
			if (mHandle != -1)
			{
				flag = 1;//缩放
				symb = i;
				break;
			}
			else if (pCurGliph->isSelected(point))
			{
				flag = 0;//移动		
				symb = i;
				break;
			}
		}
	}
}

void MyController::OnLButtonUp(UINT nFlags, CPoint point)
{	
	if (mMode != DRAW_SELECT)
	{
		pCurGliph->setCorner(mousePtS, point);
		showHandle(pCurGliph);
	}
	else
	{
		if (flag == -1)
			return;

		m_pDC->SetROP2(R2_NOT);
		m_pDC->SelectStockObject(NULL_BRUSH);

		//擦除原本的图形
		hideHandle(pCurGliph);
		m_pDoc->delGliphAt(symb);
		m_pDoc->addGliph(pNewGliph); 
		showHandle(pNewGliph);

		symb = -1;
		flag = -1;
        prevOffset = point - point;
        prevOffset1 = point - point;
        prevOffset2 = point - point;
	}
}
void MyController::OnMouseMove(UINT nFlags, CPoint point)
{	
	m_pDC->SetROP2(R2_NOT);
    m_pDC->SelectStockObject(NULL_BRUSH);
	if (mMode != DRAW_SELECT) {
		if (nFlags & MK_LBUTTON) {
			showSelf(pCurGliph);
			hideHandle(pCurGliph);
			
			pCurGliph->setCorner(mousePtS, point);

			showSelf(pCurGliph);
			showHandle(pCurGliph);
		}
	}
	else
	{
        if (flag == -1)
            return;
		
		CPoint offset = point - mousePtS;//更新offset		

        Gliph::TYPE type = pCurGliph->getType();

		if (flag == 0)//move要擦除两次，一次是擦除已经建立好的图元，第二次是擦除移动过程中创建的图元
		{
			//擦掉过程中的图像
			pPrevGliph = new Gliph(type, pCurGliph->getSpt() + this->prevOffset, pCurGliph->getEpt() + this->prevOffset);
			pPrevGliph->drawSelf(m_pDC);
			//绘制新图形
			pNewGliph = new Gliph(type, pCurGliph->getSpt() + offset, pCurGliph->getEpt() + offset);
			pNewGliph->drawSelf(m_pDC);

			prevOffset = offset;
		}
		else if (flag == 1)
		{
			CPoint offset1, offset2;
            int xOffset = offset.x;
            int yOffset = offset.y;
			
			// 0: 左上, 1: 右上, 2: 右下, 3: 左下
			// 4: 上, 5: 右, 6: 下, 7: 左

			if (mHandle == 0 || mHandle == 4 || mHandle == 7)
			{
				offset1.x = xOffset;
				offset1.y = yOffset;
				offset2.x = 0;
				offset2.y = 0;
			}
			if (mHandle == 1)
			{
				offset1.x = 0;
				offset1.y = yOffset;
				offset2.x = xOffset;
				offset2.y = 0;

			}
			if (mHandle == 3)
			{
				offset1.y = 0;
				offset1.x = xOffset;
				offset2.y = yOffset;
				offset2.x = 0;

			}
			if (mHandle == 2 || mHandle == 5 || mHandle == 6)
			{
				offset2.x = xOffset;
				offset2.y = yOffset;
				offset1.x = 0;
				offset1.y = 0;
			}

			//擦掉过程中的图像
			pPrevGliph = new Gliph(type, pCurGliph->getSpt() + prevOffset1, pCurGliph->getEpt() + prevOffset2);
			pPrevGliph->drawSelf(m_pDC);

			//重绘
			pNewGliph = new Gliph(type, pCurGliph->getSpt() + offset1, pCurGliph->getEpt() + offset2);
			pNewGliph->drawSelf(m_pDC);

			prevOffset1 = offset1;
			prevOffset2 = offset2;
		}
	}
}
