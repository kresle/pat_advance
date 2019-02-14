#include <iostream>
#include <string>
using namespace std;

int main()
{
    string shop, need;
    cin >> shop >> need;
    int beedNums[255] {0};
    int beedNeed[255] {0};
    for(int ii=0;ii<shop.size();ii++) beedNums[shop[ii]]++;
    for(int ii=0;ii<need.size();ii++) beedNeed[need[ii]]++;
    int more=0;
    int less=0;
    for(int ii=0;ii<255;ii++)
    {
        if (beedNums[ii]>beedNeed[ii]) more+=beedNums[ii]-beedNeed[ii];
        if (beedNums[ii]<beedNeed[ii]) less+=beedNeed[ii]-beedNums[ii];
    }
    if (less==0) cout << "Yes " << more;
    else cout << "No " << less;
    return 0;
}