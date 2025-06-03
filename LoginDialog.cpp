//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LoginDialog.h"
#include <fstream>
#include <sstream>
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
    AnsiString inputID = EditID->Text;
    AnsiString inputPassword = EditPassword->Text;

    std::ifstream ifs("user.csv");
    bool found = false;
    if (ifs.is_open()) {
        std::string line;
        while (std::getline(ifs, line)) {
            std::istringstream iss(line);
            std::string id, hash, salt;
            if (std::getline(iss, id, ',') &&
                std::getline(iss, hash, ',') &&
                std::getline(iss, salt)) {

                if (id == inputID.c_str()) {
                    found = true;

                    // Convert salt hex string to bytes
                    unsigned char salt_bytes[16];
                    for (int i = 0; i < 16; ++i) {
                        std::string byteStr = salt.substr(i * 2, 2);
                        salt_bytes[i] = (unsigned char)strtol(byteStr.c_str(), nullptr, 16);
                    }

                    // Load PBKDF2 function from DLL
                    HINSTANCE hCrypto = LoadLibraryA("libcrypto-3-x64.dll");
                    if (!hCrypto) {
                        ShowMessage("libcrypto DLL not found!");
                        loginSuccess = false;
                        return;
                    }
                    typedef int (*PKCS5_PBKDF2_HMAC_t)(
                        const char *pass, int passlen,
                        const unsigned char *salt, int saltlen,
                        int iter,
                        const void *digest,
                        int keylen, unsigned char *out
                    );
                    typedef const void* (*EVP_sha256_t)(void);

                    PKCS5_PBKDF2_HMAC_t pPKCS5_PBKDF2_HMAC = (PKCS5_PBKDF2_HMAC_t)GetProcAddress(hCrypto, "PKCS5_PBKDF2_HMAC");
                    EVP_sha256_t pEVP_sha256 = (EVP_sha256_t)GetProcAddress(hCrypto, "EVP_sha256");

                    if (!pPKCS5_PBKDF2_HMAC || !pEVP_sha256) {
                        ShowMessage("PBKDF2 or EVP_sha256 not found!");
                        FreeLibrary(hCrypto);
                        loginSuccess = false;
                        return;
                    }

                    int iterations = 10000;
                    unsigned char key[32];
                    int keylen = 32;

                    int ok = pPKCS5_PBKDF2_HMAC(
                        inputPassword.c_str(), inputPassword.Length(),
                        salt_bytes, sizeof(salt_bytes),
                        iterations,
                        pEVP_sha256(),
                        keylen, key
                    );

                    FreeLibrary(hCrypto);

                    if (ok != 1) {
                        ShowMessage("PBKDF2 failed!");
                        loginSuccess = false;
                        return;
                    }

                    // Convert key to hex string
                    char hash_hex[32 * 2 + 1] = {0};
                    for (int i = 0; i < 32; ++i)
                        sprintf_s(&hash_hex[i * 2], sizeof(hash_hex) - (i * 2), "%02x", key[i]);

                    if (hash == hash_hex) {
                        loginSuccess = true;
                        printf("Login successful\n");
                        Close();
                        return;
                    } else {
                        ShowMessage("Login failed!");
                        EditPassword->Text = ""; // Clear password field on failure
                        loginSuccess = false;
                        return;
                    }
                }
            }
        }
        ifs.close();
    }

    ShowMessage("Login failed!");
    EditPassword->Text = ""; // Clear password field on failure
    loginSuccess = false;
}

//---------------------------------------------------------------------------

void __fastcall TLoginDiaglog::ButtonCancelClick(TObject *Sender)
{
    loginSuccess = false;
    printf("Login cancelled\n");
    Close();
}
//---------------------------------------------------------------------------

