#include <iostream>
#include <vector>
#include <set>
using namespace std;

#define NN 

set<int> forbidPairs;
vector<int> shipList;
bool app[100000];

int nn, mm, kk;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    fill(app, app+100000, false);
    cin >> nn >> mm;
    int pa, pb;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> pa >> pb;
        app[pa] = true;
        app[pb] = true;
        forbidPairs.insert(pa*100000+pb);
        forbidPairs.insert(pb*100000+pa);
    }

    for(int ii=0;ii<mm;ii++)
    {
        cin >> kk;
        shipList.clear();
        int id;
        for(int jj=0;jj<kk;jj++)
        {
            cin >> id;
            if (app[id])
            {
                shipList.push_back(id);
            }
        }
        bool safe = true;
        for(int jj=0;jj<shipList.size()&&safe;jj++)
        {
            for(int kk=jj+1;kk<shipList.size()&&safe;kk++)
            {
                if (forbidPairs.find(shipList[jj]*100000+shipList[kk])!=forbidPairs.end())
                {
                    safe = false;
                }
            }
        }
        if (safe)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}