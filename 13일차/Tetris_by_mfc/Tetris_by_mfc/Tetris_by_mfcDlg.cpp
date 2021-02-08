
// Tetris_by_mfcDlg.cpp: 구현 파일
//
#include "pch.h"
#include "framework.h"
#include "Tetris_by_mfc.h"
#include "Tetris_by_mfcDlg.h"
#include "afxdialogex.h"
#include "Board.h"
#include "Block.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetrisbymfcDlg 대화 상자


CTetrisbymfcDlg::CTetrisbymfcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TETRIS_BY_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTetrisbymfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEVEL, idc_level);
	DDX_Control(pDX, IDC_SCORE, idc_score);
}

BEGIN_MESSAGE_MAP(CTetrisbymfcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTetrisbymfcDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CTetrisbymfcDlg::OnBnClickedButtonPause)
END_MESSAGE_MAP()


// CTetrisbymfcDlg 메시지 처리기

BOOL CTetrisbymfcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}



void CTetrisbymfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CTetrisbymfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTetrisbymfcDlg::GameClear() {
	// 게임 클리어 항목들 다 넣어서 캡슐화
}

Block *block = NULL;
Board *board = NULL;
static bool  start = false;
static int speed = 400;
UINT CTetrisbymfcDlg::ThreadFirst(LPVOID _mothod) // 게임을 시작했을 때
{
	CTetrisbymfcDlg *fir = (CTetrisbymfcDlg*)_mothod;

	int moveTime = GetTickCount();


	block->getRandBlockColor();

	start = true;

	while (start)
	{
		int t = GetTickCount();
		if (t  - moveTime >= speed) {
			moveTime = t;
			if (block->Down(board->board, board->getHeight(), board->getWidth())) {
				board->deleteLine(speed);
			}
		}
	}
	return 0;
}


void CTetrisbymfcDlg::OnBnClickedButtonStart() // 시작하기 버튼 클릭시에 쓰레드 하나 생성
{
	block = new Block(this);
	board = new Board(this);

	CClientDC dc(this);
	dc.Rectangle(0, 0, 210, 420);
	board->mustInit(20, 10);
	board->printBoard();

	start = false;
	
	CWinThread *p1 = NULL;
	p1 = AfxBeginThread(ThreadFirst, this);
	if (p1 == NULL)
	{
		AfxMessageBox(L"Error");
	}
	CloseHandle(p1);
}


void CTetrisbymfcDlg::OnBnClickedButtonPause()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CTetrisbymfcDlg::PreTranslateMessage(MSG* pMsg){
	if (pMsg->message == WM_KEYDOWN && start) {
		if (pMsg->wParam == 0x53) { // s	
			if (block->Down(board->board, board->getHeight(), board->getWidth())) {
				board->deleteLine(speed);
			}
			return true;
		}
		else if (pMsg->wParam == 0x41) { //  a
			block->left(board->board, board->getHeight(), board->getWidth());
			return true;
		} 
		else if (pMsg->wParam == 0x44) { // d
			block->right(board->board, board->getHeight(), board->getWidth());
			return true;
		}
		else if (pMsg->wParam == 0x52) {
			block->Lotation(board->board, board->getHeight(), board->getWidth());
			return true;
		}
		else if (pMsg->wParam == 0x20) {
			while (!block->Down(board->board, board->getHeight(), board->getWidth()));
			board->deleteLine(speed);
			return true;
		}
	}
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}
