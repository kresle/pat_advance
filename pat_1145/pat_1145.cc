#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;

int nn, pp, kk;
vector<int> primeList;
vector<int> hashTable;

bool isPrime(int num)
{
    int ed = sqrt(num);
    bool isPrime = true;
    for(int ii=0;ii<primeList.size()&&primeList[ii]<=ed;ii++)
    {
        if (num%primeList[ii]==0)
        {
            isPrime = false;
        }
    }
    return isPrime;
}

void findPrimes()
{
    primeList.push_back(2);
    while(primeList.back()<pp)
    {
        int ii;
        for(ii=primeList.back()+1;!isPrime(ii);ii++);
        primeList.push_back(ii);
    }
    pp = primeList.back();
}

int findValidInc(int num)
{
    int jj;
    int id;
    for(jj=0;jj<pp;jj++)//pat这里是到pp,实际到pp-1就够了
    {
        id = (num+jj*jj)%pp;
        if (hashTable[id]==-1) break;
    }
    if (jj==pp) return -1;
    else return jj;
}

int stepsTakenToFindNum(int num)
{
    int jj;
    int id;
    for(jj=0;jj<pp;jj++)//pat这里是到pp,实际到pp-1就够了
    {
        id = (num+jj*jj)%pp;
        if (hashTable[id]==-1||hashTable[id]==num) break;
    }
    return jj+1;
}

void insertIntoHT(int num)
{
    int ic = findValidInc(num);
    // cerr << num << " " << ic << endl;
    if (ic==-1)
    {
        cout << num << " cannot be inserted." << endl;
    }
    else
    {
        int id = (num+ic*ic)%pp;
        hashTable[id] = num;
    }
}

int main()
{
    cin >> pp >> nn >> kk;
    findPrimes();
    hashTable.resize(pp, -1);
    int num;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> num;
        insertIntoHT(num);
    }
    int ans = 0, stepTaken;
    for(int ii=0;ii<kk;ii++)
    {
        cin >> num;
        stepTaken = stepsTakenToFindNum(num);
        // cerr << num << " " << stepsTakenToFindNum(num) << endl;
        ans += stepTaken;
    }
    printf("%.1f", ans*1.0/kk);
    return 0;
}