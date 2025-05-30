//---------------------------------------------------------------------------

#pragma hdrstop
#include <windows.h>
#include "crypto.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// OpenSSL EVP 함수 포인터 타입 선언
typedef struct evp_cipher_st EVP_CIPHER;
typedef struct evp_cipher_ctx_st EVP_CIPHER_CTX;

typedef EVP_CIPHER_CTX* (__cdecl *EVP_CIPHER_CTX_new_Func)(void);
typedef void (__cdecl *EVP_CIPHER_CTX_free_Func)(EVP_CIPHER_CTX*);
typedef const EVP_CIPHER* (__cdecl *EVP_aes_128_cbc_Func)(void);
typedef int (__cdecl *EVP_EncryptInit_ex_Func)(EVP_CIPHER_CTX*, const EVP_CIPHER*, void*, const unsigned char*, const unsigned char*);
typedef int (__cdecl *EVP_EncryptUpdate_Func)(EVP_CIPHER_CTX*, unsigned char*, int*, const unsigned char*, int);
typedef int (__cdecl *EVP_EncryptFinal_ex_Func)(EVP_CIPHER_CTX*, unsigned char*, int*);
typedef int (__cdecl *EVP_EncodeBlock_Func)(unsigned char *out, const unsigned char *in, int inlen);
typedef int (__cdecl *RAND_bytes_Func)(unsigned char *buf, int num);

typedef int (__cdecl *EVP_DecodeBlock_Func)(unsigned char *out, const unsigned char *in, int inlen);
typedef int (__cdecl *EVP_DecryptInit_ex_Func)(EVP_CIPHER_CTX*, const EVP_CIPHER*, void*, const unsigned char*, const unsigned char*);
typedef int (__cdecl *EVP_DecryptUpdate_Func)(EVP_CIPHER_CTX*, unsigned char*, int*, const unsigned char*, int);
typedef int (__cdecl *EVP_DecryptFinal_ex_Func)(EVP_CIPHER_CTX*, unsigned char*, int*);


HMODULE hOpenSSL = NULL;
RAND_bytes_Func pRAND_bytes = NULL;
EVP_CIPHER_CTX_new_Func pEVP_CIPHER_CTX_new = NULL;
EVP_CIPHER_CTX_free_Func pEVP_CIPHER_CTX_free = NULL;
EVP_aes_128_cbc_Func pEVP_aes_128_cbc = NULL;
EVP_EncryptInit_ex_Func pEVP_EncryptInit_ex = NULL;
EVP_EncryptUpdate_Func pEVP_EncryptUpdate = NULL;
EVP_EncryptFinal_ex_Func pEVP_EncryptFinal_ex = NULL;
EVP_EncodeBlock_Func pEVP_EncodeBlock = NULL;
EVP_DecodeBlock_Func pEVP_DecodeBlock = NULL;
EVP_DecryptInit_ex_Func pEVP_DecryptInit_ex = NULL;
EVP_DecryptUpdate_Func pEVP_DecryptUpdate = NULL;
EVP_DecryptFinal_ex_Func pEVP_DecryptFinal_ex = NULL;

void InitOpenSSL()
{
    hOpenSSL = LoadLibraryA("libcrypto-3-x64.dll"); // 또는 libcrypto-1_1-x64.dll 등 환경에 맞게
    if (!hOpenSSL) {
        ShowMessage("OpenSSL DLL load failed");
        return;
    }
    pEVP_CIPHER_CTX_new = (EVP_CIPHER_CTX_new_Func)GetProcAddress(hOpenSSL, "EVP_CIPHER_CTX_new");
    pEVP_CIPHER_CTX_free = (EVP_CIPHER_CTX_free_Func)GetProcAddress(hOpenSSL, "EVP_CIPHER_CTX_free");
    pEVP_aes_128_cbc = (EVP_aes_128_cbc_Func)GetProcAddress(hOpenSSL, "EVP_aes_128_cbc");
    pEVP_EncryptInit_ex = (EVP_EncryptInit_ex_Func)GetProcAddress(hOpenSSL, "EVP_EncryptInit_ex");
    pEVP_EncryptUpdate = (EVP_EncryptUpdate_Func)GetProcAddress(hOpenSSL, "EVP_EncryptUpdate");
    pEVP_EncryptFinal_ex = (EVP_EncryptFinal_ex_Func)GetProcAddress(hOpenSSL, "EVP_EncryptFinal_ex");
    pEVP_EncodeBlock = (EVP_EncodeBlock_Func)GetProcAddress(hOpenSSL, "EVP_EncodeBlock");
    pEVP_DecodeBlock = (EVP_DecodeBlock_Func)GetProcAddress(hOpenSSL, "EVP_DecodeBlock");
    pEVP_DecryptInit_ex = (EVP_DecryptInit_ex_Func)GetProcAddress(hOpenSSL, "EVP_DecryptInit_ex");
    pEVP_DecryptUpdate = (EVP_DecryptUpdate_Func)GetProcAddress(hOpenSSL, "EVP_DecryptUpdate");
    pEVP_DecryptFinal_ex = (EVP_DecryptFinal_ex_Func)GetProcAddress(hOpenSSL, "EVP_DecryptFinal_ex");
    pRAND_bytes = (RAND_bytes_Func)GetProcAddress(hOpenSSL, "RAND_bytes");
    if (!pEVP_CIPHER_CTX_new || !pEVP_CIPHER_CTX_free || !pEVP_aes_128_cbc ||
        !pEVP_EncryptInit_ex || !pEVP_EncryptUpdate || !pEVP_EncryptFinal_ex ||
        !pEVP_EncodeBlock || !pEVP_DecodeBlock ||
        !pEVP_DecryptInit_ex || !pEVP_DecryptUpdate || !pEVP_DecryptFinal_ex ||
        !pRAND_bytes) {
        ShowMessage("OpenSSL 함수 load failed");
        FreeLibrary(hOpenSSL);
        hOpenSSL = NULL;
    }
}

void FreeOpenSSL()
{
    if (hOpenSSL) {
        FreeLibrary(hOpenSSL);
        hOpenSSL = NULL;
    }
}


AnsiString AESEncryptLine(const AnsiString& plain, const AnsiString& key)
{
    // 16바이트 IV 생성
    unsigned char iv[16];
    pRAND_bytes(iv, sizeof(iv));

    EVP_CIPHER_CTX *ctx = pEVP_CIPHER_CTX_new();
    int outlen1 =0, outlen2 =0;
    int plainLen = plain.Length();
    unsigned char outbuf[1024] = {0};

    // 키는 16바이트로 맞춰야 함
    unsigned char keybuf[16] = {0};
    strncpy((char*)keybuf, key.c_str(), 16);
    printf("AES plain: (%d)%s\n", plainLen, plain.c_str());

    pEVP_EncryptInit_ex(ctx, pEVP_aes_128_cbc(), NULL, keybuf, iv);
    pEVP_EncryptUpdate(ctx, outbuf, &outlen1, (unsigned char*)plain.c_str(), plainLen);
    printf("AESEncryptLine: outlen1=%d, outlen2=%d\n", outlen1, outlen2);
    pEVP_EncryptFinal_ex(ctx, outbuf + outlen1, &outlen2);

    printf("AESEncryptLine: outlen1=%d, outlen2=%d\n", outlen1, outlen2);

    pEVP_CIPHER_CTX_free(ctx);

    // IV + 암호문을 Base64로 인코딩해서 반환
    AnsiString result;
    unsigned char combined[16 + outlen1 + outlen2];
    memcpy(combined, iv, 16);
    memcpy(combined + 16, outbuf, outlen1 + outlen2);

    int b64len = 4 * ((16 + outlen1 + outlen2 + 2) / 3);
    char* b64 = new char[b64len + 1];
    pEVP_EncodeBlock((unsigned char*)b64, combined, 16 + outlen1 + outlen2);
    result = b64;
    delete[] b64;
    return result;
}

AnsiString AESDecryptLine(const AnsiString& cipher, const AnsiString& key)
{
    // Base64 디코딩
    int cipherLen = cipher.Length();
    unsigned char* combined = new unsigned char[cipherLen];
    int decodedLen = pEVP_DecodeBlock(combined, (const unsigned char*)cipher.c_str(), cipherLen);

    if (decodedLen < 16) {
        delete[] combined;
        return "";
    }

    unsigned char iv[16];
    memcpy(iv, combined, 16);

    EVP_CIPHER_CTX *ctx = pEVP_CIPHER_CTX_new();
    int outlen1=0, outlen2=0;
    unsigned char outbuf[1024] = {0};

    unsigned char keybuf[16] = {0};
    strncpy((char*)keybuf, key.c_str(), 16);

    pEVP_DecryptInit_ex(ctx, pEVP_aes_128_cbc(), NULL, keybuf, iv);
    pEVP_DecryptUpdate(ctx, outbuf, &outlen1, combined + 16, decodedLen - 16);
    printf("AESDecryptLine: outlen1=%d, outlen2=%d\n", outlen1, outlen2);
    pEVP_DecryptFinal_ex(ctx, outbuf + outlen1, &outlen2);
    printf("AESDecryptLine: outlen1=%d, outlen2=%d\n", outlen1, outlen2);

    pEVP_CIPHER_CTX_free(ctx);
    //printf("AESDecryptLine: outlen1=%d, outlen2=%d\n", outlen1, outlen2);
    AnsiString result((char*)outbuf, outlen1 + outlen2);
    delete[] combined;
    return result;
}
