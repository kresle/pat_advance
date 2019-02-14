#include <iostream>
// #include <math.h>
#include <vector>
// #include <algorithm>
#include <numeric>
using namespace std;

int nn, kk, pp;

vector<int> tmpAns, ans;
int npp[401];

int maxSum = 0;

bool find(int n, int k, int idx=nn)
{
    if (k==0)
    {
        if (n!=0) return false;
        int tmpSum = accumulate(tmpAns.begin(), tmpAns.end(), 0);
        if (tmpSum > maxSum)
        {
            ans = tmpAns;
            maxSum = tmpSum;
        }

        return true;
    }

    bool findSol = false;
    for(int ii=idx;ii>0;ii--)
    {
        if (npp[ii]>n) continue;
        else
        {
            tmpAns.push_back(ii);
            if (find(n-npp[ii], k-1, ii))
            {
                findSol = true;
            }
            tmpAns.pop_back();
        }
    }
    return findSol;
}

int main(int argc, char const *argv[])
{
    cin >> nn >> kk >> pp;
    fill(npp, npp+nn+1, 1);
    for(int ii=0;ii<=nn;ii++)
    {
        for(int jj=0;jj<pp;jj++)
        {
            npp[ii]*=ii;
        }
        // cerr << npp[ii] << " ";
    }

    int idx = nn;
    while(npp[idx]+kk-1>nn) idx--;

    if (find(nn, kk, idx))
    {
        // sort(ans.rbegin(), ans.rend());
        cout << nn << " = ";
        cout << ans.front() << "^" << pp;
        for(int ii=1;ii<ans.size();ii++)
        {
            cout << " + " << ans[ii] << "^" << pp;
        }
        cout << endl;
    }
    else
    {
        cout << "Impossible" << endl;
    }
    return 0;
}
