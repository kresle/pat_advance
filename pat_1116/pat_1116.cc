#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

#define MAXSIZE 10000

bool isPrime[MAXSIZE];
int ranking[MAXSIZE];
bool isQueryed[MAXSIZE];

void findAllPrime()
{
    for (int ii = 2; ii < MAXSIZE; ii++)
    {
        bool flag = true;
        for (int jj = 2; jj * jj <= ii; jj++)
        {
            if (isPrime[jj] && ii % jj == 0)
            {
                flag = false;
                break;
            }
        }
        isPrime[ii] = flag;
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    fill(isPrime, isPrime + MAXSIZE, false);
    fill(ranking, ranking + MAXSIZE, -1);
    fill(isQueryed, isQueryed + MAXSIZE, false);
    findAllPrime();

    int nn, id, kk;
    cin >> nn;
    for (int ii = 1; ii <= nn; ii++)
    {
        cin >> id;
        ranking[id] = ii;
    }
    cin >> kk;
    while (kk--)
    {
        cin >> id;
        if (ranking[id] == -1)
        {
            printf("%04d: Are you kidding?\n", id);
            continue;
        }
        if (isQueryed[id])
        {
            printf("%04d: Checked\n", id);
        }
        else
        {
            if (ranking[id] == 1)
                printf("%04d: Mystery Award\n", id);
            else
            {
                if (isPrime[ranking[id]])
                    printf("%04d: Minion\n", id);
                else
                    printf("%04d: Chocolate\n", id);
            }
            isQueryed[id] = true;
        }
    }
    return 0;
}