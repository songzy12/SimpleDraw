#pragma once
#include"Gliph.h"
class Rectangle:
	public Gliph
{
public:
	Rectangle(int type,CPoint pt1,CPoint pt2);
	~Rectangle();
};

