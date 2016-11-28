#pragma once
#include"Gliph.h"
class Line:
	public Gliph
{
public:
	Line(int type,CPoint pt1, CPoint pt2);
	~Line();
	//CRect DrawHandle(CDC *PDC);
	//int hitHandle(CPoint pt);

	
};

