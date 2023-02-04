
// Binoxxo_FlessaDlg.h: Headerdatei
//

#pragma once


// CBinoxxoFlessaDlg-Dialogfeld
class CBinoxxoBelegDlg : public CDialogEx
{
// Konstruktion
public:
	CBinoxxoBelegDlg(CWnd* pParent = nullptr);	// Standardkonstruktor

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINOXXO_FLESSA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;

	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonAbout();
	afx_msg void OnGameButton(UINT nID);
	void SetGame(int curstate[100]);
	int state[100] = { 0 };
	int backupstate1[100] = { 0 };
	int backupstate2[100] = { 0 };
	int backupstate3[100] = { 0 };
	int undostate = 0;
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonUndo();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonImport();
	afx_msg void OnBnClickedButtonSave2();
	afx_msg void OnBnClickedButtonSave3();
	afx_msg void OnBnClickedButtonImport2();
	afx_msg void OnBnClickedButtonImport3();
};
