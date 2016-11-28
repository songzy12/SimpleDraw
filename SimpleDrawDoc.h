// SimpleDrawDoc.h :  CSimpleDrawDoc 类的接口
//


#pragma once
#include "Gliph.h"
class CSimpleDrawDoc : public CDocument
{
protected: // 仅从序列化创建
	CSimpleDrawDoc();
	DECLARE_DYNCREATE(CSimpleDrawDoc)

	// 属性
public:

	// 操作
public:

	// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
public:
	bool      addGliph(Gliph * Obj);//增加一个stroke
	Gliph* getGliphAt(unsigned int index);//得到一个stroke指针
	bool      delGliphAt(unsigned int index);//删除一个stroke
	bool      delGliph(Gliph* Obj);//删除一个stroke
	unsigned int GliphCount();//stroke的个数
	void      clear();//清空当前文档
					  // 操作
public:
	 CList<Gliph*, Gliph*> m_GliphList;//private 还是 public

// 实现
public:
	virtual ~CSimpleDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


