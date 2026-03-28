// Практичне заняття 3
// Функції. Структури.

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

// Бібліотеки

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits>
#include <windows.h>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_ROWS = 20;
const int MAX_COLS = 20;



// ЗАВДАННЯ 1


// Вузол однозв'язного списку

struct Node
{
    double value;
    Node* next;
};


// Додавання елемента в кінець списку

void appendNode(Node*& head, Node*& tail, double value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}


// Формування послідовності з клавіатури

Node* formSequence(int n, const char* sequenceName)
{
    Node* head = nullptr;
    Node* tail = nullptr;
    double x;

    cout << "Enter " << n << " elements of sequence " << sequenceName << ": ";

    for (int i = 0; i < n; i++)
    {
        cin >> x;
        appendNode(head, tail, x);
    }

    return head;
}


// Виведення послідовності

void printSequence(Node* head)
{
    Node* p = head;

    while (p != nullptr)
    {
        cout << p->value << " ";
        p = p->next;
    }

    cout << endl;
}


// Пошук першого вузла з максимальним значенням

Node* findFirstMaxNode(Node* head)
{
    if (head == nullptr)
        return nullptr;

    Node* maxNode = head;
    Node* p = head->next;

    while (p != nullptr)
    {
        if (p->value > maxNode->value)
            maxNode = p;

        p = p->next;
    }

    return maxNode;
}


// Замінити всі елементи після першого максимального на 0.5

void replaceAfterFirstMax(Node* head)
{
    Node* maxNode = findFirstMaxNode(head);

    if (maxNode == nullptr)
        return;

    Node* p = maxNode->next;

    while (p != nullptr)
    {
        p->value = 0.5;
        p = p->next;
    }
}


// Звільнення пам'яті списку

void deleteSequence(Node*& head)
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


// Керуюча функція завдання 1

void task31()
{
    int n;
    int m;

    Node* a = nullptr;
    Node* b = nullptr;

    cout << "========== TASK 3.1 ==========" << endl;

    cout << "Enter number of elements in sequence a: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid number of elements." << endl;
        return;
    }

    cout << "Enter number of elements in sequence b: ";
    cin >> m;

    if (cin.fail() || m <= 0)
    {
        cout << "Invalid number of elements." << endl;
        return;
    }

    a = formSequence(n, "a");
    b = formSequence(m, "b");

    cout << "Sequence a before: ";
    printSequence(a);

    replaceAfterFirstMax(a);

    cout << "Sequence a after:  ";
    printSequence(a);

    cout << "Sequence b before: ";
    printSequence(b);

    replaceAfterFirstMax(b);

    cout << "Sequence b after:  ";
    printSequence(b);

    deleteSequence(a);
    deleteSequence(b);
}



// ЗАВДАННЯ 2


// Перевірка, чи є число числом Фібоначчі

bool isFibonacci(int n)
{
    if (n < 0)
        return false;

    if (n == 0 || n == 1)
        return true;

    int a = 0;
    int b = 1;

    while (b < n)
    {
        int next = a + b;
        a = b;
        b = next;
    }

    return b == n;
}


// Заповнення одновимірного масиву випадковими числами

void fillArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand() % 61 - 20;   // [-20; 40]
}


// Виведення одновимірного масиву

void printArray(const int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}


// Видалення з масиву всіх чисел Фібоначчі

int deleteFibonacciNumbers(int a[], int n)
{
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        if (!isFibonacci(a[i]))
        {
            a[k] = a[i];
            k++;
        }
    }

    return k;
}


// Заповнення матриці випадковими числами

void fillMatrix(int a[][MAX_COLS], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            a[i][j] = rand() % 61 - 20;   // [-20; 40]
    }
}


// Виведення матриці

void printMatrix(const int a[][MAX_COLS], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << a[i][j] << "\t";

        cout << endl;
    }
}


// Сортування одного стовпця за спаданням методом вибору

void sortColumnDesc(int a[][MAX_COLS], int rows, int col)
{
    for (int i = 0; i < rows - 1; i++)
    {
        int maxIndex = i;

        for (int j = i + 1; j < rows; j++)
        {
            if (a[j][col] > a[maxIndex][col])
                maxIndex = j;
        }

        if (maxIndex != i)
        {
            int temp = a[i][col];
            a[i][col] = a[maxIndex][col];
            a[maxIndex][col] = temp;
        }
    }
}


// Сортування всіх стовпців матриці за спаданням

void sortAllColumnsDesc(int a[][MAX_COLS], int rows, int cols)
{
    for (int j = 0; j < cols; j++)
        sortColumnDesc(a, rows, j);
}


// Керуюча функція завдання 2

void task32()
{
    srand((unsigned)time(0));

    int a[MAX_SIZE];
    int n;

    int m[MAX_ROWS][MAX_COLS];
    int rows;
    int cols;

    cout << "========== TASK 3.2 ==========" << endl;

    cout << "Enter size of 1D array (1-" << MAX_SIZE << "): ";
    cin >> n;

    if (cin.fail() || n <= 0 || n > MAX_SIZE)
    {
        cout << "Invalid array size." << endl;
        return;
    }

    fillArray(a, n);

    cout << "Initial 1D array: ";
    printArray(a, n);

    n = deleteFibonacciNumbers(a, n);

    cout << "Array after deleting Fibonacci numbers: ";
    printArray(a, n);

    cout << endl;
    cout << "Enter matrix size (rows cols): ";
    cin >> rows >> cols;

    if (cin.fail() || rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS)
    {
        cout << "Invalid matrix size." << endl;
        return;
    }

    fillMatrix(m, rows, cols);

    cout << "Initial matrix:" << endl;
    printMatrix(m, rows, cols);

    sortAllColumnsDesc(m, rows, cols);

    cout << "Matrix after sorting columns descending:" << endl;
    printMatrix(m, rows, cols);
}



// ЗАВДАННЯ 3


// Структура person

struct person
{
    char* name;
    int age;
};


// Формування однієї структури

person makePerson()
{
    char buffer[100];
    int age;

    cout << "Name: ";
    cin >> buffer;

    cout << "Age: ";
    cin >> age;

    person p;
    p.name = new char[strlen(buffer) + 1];
    strcpy(p.name, buffer);
    p.age = age;

    return p;
}


// Виведення однієї структури

void printPerson(const person& p)
{
    cout << "Name: " << p.name << "\tAge: " << p.age << endl;
}


// Формування масиву структур

person* formPersonArray(int n)
{
    person* arr = new person[n];

    for (int i = 0; i < n; i++)
        arr[i] = makePerson();

    return arr;
}


// Виведення масиву структур

void printPersonArray(const person* arr, int n)
{
    for (int i = 0; i < n; i++)
        printPerson(arr[i]);
}


// Пошук осіб віком більше 25 років та формування нового масиву

person* findOlderThan25(const person* arr, int n, int& count)
{
    count = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i].age > 25)
            count++;
    }

    if (count == 0)
        return nullptr;

    person* result = new person[count];
    int k = 0;

    for (int i = 0; i < n; i++)
    {
        if (arr[i].age > 25)
        {
            result[k].name = new char[strlen(arr[i].name) + 1];
            strcpy(result[k].name, arr[i].name);
            result[k].age = arr[i].age;
            k++;
        }
    }

    return result;
}


// Звільнення пам'яті масиву структур

void deletePersonArray(person*& arr, int n)
{
    if (arr != nullptr)
    {
        for (int i = 0; i < n; i++)
            delete[] arr[i].name;

        delete[] arr;
        arr = nullptr;
    }
}


// Формування масиву динамічних рядків

char** formStringArray(int n)
{
    char** arr = new char* [n];
    char buffer[200];

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');

    for (int i = 0; i < n; i++)
    {
        cout << "Enter string " << i + 1 << ": ";
        cin.getline(buffer, 200);

        arr[i] = new char[strlen(buffer) + 1];
        strcpy(arr[i], buffer);
    }

    return arr;
}


// Виведення масиву рядків

void printStringArray(char** arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << "[" << i << "] " << arr[i] << endl;
}


// Видалення першого рядка з масиву

void deleteFirstString(char**& arr, int& n)
{
    if (n <= 0 || arr == nullptr)
    {
        cout << "Error: string array is empty." << endl;
        return;
    }

    delete[] arr[0];

    int newSize = n - 1;
    char** newArray = (newSize > 0) ? new char* [newSize] : nullptr;

    for (int i = 1; i < n; i++)
        newArray[i - 1] = arr[i];

    delete[] arr;
    arr = newArray;
    n = newSize;

    cout << "First string deleted." << endl;
}


// Звільнення пам'яті масиву рядків

void deleteStringArray(char**& arr, int n)
{
    if (arr != nullptr)
    {
        for (int i = 0; i < n; i++)
            delete[] arr[i];

        delete[] arr;
        arr = nullptr;
    }
}


// Керуюча функція завдання 3

void task33()
{
    int n;
    person* persons = nullptr;
    person* found = nullptr;
    int foundCount = 0;

    int stringCount;
    char** strings = nullptr;

    cout << "========== TASK 3.3 ==========" << endl;

    cout << "Enter number of persons: ";
    cin >> n;

    if (cin.fail() || n <= 0)
    {
        cout << "Invalid number of persons." << endl;
        return;
    }

    persons = formPersonArray(n);

    cout << endl;
    cout << "All persons:" << endl;
    printPersonArray(persons, n);

    found = findOlderThan25(persons, n, foundCount);

    cout << endl;
    if (found == nullptr)
    {
        cout << "No persons older than 25 found." << endl;
    }
    else
    {
        cout << "Persons older than 25:" << endl;
        printPersonArray(found, foundCount);
    }

    deletePersonArray(found, foundCount);
    deletePersonArray(persons, n);

    cout << endl;
    cout << "Enter number of strings: ";
    cin >> stringCount;

    if (cin.fail() || stringCount < 0)
    {
        cout << "Invalid number of strings." << endl;
        return;
    }

    if (stringCount == 0)
    {
        cout << "String array is empty." << endl;
        deleteFirstString(strings, stringCount);
        return;
    }

    strings = formStringArray(stringCount);

    cout << endl;
    cout << "Initial string array:" << endl;
    printStringArray(strings, stringCount);

    deleteFirstString(strings, stringCount);

    cout << endl;
    cout << "String array after deleting first string:" << endl;
    printStringArray(strings, stringCount);

    deleteStringArray(strings, stringCount);
}


// Головна функція

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //task31();
    //task32();
    task33();

    return 0;
}