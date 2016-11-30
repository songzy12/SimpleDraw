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
	int symb;
	for (symb = 0; symb < 8; symb++)
	{
		this->m_pDC->Rectangle(ptgliph->handleList[symb]);
	}
}

void MyController::hideHandle(Gliph* ptgliph) {
	m_pDC->SetROP2(R2_NOT);
	m_pDC->SelectStockObject(NULL_BRUSH);
	showHandle(ptgliph);
}

void MyController::showBoundingBox(Gliph* ptGliph)
{
	this->m_pDC->Rectangle(ptGliph->m_BoundingBox);
}

void MyController::hideBoundingBox(Gliph* ptGliph) {
	m_pDC->SetROP2(R2_NOT);
	m_pDC->SelectStockObject(NULL_BRUSH);
	showBoundingBox(ptGliph);
}

void MyController::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->m_ptStart = point;
	this->m_ptPrev = point;
	
	if (m_mode != MyController::DRAW_SELECT)
	{
		pCurGliph = new Gliph(m_mode, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, m_mode);
		showHandle(pCurGliph);
	}
	else
	{
		if (this->flag != -1)
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
			
			if (pCurGliph->hitHandleTest(point) != -1)
			{
				a = pCurGliph->hitHandleTest(point);

				std::ofstream log;
				log.open("log.txt", std::ofstream::out | std::ofstream::app);
				log << "handle hit: " << a << std::endl;
				log.close();

				this->flag = 1;//缩放
				this->symb = i;
				break;
			}
			else if (m_pDoc->getGliphAt(i)->hitTest(point))
			{
				this->flag = 0;//移动		
				this->showBoundingBox(pCurGliph);//击中就显示boundingbox
				this->symb = i;
				break;
			}
		}
	}
}

void MyController::OnLButtonUp(UINT nFlags, CPoint point)
{
	this->m_ptEnd = point;
	
	if (m_mode != DRAW_SELECT)
	{
		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, m_mode);
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

		m_pDC->SetROP2(R2_NOT);
		m_pDC->SelectStockObject(NULL_BRUSH);
		
		if (flag == 0) {
			int type = pCurGliph->getType();
			//擦除原本的图形
			pCurGliph->drawSelf(m_pDC);

			this->hideBoundingBox(pCurGliph);
			this->hideHandle(pCurGliph);
			
			std::ofstream log;
			log.open("log.txt", std::ofstream::out | std::ofstream::app);

			log << "symb: " << symb << std::endl;
			log << "count before del: " << m_pDoc->m_GliphList.GetCount() << std::endl;
			m_pDoc->delGliphAt(symb);
			log << "count after del: " << m_pDoc->m_GliphList.GetCount() << std::endl;
			m_pDoc->addGliph(newGliph); 
			log << "count after add: " << m_pDoc->m_GliphList.GetCount() << std::endl;
			
			log.close();
			
			newGliph->setBoundingBox();
			newGliph->CreateHandleList(newGliph->getSpt(), newGliph->getEpt(), type);
			showHandle(newGliph);
		}
		else if (flag == 1) {
			if (pCurGliph->getType() == 0) {
				if (a == 0) {
					newGliph = new Gliph(0, pCurGliph->getSpt() + this->offset, pCurGliph->getEpt());
					m_pDoc->delGliphAt(symb);
					m_pDoc->addGliph(newGliph);
					newGliph->setBoundingBox();
					newGliph->CreateHandleList(newGliph->getSpt(), newGliph->getEpt(), 0);
					showHandle(newGliph);
				}
			}
		}
		
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
			pCurGliph->addpoint(point);
			showSelf(pCurGliph);
			showHandle(pCurGliph);

			pCurGliph->setBoundingBox();
			pCurGliph->CreateHandleList(this->m_ptStart, point, 1);
		}
	}
	else
	{
		mousepointE = point;
		m_pDC->SelectStockObject(NULL_BRUSH);
		this->offset = mousepointE - mousepointS;//更新offset		
		this->Xoffset = offset.x;
		this->Yoffset = offset.y;

		if (this->flag == 0)//move要擦除两次，一次是擦除已经建立好的图元，第二次是擦除移动过程中创建的图元
		{
			int type = pCurGliph->getType();
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
			
			if (pCurGliph->getType() == 0)
			{
				//擦除
				m_pDC->MoveTo(pCurGliph->getSpt());
				m_pDC->LineTo(pCurGliph->getEpt());

				if (a == 0 || a == 4 || a == 7)
				{
					offset1.x = Xoffset;
					offset1.y = Yoffset;
					offset2.x = 0;
					offset2.y = 0;
				}
				if (a == 1)
				{
					offset1.x = 0;
					offset1.y = Yoffset;
					offset2.x = Xoffset;
					offset2.y = 0;

				}
				if (a == 3)
				{
					offset1.y = 0;
					offset1.x = Xoffset;
					offset2.y = Yoffset;
					offset2.x = 0;

				}
				if (a == 2 || a == 5 || a == 6)
				{
					offset2.x = Xoffset;
					offset2.y = Yoffset;
					offset1.x = 0;
					offset1.y = 0;
				}
				//重绘
				m_pDC->MoveTo(pCurGliph->getSpt() + offset1);
				m_pDC->LineTo(pCurGliph->getEpt() + offset2);

				//擦掉过程中的图像
				m_pDC->MoveTo(pCurGliph->getSpt() + this->prevoffset);
				m_pDC->LineTo(pCurGliph->getEpt());
				mousepointP = point;
				this->prevoffset = mousepointP - mousepointS;

			}
			if (pCurGliph->getType() == 1)
			{
				//擦除
				m_pDC->Rectangle(CRect(pCurGliph->getSpt(), pCurGliph->getEpt()));


				if (a == 0 || a == 4 || a == 7)
				{
					offset1.x = Xoffset;
					offset1.y = Yoffset;
					offset2.x = 0;
					offset2.y = 0;


				}
				if (a == 1)
				{
					offset1.x = 0;
					offset1.y = Yoffset;
					offset2.x = Xoffset;
					offset2.y = 0;

				}
				if (a == 3)
				{
					offset1.y = 0;
					offset1.x = Xoffset;
					offset2.y = Yoffset;
					offset2.x = 0;

				}
				if (a == 2 || a == 5 || a == 6)
				{
					offset2.x = Xoffset;
					offset2.y = Yoffset;
					offset1.x = 0;
					offset1.y = 0;
				}
				m_pDC->Rectangle(CRect(pCurGliph->getSpt() + offset1, pCurGliph->getEpt() + offset2));

			}
			if (pCurGliph->getType() == 2)
			{
				//擦除
				m_pDC->RoundRect(CRect(pCurGliph->getSpt(), m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(symb))->getEpt()), CPoint(30, 30));


				if (a == 0 || a == 4 || a == 7)
				{
					offset1.x = Xoffset;
					offset1.y = Yoffset;
					offset2.x = 0;
					offset2.y = 0;


				}
				if (a == 1)
				{
					offset1.x = 0;
					offset1.y = Yoffset;
					offset2.x = Xoffset;
					offset2.y = 0;

				}
				if (a == 3)
				{
					offset1.y = 0;
					offset1.x = Xoffset;
					offset2.y = Yoffset;
					offset2.x = 0;

				}
				if (a == 2 || a == 5 || a == 6)
				{
					offset2.x = Xoffset;
					offset2.y = Yoffset;
					offset1.x = 0;
					offset1.y = 0;
				}
				m_pDC->RoundRect(CRect(pCurGliph->getSpt()+offset1, m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(symb))->getEpt()+offset2), CPoint(30, 30));

			}
			if (pCurGliph->getType() == 3)
			{
				//擦除
				m_pDC->Ellipse(CRect(pCurGliph->getSpt(), pCurGliph->getEpt()));


				if (a == 0 || a == 4 || a == 7)
				{
					offset1.x = Xoffset;
					offset1.y = Yoffset;
					offset2.x = 0;
					offset2.y = 0;


				}
				if (a == 1)
				{
					offset1.x = 0;
					offset1.y = Yoffset;
					offset2.x = Xoffset;
					offset2.y = 0;

				}
				if (a == 3)
				{
					offset1.y = 0;
					offset1.x = Xoffset;
					offset2.y = Yoffset;
					offset2.x = 0;

				}
				if (a == 2 || a == 5 || a == 6)
				{
					offset2.x = Xoffset;
					offset2.y = Yoffset;
					offset1.x = 0;
					offset1.y = 0;
				}
				m_pDC->Ellipse(CRect(pCurGliph->getSpt()+offset1, pCurGliph->getEpt()+offset2));
			}
		}
		
	}
	this->m_ptEnd = point;
}
