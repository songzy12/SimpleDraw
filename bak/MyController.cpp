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
void MyController::showBoundingBox(Gliph* ptGliph)
{
	this->m_pDC->Rectangle(ptGliph->m_BoundingBox);

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
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 0);
		showHandle(pCurGliph);



	}
	break;
	case MyController::DRAW_Rectangle:
	{
		pCurGliph = new Gliph(1, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 1);
		showHandle(pCurGliph);
	}
	break;
	case MyController::DRAW_RoundRect:
	{
		pCurGliph = new Gliph(2, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 2);
		
		showHandle(pCurGliph);
		showHandle(pCurGliph);
	}
	break;
	case MyController::DRAW_Ellipse:
	{
		pCurGliph = new Gliph(3, point, point);
		m_pDoc->addGliph(pCurGliph);

		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 3);
		showHandle(pCurGliph);
	}
	break;
	case MyController::DRAW_SELECT:
	{
		mousepointS = point;
		mousepointP = point;
		
		m_pDC->SelectStockObject(NULL_BRUSH);
		
		int i;
		int j = m_pDoc->m_GliphList.GetCount();
		std::ofstream log;
		log.open("log.txt", std::ofstream::out | std::ofstream::app);
		log << "count: " << m_pDoc->m_GliphList.GetCount() << std::endl;
		log.close();
		for (i = 0; i < m_pDoc->m_GliphList.GetCount(); i++)
		{
			if (m_pDoc->getGliphAt(i)->hitTest(point) == true)
			{
				
				this->symb = i;
				pCurGliph = m_pDoc->getGliphAt(i);
				
				this->showBoundingBox(pCurGliph);//���о���ʾboundingbox
				//��������handle
				if (pCurGliph->hitHandleTest(point) != -1)
				{
					this->flag = 1;//����
					m_pDC->SetROP2(R2_NOT);
					
				}
				else
				{
					this->flag = 0;//�ƶ�

				}
			}

		}
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
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 0);
		showHandle(pCurGliph);


	}
	break;
	case DRAW_Rectangle:
	{
		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 1);
		showHandle(pCurGliph);
	}
	break;
	case DRAW_RoundRect:
	{
		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 2);
		showHandle(pCurGliph);
	}
	break;
	case DRAW_Ellipse:
	{
		pCurGliph->addpoint(point);
		pCurGliph->setBoundingBox();
		pCurGliph->CreateHandleList(this->m_ptStart, point, 3);
		showHandle(pCurGliph);
	}
	case DRAW_SELECT://///////////////////////////////////////////��Ӵ��룡������
	{
		mousepointE = point;
		flag = -1;
		/*
		m_pDoc->addGliph(newGliph);
		newGliph->addpoint(point);
		newGliph->setBoundingBox();
		//showBoundingBox(newGliph);
		newGliph->CreateHandleList(, point, 0);
		showHandle(pCurGliph);
		showHandle(pCurGliph);
		*/
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
			pCurGliph->setBoundingBox();
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
			pCurGliph->setBoundingBox();
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
			pCurGliph->setBoundingBox();
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
			pCurGliph->setBoundingBox();
			pCurGliph->CreateHandleList(this->m_ptStart, point, 3);
			showHandle(pCurGliph);
			showHandle(pCurGliph);
		}
	}
	break;
	case DRAW_SELECT:
	{

		m_pDC->SelectStockObject(NULL_BRUSH);
		mousepointE = point;
		this->offset = mousepointE - mousepointS;//����offset
		
		
		if (this->flag == 0)//moveҪ�������Σ�һ���ǲ����Ѿ������õ�ͼԪ���ڶ����ǲ����ƶ������д�����ͼԪ
		{
			if (pCurGliph->getType() == 0)//��
			{
				//����ԭ����ͼ��
				m_pDC->MoveTo(pCurGliph->getSpt());
				m_pDC->LineTo(pCurGliph->getEpt());
				
				//������ͼ��
				m_pDC->MoveTo(pCurGliph->getSpt() + this->offset);
				m_pDC->LineTo(pCurGliph->getEpt() + this->offset);
				
				//���������е�ͼ��
				m_pDC->MoveTo(pCurGliph->getSpt() + this->prevoffset);
				m_pDC->LineTo(pCurGliph->getEpt() + this->prevoffset);
				mousepointP = point;
				this->prevoffset = mousepointP - mousepointS;
				
				//������ͼ��
				m_pDC->MoveTo(pCurGliph->getSpt() + this->offset);
				m_pDC->LineTo(pCurGliph->getEpt() + this->offset);

				m_pDC->MoveTo(pCurGliph->getSpt() + this->offset);
				m_pDC->LineTo(pCurGliph->getEpt() + this->offset);
				
				//��ԭ������λ�ô�������ͼ��,�Լ���ʾ��handle
				newGliph = new Gliph(0,pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset);
				m_pDoc->delGliphAt(symb);
				//m_pDoc->upadateGliph(pCurGliph, newGliph);
				m_pDoc->addGliph(newGliph);
				//newGliph->addpoint(point);
				//newGliph->setBoundingBox();
				//showBoundingBox(newGliph);
				//pCurGliph->CreateHandleList(this->m_ptStart, point, 0);
				//showHandle(pCurGliph);
				//showHandle(pCurGliph);
				

			}
			if (pCurGliph->getType() == 1)//����
			{
				

				//����ԭ����
				m_pDC->Rectangle(CRect(pCurGliph->getSpt(), pCurGliph->getEpt()));
				//�����µ�ͼ��
				m_pDC->Rectangle(CRect(pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset));

				//���������е�
				m_pDC->Rectangle(CRect(pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset));
				mousepointP = point;
				this->prevoffset = mousepointP - mousepointS;
				//�����µ�ͼ��
				m_pDC->Rectangle(CRect(pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset));
				m_pDC->Rectangle(CRect(pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset));
				////��ԭ������λ�ô�������ͼ��,�Լ���ʾ��handle
				newGliph = new Gliph(1, pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset);
				m_pDoc->delGliphAt(symb);
				//m_pDoc->upadateGliph(pCurGliph, newGliph);
				m_pDoc->addGliph(newGliph);

			}
			if (pCurGliph->getType() == 2)//Բ��
			{
		
				//����ԭ����
				m_pDC->RoundRect(CRect(pCurGliph->getSpt(), pCurGliph->getEpt()), CPoint(30, 30));
				//�����µ�ͼ��
				m_pDC->RoundRect(CRect(pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset), CPoint(30, 30));
				//���������е�
				m_pDC->RoundRect(CRect(pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset), CPoint(30, 30));
				mousepointP = point;
				this->prevoffset = mousepointP - mousepointS;
				//�����µ�ͼ��
				m_pDC->Rectangle(CRect(pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset));
				m_pDC->Rectangle(CRect(pCurGliph->getSpt() + this->prevoffset, pCurGliph->getEpt() + this->prevoffset));
				////��ԭ������λ�ô�������ͼ��,�Լ���ʾ��handle
				newGliph = new Gliph(2, pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset);
				m_pDoc->delGliphAt(symb);
				//m_pDoc->upadateGliph(pCurGliph, newGliph);
				m_pDoc->addGliph(newGliph);
			}  
			if (pCurGliph->getType() == 3)//��Բ
			{
				//����ԭ����
				m_pDC->Ellipse(CRect(pCurGliph->getSpt(), pCurGliph->getEpt()));
				//�����µ�ͼ��
				m_pDC->Ellipse(CRect(pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset));
				//���������е�
				m_pDC->Ellipse(CRect(pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset));
				mousepointP = point;
				this->prevoffset = mousepointP - mousepointS;
				//�����µ�ͼ��
				m_pDC->Ellipse(CRect(pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset));
				m_pDC->Ellipse(CRect(pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset));
				////��ԭ������λ�ô�������ͼ��,�Լ���ʾ��handle
				newGliph = new Gliph(3, pCurGliph->getSpt() + this->offset, pCurGliph->getEpt() + this->offset);
				m_pDoc->delGliphAt(symb);
				//m_pDoc->upadateGliph(pCurGliph, newGliph);
				m_pDoc->addGliph(newGliph);

			}
		}
		if (this->flag == 1)
		{
			CPoint offset1, offset2;
			int a = pCurGliph->hitHandleTest(point);
			
			if (pCurGliph->getType() == 0)
			{
				//����
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
				//�ػ�
				m_pDC->MoveTo(pCurGliph->getSpt() + offset1);
				m_pDC->LineTo(pCurGliph->getEpt() + offset2);

			}
			if (pCurGliph->getType() == 1)
			{
				//����
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
				//����
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
				//����
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
}
