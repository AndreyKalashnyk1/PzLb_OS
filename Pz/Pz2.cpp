// Практичне заняття 2

// Бібліотеки

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_N = 20;


// Виведення масиву

void printArray(const int* a, int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}


// Заповнення масиву випадковими числами

void fillRandomArray(int* a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand() % 101 - 50;
}


// Видалення всіх елементів з парними індексами

int deleteEvenIndexElements(int* a, int n)
{
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        if (i % 2 != 0)
        {
            a[k] = a[i];
            k++;
        }
    }

    return k;
}


// Додавання K елементів у кінець масиву

int addElementsToEnd(int* a, int n, int k)
{
    int freePlaces = MAX_SIZE - n;

    if (k > freePlaces)
    {
        cout << "Only " << freePlaces << " elements can be added." << endl;
        k = freePlaces;
    }

    cout << "Enter " << k << " elements: ";

    for (int i = 0; i < k; i++)
    {
        cin >> a[n];
        n++;
    }

    return n;
}


// Перестановка мінімального і максимального елементів

void swapMinMax(int* a, int n)
{
    if (n <= 1)
        return;

    int minIndex = 0;
    int maxIndex = 0;

    for (int i = 1; i < n; i++)
    {
        if (a[i] < a[minIndex])
            minIndex = i;

        if (a[i] > a[maxIndex])
            maxIndex = i;
    }

    int temp = a[minIndex];
    a[minIndex] = a[maxIndex];
    a[maxIndex] = temp;
}


// Лінійний пошук першого від'ємного елемента

int findFirstNegativeLinear(const int* a, int n, int& comparisons)
{
    comparisons = 0;

    for (int i = 0; i < n; i++)
    {
        comparisons++;

        if (a[i] < 0)
            return i;
    }

    return -1;
}


// Сортування масиву методом вставок

void insertionSort(int* a, int n)
{
    for (int i = 1; i < n; i++)
    {
        int x = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > x)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = x;
    }
}


// Пошук першого від'ємного елемента у відсортованому масиві
// (після сортування за зростанням він знаходиться на позиції 0)

int findFirstNegativeSorted(const int* a, int n, int& comparisons)
{
    comparisons = 0;

    if (n == 0)
        return -1;

    comparisons++;

    if (a[0] < 0)
        return 0;

    return -1;
}


// Завдання 2.1

void task21()
{
    srand((unsigned)time(0));

    int a[MAX_SIZE];
    int n;
    int k;

    cout << "Enter size of array (1-" << MAX_SIZE << "): ";
    cin >> n;

    if (cin.fail() || n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid array size" << endl;
        return;
    }

    fillRandomArray(a, n);

    cout << "Initial array: ";
    printArray(a, n);

    n = deleteEvenIndexElements(a, n);

    cout << "Array after deleting elements with even indices: ";
    printArray(a, n);

    cout << "Enter number of elements to add: ";
    cin >> k;

    if (cin.fail() || k < 0)
    {
        cout << "Invalid number of elements" << endl;
        return;
    }

    n = addElementsToEnd(a, n, k);

    cout << "Array after adding elements to the end: ";
    printArray(a, n);

    swapMinMax(a, n);

    cout << "Array after swapping minimum and maximum: ";
    printArray(a, n);

    int comparisonsLinear;
    int indexLinear = findFirstNegativeLinear(a, n, comparisonsLinear);

    if (indexLinear != -1)
    {
        cout << "First negative (linear): a[" << indexLinear << "] = "
            << a[indexLinear] << ", comparisons = " << comparisonsLinear << endl;
    }
    else
    {
        cout << "No negative elements. Comparisons = " << comparisonsLinear << endl;
    }

    insertionSort(a, n);

    cout << "Sorted array: ";
    printArray(a, n);

    int comparisonsSorted;
    int indexSorted = findFirstNegativeSorted(a, n, comparisonsSorted);

    if (indexSorted != -1)
    {
        cout << "First negative (sorted): a[" << indexSorted << "] = "
            << a[indexSorted] << ", comparisons = " << comparisonsSorted << endl;
    }
    else
    {
        cout << "No negative elements. Comparisons = " << comparisonsSorted << endl;
    }
}


// Завдання 2.2

void task22()
{
    int a[MAX_SIZE];
    int n;

    cout << "Enter count of numbers: ";
    cin >> n;

    if (cin.fail() || n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid count" << endl;
        return;
    }

    cout << "Enter " << n << " numbers: ";

    for (int i = 0; i < n; i++)
        cin >> a[i];

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] % 2 == 0 && a[i] % 3 != 0)
            count++;
    }

    cout << "Count divisible by 2 and not by 3: " << count << endl;
}


// Виведення квадратної матриці

void printMatrix(int a[MAX_N][MAX_N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << "\t";

        cout << endl;
    }
}


// Заповнення квадратної матриці випадковими числами

void fillRandomMatrix(int a[MAX_N][MAX_N], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            a[i][j] = rand() % 41 - 20;
    }
}


// Завдання 2.3

void task23()
{
    srand((unsigned)time(0));

    int a[MAX_N][MAX_N];
    int n;

    cout << "Enter matrix size n x n: ";
    cin >> n;

    if (cin.fail() || n <= 0 || n > MAX_N)
    {
        cout << "Invalid matrix size" << endl;
        return;
    }

    fillRandomMatrix(a, n);

    cout << "Matrix:" << endl;
    printMatrix(a, n);

    int sum = 0;

    cout << "Secondary diagonal: ";

    for (int i = 0; i < n; i++)
    {
        int value = a[i][n - 1 - i];
        cout << value << " ";

        if (value % 2 != 0)
            sum += value;
    }

    cout << endl;
    cout << "Sum of odd elements on secondary diagonal: " << sum << endl;
}


// ОДНОВИМІРНИЙ МАСИВ

// Виділення пам'яті під одновимірний масив

int* formArray(int n)
{
    return new int[n];
}


// Заповнення одновимірного масиву випадковими числами

void fillArray(int* a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand() % 101 - 50;
}


// Виведення одновимірного масиву

void printArray(int* a, int n)
{
    if (a == nullptr || n <= 0)
    {
        cout << "Array is empty." << endl;
        return;
    }

    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}


// Видалення N елементів, починаючи з номера K

void deleteElementsFromK(int*& a, int& n, int k, int count)
{
    if (a == nullptr || n == 0)
    {
        cout << "Error: array is empty." << endl;
        return;
    }

    if (k < 0 || k >= n)
    {
        cout << "Error: invalid K." << endl;
        return;
    }

    if (count <= 0)
    {
        cout << "Error: invalid count." << endl;
        return;
    }

    if (count > n - k)
    {
        cout << "Error: too many elements to delete." << endl;
        return;
    }

    int newSize = n - count;
    int* newArray = (newSize > 0) ? new int[newSize] : nullptr;
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (i < k || i >= k + count)
        {
            newArray[j] = a[i];
            j++;
        }
    }

    delete[] a;
    a = newArray;
    n = newSize;

    cout << "Elements deleted successfully." << endl;
}


// Звільнення пам'яті одновимірного масиву

void deleteArrayMemory(int*& a)
{
    delete[] a;
    a = nullptr;
}


// ДВОВИМІРНИЙ МАСИВ

// Виділення пам'яті під матрицю

int** formMatrix(int rows, int cols)
{
    int** m = new int* [rows];

    for (int i = 0; i < rows; i++)
        m[i] = new int[cols];

    return m;
}


// Заповнення матриці випадковими числами

void fillMatrix(int** m, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            m[i][j] = rand() % 41 - 20;
    }
}


// Виведення матриці

void printMatrix(int** m, int rows, int cols)
{
    if (m == nullptr || rows <= 0 || cols <= 0)
    {
        cout << "Matrix is empty." << endl;
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << m[i][j] << "\t";

        cout << endl;
    }
}


// Додавання стовпця в початок матриці

void addColumnToStart(int**& m, int rows, int& cols)
{
    if (m == nullptr || rows <= 0 || cols <= 0)
    {
        cout << "Error: matrix is empty." << endl;
        return;
    }

    int newCols = cols + 1;
    int** newMatrix = formMatrix(rows, newCols);

    cout << "Enter elements of the new first column:" << endl;

    for (int i = 0; i < rows; i++)
    {
        cin >> newMatrix[i][0];

        for (int j = 0; j < cols; j++)
            newMatrix[i][j + 1] = m[i][j];
    }

    for (int i = 0; i < rows; i++)
        delete[] m[i];

    delete[] m;
    m = newMatrix;
    cols = newCols;

    cout << "Column added successfully." << endl;
}


// Звільнення пам'яті матриці

void deleteMatrixMemory(int**& m, int rows)
{
    if (m != nullptr)
    {
        for (int i = 0; i < rows; i++)
            delete[] m[i];

        delete[] m;
        m = nullptr;
    }
}


// МЕНЮ — Завдання 2.4

void task24()
{
    srand((unsigned)time(0));

    int* a = nullptr;
    int n = 0;

    int** m = nullptr;
    int rows = 0;
    int cols = 0;

    int choice;

    do
    {
        cout << endl;
        cout << "========== TASK 2.4 MENU ==========" << endl;
        cout << "1. Form 1D array" << endl;
        cout << "2. Print 1D array" << endl;
        cout << "3. Delete N elements from position K" << endl;
        cout << "4. Form 2D matrix" << endl;
        cout << "5. Print 2D matrix" << endl;
        cout << "6. Add column to start of matrix" << endl;
        cout << "7. Exit" << endl;
        cout << "Choose: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            deleteArrayMemory(a);

            cout << "Enter size: ";
            cin >> n;

            if (cin.fail() || n <= 0)
            {
                cout << "Invalid size." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                n = 0;
                break;
            }

            a = formArray(n);
            fillArray(a, n);

            cout << "Array: ";
            printArray(a, n);
            break;
        }

        case 2:
        {
            printArray(a, n);
            break;
        }

        case 3:
        {
            int k;
            int count;

            cout << "Enter K: ";
            cin >> k;
            cout << "Enter count: ";
            cin >> count;

            deleteElementsFromK(a, n, k, count);

            if (a != nullptr && n > 0)
            {
                cout << "Array after deletion: ";
                printArray(a, n);
            }
            else
            {
                cout << "Array is now empty." << endl;
            }

            break;
        }

        case 4:
        {
            deleteMatrixMemory(m, rows);

            cout << "Rows: ";
            cin >> rows;
            cout << "Cols: ";
            cin >> cols;

            if (cin.fail() || rows <= 0 || cols <= 0)
            {
                cout << "Invalid size." << endl;
                cin.clear();
                cin.ignore(10000, '\n');
                rows = 0;
                cols = 0;
                break;
            }

            m = formMatrix(rows, cols);
            fillMatrix(m, rows, cols);

            cout << "Matrix:" << endl;
            printMatrix(m, rows, cols);
            break;
        }

        case 5:
        {
            printMatrix(m, rows, cols);
            break;
        }

        case 6:
        {
            addColumnToStart(m, rows, cols);

            if (m != nullptr)
            {
                cout << "Matrix after adding column:" << endl;
                printMatrix(m, rows, cols);
            }

            break;
        }

        case 7:
        {
            cout << "Exit." << endl;
            break;
        }

        default:
        {
            cout << "Wrong choice." << endl;
            break;
        }
        }

    } while (choice != 7);

    deleteArrayMemory(a);
    deleteMatrixMemory(m, rows);
}


// Перевірка, чи є символ голосною літерою

bool isVowel(char c)
{
    string vowels = "aeiouAEIOUаеиіоуяєюАЕИІОУЯЄЮ";
    return vowels.find(c) != string::npos;
}


// Видалення слів, що починаються на голосну

string removeVowelWords(const string& line)
{
    istringstream input(line);
    string word;
    string result;

    while (input >> word)
    {
        if (!word.empty() && !isVowel(word[0]))
        {
            if (!result.empty())
                result += " ";

            result += word;
        }
    }

    return result;
}


// Перетворення символу в числове значення

int charToDigit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return -1;
}


// Перетворення числа із заданої системи у десяткову

long long parseNumber(const string& s, int base)
{
    long long result = 0;

    for (int i = 0; i < (int)s.length(); i++)
    {
        int digit = charToDigit(s[i]);

        if (digit == -1)
        {
            cout << "Error: invalid character '" << s[i] << "'" << endl;
            return -1;
        }

        if (digit >= base)
        {
            cout << "Error: digit out of range for base " << base << endl;
            return -1;
        }

        result = result * base + digit;
    }

    return result;
}


// Завдання 2.5

void task25()
{
    string line;

    cout << "Enter a string: ";
    getline(cin, line);

    string processed = removeVowelWords(line);

    cout << "Result: " << processed << endl;

    string numberStr;
    int base;

    cout << "Enter number: ";
    cin >> numberStr;

    cout << "Enter base (2, 10 or 16): ";
    cin >> base;

    if (base != 2 && base != 10 && base != 16)
    {
        cout << "Error: base must be 2, 10 or 16." << endl;
        return;
    }

    long long val = parseNumber(numberStr, base);

    if (val != -1)
        cout << "Decimal value: " << val << endl;
}


// Головна функція

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //task21();
    //task22();
    //task23();
    //task24();
    task25();

    return 0;
}