// перевірка у статичному режимі


#include <iostream>
#include <cstdint>
#include "ArithLib.h"
#include <windows.h>

using namespace std;


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
    
    cout << "=== Приклад 3: статичне завантаження ArithLib.dll ===\n\n";

    int64_t r;
    int     c;

    cout << "Додавання:\n";
    c = Add64(100, 200, &r);
    printResult("100 + 200", c, r);

    c = Add64(9000000000LL, 1000000000LL, &r);
    printResult("9000000000 + 1000000000", c, r);

    c = Add64(INT64_MAX, 1, &r);
    printResult("INT64_MAX + 1", c, r);                      

    cout << "\nВіднімання:\n";
    c = Sub64(500, 300, &r);
    printResult("500 - 300", c, r);

    c = Sub64(INT64_MIN, 1, &r);
    printResult("INT64_MIN - 1", c, r);                      

    cout << "\nМноження:\n";
    c = Mul64(123456, 789, &r);
    printResult("123456 * 789", c, r);                       

    c = Mul64(1000000000LL, 1000000000LL, &r);
    printResult("1000000000 * 1000000000", c, r);             

    c = Mul64(INT64_MAX, 2, &r);
    printResult("INT64_MAX * 2", c, r);                      

    cout << "\nДілення:\n";
    c = Div64(100, 4, &r);
    printResult("100 / 4", c, r);                            

    c = Div64(10, 0, &r);
    printResult("10 / 0", c, r);                             

    c = Div64(INT64_MIN, -1, &r);
    printResult("INT64_MIN / -1", c, r);                     

    return 0;
}