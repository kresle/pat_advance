#include <iostream>
#include <vector>
using namespace std;

int nn;
vector<int> disFrom1;
vector<int> dis;

int distance(int ii, int jj)
{
    // int ii = min(i,j);
    // int jj = max(i,j);
    if (jj>=ii) {return disFrom1[jj]-disFrom1[ii];}
    else{
        return disFrom1[jj]+(disFrom1[nn-1]-disFrom1[ii])+dis[nn-1];
    }
}

int main()
{
    cin >> nn;
    dis.resize(nn);
    for(int ii=0;ii<nn;ii++) cin >> dis[ii];
    disFrom1.resize(nn, 0);
    for(int ii=1;ii<nn;ii++) disFrom1[ii] = disFrom1[ii-1]+dis[ii-1];
    // for(int ii=0;ii<nn;ii++) cout << disFrom1[ii];
    int mm;
    cin >> mm;
    while(mm>0)
    {
        int st, ed;
        cin >> st >> ed;
        st--;ed--;
        cout << min(distance(st,ed), distance(ed,st)) << endl;
        mm--;
    }
    return 0;
}