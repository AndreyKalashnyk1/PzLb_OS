#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;


struct Process
{
    string name;       // ім'я процесу (P0, P1 ...)
    int arrivalTime;   // час появи в системі
    int burstTime;     // загальна тривалість виконання
    int basePriority;  // початковий (статичний) пріоритет
    int curPriority;   // поточний (динамічний) пріоритет
    int remaining;     // залишок часу виконання
    int finishTime;    // час завершення
    int waitStart;     // момент початку очікування
};

void enqueue(vector<Process*>& queue, Process* p)
{
    queue.push_back(p);
    sort(queue.begin(), queue.end(), [](Process* a, Process* b) {
        if (a->curPriority != b->curPriority)
            return a->curPriority < b->curPriority;
        return a->waitStart < b->waitStart;
        });
}

Process* dequeue(vector<Process*>& queue)
{
    if (queue.empty()) return nullptr;
    Process* chosen = queue.front();
    queue.erase(queue.begin());
    for (Process* p : queue)
        p->curPriority--;
    return chosen;
}

void simulateDynamicPriority(vector<Process>& procs, int quantum)
{
    int time = 0;
    int done = 0;
    int n = (int)procs.size();
    vector<Process*> ready;
    vector<bool> inQueue(n, false);

    cout << "Час\tПроцес\t\tЗалишок\tПріоритет\n";
    cout << string(55, '-') << "\n";

    while (done < n)
    {
        for (int i = 0; i < n; i++)
            if (!inQueue[i] && procs[i].arrivalTime <= time && procs[i].remaining > 0 && procs[i].finishTime == 0)
            {
                procs[i].waitStart = time;
                enqueue(ready, &procs[i]);
                inQueue[i] = true;
            }

        if (ready.empty()) { time++; continue; }

        Process* cur = dequeue(ready);
        int slice = min(quantum, cur->remaining);

        cout << time << "\t" << cur->name
            << "\t\t" << cur->remaining
            << "\t" << cur->curPriority << "\n";

        time += slice;
        cur->remaining -= slice;

        for (int i = 0; i < n; i++)
            if (!inQueue[i] && procs[i].arrivalTime <= time && procs[i].remaining > 0 && procs[i].finishTime == 0)
            {
                procs[i].waitStart = procs[i].arrivalTime;
                enqueue(ready, &procs[i]);
                inQueue[i] = true;
            }

        if (cur->remaining == 0)
        {
            cur->finishTime = time;
            done++;
        }
        else
        {
            cur->curPriority = cur->basePriority;
            cur->waitStart = time;
            enqueue(ready, cur);
        }
    }

    cout << "\nРезультати:\n";
    cout << string(55, '-') << "\n";
    cout << "Процес\tЗавершення\tЧас виконання\tЧас чекання\n";

    double avgTurnaround = 0, avgWaiting = 0;
    for (auto& p : procs)
    {
        int turnaround = p.finishTime - p.arrivalTime;
        int waiting = turnaround - p.burstTime;
        avgTurnaround += turnaround;
        avgWaiting += waiting;
        cout << p.name << "\t" << p.finishTime
            << "\t\t" << turnaround
            << "\t\t" << waiting << "\n";
    }
    cout << "\nСередній час виконання: " << avgTurnaround / n << "\n";
    cout << "Середній час чекання:   " << avgWaiting / n << "\n";
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Process> procs = {
        { "P0", 0, 10, 3, 3, 10, 0, 0 },
        { "P1", 1,  8, 2, 2,  8, 0, 0 },
        { "P2", 2,  6, 1, 1,  6, 0, 0 },
        { "P3", 3,  4, 0, 0,  4, 0, 0 },
    };

    int quantum = 2;

    cout << "=== Завдання 1: Динамічний пріоритет ===\n";
    cout << "Квант часу: " << quantum << "\n\n";

    simulateDynamicPriority(procs, quantum);

    return 0;
}
