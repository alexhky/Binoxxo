
// Binoxxo_BelegDlg.cpp: Implementierungsdatei
//

#include "pch.h"
#include "framework.h"
#include "Binoxxo_Beleg.h"
#include "Binoxxo_BelegDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>


// CBinoxxoBelegDlg-Dialogfeld



CBinoxxoBelegDlg::CBinoxxoBelegDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BINOXXO_BELEG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinoxxoBelegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBinoxxoBelegDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CBinoxxoBelegDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CBinoxxoBelegDlg::OnBnClickedButtonAbout)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON1, IDC_BUTTON100, OnGameButton)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CBinoxxoBelegDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CBinoxxoBelegDlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_Undo, &CBinoxxoBelegDlg::OnBnClickedButtonUndo)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CBinoxxoBelegDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CBinoxxoBelegDlg::OnBnClickedButtonImport)
	ON_BN_CLICKED(IDC_BUTTON_SAVE2, &CBinoxxoBelegDlg::OnBnClickedButtonSave2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE3, &CBinoxxoBelegDlg::OnBnClickedButtonSave3)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT2, &CBinoxxoBelegDlg::OnBnClickedButtonImport2)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT3, &CBinoxxoBelegDlg::OnBnClickedButtonImport3)
END_MESSAGE_MAP()


// CBinoxxoBelegDlg-Meldungshandler

BOOL CBinoxxoBelegDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	// Initialisierung des Spielfeldes

	SetGame(state);

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CBinoxxoBelegDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CBinoxxoBelegDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBinoxxoBelegDlg::OnBnClickedCancel()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	CDialogEx::OnCancel();
}

void CBinoxxoBelegDlg::SetGame(int curstate[100])
{
	//Setzt alle Buttons auf den Ursprungszustand zurück. Reset kann darauf verweisen.
	//Im Moment noch alles auf 0, später könnte man die Zustände aus einer Datei einlesen.
	for (int i = 1001; i < 1101; i++) {
		if (curstate[i - 1001] == 0)
			GetDlgItem(i)->SetWindowText("O");
		//curstate[i - 1001] = 0;		//Array wird auch auf Null gesetzt
		else if (curstate[i - 1001] == 1)
			GetDlgItem(i)->SetWindowText("X");
		else
			GetDlgItem(i)->SetWindowText(" ");
	}
}




void CBinoxxoBelegDlg::OnBnClickedButtonAbout()
{
	// TODO: Fügen Sie hier Ihren Handlercode für Benachrichtigungen des Steuerelements ein.
	MessageBox("Binoxxo Beleg von s82514 SS22", "About", MB_OK);
}


void CBinoxxoBelegDlg::OnGameButton(UINT nID)
{
	undostate = 0;
	GetDlgItem(1105)->EnableWindow(TRUE);

	//Sicherungsarrays für dreistufige Undo-Funktion.
	//Im Moment noch broken
	std::copy(backupstate2, backupstate2 + 100, backupstate3);
	std::copy(backupstate1, backupstate1 + 100, backupstate2);
	std::copy(state, state + 100, backupstate1);

	//Koordiniert die Zuuordnung zwischen state array und den Buttonbeschriftungen. Reagiert auf Knopfdrücke
	if (state[nID - 1001] == 0) {
		GetDlgItem(nID)->SetWindowText("X");
		state[nID - 1001] = 1;
	}
	else if (state[nID - 1001] == 1) {
		GetDlgItem(nID)->SetWindowText(" ");
		state[nID - 1001] = 2;
	}
	else {
		GetDlgItem(nID)->SetWindowText("O");
		state[nID - 1001] = 0;
	}
}



void CBinoxxoBelegDlg::OnBnClickedButtonReset()
{
	//setzt das Spiel auf den Originalzustand zurück
	//To do: actual Originalzustand nehmen
	memset(state, 0, sizeof(state));
	CBinoxxoBelegDlg::SetGame(state);
}


void CBinoxxoBelegDlg::OnBnClickedButtonCheck()
{
	//Zähler für den Check der Reihen und Spalten

	int statecount0 = 0;
	int statecount1 = 0;

	
	//int debug = 0;


	//Alle Spalten durchsuchen

	
	for (int e = 0; e < 100; e = e + 10) {
		for (int i = e; i < e + 10; i++) {
			if (state[i] == 2) {
				MessageBox("Es müssen alle Felder gefüllt sein.", "Fehler", MB_OK);
				goto exit;
			}
			else if (state[i] == 0) {
				statecount0++;
			}
			else if (state[i] == 1) {
				statecount1++;
			}

			//debug = i;
		}

		//debug = e;

		if (statecount0 != statecount1) {

			/*std::stringstream box_message;
			box_message << "Fehler in Spaltendurchsuchung: " << debug << " uwu.";
			MessageBoxA(box_message.str().c_str(), "My Message Box", MB_OK);*/


			MessageBox("Da muss nachgebessert werden smh", "Ergebnis", MB_OK);
			goto exit;
		}
		else {
			statecount0 = 0;
			statecount1 = 0;
		}
	}
	

	//Alle Zeilen durchsuchen

	

	zeilen:
	for (int e = 0; e < 11; e++) {
		for (int i = e; i < 100; i = i+10) {
			if (state[i] == 2) {
				MessageBox("Es müssen alle Felder gefüllt sein.", "Fehler", MB_OK);
				goto exit;
			}
			else if (state[i] == 0) {
				statecount0++;
			}
			else if (state[i] == 1) {
				statecount1++;
			}
			else
				MessageBox("Unerwarteter Fehler.", "Fehler", MB_OK);


			//debug = i;

			}
		if (statecount0 != statecount1) {

			//DEBUGÜBERRESTE

			/*std::stringstream box_message;
			box_message << "Fehler in Zeilendurchsuchung: " << debug << " uwu.";
			MessageBoxA(box_message.str().c_str(), "My Message Box", MB_OK);*/


			MessageBox("Falsche Lösung", "Ergebnis", MB_OK);
			goto exit;
		}

	MessageBox("Gute Arbeit. Die Eingabe ist richtig.", "Ergebnis", MB_OK);
	goto exit;
	}

	exit:
	statecount0 = 0;
	statecount1 = 0;
}


void CBinoxxoBelegDlg::OnBnClickedButtonUndo()
{
	// TODO: Add your control notification handler code here
	if (undostate < 2) {
		if (undostate == 0) {
			undostate++;
			SetGame(backupstate1);
		}
		else if (undostate == 1) {
			undostate++;
			SetGame(backupstate2);
		}
		else {
			undostate++;
			SetGame(backupstate3);
		}
	}
	else
		GetDlgItem(1105)->EnableWindow(FALSE);
}


void CBinoxxoBelegDlg::OnBnClickedButtonSave()
{


	// TODO: Add your control notification handler code here
	const int size = 100;
	
	//::ofstream myfile("%userprofile%\documents\example.txt",ofstream::out);
	std::fstream myfile("saved.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (myfile.is_open())
	{
		for (int count = 0; count < size; count++) {
			myfile << state[count] << std::endl;
		}
		myfile.close();
	}
	else MessageBox("Unable to open file.", "Fehler", MB_OK);
}


void CBinoxxoBelegDlg::OnBnClickedButtonSave2()
{
	// TODO: Add your control notification handler code here
	const int size = 100;

	//::ofstream myfile("%userprofile%\documents\example.txt",ofstream::out);
	std::fstream myfile("saved2.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (myfile.is_open())
	{
		for (int count = 0; count < size; count++) {
			myfile << state[count] << std::endl;
		}
		myfile.close();
	}
	else MessageBox("Unable to open file.", "Fehler", MB_OK);
}


void CBinoxxoBelegDlg::OnBnClickedButtonSave3()
{
	// TODO: Add your control notification handler code here
	const int size = 100;

	//::ofstream myfile("%userprofile%\documents\example.txt",ofstream::out);
	std::fstream myfile("saved3.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
	if (myfile.is_open())
	{
		for (int count = 0; count < size; count++) {
			myfile << state[count] << std::endl;
		}
		myfile.close();
	}
	else MessageBox("Unable to open file.", "Fehler", MB_OK);
}


void CBinoxxoBelegDlg::OnBnClickedButtonImport()
{
	//Opening the file
	std::ifstream inputfile("saved.txt");

	if (!inputfile.is_open())
		MessageBox("Konnte Datei nicht öffnen.", "Fehler", MB_OK);

	int number;
	int a = 0;

	while (inputfile >> number) {
		state[a] = number;
		a++;
	}
	std::cout << std::endl;
	inputfile.close();

	SetGame(state);
}

void CBinoxxoBelegDlg::OnBnClickedButtonImport2()
{
	std::ifstream inputfile("saved2.txt");

	if (!inputfile.is_open())
		MessageBox("Konnte Datei nicht öffnen.", "Fehler", MB_OK);

	int number;
	int a = 0;

	while (inputfile >> number) {
		state[a] = number;
		a++;
	}
	std::cout << std::endl;
	inputfile.close();

	SetGame(state);
}


void CBinoxxoBelegDlg::OnBnClickedButtonImport3()
{
	std::ifstream inputfile("saved3.txt");

	if (!inputfile.is_open())
		MessageBox("Konnte Datei nicht öffnen.", "Fehler", MB_OK);

	int number;
	int a = 0;

	while (inputfile >> number) {
		state[a] = number;
		a++;
	}
	std::cout << std::endl;
	inputfile.close();

	SetGame(state);
}
