
// tipsWareProject_First.cpp: 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "tipsWareProject_First.h"
#include "tipsWareProject_FirstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtipsWareProjectFirstApp

BEGIN_MESSAGE_MAP(CtipsWareProjectFirstApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CtipsWareProjectFirstApp 생성

CtipsWareProjectFirstApp::CtipsWareProjectFirstApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

CtipsWareProjectFirstApp theApp;

BOOL CtipsWareProjectFirstApp::InitInstance()
{

	CWinApp::InitInstance();

	CtipsWareProjectFirstDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	
	return FALSE;
}

