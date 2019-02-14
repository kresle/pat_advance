#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int nn, mm;
vector<vector<int>> edge;

int main()
{
    cin >> nn >> mm;
    edge.resize(nn+1, vector<int>(nn+1, -1));
    int st, ed, ll;
    for(int ii=0;ii<mm;ii++)
    {
        cin >> st >> ed >> ll;
        edge[st][ed] = edge[ed][st] = ll;
    }
    int kk;
    cin >> kk;
    int minDist=UINT16_MAX, minId=-1;
    for(int ii=1;ii<=kk;ii++)
    {
        cout << "Path " << ii << ": ";
        int nc, dist=0;
        vector<bool> visited(nn+1, false);visited[0] = true;
        bool invalidPath = false;
        cin >> nc >> st;
        int st_0 = st;

        if (st<=0||st>nn) invalidPath = true;
        visited[st]=true;

        for(int jj=1;jj<nc&&!invalidPath;jj++)
        {
            cin >> ed;
            if (ed<=0||ed>nn||edge[st][ed]==-1) {
                invalidPath = true;
            }
            else{
                dist += edge[st][ed];
                visited[ed] = true;
                st = ed;
            }
        }

        if (invalidPath) {
            cout << "NA (Not a TS cycle)" << endl; 
            continue;
        }
        if (st_0==ed&&find(visited.begin(), visited.end(), false)==visited.end())
        {
            if (dist<minDist)
            {
                minDist = dist;
                minId = ii;
            }
            if (nc==nn+1) {
                cout << dist << " (TS simple cycle)" << endl;
            }
            else{
                cout << dist << " (TS cycle)" << endl;
            }
        }
        else
        {
            cout << dist << " (Not a TS cycle)" << endl;
        }
    }
    cout << "Shortest Dist("<< minId <<") = " << minDist << endl;
    return 0;
}