#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

const int maxNN=10000;

vector<vector<int>> edge(10000, vector<int>(10000, -1)); //-1,不直接相连。i:通过i号线，直接相连（紧邻）。
vector<vector<int>> dist(10000, vector<int>(10000, UINT16_MAX)); //最短距离
vector<vector<int>> prec(10000, vector<int>(10000, -1)); //p[i,j] i到j路线上的第一个i的邻居的编号。初始-1。
bool isUsed[10000];

void calcShortestDist()
{
    for(int ii=0;ii<10000;ii++)
    {
        if (!isUsed[ii]) continue;
        for(int jj=0;jj<10000;jj++)
        {
            if (!isUsed[jj]) continue;
            for(int kk=0;kk<10000;kk++)
            {
                if (!isUsed[kk]) continue;
                if (!edge[ii][kk]) continue;
                if (dist[ii][kk]+dist[kk][ii]<dist[ii][jj])
                {
                    dist[ii][jj] = dist[ii][kk]+dist[kk][ii];
                    prec[ii][jj] = kk;
                }
            }
        }
    }
}

void present(int st, int ed)
{
    cout << dist[st][ed] << endl;
    int st_bk = st, ed_bk = ed;
    int mid = -1;
    int line;
    while(mid!=ed)
    {
        mid = prec[st][ed];
        line = edge[st][mid];
        while(mid!=ed && edge[mid][prec[mid][ed]]==line) mid = prec[mid][ed];
        printf("Take Line#%d from %04d to %04d.\n", line, st, mid);
        st = mid;
    }
}

int main()
{
    int nn, mm, kk;
    int st, ed;
    cin >> nn;
    fill(isUsed, isUsed+10000, 0);
    for(int ii=1;ii<=nn;ii++)
    {
        int mm;
        cin >> mm;
        cin >> st;
        isUsed[st] = true;
        for(int jj=1;jj<mm;jj++)
        {
            cin >> ed;
            edge[st][ed] = ii;
            edge[ed][st] = ii;
            dist[st][ed] = 1;
            dist[ed][st] = 1;
            st = ed;
            isUsed[ed] = true;
        }
    }
    calcShortestDist();
    cin >> kk;
    while(kk--)
    {
        cin >> st >> ed;
        present(st, ed);
    }
}