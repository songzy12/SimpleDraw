// SimpleDrawDoc.cpp :  CSimpleDrawDoc 类的实现
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


// CSimpleDrawDoc 构造/析构

CSimpleDrawDoc::CSimpleDrawDoc()
{
	// TODO: 在此添加一次性构造代码

}

CSimpleDrawDoc::~CSimpleDrawDoc()
{
}

BOOL CSimpleDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CSimpleDrawDoc 序列化

void CSimpleDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

// CSimpleDrawDoc 诊断

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


// CSimpleDrawDoc 命令
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

