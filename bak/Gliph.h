#pragma once
class Gliph
{
public:

	
	Gliph(int type, CPoint point1, CPoint point2);
	~Gliph();
	//Gliph(CPoint point1, CPoint point2);
	

	CRect handleList[8];
	


protected:
	int m_type;//在子类里面分别定义值，line=0，rect=1,roundrect=2,ellipse=3,select=4
	
	CRect m_HandleBox;
	CRect handle;
	unsigned char m_cWidth;
	COLORREF m_color;
	bool m_bSelectedFlag;
	bool m_bSHandleFlag;
	



public:
	CPoint start;
	CPoint end;
	CRect m_BoundingBox;//CRect是类，Rectangle是函数

	bool hitTest(CPoint pt);
	int hitHandleTest(CPoint pt);//返回击中的是哪一个
	void moveByOffset(float Xoffset, float yOffset);
	void moveTo(unsigned int index, CPoint pt);
	bool getSelectedFlag();
	void setSelectedFlag(bool flag);

	void CreateHandleList(CPoint pt1, CPoint pt2, int type);

	void Drawboundingbox(CDC* pdc);//
	void setBoundingBox(CPoint point1, CPoint point2);
	void addpoint(CPoint point);
	int getType() { return this->m_type; }
	CPoint getSpt() { return start; }
	CPoint getEpt() { return end; }
};

