
// LittleChatProgram.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "LittleChatProgram.h"
#include "LittleChatProgramDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLittleChatProgramApp

BEGIN_MESSAGE_MAP(CLittleChatProgramApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLittleChatProgramApp 생성

CLittleChatProgramApp::CLittleChatProgramApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CLittleChatProgramApp 개체입니다.

CLittleChatProgramApp theApp;


// CLittleChatProgramApp 초기화

BOOL CLittleChatProgramApp::InitInstance()
{
	CWinApp::InitInstance();
	CLittleChatProgramDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
}

