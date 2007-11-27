#ifndef EXECRYPTOR_H
#define EXECRYPTOR_H

#include <windows.h>

// EXECryptor API v. 2.3

#define USE_API
//#define USE_CRYPT_REG
//#define USE_STD_SERIALS

#ifdef __cplusplus
extern "C" {
#endif

#ifdef USE_API
__declspec(dllexport) bool __stdcall EXECryptor_IsAppProtected();
__declspec(dllexport) const char * __stdcall EXECryptor_GetEXECryptorVersion();
void GetReleaseDate(int *Day, int *Month, int *Year);
void SafeGetDate(int *Day, int *Month, int *Year);
__declspec(dllexport) DWORD __stdcall EXECryptor_GetHardwareID();

__declspec(dllexport) void __stdcall EXECryptor_EncryptStr(const char *Src, char *Dst);
__declspec(dllexport) void __stdcall EXECryptor_DecryptStr(const char *Src, char *Dst);
__declspec(dllexport) void __stdcall EXECryptor_EncryptStrW(const wchar_t *Src, wchar_t *Dst);
__declspec(dllexport) void __stdcall EXECryptor_DecryptStrW(const wchar_t *Src, wchar_t *Dst);

__declspec(dllexport) bool __stdcall EXECryptor_SecureWrite(const char *Name, const char *Value);
__declspec(dllexport) bool __stdcall EXECryptor_SecureRead(const char *Name, char *Value);
__declspec(dllexport) bool __stdcall EXECryptor_SecureWriteW(const wchar_t *Name, const wchar_t *Value);
__declspec(dllexport) bool __stdcall EXECryptor_SecureReadW(const wchar_t *Name, wchar_t *Value);

__declspec(dllexport) int __stdcall EXECryptor_GetTrialDaysLeft(int TrialPeriod);
__declspec(dllexport) int __stdcall EXECryptor_GetTrialRunsLeft(int TrialRuns);

__declspec(dllexport) int __stdcall EXECryptor_MessageBoxA(HWND hWnd, LPCSTR lpText,
  LPCSTR lpCaption, UINT uType);
__declspec(dllexport) FARPROC __stdcall EXECryptor_GetProcAddr(HMODULE hModule, LPCSTR lpProcName);

__declspec(dllexport) void __stdcall EXECryptor_AntiDebug();
__declspec(dllexport) void __stdcall EXECryptor_ProtectImport();
#endif

#ifdef USE_CRYPT_REG

enum TVerifyResult { vrInvalid, vrExpired, vrStolen, vrOK };

#ifdef USE_STD_SERIALS

#pragma pack(push,1)
typedef struct {
  int LicType;    //0..15
  // if LicType = 1 then we get ExpiryMonth/ExpiryYear
  // otherwise we get UserParam
  int UserParam;  //0..1023
  int ExpiryMonth,//1..12
      ExpiryYear; //2004..2024
  bool F1,F2,F3,F4,F5,F6;
} TSerialNumberInfo;
#pragma pack(pop)

__declspec(dllexport) TVerifyResult __stdcall EXECryptor_VerifySerialNumber(const char *RegName,
  const char *SerialNumber, TSerialNumberInfo *SNInfo = NULL, const char *HardwareID = NULL);

__declspec(dllexport) TVerifyResult __stdcall EXECryptor_VerifySerialNumberW(const wchar_t *RegistrationName,
  const wchar_t *SerialNumber, TSerialNumberInfo *SNInfo = NULL, const wchar_t *HardwareID = NULL);

__declspec(dllexport) TVerifyResult __stdcall EXECryptor_DecodeSerialNumber(const char *RegistrationName,
  const char *SerialNumber, TSerialNumberInfo *SNInfo = NULL, const char *HardwareID = NULL);

__declspec(dllexport) TVerifyResult __stdcall EXECryptor_DecodeSerialNumberW(const wchar_t *RegistrationName,
  const wchar_t *SerialNumber, TSerialNumberInfo *SNInfo = NULL, const wchar_t *HardwareID = NULL);

#else

__declspec(dllexport) void __stdcall EXECryptor_SetCodeKey(const void *Key, int Size);

#endif

__declspec(dllexport) TVerifyResult __stdcall EXECryptor_IsRegistered();

__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_0();
__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_1();
__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_2();
__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_3();
__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_4();
__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_5();
__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_6();
__declspec(dllexport) DWORD __stdcall EXECryptor_RegConst_7();
#endif 

#ifdef __cplusplus
};
#endif

#define CRYPT_START  { \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0F8h; \
        {

#define CRYPT_START_UNSAFE   \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0F8h

#define CRYPT_END  } \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0FFh; \
	}

#define CRYPT_END_UNSAFE    \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0FFh 

#ifdef USE_CRYPT_REG

#define CRYPT_REG  { \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0F9h; \
        {

#define CRYPT_REG_UNSAFE   \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0F9h

#define CRYPT_UNREG  { \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0FAh; \
        {

#define CRYPT_UNREG_UNSAFE   \
	__asm _emit 0EBh \
	__asm _emit 006h \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0EBh \
	__asm _emit 0FCh \
	__asm _emit 0FFh \
	__asm _emit 0FAh

#endif

#endif
