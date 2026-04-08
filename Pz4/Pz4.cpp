#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX

#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;


// структура школяр поля: ПІБ, клас, телефон, математика, фізика, укр. мова, літ-ра
struct Schoolboy
{
    char name[60];
    int  grade;
    char phone[20];
    int  math;
    int  physics;
    int  ukrainian;
    int  literature;
};


// виведення одного запису на екран
void printSchoolboy(const Schoolboy& s, int index)
{
    cout << "  [" << index << "] "
        << s.name << " | кл." << s.grade
        << " | " << s.phone
        << " | мат:" << s.math
        << " | фіз:" << s.physics
        << " | укр:" << s.ukrainian
        << " | літ:" << s.literature
        << "\n";
}


// зчитування одного запису - один рядок через кому
Schoolboy inputSchoolboy(int index)
{
    Schoolboy s;
    char buf[200];

    cout << "  Запис " << index
        << " (ПІБ, клас, телефон, мат, фіз, укр, літ): ";
    cin.ignore();
    cin.getline(buf, 200);

    // розбиваємо рядок по комах
    char* token = strtok(buf, ",");
    if (token) { while (*token == ' ') token++; strncpy(s.name, token, 59); s.name[59] = '\0'; }

    token = strtok(NULL, ",");
    s.grade = token ? atoi(token) : 0;

    token = strtok(NULL, ",");
    if (token) { while (*token == ' ') token++; strncpy(s.phone, token, 19); s.phone[19] = '\0'; }

    token = strtok(NULL, ",");
    s.math = token ? atoi(token) : 0;

    token = strtok(NULL, ",");
    s.physics = token ? atoi(token) : 0;

    token = strtok(NULL, ",");
    s.ukrainian = token ? atoi(token) : 0;

    token = strtok(NULL, ",");
    s.literature = token ? atoi(token) : 0;

    return s;
}


// перевірка: чи є хоча б одна оцінка 2

bool hasTwos(const Schoolboy& s)
{
    return s.math == 2 || s.physics == 2 ||
        s.ukrainian == 2 || s.literature == 2;
}


// ЗАВДАННЯ 1: Стиль C (stdio.h / FILE*)


// створення файлу та запис даних
void task1_createFile(const char* filename)
{
    int n;
    cout << "\n[C] Кількість записів: ";
    cin >> n;

    FILE* f = fopen(filename, "wb");
    if (!f) { perror("Помилка відкриття файлу"); return; }

    cout << "  Формат вводу: ПІБ, клас, телефон, мат, фіз, укр, літ\n";
    cout << "  Приклад: Іваненко Олег Сергійович, 9, 0501112233, 10, 8, 7, 9\n\n";

    for (int i = 0; i < n; i++)
    {
        Schoolboy s = inputSchoolboy(i + 1);
        fwrite(&s, sizeof(Schoolboy), 1, f);
    }

    fclose(f);
    cout << "\nФайл \"" << filename << "\" створено.\n";
}

// вивід файлу на екран
void task1_printFile(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    if (!f) { perror("Помилка відкриття файлу"); return; }

    Schoolboy s;
    int i = 1;
    while (fread(&s, sizeof(Schoolboy), 1, f))
        printSchoolboy(s, i++);

    fclose(f);
}

// видалення записів з оцінкою 2 (через допоміжний файл)
void task1_deleteWithTwos(const char* filename)
{
    FILE* f = fopen(filename, "rb");
    FILE* temp = fopen("temp.bin", "wb");
    if (!f || !temp)
    {
        perror("Помилка відкриття файлу");
        if (f)    fclose(f);
        if (temp) fclose(temp);
        return;
    }

    Schoolboy s;
    int deleted = 0;
    while (fread(&s, sizeof(Schoolboy), 1, f))
    {
        if (hasTwos(s))
        {
            cout << "  Видалено: " << s.name << "\n";
            deleted++;
        }
        else
            fwrite(&s, sizeof(Schoolboy), 1, temp);
    }

    fclose(f);
    fclose(temp);
    remove(filename);
    rename("temp.bin", filename);
    cout << "  Видалено записів: " << deleted << "\n";
}

// додавання K записів у кінець файлу
void task1_addToEnd(const char* filename)
{
    int k;
    cout << "[C] Кількість нових записів (K): ";
    cin >> k;

    FILE* f = fopen(filename, "ab");
    if (!f) { perror("Помилка відкриття файлу"); return; }

    cout << "  Формат: ПІБ, клас, телефон, мат, фіз, укр, літ\n\n";
    for (int i = 0; i < k; i++)
    {
        Schoolboy s = inputSchoolboy(i + 1);
        fwrite(&s, sizeof(Schoolboy), 1, f);
    }

    fclose(f);
}


// ЗАВДАННЯ 2: Стиль C++ (fstream)


// створення файлу та запис даних
void task2_createFile(const char* filename)
{
    int n;
    cout << "\n[C++] Кількість записів: ";
    cin >> n;

    ofstream fout(filename, ios::binary);
    if (!fout) { cerr << "Помилка відкриття файлу\n"; return; }

    cout << "  Формат вводу: ПІБ, клас, телефон, мат, фіз, укр, літ\n";
    cout << "  Приклад: Коваленко Дарина Петрівна, 11, 0664445566, 11, 10, 12, 11\n\n";

    for (int i = 0; i < n; i++)
    {
        Schoolboy s = inputSchoolboy(i + 1);
        fout.write(reinterpret_cast<char*>(&s), sizeof(Schoolboy));
    }

    fout.close();
    cout << "\nФайл \"" << filename << "\" створено.\n";
}

// вивід файлу на екран
void task2_printFile(const char* filename)
{
    ifstream fin(filename, ios::binary);
    if (!fin) { cerr << "Помилка відкриття файлу\n"; return; }

    Schoolboy s;
    int i = 1;
    while (fin.read(reinterpret_cast<char*>(&s), sizeof(Schoolboy)))
        printSchoolboy(s, i++);

    fin.close();
}

// видалення записів з оцінкою 2 (через допоміжний файл)
void task2_deleteWithTwos(const char* filename)
{
    ifstream fin(filename, ios::binary);
    ofstream ftmp("temp2.bin", ios::binary);
    if (!fin || !ftmp) { cerr << "Помилка відкриття файлу\n"; return; }

    Schoolboy s;
    int deleted = 0;
    while (fin.read(reinterpret_cast<char*>(&s), sizeof(Schoolboy)))
    {
        if (hasTwos(s))
        {
            cout << "  Видалено: " << s.name << "\n";
            deleted++;
        }
        else
            ftmp.write(reinterpret_cast<char*>(&s), sizeof(Schoolboy));
    }

    fin.close();
    ftmp.close();
    remove(filename);
    rename("temp2.bin", filename);
    cout << "  Видалено записів: " << deleted << "\n";
}

// додавання K записів у кінець файлу
void task2_addToEnd(const char* filename)
{
    int k;
    cout << "[C++] Кількість нових записів (K): ";
    cin >> k;

    ofstream fout(filename, ios::binary | ios::app);
    if (!fout) { cerr << "Помилка відкриття файлу\n"; return; }

    cout << "  Формат: ПІБ, клас, телефон, мат, фіз, укр, літ\n\n";
    for (int i = 0; i < k; i++)
    {
        Schoolboy s = inputSchoolboy(i + 1);
        fout.write(reinterpret_cast<char*>(&s), sizeof(Schoolboy));
    }

    fout.close();
}


// головна функція

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const char* file1 = "schoolboys_c.bin";
    const char* file2 = "schoolboys_cpp.bin";

    // Завдання 1: C-стиль

    cout << "============ ЗАВДАННЯ 1 (C-СТИЛЬ) ============\n";

    cout << "\n--- Крок 1: Створення файлу ---\n";
    task1_createFile(file1);

    cout << "\n--- Крок 2: Вміст вихідного файлу ---\n";
    task1_printFile(file1);

    cout << "\n--- Крок 3: Видалення записів з оцінкою 2 ---\n";
    task1_deleteWithTwos(file1);

    cout << "\n--- Крок 4: Додавання нових записів ---\n";
    task1_addToEnd(file1);

    cout << "\n--- Крок 5: Вміст модифікованого файлу ---\n";
    task1_printFile(file1);

    // Завдання 2: C++-стиль

    cout << "\n============ ЗАВДАННЯ 2 (C++-СТИЛЬ) ============\n";

    cout << "\n--- Крок 1: Створення файлу ---\n";
    task2_createFile(file2);

    cout << "\n--- Крок 2: Вміст вихідного файлу ---\n";
    task2_printFile(file2);

    cout << "\n--- Крок 3: Видалення записів з оцінкою 2 ---\n";
    task2_deleteWithTwos(file2);

    cout << "\n--- Крок 4: Додавання нових записів ---\n";
    task2_addToEnd(file2);

    cout << "\n--- Крок 5: Вміст модифікованого файлу ---\n";
    task2_printFile(file2);

    return 0;
}
