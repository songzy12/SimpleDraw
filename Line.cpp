#include "stdafx.h"
#include "Line.h"


Line::Line(int type,CPoint pt1, CPoint pt2) :Gliph(0,pt1, pt2)
{

}


Line::~Line()
{

}

/*
int Line::hitHandle(CPoint pt)
{
	for (int i = 0; i < 2; i++)
	{
		if (handle[i].PtInRect(pt) == true)
			return i + 1;
	}
	return 0;
}
CRect Line::DrawHandle(CDC *PDC)
{
	for (int i = 0; i < 2; i++)
	{
		handle[i] = new CRect(box[i].x - 5, box[i].y + 5, box[i].x + 5, box[i].y + 5);
		PDC->Rectangle(handle[i]);
	}
	return handle[2];
}
*/

