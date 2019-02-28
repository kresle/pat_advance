//20:12 - 

// 首先只从float改到double就升到了24分。
// 把bfs的访问策略修改成当前版本后，AC。
// 当前版本肯定更合理，但不明白之前版本哪里有错。
// 之前版本太烂了，一上来就价格乘了系数，但还没访问任何结点，这个价格是什么意思？既不是队列里卖给下级的价格，也不是队列里收取的价格。
// 而当前版本就很合理，价格是当前队列里对其下级的售价，这个售价在一层访问完后倍乘系统以做下一层的售价。而一旦找到零售商，就不需要再知道下一级的售价了，就不需再倍乘系数。
// 另外就是自己一直疑惑的，要求记录深度的bfs的写法，实际的操作都在内层循环里，外层循环仅负责交换层队列。
// 而对结点的任何操作，都应在访问时才进行，也就是内层循环里。

#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;

int nn;
vector<bool> isRetailer;
vector<vector<int>> downStream;

double raw_price, profit_rate, price_ans;
vector<int> ans;

void bfs()
{
    queue<int> qq;
    qq.push(0);
    price_ans = raw_price;
    while (!qq.empty() && ans.empty())
    {
        queue<int> lvl_qq;
        while (!qq.empty())
        {
            if (isRetailer[qq.front()]) ans.push_back(qq.front());
            for (auto ii : downStream[qq.front()])
                lvl_qq.push(ii);
            qq.pop();
        }
        qq = lvl_qq;
        if (ans.empty()) price_ans *= (1.0+profit_rate/100);
    }
}

void bfs_24()
{
    queue<int> qq;
    qq.push(0);
    price_ans = raw_price;
    while (!qq.empty() && ans.empty())
    {
        price_ans *= (1.0+profit_rate/100);
        queue<int> lvl_qq;
        while (!qq.empty())
        {
            for (auto ii : downStream[qq.front()])
            {
                lvl_qq.push(ii);
                if (isRetailer[ii])
                    ans.push_back(ii);
            }
            qq.pop();
        }
        qq = lvl_qq;
    }
}

int main()
{
    cin >> nn >> raw_price >> profit_rate;
    isRetailer.reserve(nn), isRetailer.resize(nn, false);
    downStream.resize(nn);
    int kk, tmp;
    for (int ii = 0; ii < nn; ii++)
    {
        cin >> kk;
        if (kk)
            while (kk--)
            {
                cin >> tmp;
                downStream[ii].push_back(tmp);
            }
        else
            isRetailer[ii] = true;
    }
    bfs();
    printf("%.4f %d", price_ans, (int)ans.size());

    return 0;
}