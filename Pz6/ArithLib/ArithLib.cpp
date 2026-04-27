#include <windows.h>
#include <climits>
#include "ArithLib.h"

// контрольна сума

static DWORD CalcCheckSum(PBYTE pMem, DWORD dwSize)
{
    DWORD dwCS = 0;
    DWORD dwFull = dwSize / 4;
    PDWORD p32 = (PDWORD)pMem;

    for (DWORD i = 0; i < dwFull; i++)
        dwCS += p32[i];

    DWORD dwRest = dwSize % 4;
    if (dwRest)
    {
        DWORD dwLast = 0;
        memcpy(&dwLast, pMem + dwFull * 4, dwRest);
        dwCS += dwLast;
    }

    return dwCS;
}

// перевірка контрольної суми DLL при завантаженні

static BOOL VerifyCheckSum(HMODULE hModule)
{
    // шлях до поточного файлу DLL
    char path[MAX_PATH];
    if (!GetModuleFileNameA(hModule, path, MAX_PATH))
        return FALSE;

    HANDLE h = CreateFileA(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (h == INVALID_HANDLE_VALUE)
        return FALSE;

    DWORD dwSize = GetFileSize(h, NULL);
    if (dwSize == INVALID_FILE_SIZE || dwSize < sizeof(DWORD))
    {
        CloseHandle(h);
        return FALSE;
    }

    PBYTE pMem = new BYTE[dwSize];
    DWORD dwRead = 0;
    BOOL  b = ReadFile(h, pMem, dwSize, &dwRead, NULL);
    CloseHandle(h);

    if (!b || dwRead != dwSize)
    {
        delete[] pMem;
        return FALSE;
    }

    DWORD dwStored = *(PDWORD)(pMem + dwSize - sizeof(DWORD));

    DWORD dwCalc = CalcCheckSum(pMem, dwSize - sizeof(DWORD));
    delete[] pMem;

    return dwCalc == dwStored;
}

// головна функція DLL з перевіркою суми
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (!VerifyCheckSum(hModule))
        {
            MessageBoxA(
                NULL,
                "ArithLib.dll: контрольна сума не збігається!\n"
                "Файл пошкоджений або змінений без оновлення суми.",
                "Помилка цілісності",
                MB_OK | MB_ICONERROR
            );
            return FALSE;
        }
    }
    return TRUE;
}

// aрифметичні функції без змін з ПЗ6
ARITHAPI int Add64(int64_t a, int64_t b, int64_t* result)
{
    if (b > 0 && a > INT64_MAX - b) return ARITH_OVERFLOW;
    if (b < 0 && a < INT64_MIN - b) return ARITH_OVERFLOW;
    *result = a + b;
    return ARITH_OK;
}

ARITHAPI int Sub64(int64_t a, int64_t b, int64_t* result)
{
    if (b < 0 && a > INT64_MAX + b) return ARITH_OVERFLOW;
    if (b > 0 && a < INT64_MIN + b) return ARITH_OVERFLOW;
    *result = a - b;
    return ARITH_OK;
}

ARITHAPI int Mul64(int64_t a, int64_t b, int64_t* result)
{
    if (a != 0 && b != 0)
    {
        if (a > 0 && b > 0 && a > INT64_MAX / b) return ARITH_OVERFLOW;
        if (a < 0 && b < 0 && a < INT64_MAX / b) return ARITH_OVERFLOW;
        if (a > 0 && b < 0 && b < INT64_MIN / a) return ARITH_OVERFLOW;
        if (a < 0 && b > 0 && a < INT64_MIN / b) return ARITH_OVERFLOW;
    }
    *result = a * b;
    return ARITH_OK;
}

ARITHAPI int Div64(int64_t a, int64_t b, int64_t* result)
{
    if (b == 0)                    return ARITH_DIV_ZERO;
    if (a == INT64_MIN && b == -1) return ARITH_OVERFLOW;
    *result = a / b;
    return ARITH_OK;
}