
// Binoxxo_Beleg.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CBinoxxoBelegApp:
// Siehe Binoxxo_Beleg.cpp für die Implementierung dieser Klasse
//

class CBinoxxoBelegApp : public CWinApp
{
public:
	CBinoxxoBelegApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CBinoxxoBelegApp theApp;
