//---------------------------------------------------------------------------
//
// Name:        TangramApp.cpp
// Author:      Krzysiek
// Created:     2012-12-19 20:39:16
// Description: 
//
//---------------------------------------------------------------------------

#include "TangramApp.h"
#include "TangramDlg.h"

IMPLEMENT_APP(TangramDlgApp)

bool TangramDlgApp::OnInit()
{
	TangramDlg* dialog = new TangramDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
}
 
int TangramDlgApp::OnExit()
{
	return 0;
}
