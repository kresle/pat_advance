#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void printTime(int tt)
{
    if (tt==-1) cout << "Sorry";
    else{
        printf("%02d:%02d",8+tt/60,tt%60);
    }
}

int main(int argc, char const *argv[])
{
    int nn,mm, kk, qq;
    cin >> nn >> mm >> kk >> qq;
    vector<int> dt(kk);
    vector<int> query(qq);
    for(int ii=0;ii<kk;ii++) cin >> dt[ii];
    for(int ii=0;ii<qq;ii++) {cin >> query[ii];query[ii]--;}
    vector<queue<int>> winds(nn); //每个窗口前所排的队伍。
    vector<int> eta(nn,-1); //每个窗口处理用户还需要多久才能处理完
    vector<int> finishTime(kk, -1); //每个客户的处理完毕时间
    int waitLineFront=0;
    for(int jj=0;jj<mm&&waitLineFront<kk;jj++)
        for(int ii=0;ii<nn&&waitLineFront<kk;ii++)
        {
            winds[ii].push(waitLineFront);
            waitLineFront++;
        }
    for(int ii=0;ii<nn&&!winds[ii].empty();ii++)
    {
        eta[ii] = dt[winds[ii].front()];
    }
    int tt;
    for(tt=1;tt<60*(17-8);tt++)
    {
        for(int ii=0;ii<nn;ii++){
            if (eta[ii]==-1) continue;
            eta[ii]--;
            if (eta[ii]==0)
            {
                // printf("At time %d, %d finished\n",tt, winds[ii].front());
                finishTime[winds[ii].front()]=tt;
                winds[ii].pop();
                if (waitLineFront<kk)
                {
                    winds[ii].push(waitLineFront);
                    waitLineFront++;
                }
                if (!winds[ii].empty())
                {
                    eta[ii] = dt[winds[ii].front()];
                }
                else{
                    eta[ii] = -1;
                }
            }
        }
    }
    bool over = false;
    while(!over)
    {
        over = true;
        for(int ii=0;ii<nn;ii++){
            if (eta[ii]==-1) continue;
            eta[ii]--;
            over = false;
            if (eta[ii]==0)
            {
                finishTime[winds[ii].front()]=tt;
                winds[ii].pop();
                eta[ii]=-1;
            }
        }
        tt++;
    }
    if (qq>0) printTime(finishTime[query[0]]);
    for(int ii=1;ii<qq;ii++)
    {
        cout << "\n";
        printTime(finishTime[query[ii]]);
    }
    return 0;
}
