#pragma once
#include"Gliph.h"
class Ellipse:
	public Gliph
{
public:
	Ellipse(int type,CPoint pt1, CPoint pt2);
	~Ellipse();
};

