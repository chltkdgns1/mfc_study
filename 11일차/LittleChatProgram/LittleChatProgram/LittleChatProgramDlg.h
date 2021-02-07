
// LittleChatProgramDlg.h: 헤더 파일
//

#pragma once


// CLittleChatProgramDlg 대화 상자
class CLittleChatProgramDlg : public CDialogEx
{


private:
	CListBox idc_chat_list;
	CEdit idc_edit_input;
// 생성입니다.
public:
	CLittleChatProgramDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LITTLECHATPROGRAM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonClick();

	void PrintMessage();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
