//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "LoginDialog.h"
//---------------------------------------------------------------------------
USEFORM("DisplayGUI.cpp", Form1);
USEFORM("AreaDialog.cpp", AreaConfirm);
USEFORM("LoginDialog.cpp", LoginDiaglog);
//---------------------------------------------------------------------------
static FILE* pCout = NULL;
static void SetStdOutToNewConsole(void);
//---------------------------------------------------------------------------
static void SetStdOutToNewConsole(void)
{
    // Allocate a console for this app
    AllocConsole();
    //AttachConsole(ATTACH_PARENT_PROCESS);
	freopen_s(&pCout, "CONOUT$", "w", stdout);
}

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
        SetStdOutToNewConsole();
		Application->Initialize();
		Application->MainFormOnTaskBar = true;

        Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TAreaConfirm), &AreaConfirm);
        Application->CreateForm(__classid(TLoginDiaglog), &LoginDiaglog);
        int result = LoginDiaglog->ShowModal();
        if(!LoginDiaglog->IsLoginSuccess()) return 0;

		printf("ADS-B Display Application started\n");
		Application->Run();
	   if (pCout)
		{
		 fclose(pCout);
		 FreeConsole();
	    }
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
