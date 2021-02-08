
// Tetris_by_mfcDlg.h: 헤더 파일
//

#pragma once


// CTetrisbymfcDlg 대화 상자
class CTetrisbymfcDlg : public CDialogEx
{
// 생성입니다.

private:

public:
	CTetrisbymfcDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	static UINT ThreadFirst(LPVOID _mothod);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TETRIS_BY_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	void GameClear();

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPause();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic idc_level;
	CStatic idc_score;
};
