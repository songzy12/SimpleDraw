// SimpleDraw.h : SimpleDraw Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CSimpleDrawApp:
// �йش����ʵ�֣������ SimpleDraw.cpp
//

class CSimpleDrawApp : public CWinApp
{
public:
	CSimpleDrawApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSimpleDrawApp theApp;
