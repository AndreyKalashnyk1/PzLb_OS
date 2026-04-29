#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <windows.h>

using namespace std;

struct Process
{
    string name;      // ім'я процесу
    int arrivalTime;  // час появи
    int burstTime;    // загальна тривалість
    int remaining;    // залишок часу виконання
    int queueLevel;   // поточний рівень черги (1..4)
    int finishTime;   // час завершення
};

int highestPriorityQueue(const vector<deque<Process*>>& queues)
{
    for (int i = 0; i < (int)queues.size(); i++)
        if (!queues[i].empty())
            return i;
    return -1;
}

void simulateMLFQ(vector<Process>& procs)
{
    const int quanta[4] = { 2, 4, 8, 1000000 };
    vector<deque<Process*>> queues(4);

    int time = 0;
    int done = 0;
    int n = (int)procs.size();

    cout << "Час\tПроцес\tЧерга\tКвант\tЗалишок після\n";
    cout << string(55, '-') << "\n";

    while (done < n)
    {
        for (auto& p : procs)
            if (p.arrivalTime == time && p.remaining == p.burstTime)
            {
                p.queueLevel = 1;
                queues[0].push_back(&p);
            }

        int qi = highestPriorityQueue(queues);

        if (qi == -1) { time++; continue; }

        Process* cur = queues[qi].front();
        queues[qi].pop_front();

        int quantum = quanta[qi];
        int slice = min(quantum, cur->remaining);

        cout << time << "\t" << cur->name
            << "\tQ" << (qi + 1)
            << "\t" << quantum
            << "\t";

        for (int t = 0; t < slice; t++)
        {
            time++;
            cur->remaining--;

            for (auto& p : procs)
                if (p.arrivalTime == time && p.remaining == p.burstTime)
                {
                    p.queueLevel = 1;
                    queues[0].push_back(&p);
                }

            int newQi = highestPriorityQueue(queues);
            if (newQi != -1 && newQi < qi && cur->remaining > 0)
            {
                cout << cur->remaining << " (витіснено)\n";
                queues[qi].push_front(cur);
                goto next_iteration;
            }
        }

        cout << cur->remaining << "\n";

        if (cur->remaining == 0)
        {
            cur->finishTime = time;
            done++;
        }
        else
        {
            int nextQ = min(qi + 1, 3);
            cur->queueLevel = nextQ + 1;
            queues[nextQ].push_back(cur);
        }

    next_iteration:;
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

    // процеси: ім'я, час появи, тривалість, залишок, рівень черги, час завершення
    vector<Process> procs = {
        { "P0", 0, 10, 10, 1, 0 },
        { "P1", 1,  8,  8, 1, 0 },
        { "P2", 2,  6,  6, 1, 0 },
        { "P3", 3,  4,  4, 1, 0 },
    };

    cout << "=== Завдання 2: Багаторівнева черга (MLFQ) ===\n";
    cout << "Черги: Q1(квант=2), Q2(квант=4), Q3(квант=8), Q4(FCFS)\n\n";

    simulateMLFQ(procs);

    return 0;
}
