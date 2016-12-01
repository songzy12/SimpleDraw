#include "StdAfx.h"
#include ".\mycontroller.h"
#include <fstream>

MyController::MyController(void)
{
	m_mode = DRAW_SELECT;
	flag = -1;
	symb = -1;
	newGliph = nullptr;
}

MyController::MyController(CDC * pDC, CSimpleDrawDoc* pDoc)
{
	this->m_pDC = pDC;
	this->m_pDoc = pDoc;
	flag = -1;
	symb = -1;
	newGliph = nullptr;
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
	m_ptStart = point;
	m_ptPrev = point;
	
	if (m_mode != MyController::DRAW_SELECT)
	{
        Gliph::TYPE type = static_cast<Gliph::TYPE> (m_mode);
		pCurGliph = new Gliph(type, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->setCorner(m_ptStart, point);
		pCurGliph->setBoundingBox();
		pCurGliph->setHandleList();
		showHandle(pCurGliph);
	}
	else
	{
		if (flag != -1)
			return;
		mousepointS = point;
		mousepointP = point;

		int count = m_pDoc->m_GliphList.GetCount();

		std::ofstream log;
		log.open("log.txt", std::ofstream::out | std::ofstream::app);
		log << "count: " << count << std::endl;
		log.close();
		
		for (int i = 0; i < count; i++)
		{
			pCurGliph = m_pDoc->getGliphAt(i);
			
			if (pCurGliph->handleSelected(point) != -1)
			{
				handle = pCurGliph->handleSelected(point);

				std::ofstream log;
				log.open("log.txt", std::ofstream::out | std::ofstream::app);
				log << "handle hit: " << handle << std::endl;
				log.close();

				flag = 1;//缩放
				symb = i;
				break;
			}
			else if (m_pDoc->getGliphAt(i)->isSelected(point))
			{
				flag = 0;//移动		
				//this->showBoundingBox(pCurGliph); //击中就显示boundingbox
				symb = i;
				break;
			}
		}
	}
}

void MyController::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_ptEnd = point;
	
	if (m_mode != DRAW_SELECT)
	{
		pCurGliph->setCorner(m_ptStart, point);
		pCurGliph->setBoundingBox();
		pCurGliph->setHandleList();
		showHandle(pCurGliph);
	}
	else
	{
		std::ofstream log;
		log.open("log.txt", std::ofstream::out | std::ofstream::app);
		log << "buttonUp" << std::endl;
		log.close();
		if (flag == -1)
			return;

		mousepointE = point;
		prevoffset = point - point;
		prevOffset1 = point - point;
		prevOffset2 = point - point;

		m_pDC->SetROP2(R2_NOT);
		m_pDC->SelectStockObject(NULL_BRUSH);

		int type = pCurGliph->getType();
		//擦除原本的图形
		//pCurGliph->drawSelf(m_pDC);

		//this->hideBoundingBox(pCurGliph);
		this->hideHandle(pCurGliph);
			
		//std::ofstream log;
		//log.open("log.txt", std::ofstream::out | std::ofstream::app);
		//log << "symb: " << symb << std::endl;
		//log << "count before del: " << m_pDoc->m_GliphList.GetCount() << std::endl;
		m_pDoc->delGliphAt(symb);
		//log << "count after del: " << m_pDoc->m_GliphList.GetCount() << std::endl;
		m_pDoc->addGliph(newGliph); 
		//log << "count after add: " << m_pDoc->m_GliphList.GetCount() << std::endl;			
		//log.close();
			
		newGliph->setBoundingBox();
		newGliph->setHandleList();
		showHandle(newGliph);
		
		/*newGliph = nullptr; */
		symb = -1;
		flag = -1;
	}
}
void MyController::OnMouseMove(UINT nFlags, CPoint point)
{	
	m_pDC->SetROP2(R2_NOT);
	if (m_mode != DRAW_SELECT) {
		m_pDC->SelectStockObject(NULL_BRUSH);
		if (nFlags & MK_LBUTTON) {
			showSelf(pCurGliph);
			hideHandle(pCurGliph);
			
			pCurGliph->setCorner(m_ptStart, point);
			showSelf(pCurGliph);
			showHandle(pCurGliph);

			pCurGliph->setBoundingBox();
			pCurGliph->setHandleList();
		}
	}
	else
	{
		mousepointE = point;
		m_pDC->SelectStockObject(NULL_BRUSH);
		
		this->offset = mousepointE - mousepointS;//更新offset		
		this->Xoffset = offset.x;
		this->Yoffset = offset.y;
        if (flag == -1)
            return;

        Gliph::TYPE type = pCurGliph->getType();

		if (this->flag == 0)//move要擦除两次，一次是擦除已经建立好的图元，第二次是擦除移动过程中创建的图元
		{
			//擦掉过程中的图像
			prevGliph = new Gliph(type, pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset);
			prevGliph->drawSelf(m_pDC);
			//绘制新图形
			newGliph = new Gliph(type, pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset);
			newGliph->drawSelf(m_pDC);

			mousepointP = point;
			this->prevoffset = mousepointP - mousepointS;
		}
		if (this->flag == 1)
		{
			CPoint offset1, offset2; 
			
			// 0: 左上, 1: 右上, 2: 右下, 3: 左下
			// 4: 上, 5: 右, 6: 下, 7: 左

			if (handle == 0 || handle == 4 || handle == 7)
			{
				offset1.x = Xoffset;
				offset1.y = Yoffset;
				offset2.x = 0;
				offset2.y = 0;
			}
			if (handle == 1)
			{
				offset1.x = 0;
				offset1.y = Yoffset;
				offset2.x = Xoffset;
				offset2.y = 0;

			}
			if (handle == 3)
			{
				offset1.y = 0;
				offset1.x = Xoffset;
				offset2.y = Yoffset;
				offset2.x = 0;

			}
			if (handle == 2 || handle == 5 || handle == 6)
			{
				offset2.x = Xoffset;
				offset2.y = Yoffset;
				offset1.x = 0;
				offset1.y = 0;
			}

			//擦掉过程中的图像
			prevGliph = new Gliph(type, pCurGliph->getSpt() + prevOffset1, pCurGliph->getEpt() + prevOffset2);
			prevGliph->drawSelf(m_pDC);

			//重绘
			newGliph = new Gliph(type, pCurGliph->getSpt() + offset1, pCurGliph->getEpt() + offset2);
			newGliph->drawSelf(m_pDC);

			prevOffset1 = offset1;
			prevOffset2 = offset2;
		}
	}
	this->m_ptEnd = point;
}
