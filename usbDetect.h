// usbDetect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CusbDetectApp:
// �йش����ʵ�֣������ usbDetect.cpp
//

class CusbDetectApp : public CWinApp
{
public:
	CusbDetectApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CusbDetectApp theApp;