#include "StdAfx.h"
#include ".\mycontroller.h"
#include <fstream>

MyController::MyController(void)
{
	m_mode = DRAW_SELECT;
}
MyController::MyController(CDC * pDC, CSimpleDrawDoc* pDoc)
{
	this->m_pDC = pDC;
	this->m_pDoc = pDoc;

}
MyController::~MyController(void)
{
}

void MyController::showHandle(Gliph* ptgliph)
{
	int symb;
	for (symb = 0; symb < 8; symb++)
	{
		this->m_pDC->Rectangle(ptgliph->handleList[symb]);
	}

}

void MyController::OnLButtonDown(UINT nFlags, CPoint point)
{
	this->m_ptStart = point;
	this->m_ptPrev = point;
	switch (m_mode)
	{
	case MyController::DRAW_LINE:
	{
		pCurGliph = new Gliph(0, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 0);
		showHandle(pCurGliph);
	}
	break;
	case MyController::DRAW_Rectangle:
	{
		pCurGliph = new Gliph(1, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 1);
		showHandle(pCurGliph);
	}
	break;
	case MyController::DRAW_RoundRect:
	{
		pCurGliph = new Gliph(2, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 2);
		showHandle(pCurGliph);
	}
	break;
	case MyController::DRAW_Ellipse:
	{
		pCurGliph = new Gliph(3, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 3);
		showHandle(pCurGliph);
	}
	break;
	case MyController::DRAW_SELECT:
	{
		mousepointS = point;
		// TODO
		std::ofstream log;
		log.open("log.txt", std::ofstream::out | std::ofstream::app);
		//log << mousepointS.x << "\n";
		//log << m_pDoc->m_GliphList.GetCount() << "\n";
		int i;
		for (i = 0; i < m_pDoc->m_GliphList.GetCount(); i++)
		{
			log << i << ": " << m_pDoc->getGliphAt(i)->hitTest(point)<<"\n";
			if (m_pDoc->getGliphAt(i)->hitTest(point) == true)
			{
				this->showHandle(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(i)));
				this->symb = i;

				if (m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->hitHandleTest(point) != -1)
				{
					this->flag = 1;//Ëõ·Å
				}
				else
				{
					this->flag = 0;//Æ½ÒÆ
				}
			}

		}
		log << "flag:" << this->flag << "\n";
		//log << "symb:" << this->symb << "\n";
		log.close();
	}break;
	default:
		break;
	}
}
void MyController::OnLButtonUp(UINT nFlags, CPoint point)
{
	this->m_ptEnd = point;
	switch (m_mode)
	{
	case DRAW_LINE:
	{
		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 0);
		showHandle(pCurGliph);
		pCurGliph->setBoundingBox(pCurGliph->start, pCurGliph->end);
	}
	break;
	case DRAW_Rectangle:
	{
		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 1);
		showHandle(pCurGliph);
		pCurGliph->setBoundingBox(pCurGliph->start, pCurGliph->end);
	}
	break;
	case DRAW_RoundRect:
	{
		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 2);
		showHandle(pCurGliph);
		pCurGliph->setBoundingBox(pCurGliph->start, pCurGliph->end);
	}
	break;
	case DRAW_Ellipse:
	{
		pCurGliph->addpoint(point);
		pCurGliph->CreateHandleList(this->m_ptStart, point, 3);
		showHandle(pCurGliph);
		pCurGliph->setBoundingBox(pCurGliph->start, pCurGliph->end);
	}
	case DRAW_SELECT:
	{	
	}
	break;
	}
}
void MyController::OnMouseMove(UINT nFlags, CPoint point)
{
	m_pDC->SetROP2(R2_NOT);
	switch (m_mode) {
	case DRAW_LINE:
		if (nFlags & MK_LBUTTON) 
		{
			m_pDC->MoveTo(this->m_ptStart);
			m_pDC->LineTo(this->m_ptPrev);
			m_pDC->MoveTo(this->m_ptStart);
			m_pDC->LineTo(point);
			m_ptPrev = point;

			pCurGliph->addpoint(point);
			pCurGliph->CreateHandleList(this->m_ptStart, point, 0);
			showHandle(pCurGliph);
			showHandle(pCurGliph);

		}
		break;
	case DRAW_Rectangle:
	{
		m_pDC->SelectStockObject(NULL_BRUSH);
		if (nFlags & MK_LBUTTON)
		{
			m_pDC->Rectangle(CRect(m_ptStart, m_ptPrev));
			m_pDC->Rectangle(CRect(m_ptStart, point));
			m_ptPrev = point;

			pCurGliph->addpoint(point);
			pCurGliph->CreateHandleList(this->m_ptStart, point, 1);
			showHandle(pCurGliph);
			showHandle(pCurGliph);
		}
	}
	break;
	case DRAW_RoundRect:
	{
		m_pDC->SelectStockObject(NULL_BRUSH);
		if (nFlags & MK_LBUTTON)
		{
			m_pDC->RoundRect(CRect(m_ptStart, m_ptPrev), CPoint(30, 30));
			m_pDC->RoundRect(CRect(m_ptStart, point), CPoint(30, 30));
			m_ptPrev = point;

			pCurGliph->addpoint(point);
			pCurGliph->CreateHandleList(this->m_ptStart, point, 2);
			showHandle(pCurGliph);
			showHandle(pCurGliph);
		}
	}
	break;
	case DRAW_Ellipse:
	{
		m_pDC->SelectStockObject(NULL_BRUSH);
		if (nFlags & MK_LBUTTON)
		{
			m_pDC->Ellipse(CRect(m_ptStart, m_ptPrev));
			m_pDC->Ellipse(CRect(m_ptStart, point));
			m_ptPrev = point;

			pCurGliph->addpoint(point);
			pCurGliph->CreateHandleList(this->m_ptStart, point, 3);
			showHandle(pCurGliph);
			showHandle(pCurGliph);
		}
	}
	break;
	case DRAW_SELECT:
	{

		mousepointE = point;
		offset = mousepointE - mousepointS;
		mousepointS = point;
		m_pDC->SetROP2(R2_NOT);
		m_pDC->SelectStockObject(NULL_BRUSH);
		// TODO
		std::ofstream log;
		log.open("log.txt", std::ofstream::out | std::ofstream::app);
		if (this->flag == 0)
		{
			log << "type: " << m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getType() << "\n";
			log << "offset: " << this->offset.x << " " << this->offset.y << "\n";

			if (m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getType() == 0)
			{
				m_pDC->MoveTo(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt());
				m_pDC->LineTo(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getEpt());

				m_pDC->MoveTo(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt() + this->offset);
				m_pDC->LineTo(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getEpt() + this->offset);

			}
			if (m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getType() == 1)
			{
				m_pDC->Rectangle(CRect(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt(), m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getEpt()));
				m_pDC->Rectangle(CRect(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt() + this->offset, m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getEpt() + this->offset));
			}
			if (m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getType() == 2)
			{
				m_pDC->RoundRect(CRect(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt(), m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(symb))->getEpt()), CPoint(30, 30));
				m_pDC->RoundRect(CRect(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt() + this->offset, m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(symb))->getEpt() + this->offset), CPoint(30, 30));

			}
			if (m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getType() == 3)
			{
				m_pDC->Ellipse(CRect(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt(), m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getEpt()));
				m_pDC->Ellipse(CRect(m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getSpt() + this->offset, m_pDoc->m_GliphList.GetAt(m_pDoc->m_GliphList.FindIndex(this->symb))->getEpt() + this->offset));

			}
		}
		log.close();
	}
	this->m_ptEnd = point;
	}
}
