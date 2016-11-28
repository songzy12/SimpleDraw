#pragma once
class Gliph
{
public:

	
	Gliph(int type, CPoint point1, CPoint point2);
	~Gliph();
	//Gliph(CPoint point1, CPoint point2);
	

	CRect handleList[8];
	


protected:
	int m_type;//����������ֱ���ֵ��line=0��rect=1,roundrect=2,ellipse=3,select=4
	
	CRect m_HandleBox;
	CRect handle;
	unsigned char m_cWidth;
	COLORREF m_color;
	bool m_bSelectedFlag;
	bool m_bSHandleFlag;
	



public:
	CPoint start;
	CPoint end;
	CRect m_BoundingBox;//CRect���࣬Rectangle�Ǻ���

	bool hitTest(CPoint pt);
	int hitHandleTest(CPoint pt);//���ػ��е�����һ��
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

