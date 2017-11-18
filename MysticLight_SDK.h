// MysticLight_Sample.h : header file
//

#pragma once

typedef int (*LPMLAPI_Initialize)();
typedef int (*LPMLAPI_GetErrorMessage)(int ErrorCode, BSTR* pDesc);
typedef int (*LPMLAPI_GetDeviceInfo)(SAFEARRAY** pDevType, SAFEARRAY** pLedCount);
typedef int (*LPMLAPI_GetLedInfo)(BSTR type, DWORD index, BSTR* pName, SAFEARRAY** pLedStyles);
typedef int (*LPMLAPI_GetLedColor)(BSTR type, DWORD index, DWORD* R, DWORD* G, DWORD* B);
typedef int (*LPMLAPI_GetLedStyle)(BSTR type, DWORD index, BSTR* style);
typedef int (*LPMLAPI_GetLedMaxBright)(BSTR type, DWORD index, DWORD* maxLevel);
typedef int (*LPMLAPI_GetLedBright)(BSTR type, DWORD index, DWORD* currentLevel);
typedef int (*LPMLAPI_GetLedMaxSpeed)(BSTR type, DWORD index, DWORD* maxLevel);
typedef int (*LPMLAPI_GetLedSpeed)(BSTR type, DWORD index, DWORD* currentLevel);
typedef int (*LPMLAPI_SetLedColor)(BSTR type, DWORD index, DWORD R, DWORD G, DWORD B);
typedef int (*LPMLAPI_SetLedStyle)(BSTR type, DWORD index, BSTR style);
typedef int (*LPMLAPI_SetLedBright)(BSTR type, DWORD index, DWORD level);
typedef int (*LPMLAPI_SetLedSpeed)(BSTR type, DWORD index, DWORD level);