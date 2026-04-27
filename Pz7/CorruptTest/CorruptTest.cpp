#include <windows.h>
#include <iostream>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    // відкриття DLL і зміна одного байту
    HANDLE h = CreateFileA(
        "E:\\Пзшки\\Pz\\x64\\Debug\\ArithLib.dll",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ, NULL,
        OPEN_EXISTING, 0, NULL
    );

    if (h == INVALID_HANDLE_VALUE)
    {
        cout << "Не вдалося відкрити файл\n";
        return 1;
    }

    // перехід на байт 100 і його звміна
    SetFilePointer(h, 100, NULL, FILE_BEGIN);
    BYTE b = 0xFF;
    DWORD dw;
    WriteFile(h, &b, 1, &dw, NULL);
    CloseHandle(h);

    cout << "DLL пошкоджена\n";
    return 0;
}