#include "stdafx.h"
#include "Gliph.h"
#include <fstream>

Gliph::Gliph(int type, CPoint point1, CPoint point2)
{
	this->m_type = type;
	this->start = point1;
	this->end = point2;
}

Gliph::~Gliph()
{
}

void Gliph::setBoundingBox(CPoint point1, CPoint point2) 
{
	this->m_BoundingBox = new CRect(point1, point2);
}

bool Gliph::hitTest(CPoint pt)
{
	/*std::ofstream log;
	log.open("log.txt", std::ofstream::out | std::ofstream::app);
	log << "topleft: "<<m_BoundingBox.TopLeft().x << " " << m_BoundingBox.TopLeft().y << "\n";
	log << "bottomright: "<<m_BoundingBox.BottomRight().x << " " << m_BoundingBox.BottomRight().y << "\n";
	log << "pt: "<<pt.x << " " << pt.y << "\n";
	log.close()*/

	if (m_BoundingBox.PtInRect(pt) == true)
	{
		m_bSelectedFlag = true;
		return m_bSelectedFlag;
	}
	else
	{
		m_bSelectedFlag = false;
		return m_bSelectedFlag;
	}
}
void Gliph::moveByOffset(float Xoffset, float yOffset)
{
	m_BoundingBox.OffsetRect(Xoffset, yOffset);
}
void Gliph::moveTo(unsigned int index, CPoint pt)
{
}
bool Gliph::getSelectedFlag()
{
	if (m_bSelectedFlag == true)
		return true;
	if (m_bSelectedFlag == false)
		return false;
}
void Gliph::setSelectedFlag(bool flag)
{
	if (flag == true)
		m_bSelectedFlag = true;
	if (flag == false)
		m_bSelectedFlag = false;
}void Gliph::CreateHandleList(CPoint pt1, CPoint pt2, int type)
{
	int middleX = (pt1.x + pt2.x) / 2;
	int middleY = (pt1.y + pt2.y) / 2;

	CRect handlelist[8];
	

	if (type == 0)
	{
		handlelist[0] = new CRect(pt1.x - 5, pt1.y + 5, pt1.x + 5, pt1.y - 5);
		handlelist[1] = new CRect(pt2.x - 5, pt2.y + 5, pt2.x + 5, pt2.y - 5);
	}
	else
	{
		handlelist[0] = new CRect(pt1.x - 5, pt1.y + 5, pt1.x + 5, pt1.y - 5);
		handlelist[1] = new CRect(pt2.x - 5, pt1.y + 5, pt2.x + 5, pt1.y - 5);
		handlelist[2] = new CRect(pt2.x - 5, pt2.y + 5, pt2.x + 5, pt2.y - 5);
		handlelist[3] = new CRect(pt1.x - 5, pt2.y + 5, pt1.x + 5, pt2.y - 5);
		handlelist[4] = new CRect(middleX - 5, pt1.y + 5, middleX + 5, pt1.y - 5);
		handlelist[5] = new CRect(pt2.x - 5, middleY + 5, pt2.x + 5, middleY - 5);
		handlelist[6] = new CRect(middleX - 5, pt2.y + 5, middleX + 5, pt2.y - 5);
		handlelist[7] = new CRect(pt1.x - 5, middleY + 5, pt1.x + 5, middleY - 5);
	}
	int i;
	for (i = 0; i < 8; i++)
	{
		this->handleList[i] = handlelist[i];
	}
}
void Gliph::Drawboundingbox(CDC* pdc)
{
	pdc->Rectangle(m_BoundingBox);
}
int Gliph::hitHandleTest(CPoint pt)
{
	int j,flag;
	for (j = 0; j < 8; j++)
	{
		if (this->handleList[j].PtInRect(pt) == true)
		{
			flag = j;
			return flag;
		}
	}
	return -1;
}
void Gliph::addpoint(CPoint point)
{
	this->end = point;
}