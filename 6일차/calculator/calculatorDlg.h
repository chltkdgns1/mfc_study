
// calculatorDlg.h: 헤더 파일
//

#pragma once


// CcalculatorDlg 대화 상자
class CcalculatorDlg : public CDialogEx
{

private :
	CCheckListBox m_item_list;
	CButton button_cal_total_price;
	int	*price_list;
	int size;

// 생성입니다.
public:
	CcalculatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	void init(); // 뷰들 선언 정의
	void synCursor(int idx);
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeItemList();
	//void setPriceListLength(int n) ;
	//void initPriceList(int list[]);

private:
	CListBox m_cnt_list;
public:
	afx_msg void OnBnClickedCalTotalPrice();
};
