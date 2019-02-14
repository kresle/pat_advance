#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/**
 * 这道题不难，但要特别注意越界的问题。
 */

int nn, mm;
// bool coins[100000] {false};
int coins[501] {0};

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int tmp;
    cin >> nn >> mm;
    if (mm>1000)
    {
        cout << "No Solution";
        return 0;
    }
    for(int ii=0;ii<nn;ii++) 
    {
        cin >> tmp;
        coins[tmp]++;
    }
    for(int ii=1;ii<=mm/2;ii++)
    {
        if (mm-ii<=500&&coins[ii]&&coins[mm-ii]&&(ii*2!=mm))
        {
            cout << ii << " " << mm-ii;
            return 0;
        }
    }
    if (mm<=1000&&mm%2==0&&coins[mm/2]>=2)
    {
        cout << mm/2 << " " << mm/2;
    }
    else{
        cout << "No Solution";
    }
    return 0;
}
