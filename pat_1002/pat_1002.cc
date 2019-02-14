#include <iostream>
#include <vector>
#include <stdio.h>
using namespace std;

int main(int argc, char const *argv[])
{
    vector<float> res(1001, 0);
    int kk, ni, maxN=0;
    float ai;
    while(cin >> kk)
    {
        for(int ii=0;ii<kk;ii++)
        {
            cin >> ni;
            if (ni>maxN) maxN=ni;
            cin >> ai;
            res[ni]+=ai;
        }
    }
    int res_K=0;
    for(int ii=0;ii<=maxN;ii++)
    {
        if (res[ii]>-0.01 && res[ii]<0.01) continue;
        res_K++;
    }
    cout << res_K;
    for(int ii=maxN;ii>=0;ii--)
    {
        if (res[ii]>-0.01 && res[ii]<0.01) continue;
        printf(" %d %.1f", ii, res[ii]);
    }
    return 0;
}
