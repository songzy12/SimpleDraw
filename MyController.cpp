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
				flag = 1;//����
				symb = i;
				break;
			}
			else if (pCurGliph->isSelected(point))
			{
				flag = 0;//�ƶ�		
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

		//����ԭ����ͼ��
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
		
		CPoint offset = point - mousePtS;//����offset		

        Gliph::TYPE type = pCurGliph->getType();

		if (flag == 0)//moveҪ�������Σ�һ���ǲ����Ѿ������õ�ͼԪ���ڶ����ǲ����ƶ������д�����ͼԪ
		{
			//���������е�ͼ��
			pPrevGliph = new Gliph(type, pCurGliph->getSpt() + this->prevOffset, pCurGliph->getEpt() + this->prevOffset);
			pPrevGliph->drawSelf(m_pDC);
			//������ͼ��
			pNewGliph = new Gliph(type, pCurGliph->getSpt() + offset, pCurGliph->getEpt() + offset);
			pNewGliph->drawSelf(m_pDC);

			prevOffset = offset;
		}
		else if (flag == 1)
		{
			CPoint offset1, offset2;
            int xOffset = offset.x;
            int yOffset = offset.y;
			
			// 0: ����, 1: ����, 2: ����, 3: ����
			// 4: ��, 5: ��, 6: ��, 7: ��

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

			//���������е�ͼ��
			pPrevGliph = new Gliph(type, pCurGliph->getSpt() + prevOffset1, pCurGliph->getEpt() + prevOffset2);
			pPrevGliph->drawSelf(m_pDC);

			//�ػ�
			pNewGliph = new Gliph(type, pCurGliph->getSpt() + offset1, pCurGliph->getEpt() + offset2);
			pNewGliph->drawSelf(m_pDC);

			prevOffset1 = offset1;
			prevOffset2 = offset2;
		}
	}
}
