// Практичне заняття 1

// Бібліотеки

#include <iostream> // – введення та виведення даних
#include <iomanip> // – форматування виведення
#include <cmath> // – математичні функції
#include <windows.h> // - UTF-8 для української мови

using namespace std;


// Завдання 1
// Введення дробового числа та виведення з точністю до двох знаків

void task1()
{
    double number;

    cout << "Enter a real number: ";
    cin >> number;

    if (cin.fail())
    {
        cout << "Input error" << endl;
    }
    else
    {
        cout << "Number with two decimal places: ";
        cout << fixed << setprecision(2) << number << endl;
    }
}


// Завдання 2.1
// Обчислення значення функції

void task2()
{
    double c, z, x, y;

    cout << "Enter c: ";
    cin >> c;

    z = cos(c);

    if (z < 0)
    {
        x = 2 * z + tan(z);
    }
    else if (z <= 8)
    {
        x = log(pow(z, 4)) + 2 * z;
    }
    else
    {
        x = 2 * sin(z * z);
    }

    cout << "z = " << z << endl;
    cout << "x = " << x << endl;

    if (x > 0)
    {
        y = sin(x) + 2 * log(x);
        cout << "y = " << y << endl;
    }
    else
    {
        cout << "y is undefined because ln(x) exists only for x > 0" << endl;
    }
}


// Завдання 2.2
// Словесний опис шкільної оцінки

void task3()
{
    int grade;

    cout << "Enter grade (1-5): ";
    cin >> grade;

    switch (grade)
    {
    case 1:
        cout << "Bad (погано)" << endl;
        break;

    case 2:
        cout << "Unsatisfactory (незадовільно)" << endl;
        break;

    case 3:
        cout << "Satisfactory (задовільно)" << endl;
        break;

    case 4:
        cout << "Good (добре)" << endl;
        break;

    case 5:
        cout << "Excellent (відмінно)" << endl;
        break;

    default:
        cout << "Invalid grade" << endl;
    }
}


// Завдання 3.1
// Пошук мінімального елемента послідовності без використання масиву

void task4()
{
    int n, value, min;

    cout << "Enter number of elements: ";
    cin >> n;

    // цикл for
    cout << "\nUsing for loop\n";

    cout << "Enter element 1: ";
    cin >> value;
    min = value;

    for (int i = 2; i <= n; i++)
    {
        cout << "Enter element " << i << ": ";
        cin >> value;

        if (value < min)
            min = value;
    }

    cout << "Minimum element = " << min << endl;


    // цикл while
    cout << "\nUsing while loop\n";

    int i = 1;

    cout << "Enter element 1: ";
    cin >> value;
    min = value;

    i = 2;

    while (i <= n)
    {
        cout << "Enter element " << i << ": ";
        cin >> value;

        if (value < min)
            min = value;

        i++;
    }

    cout << "Minimum element = " << min << endl;


    // цикл do while
    cout << "\nUsing do while loop\n";

    i = 1;

    do
    {
        cout << "Enter element " << i << ": ";
        cin >> value;

        if (i == 1)
            min = value;
        else if (value < min)
            min = value;

        i++;

    } while (i <= n);

    cout << "Minimum element = " << min << endl;
}


// Завдання 3.2
// Табулювання функції на інтервалі

void task5()
{
    double a, b, h;
    double x, y;

    cout << "Enter start of interval (a): ";
    cin >> a;

    cout << "Enter end of interval (b): ";
    cin >> b;

    cout << "Enter step (h): ";
    cin >> h;

    cout << "\n x\tF(x)" << endl;
    cout << "----------------" << endl;

    for (x = a; x <= b; x += h)
    {
        y = sin(x) - cos(x);
        cout << x << "\t" << y << endl;
    }
}


// Головна функція

//int main()
//{
//	// Налаштування консолі для української мови
//
//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
//
//    // Виклик поточного завдання
//
//    // task1();
//    //task2();
//	// task3();
//	// task4();
//	task5();
//
//    return 0;
//}