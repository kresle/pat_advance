// 差不多0点开始 -> 01:27(AC)
// 也就是花了差不多一个半小时。
// 问题：
// 1.最大的问题，肯定是在循环的中止条件上，即使到了时间，如果有还在等的，就要继续下去，只是不接受新来的去排队了。这点是最大的问题，花了25分钟才排除出来。
// 2.分配窗口的代码，一开始少写了一个条件：!qq.empty()。也排查了12分钟。
// 3.遗忘了priority_queue如果不是先弹大的而是先弹小的，该怎么写。（要定容器，给compare方法，小根堆用greater而不是less。priority_queue还要再加练，比如自己定义的结构怎么写cmp。

#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct customer
{
    int arrTime;
    int prcTime;
    bool operator<(customer obj) { return arrTime < obj.arrTime; }
};

int nn, kk;
vector<customer> customers;
int startTime = 8 * 3600;
int endTime = 17 * 3600;
priority_queue<int, vector<int>, greater<int>> wind_qq;
queue<int> qq;

int stimeToTime(string ss)
{
    return stoi(ss.substr(0, 2)) * 3600 + stoi(ss.substr(3, 2)) * 60 + stoi(ss.substr(6));
}

int main()
{
    cin >> nn >> kk;
    customers.resize(nn);
    string ss;
    for (int ii = 0; ii < nn; ii++)
    {
        cin >> ss >> customers[ii].prcTime;
        customers[ii].arrTime = stimeToTime(ss);
        if (customers[ii].prcTime >= 60)
            customers[ii].prcTime = 3600;
        else
            customers[ii].prcTime *= 60;
    }
    sort(customers.begin(), customers.end());
    for (int ii = 0; ii < nn && customers[ii].arrTime <= endTime; ii++)
    {
        // cerr << customers[ii].arrTime << " " << startTime - customers[ii].arrTime << endl;
        qq.push(ii);
    }
    int cnt = qq.size();
    // cerr << cnt << endl;

    int ttl_waitSeconds = 0;
    //怎么控制窗口的结束，怎么回收？
    int ii;
    for (ii = startTime; ii <= endTime || !qq.empty(); ii++) //注意这里的条件
    {
        //先回收窗口
        while (!wind_qq.empty() && wind_qq.top() == ii)
            wind_qq.pop();
        //再分配窗口
        while (wind_qq.size() < kk && !qq.empty() && customers[qq.front()].arrTime <= ii) //有窗口空闲，且有顾客等待
        {
            // cerr << qq.size() << " " << ii - customers[qq.front()].arrTime << endl;
            ttl_waitSeconds += (ii - customers[qq.front()].arrTime);
            wind_qq.push(ii + customers[qq.front()].prcTime);
            qq.pop();
        }
    }
    // cerr << startTime << " " << ii << " " << endTime << endl;
    // cerr << qq.size() << " " << customers[qq.front()].arrTime << endl;
    printf("%.1f", ttl_waitSeconds / 60.0 / cnt);
}