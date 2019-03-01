// 23：12上一题AC，之后应该耽误的也不多就开始写这题。00：08AC。差不多一个小时。
// 居然一次就AC，看来推导充分，就是有帮助。

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <stack>
using namespace std;

int appCnt[100001];
int buckCnt[317]; //最后一个桶小一点没关系的，ceil(sqrt(max_int));
stack<int> ss;

int nn, num;
string cmd;

inline int buckId(int num)
{
    return num / 316;
}

void pop()
{
    if (ss.empty())
        cout << "Invalid" << endl;
    else
    {
        cout << ss.top() << endl;
        appCnt[ss.top()]--;
        buckCnt[buckId(ss.top())]--;
        ss.pop();
    }
}

void push(int num)
{
    ss.push(num);
    appCnt[num]++;
    buckCnt[buckId(num)]++;
}

void peekMedian()
{
    if (ss.empty())
    {
        cout << "Invalid" << endl;
        return;
    }
    int cnt = ss.size() % 2 == 0 ? ss.size() / 2 : (ss.size() + 1) / 2;
    int buckId = 0; //目标数在本桶内
    int cumBcnt = buckCnt[0];
    while (cumBcnt < cnt)
        cumBcnt += buckCnt[++buckId];
    int tmpCnt = cumBcnt - buckCnt[buckId]; //实际num对应的cnt，实际值是：不包括此桶，此桶前面所有桶里有多少数
    int num = buckId * 316 - 1; //实际num, 上一桶的最后一个数
    while (tmpCnt < cnt)
        tmpCnt += appCnt[++num];
    cout << num << endl;
}

int main()
{
    memset(appCnt, 0, sizeof(appCnt));
    memset(appCnt, 0, sizeof(buckCnt));
    cin >> nn;
    while (nn--)
    {
        cin >> cmd;
        if (cmd == "Pop")
        {
            pop();
        }
        if (cmd == "Push")
        {
            cin >> num;
            push(num);
        }
        if (cmd == "PeekMedian")
        {
            peekMedian();
        }
    }
}