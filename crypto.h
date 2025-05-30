//---------------------------------------------------------------------------

#ifndef CryptoH
#define CryptoH

void InitOpenSSL();
void FreeOpenSSL();
AnsiString AESEncryptLine(const AnsiString& plain, const AnsiString& key);
AnsiString AESDecryptLine(const AnsiString& cipher, const AnsiString& key);
//---------------------------------------------------------------------------
#endif
