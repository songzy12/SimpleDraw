// SimpleDrawDoc.cpp :  CSimpleDrawDoc ���ʵ��
//

#include "stdafx.h"
#include "SimpleDraw.h"

#include "SimpleDrawDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimpleDrawDoc

IMPLEMENT_DYNCREATE(CSimpleDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimpleDrawDoc, CDocument)
END_MESSAGE_MAP()


// CSimpleDrawDoc ����/����

CSimpleDrawDoc::CSimpleDrawDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CSimpleDrawDoc::~CSimpleDrawDoc()
{
}

BOOL CSimpleDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CSimpleDrawDoc ���л�

void CSimpleDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

// CSimpleDrawDoc ���

#ifdef _DEBUG
void CSimpleDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimpleDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSimpleDrawDoc ����
bool  CSimpleDrawDoc::addGliph(Gliph * Obj)
{
	this->m_GliphList.AddTail(Obj);
	return true;
}
Gliph * CSimpleDrawDoc::getGliphAt(int index)
{
	if (index < 0 || index >= this->m_GliphList.GetCount()) {
		return NULL;
	}
	return this->m_GliphList.GetAt(m_GliphList.FindIndex(index));
}
bool CSimpleDrawDoc::delGliphAt(int index)
{
	if (index < 0 || index >= this->m_GliphList.GetCount()) {
		return NULL;
	}
	this->m_GliphList.RemoveAt(m_GliphList.FindIndex(index));
	return true;
}
bool CSimpleDrawDoc::delGliph(Gliph* Obj)
{
	if (Obj == NULL) {
		return false;
	}
	POSITION pos = this->m_GliphList.Find(Obj);
	this->m_GliphList.RemoveAt(pos);
	return true;
}
unsigned int  CSimpleDrawDoc::GliphCount()
{
	return this->m_GliphList.GetCount();
}

