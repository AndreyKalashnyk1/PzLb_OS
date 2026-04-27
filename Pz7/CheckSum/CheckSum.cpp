#include <windows.h>
#include <iostream>

using namespace std;

// обчислення контрольної суми блоку пам'яті
DWORD CalcCheckSum(PBYTE pMem, DWORD dwSize)
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

// зчитує вміст DLL, обчислює контрольну суму і дописує 4 байти в кінець файлу
bool WriteCheckSum(const char* path)
{
    // відкриття файлу для читання і запису
    HANDLE h = CreateFileA(
        path,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (h == INVALID_HANDLE_VALUE)
    {
        cerr << "Помилка: не вдалося відкрити файл: " << path << "\n";
        return false;
    }

    // отримання розміру файлу
    DWORD dwSize = GetFileSize(h, NULL);
    if (dwSize == INVALID_FILE_SIZE)
    {
        cerr << "Помилка: не вдалося отримати розмір файлу.\n";
        CloseHandle(h);
        return false;
    }

    // читання всього файлу у пам'ять
    PBYTE pMem = new BYTE[dwSize];
    DWORD dwRead = 0;
    BOOL  b = ReadFile(h, pMem, dwSize, &dwRead, NULL);

    if (!b || dwRead != dwSize)
    {
        cerr << "Помилка: не вдалося прочитати файл.\n";
        delete[] pMem;
        CloseHandle(h);
        return false;
    }

    // обчислення контрольної суми
    DWORD dwCS = CalcCheckSum(pMem, dwSize);
    delete[] pMem;

    // допис суми в кінець файлу
    SetFilePointer(h, 0, NULL, FILE_END);
    DWORD dwWritten = 0;
    b = WriteFile(h, &dwCS, sizeof(dwCS), &dwWritten, NULL);

    CloseHandle(h);

    if (!b)
    {
        cerr << "Помилка: не вдалося записати контрольну суму.\n";
        return false;
    }

    cout << "Checksum 0x" << hex << uppercase << dwCS
        << " written to: " << path << "\n";
    return true;
}

int main(int argc, char* argv[])
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    if (argc < 2)
    {
        cerr << "Використання: CheckSum.exe <шлях до DLL>\n";
        return 1;
    }

    return WriteCheckSum(argv[1]) ? 0 : 1;
}
