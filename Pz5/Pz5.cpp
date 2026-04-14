#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include <cstring>
#include <cwchar>
#include <algorithm>

using namespace std;


// Завдання 1 порівняння двох каталогів (регістронезалежно, з урахуванням можливого '\' в кінці)


void stripTrailingSlash(TCHAR* path)
{
    size_t len = _tcslen(path);
    if (len > 0 && path[len - 1] == _T('\\'))
        path[len - 1] = _T('\0');
}

BOOL CompareDirectories(const TCHAR* dir1, const TCHAR* dir2)
{
    TCHAR buf1[MAX_PATH];
    TCHAR buf2[MAX_PATH];

    _tcscpy(buf1, dir1);
    _tcscpy(buf2, dir2);

    stripTrailingSlash(buf1);
    stripTrailingSlash(buf2);

    return _tcsicmp(buf1, buf2) == 0;
}

void task1()
{
    wprintf(L"=== Завдання 1: Порівняння каталогів ===\n\n");

    const wchar_t* tests[3][2] = {
        { L"C:\\Temp\\MyFolder\\", L"C:\\TEMP\\myfolder"  },
        { L"C:\\Temp\\FolderA",   L"C:\\Temp\\FolderB\\" },
        { L"D:\\Projects",        L"D:\\PROJECTS"         },
    };

    for (int i = 0; i < 3; i++)
    {
        BOOL res = CompareDirectories(tests[i][0], tests[i][1]);
        wprintf(L"  dir1: %ls\n  dir2: %ls\n  Результат: %ls\n\n",
            tests[i][0],
            tests[i][1],
            res ? L"рівні" : L"різні");
    }
}


// Завдання 2 сортування рядків (тип кодування відомий)


void sortAsciiStrings(char** arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (strcmp(arr[j], arr[minIdx]) < 0)
                minIdx = j;
        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
    }
}

void sortUnicodeStrings(wchar_t** arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (wcscmp(arr[j], arr[minIdx]) < 0)
                minIdx = j;
        if (minIdx != i)
            swap(arr[i], arr[minIdx]);
    }
}

void task2()
{
    wprintf(L"=== Завдання 2: Сортування рядків (відоме кодування) ===\n\n");

    const int N = 5;

    char* asciiArr[N] = {
        (char*)"Warsaw", (char*)"Berlin",  (char*)"Vienna",
        (char*)"Prague", (char*)"Krakow"
    };

    wprintf(L"  ASCII до сортування:    ");
    for (int i = 0; i < N; i++) wprintf(L"%S ", asciiArr[i]);
    wprintf(L"\n");

    sortAsciiStrings(asciiArr, N);

    wprintf(L"  ASCII після сортування: ");
    for (int i = 0; i < N; i++) wprintf(L"%S ", asciiArr[i]);
    wprintf(L"\n\n");

    wchar_t* uniArr[N] = {
        (wchar_t*)L"Tokyo",  (wchar_t*)L"London", (wchar_t*)L"Athens",
        (wchar_t*)L"Dublin", (wchar_t*)L"Lisbon"
    };

    wprintf(L"  Unicode до сортування:    ");
    for (int i = 0; i < N; i++) wprintf(L"%ls ", uniArr[i]);
    wprintf(L"\n");

    sortUnicodeStrings(uniArr, N);

    wprintf(L"  Unicode після сортування: ");
    for (int i = 0; i < N; i++) wprintf(L"%ls ", uniArr[i]);
    wprintf(L"\n\n");
}


// Завдання 3 сортування рядків (тип кодування невідомий)


wchar_t* toUnicode(const char* str, int len)
{
    wchar_t* buf = new wchar_t[len + 1];
    MultiByteToWideChar(CP_ACP, 0, str, len + 1, buf, len + 1);
    return buf;
}

int compareUnknown(PVOID p1, size_t n1, PVOID p2, size_t n2)
{
    int fl1 = -1, fl2 = -1;
    BOOL b1 = IsTextUnicode(p1, (int)n1, &fl1);
    BOOL b2 = IsTextUnicode(p2, (int)n2, &fl2);

    wchar_t* w1 = b1 ? (wchar_t*)p1 : toUnicode((char*)p1, (int)n1 - 1);
    wchar_t* w2 = b2 ? (wchar_t*)p2 : toUnicode((char*)p2, (int)n2 - 1);

    int res = wcscmp(w1, w2);

    if (!b1) delete[] w1;
    if (!b2) delete[] w2;

    return res;
}

void task3()
{
    wprintf(L"=== Завдання 3: Сортування рядків (невідоме кодування) ===\n\n");

    const int COUNT = 5;
    PVOID arr[COUNT] = {
        (PVOID)"Madrid",
        (PVOID)L"Paris",
        (PVOID)"Ankara",
        (PVOID)L"Kyiv",
        (PVOID)"Rome"
    };
    size_t sizes[COUNT] = {
        sizeof("Madrid"),
        sizeof(L"Paris"),
        sizeof("Ankara"),
        sizeof(L"Kyiv"),
        sizeof("Rome")
    };

    PVOID  origArr[COUNT];
    size_t origSizes[COUNT];
    for (int i = 0; i < COUNT; i++) { origArr[i] = arr[i]; origSizes[i] = sizes[i]; }

    wprintf(L"  Вхідні дані (змішане кодування):\n");
    for (int i = 0; i < COUNT; i++)
    {
        int fl = -1;
        BOOL isUni = IsTextUnicode(origArr[i], (int)origSizes[i], &fl);
        if (isUni)
            wprintf(L"  [%d] %ls  (Unicode)\n", i + 1, (wchar_t*)origArr[i]);
        else
            wprintf(L"  [%d] %S  (ASCII)\n", i + 1, (char*)origArr[i]);
    }
    wprintf(L"\n");

    for (int i = 0; i < COUNT - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < COUNT; j++)
            if (compareUnknown(arr[j], sizes[j], arr[minIdx], sizes[minIdx]) < 0)
                minIdx = j;

        if (minIdx != i)
        {
            swap(arr[i], arr[minIdx]);
            swap(sizes[i], sizes[minIdx]);
        }
    }

    wprintf(L"  Результат після сортування:\n");
    for (int i = 0; i < COUNT; i++)
    {
        int fl = -1;
        BOOL isUni = IsTextUnicode(arr[i], (int)sizes[i], &fl);
        if (isUni)
            wprintf(L"  [%d] %ls\n", i + 1, (wchar_t*)arr[i]);
        else
            wprintf(L"  [%d] %S\n", i + 1, (char*)arr[i]);
    }
    wprintf(L"\n");
}


// головна функція

int _tmain(int argc, TCHAR* argv[])
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    task1();
    task2();
    task3();

    return 0;
}
