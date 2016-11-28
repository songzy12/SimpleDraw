#pragma once
#include"Gliph.h"
class RoundRect:
	public Gliph
{
public:
	RoundRect(int type,CPoint pt1, CPoint pt2);
	~RoundRect();
};

