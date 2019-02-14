#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;

// bool isSingle[100000];
int mateId[100000];
set<int> guests;
int nn, mm;

int main(int argc, char const *argv[])
{
    int c1, c2;
    cin >> nn;
    fill(mateId, mateId+100000, -1);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> c1 >> c2;
        mateId[c1] = c2;
        mateId[c2] = c1;
    }
    vector<int> ans;
    cin >> mm;
    while(mm--)
    {
        cin >> c1;
        if (mateId[c1]==-1) ans.push_back(c1);
        else guests.insert(c1);

    }
    for(auto gg: guests)
    {
        if (guests.find(mateId[gg])==guests.end()) ans.push_back(gg);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    if (!ans.empty()) printf("%05d", ans.front());
    for(int ii=1;ii<ans.size();ii++)
    {
        printf(" %05d", ans[ii]);
    }
    return 0;
}
