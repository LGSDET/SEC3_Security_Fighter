//---------------------------------------------------------------------------

#ifndef LoginDialogH
#define LoginDialogH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TLoginDiaglog : public TForm
{
__published:
    TLabel *Label1;
    TLabel *Label2;
    TEdit *EditID;
    TEdit *EditPassword;
    TButton *ButtonLogin;
	TButton *ButtonCancel;
    void __fastcall ButtonLoginClick(TObject *Sender);
private:
    bool loginSuccess;
public:
    __fastcall TLoginDiaglog(TComponent* Owner);
    bool IsLoginSuccess() const { return loginSuccess; }
};
//---------------------------------------------------------------------------
extern PACKAGE TLoginDiaglog *LoginDiaglog;
//---------------------------------------------------------------------------
#endif
