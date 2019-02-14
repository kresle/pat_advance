#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool toSub[256] {false};

int main()
{
    string S1,S2;
    getline(cin >> ws, S1);
    getline(cin >> ws, S2);
    for(int ii=0;ii<S2.size();ii++)
    {
        toSub[S2[ii]] = true;
    }
    string res;
    for(int ii=0;ii<S1.size();ii++)
    {
        if (!toSub[S1[ii]]) res.push_back(S1[ii]);
    }
    cout << res;
    return 0;
}