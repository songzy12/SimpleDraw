#pragma once
class Gliph
{
public:
    enum TYPE
    {
        LINE,
        RECTANGLE,
        ROUNDRECT,
        ELLIPSE,
        SELECT
    };

    Gliph(TYPE type, CPoint pt1, CPoint pt2);
    ~Gliph();

protected:
	TYPE mType;//����������ֱ���ֵ��line=0��rect=1,roundrect=2,ellipse=3,select=4
	CPoint mTopLeftPt;
	CPoint mBottomRightPt;
    bool mSelectedFlag;

    CRect mHandleList[8];
    CRect mBoundingBox;//CRect���࣬Rectangle�Ǻ���

public:
	BOOL isSelected(CPoint pt);
	int handleSelected(CPoint pt);//���ػ��е�����һ��
	
    void drawSelf(CDC* pDC);
	void drawBoundingBox(CDC* pdc);
    void drawHandle(CDC* pdc);

    void setCorner(CPoint pt1, CPoint pt2);
    void setSelectedFlag(bool flag);
    void setBoundingBox();
    void setHandleList();

    bool getSelectedFlag() { return mSelectedFlag; }
    TYPE getType() { return mType; }	
    CPoint getSpt() { return mTopLeftPt; }
	CPoint getEpt() { return mBottomRightPt; }
};

