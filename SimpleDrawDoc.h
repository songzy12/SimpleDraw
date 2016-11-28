// SimpleDrawDoc.h :  CSimpleDrawDoc ��Ľӿ�
//


#pragma once
#include "Gliph.h"
class CSimpleDrawDoc : public CDocument
{
protected: // �������л�����
	CSimpleDrawDoc();
	DECLARE_DYNCREATE(CSimpleDrawDoc)

	// ����
public:

	// ����
public:

	// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
public:
	bool      addGliph(Gliph * Obj);//����һ��stroke
	Gliph* getGliphAt(unsigned int index);//�õ�һ��strokeָ��
	bool      delGliphAt(unsigned int index);//ɾ��һ��stroke
	bool      delGliph(Gliph* Obj);//ɾ��һ��stroke
	unsigned int GliphCount();//stroke�ĸ���
	void      clear();//��յ�ǰ�ĵ�
					  // ����
public:
	 CList<Gliph*, Gliph*> m_GliphList;//private ���� public

// ʵ��
public:
	virtual ~CSimpleDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


