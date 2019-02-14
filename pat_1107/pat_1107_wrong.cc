#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;

int nn;
vector<set<int>> hobNb;
vector<set<int>> ans;
vector<set<int>> peopleHobs;

int main(int argc, char const *argv[])
{
    /* code */
    cin >> nn;
    for(int ii=1;ii<=nn;ii++)
    {
        int kk;
        char cc;
        cin >> kk >> cc;
        int hob;
        set<int> hobs;
        for(int jj=0;jj<kk;jj++)
        {
            cin >> hob;
            hobs.insert(hob);
        }
        for(auto hob: hobs)
        {
            hobNb[hob]+=hobs;
        }
    }
    return 0;
}
