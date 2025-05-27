//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LoginDialog.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoginDiaglog *LoginDiaglog;
//---------------------------------------------------------------------------
__fastcall TLoginDiaglog::TLoginDiaglog(TComponent* Owner)
	: TForm(Owner)
{
    loginSuccess = false;
}

void __fastcall TLoginDiaglog::ButtonLoginClick(TObject *Sender)
{
    if(EditID->Text == "admin" && EditPassword->Text == "1234") {
        loginSuccess = true;
        printf("Login successful\n");
        Close();
    } else {
        ShowMessage("Login failed!");
        loginSuccess = false;
    }
}
//---------------------------------------------------------------------------
