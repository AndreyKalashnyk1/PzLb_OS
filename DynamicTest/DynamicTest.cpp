//перевірка бібліотеки ArithLib у динамічному режимі

#include <iostream>
#include <cstdint>
#include <windows.h>

using namespace std;

// коди результату
#define ARITH_OK        0
#define ARITH_OVERFLOW  1
#define ARITH_DIV_ZERO  2

// типи покажчиків на функції бібліотеки
typedef int (*PFN_Add64)(int64_t, int64_t, int64_t*);
typedef int (*PFN_Sub64)(int64_t, int64_t, int64_t*);
typedef int (*PFN_Mul64)(int64_t, int64_t, int64_t*);
typedef int (*PFN_Div64)(int64_t, int64_t, int64_t*);

// функція виводу результату операції
static void printResult(const char* expr, int code, int64_t res)
{
    cout << "  " << expr << " = ";
    if (code == ARITH_OK)       cout << res;
    else if (code == ARITH_OVERFLOW) cout << "OVERFLOW";
    else                             cout << "DIVISION BY ZERO";
    cout << "\n";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "=== Приклад 4: динамічне завантаження ArithLib.dll ===\n\n";

    // завантаження бібліотеки
    HMODULE hLib = LoadLibraryA("ArithLib.dll");
    if (!hLib)
    {
        cerr << "Помилка: неможливо завантажити ArithLib.dll\n"
            << "Переконайтеся, що DLL знаходиться поряд з .exe\n";
        return 1;
    }
    cout << "ArithLib.dll завантажено успішно.\n\n";

    // отримання адресів функцій
    PFN_Add64 fnAdd = (PFN_Add64)GetProcAddress(hLib, "Add64");
    PFN_Sub64 fnSub = (PFN_Sub64)GetProcAddress(hLib, "Sub64");
    PFN_Mul64 fnMul = (PFN_Mul64)GetProcAddress(hLib, "Mul64");
    PFN_Div64 fnDiv = (PFN_Div64)GetProcAddress(hLib, "Div64");

    if (!fnAdd || !fnSub || !fnMul || !fnDiv)
    {
        cerr << "Помилка: не вдалося отримати адреси функцій.\n";
        FreeLibrary(hLib);
        return 1;
    }
    cout << "Адреси всіх функцій отримано успішно.\n\n";

    // виклик функції через покажчики
    int64_t r;
    int     c;

    cout << "Додавання:\n";
    c = fnAdd(100, 200, &r);
    printResult("100 + 200", c, r);

    c = fnAdd(9000000000LL, 1000000000LL, &r);
    printResult("9000000000 + 1000000000", c, r);

    c = fnAdd(INT64_MAX, 1, &r);
    printResult("INT64_MAX + 1", c, r); 

    cout << "\nВіднімання:\n";
    c = fnSub(500, 300, &r);
    printResult("500 - 300", c, r);

    c = fnSub(INT64_MIN, 1, &r);
    printResult("INT64_MIN - 1", c, r); 

    cout << "\nМноження:\n";
    c = fnMul(123456, 789, &r);
    printResult("123456 * 789", c, r);

    c = fnMul(1000000000LL, 1000000000LL, &r);
    printResult("1000000000 * 1000000000", c, r);

    c = fnMul(INT64_MAX, 2, &r);
    printResult("INT64_MAX * 2", c, r); 

    cout << "\nДілення:\n";
    c = fnDiv(100, 4, &r);
    printResult("100 / 4", c, r);

    c = fnDiv(10, 0, &r);
    printResult("10 / 0", c, r);

    c = fnDiv(INT64_MIN, -1, &r);
    printResult("INT64_MIN / -1", c, r);

    // вивантаження бібліотеки
    FreeLibrary(hLib);
    cout << "\nArithLib.dll вивантажено.\n";

    return 0;
}