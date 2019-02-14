// #include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

int nn, mm;
vector<vector<int>> adj;
set<int> vertexHasEdge;
vector<int> leftV, rightV;

int main(int argc, char const *argv[])
{
    // ios_base::sync_with_stdio(0), cin.tie(0);
    // cin >> nn >> mm;
    scanf("%d %d", &nn, &mm);
    // adj.reserve(nn);
    // adj.resize(nn);
    leftV.reserve(mm), leftV.resize(mm);
    rightV.reserve(mm), rightV.resize(mm);
    int vv, uu;
    for(int ii=0;ii<mm;ii++)
    {
        // cin >> vv >> uu;
        scanf("%d %d", &vv, &uu);
        leftV[ii] = vv;
        rightV[ii] = uu;
        // adj[vv].push_back(uu);
        // adj[uu].push_back(vv);
        // vertexHasEdge.insert(uu);
        // vertexHasEdge.insert(vv);

    }
    int kk, nv;
    // cin >> kk;
    scanf("%d", &kk);
    set<int> cover;
    while(kk--)
    {
        cover.clear();
        // cin >> nv;
        scanf("%d", &nv);
        for(int ii=0;ii<nv;ii++)
        {
            // cin >> vv;
            scanf("%d", &vv);
            cover.insert(vv);
            // for(auto uu: adj[vv])
                // cover.insert(uu);
        }
        // cout << ((cover==vertexHasEdge)?"Yes":"No") << endl;
        bool allIn = true;
        for(int ii=0;ii<mm;ii++)
        {
            if (cover.find(leftV[ii])==cover.end()&&cover.find(rightV[ii])==cover.end())
            {
                allIn = false;
                printf("No\n");
                break;

            }
        }
        if (allIn) printf("Yes\n");
    }
    return 0;
}
