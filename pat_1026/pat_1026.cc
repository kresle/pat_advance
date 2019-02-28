// 11:20 - 14:14(AC)

// 太麻烦了，这花了将近3个小时才AC掉。
// 关于时间模拟的其他几道题也是这样，尤其是cars on campus. 遇上这种题真的是只能自求多福，放在最后面做了。
// 最重大的几个失误有：
// 1. 如昨天还是前天做的某题一样，条件判断里，忘了!empty().
// 2. priority_queue，自定义比较函数的写法（和set这些是一样的，要有一个重载了括号运算符的类或者结构体，括号运算符函数用来进行比较操作）
// 3. 关于player的两个队列里，队首player是否已经被serve过，想到了要对all_qq里的进行排查，但却忘了对vip_qq里的也进行同样的排查。这个是有三个样例过不了的那份代码的原因。
// 4. 代码太长，细节太多，就容易出错。在不同时有vip桌子和vip会员的压队逻辑里，也就是第二个while循环里，居然一开始漏写了all_qq.pop(). 这个可以算是重大逻辑疏漏了
// 5. 最后的最后，输出时，居然还要再依服务时间，对player再进行一次排序，这题要求做的东西也太多了。
// 6. 这份代码这么长，但是没一行是多余没用的。

#include <iostream>
#include <stdio.h>
#include <string>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

#define INF 0x3f3f3f3f

struct player
{
    int arrTime;
    int svTime = INF; //顺带实现visit功能
    int playTime;
    bool isVip;
    bool operator<(player obj) { return arrTime < obj.arrTime; }
    bool operator>(player obj)
    {
        if (svTime != obj.svTime)
            return svTime < obj.svTime;
        return (svTime-arrTime)<(obj.svTime-obj.arrTime);
    }
};

struct table
{
    int id;
    bool isVip;
    int expTime;
    int svCnt = 0;
    bool operator<(table obj) { return expTime < obj.expTime; }
};

int nn, kk, mm;
vector<table> tables;
vector<player> players;

struct tabHeapCmp
{
    bool operator()(int id1, int id2)
    {
        return tables[id1].expTime > tables[id2].expTime;
    }
};

inline int stimeToSeconds(string ss) { return stoi(ss.substr(0, 2)) * 3600 + stoi(ss.substr(3, 2)) * 60 + stoi(ss.substr(6)); }

void printTime(int tt)
{
    printf("%02d:%02d:%02d ", tt / 3600, (tt / 60) % 60, tt % 60);
}

int main()
{
    int pid, tid;
    string ss;
    cin >> nn;
    players.resize(nn);
    for (int ii = 0; ii < nn; ii++)
    {
        cin >> ss >> players[ii].playTime >> players[ii].isVip;
        players[ii].arrTime = stimeToSeconds(ss);
        if (players[ii].playTime >= 120)
            players[ii].playTime = 7200;
        else
            players[ii].playTime *= 60;
    }
    sort(players.begin(), players.end());

    cin >> kk >> mm;
    tables.resize(kk);
    for (int ii = 0; ii < kk; ii++)
        tables[ii].id = ii;
    for (int ii = 0; ii < mm; ii++)
    {
        cin >> tid;
        tid--;
        tables[tid].isVip = true;
    }

    queue<int> all_qq;      //所有player的队列，要记住与vip队列进行服务状态排查
    queue<int> vip_qq;      //vip player的队列，也要记住与所有成员的队列进行服务状态排查
    for (int ii = 0; ii < nn; ii++)
    {
        if (players[ii].isVip)
            vip_qq.push(ii);
        all_qq.push(ii);
    }

    priority_queue<int, vector<int>, tabHeapCmp> tab_qq;        //已用台子的编号队列，是结束时间的小根堆，以判断是否有台子可以回收
    priority_queue<int, vector<int>, greater<int>> normTab_qq;  //普通台子的编号队列，方便得到最小编号
    priority_queue<int, vector<int>, greater<int>> vipTab_qq;   //vip台子的编号队列
    for (int ii = 0; ii < kk; ii++)
    {
        if (tables[ii].isVip)
            vipTab_qq.push(ii);
        else
            normTab_qq.push(ii);
    }

    // If one cannot get a table before the closing time, their information must NOT be printed.
    for (int ii = 8 * 3600; ii < 21 * 3600 && !all_qq.empty(); ii++)
    {
        //先弹桌子
        while (!tab_qq.empty() && tables[tab_qq.top()].expTime == ii)
        {
            tid = tab_qq.top();
            if (tables[tid].isVip)
                vipTab_qq.push(tid); //, cerr << " , vip\n";
            else
                normTab_qq.push(tid); //, cerr << " , ordinary\n";
            tab_qq.pop();
        }

        //再分配桌子，先分配普通桌子，再分配vip桌子。如果两者都有，且队首是vip，应该分到哪？
        //  if when it is the turn of a VIP pair, yet no VIP table is available, they can be assigned as any ordinary players.
        // 应该是先看有没有vip用户和vip桌子，有，则依序分配vip桌子给vip用户;
        // 如果没有vip用户而有vip桌子，则vip桌子应与普通桌子一视同仁，从编号小的起分配；
        // 如果有vip用户而没有vip桌子，则就是普通情形，不用特殊处理。
        // 如果两者都没有，则普通情形。
        if (normTab_qq.empty() && vipTab_qq.empty())
            continue;
        while (!vipTab_qq.empty() && !vip_qq.empty() && players[vip_qq.front()].arrTime <= ii)
        {
            if (players[vip_qq.front()].svTime != INF)  //对此队进行排查，以防止被当做普通用户就服务过后，这里再次提供服务
            {
                vip_qq.pop();
                continue;
            }
            pid = vip_qq.front(), vip_qq.pop();
            tid = vipTab_qq.top(), vipTab_qq.pop();
            players[pid].svTime = ii;
            tables[tid].svCnt++;
            tables[tid].expTime = ii + players[pid].playTime;
            tab_qq.push(tid);
        }
        while (!(vipTab_qq.empty() && normTab_qq.empty()) && !all_qq.empty() && players[all_qq.front()].arrTime <= ii)
        {
            if (players[all_qq.front()].svTime != INF)  //对此队进行排查，以防止其中的享受了vip待遇的vip用户这里再次被服务。其实逻辑可以再加上是否是vip以增强可读性，但这样也没任何问题
            {
                all_qq.pop();
                continue;
            }
            pid = all_qq.front(), all_qq.pop();         //这两个操作算是原子操作，一定要绑定。之前的代码居然忘了pop.
            if (vipTab_qq.empty())
                tid = normTab_qq.top(), normTab_qq.pop();
            else if (normTab_qq.empty())
                tid = vipTab_qq.top(), vipTab_qq.pop();
            else if (vipTab_qq.top() < normTab_qq.top())
                tid = vipTab_qq.top(), vipTab_qq.pop();
            else
                tid = normTab_qq.top(), normTab_qq.pop();
            players[pid].svTime = ii;
            tables[tid].svCnt++;
            tables[tid].expTime = ii + players[pid].playTime;
            tab_qq.push(tid);
        }
    }

    sort(players.begin(), players.end(), [](player ll, player rr) { return ll > rr; });
    for (auto pp : players)
    {
        if (pp.svTime == INF)
            break;
        printTime(pp.arrTime);
        printTime(pp.svTime);
        printf("%d\n", (int)round((pp.svTime - pp.arrTime) / 60.0));
        // printf("%.0f\n", round((pp.svTime - pp.arrTime) / 60.0));
    }
    if (kk > 0)
        printf("%d", tables[0].svCnt);
    for (int ii = 1; ii < kk; ii++)
    {
        printf(" %d", tables[ii].svCnt);
    }
}