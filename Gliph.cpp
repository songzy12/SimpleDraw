#include "stdafx.h"
#include "Gliph.h"
#include <fstream>

Gliph::Gliph(TYPE type, CPoint pt1, CPoint pt2)
{
    mType = type;
    setCorner(pt1, pt2);
}

void Gliph::setCorner(CPoint pt1, CPoint pt2)
{
    this->mTopLeftPt = CPoint(min(pt1.x, pt2.x), min(pt1.y, pt2.y));
    this->mBottomRightPt = CPoint(max(pt1.x, pt2.x), max(pt1.y, pt2.y));
    setBoundingBox();
    setHandleList();
}

void Gliph::setBoundingBox()
{
    mBoundingBox = new CRect(this->mTopLeftPt, this->mBottomRightPt);
}

void Gliph::setHandleList()
{
    CPoint pt1 = mTopLeftPt;
    CPoint pt2 = mBottomRightPt;

    int middleX = (pt1.x + pt2.x) / 2;
    int middleY = (pt1.y + pt2.y) / 2;

    mHandleList[0] = new CRect(pt1.x - 5, pt1.y - 5, pt1.x + 5, pt1.y + 5); // 左上
    mHandleList[1] = new CRect(pt2.x - 5, pt1.y - 5, pt2.x + 5, pt1.y + 5); // 右上
    mHandleList[2] = new CRect(pt2.x - 5, pt2.y - 5, pt2.x + 5, pt2.y + 5); // 右下
    mHandleList[3] = new CRect(pt1.x - 5, pt2.y - 5, pt1.x + 5, pt2.y + 5); // 左下
    mHandleList[4] = new CRect(middleX - 5, pt1.y - 5, middleX + 5, pt1.y + 5); // 上
    mHandleList[5] = new CRect(pt2.x - 5, middleY - 5, pt2.x + 5, middleY + 5); // 右
    mHandleList[6] = new CRect(middleX - 5, pt2.y - 5, middleX + 5, pt2.y + 5); // 下
    mHandleList[7] = new CRect(pt1.x - 5, middleY - 5, pt1.x + 5, middleY + 5); // 左
}

Gliph::~Gliph()
{
}

void Gliph::drawSelf(CDC* m_pDC)
{
    switch (mType)
    {
        case LINE:
            m_pDC->MoveTo(this->mTopLeftPt);
            m_pDC->LineTo(this->mBottomRightPt);
            break;
        case RECTANGLE:
            m_pDC->Rectangle(CRect(mTopLeftPt, mBottomRightPt));
            break;
        case ROUNDRECT:
            m_pDC->RoundRect(CRect(mTopLeftPt, mBottomRightPt), CPoint(30, 30));
            break;
        case ELLIPSE:
            m_pDC->Ellipse(CRect(mTopLeftPt, mBottomRightPt));
            break;
    }
}

void Gliph::drawBoundingBox(CDC* pdc)
{
    pdc->Rectangle(mBoundingBox);
}

void Gliph::drawHandle(CDC* pdc)
{
    for (int symb = 0; symb < 8; symb++)
    {
        pdc->Rectangle(mHandleList[symb]);
    }
}

BOOL Gliph::isSelected(CPoint pt)
{
    return mSelectedFlag = mBoundingBox.PtInRect(pt);
}

int Gliph::handleSelected(CPoint pt)
{
    for (int j = 0; j < 8; j++)
    {
        if (mHandleList[j].PtInRect(pt))
        {
            return j;
        }
    }
    return -1;
}

void Gliph::setSelectedFlag(bool flag)
{
    mSelectedFlag = flag;
}