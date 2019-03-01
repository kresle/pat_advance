// 没难度，如果考试出现这种题，最多半小时内肯定要搞定。

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int nn, mm;
vector<vector<int>> edge;

int main()
{
    cin >> nn >> mm;
    edge.resize(nn + 1, vector<int>(nn + 1, -1));
    int st, ed, ll, kk;
    for (int ii = 0; ii < mm; ii++)
    {
        cin >> st >> ed >> ll;
        edge[st][ed] = edge[ed][st] = ll;
    }

    cin >> kk;
    int minDist = UINT16_MAX, minId = -1;
    for (int ii = 1; ii <= kk; ii++)
    {
        cout << "Path " << ii << ": ";
        int nc, dist = 0;
        // vector<bool> visited(nn + 1, false);
        set<int> visited;
        bool invalidPath = false;

        cin >> nc >> st;
        int st_0 = st;

        if (st <= 0 || st > nn)
            invalidPath = true;
        visited.insert(st);

        for (int jj = 1; jj < nc; jj++) //原来这里出错了。不管什么情况，都要把这一串读完，不然会影响后面的。原来的失误也太低级了。
        {
            cin >> ed;
            if (ed <= 0 || ed > nn || edge[st][ed] == -1)
            {
                invalidPath = true;
            }
            else
            {
                dist += edge[st][ed];
                visited.insert(ed);
            }
            st = ed;
        }

        if (invalidPath)
        {
            cout << "NA (Not a TS cycle)" << endl;
            continue;
        }
        if (st_0 == ed && visited.size()==nn)   //始末相同，且访问过所有结点
        {
            if (dist < minDist)
            {
                minDist = dist;
                minId = ii;
            }
            if (nc == nn + 1)                   //cycle
            {
                cout << dist << " (TS simple cycle)" << endl;
            }
            else                                // there's some city been visited more than once 
            {
                cout << dist << " (TS cycle)" << endl;
            }
        }
        else
        {
            cout << dist << " (Not a TS cycle)" << endl;
        }
    }
    cout << "Shortest Dist(" << minId << ") = " << minDist << endl;
    return 0;
}