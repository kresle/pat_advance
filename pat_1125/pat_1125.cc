#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int nn;
    cin >> nn;
    float llen[nn];
    for(int ii=0;ii<nn;ii++) cin >> llen[ii];
    sort(llen, llen+nn);
    float ans=llen[0];
    for(int ii=1;ii<nn;ii++)
    {
        ans = ans/2+llen[ii]/2;
    }
    cout << int(ans) << endl;
}