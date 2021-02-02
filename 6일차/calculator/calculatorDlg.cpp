
// calculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define MAX_ITEM_COUNT 7

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CcalculatorDlg 대화 상자

//void CcalculatorDlg::setPriceListLength(int n) {
//	price_list = new int[n];
//	size = n;
//}
//
//
//void CcalculatorDlg::initPriceList(int list[]) {
//	for (int i = 0; i < size; i++) {
//		price_list[i] = list[i];
//	}
//}


CcalculatorDlg::CcalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BEGIN_MESSAGE_MAP(CcalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_ITEM_LIST, &CcalculatorDlg::OnLbnSelchangeItemList)
	ON_BN_CLICKED(BUTTON_CAL_TOTAL_PRICE, &CcalculatorDlg::OnBnClickedCalTotalPrice)
END_MESSAGE_MAP()


// CcalculatorDlg 메시지 처리기

BOOL CcalculatorDlg::OnInitDialog(){
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	init(); // 초기화 부분


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CcalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CcalculatorDlg::OnPaint()
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

HCURSOR CcalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CcalculatorDlg::init() {

	CString str[MAX_ITEM_COUNT] = {
		L"아메리카노     1900원",
		L"카페라떼       2500원",
		L"카페모카       2800원",
		L"에스프레소     1800원",
		L"바닐라라떼     3500원",
		L"카푸치노       3300원",
		L"비엔나         3500원"
	};


	int list[MAX_ITEM_COUNT] = {
		1900,2500,2800,1800,3500,3300,3500
	};

	m_item_list.SubclassDlgItem(IDC_ITEM_LIST, this);
	m_item_list.SetItemHeight(0, 24);

	m_cnt_list.SubclassDlgItem(IDC_CNT_LIST, this);
	m_cnt_list.SetItemHeight(0, 24);

	button_cal_total_price.SubclassDlgItem(BUTTON_CAL_TOTAL_PRICE, this);

	for (int i = 0; i < MAX_ITEM_COUNT; i++) {
		m_item_list.InsertString(i, str[i]);
		m_item_list.SetItemData(i, list[i]);
		m_cnt_list.InsertString(i, L"0");
		m_cnt_list.SetItemData(i, 0);
	}
}

CMutex g_mutex(FALSE, NULL);

void CcalculatorDlg::OnLbnSelchangeItemList()
{
	int idx = m_item_list.GetCurSel();
	SetDlgItemInt(IDC_TOTAL_PRICE, idx);
	synCursor(idx);

	//g_mutex.Lock();
	if (m_item_list.GetCheck(idx)) {
		m_cnt_list.DeleteString(idx);
		m_cnt_list.InsertString(idx, L"1");
		m_cnt_list.SetCurSel(idx);
	}
	else {
		m_cnt_list.DeleteString(idx);
		m_cnt_list.InsertString(idx, L"0");
		m_cnt_list.SetCurSel(idx);
	}
	//g_mutex.Unlock();
}

void CcalculatorDlg::synCursor(int idx) {
	m_cnt_list.SetCurSel(idx);
}

void CcalculatorDlg::OnBnClickedCalTotalPrice()
{
	int sum = 0, count = m_item_list.GetCount();
	for (int i = 0; i < count; i++) {
		if (m_item_list.GetCheck(i)) {
			sum += m_item_list.GetItemData(i);
		}
	}

	SetDlgItemInt(IDC_TOTAL_PRICE, sum);
}
