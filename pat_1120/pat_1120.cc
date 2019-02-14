#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int nn;
set<int> sums;

int digitSum(int num)
{
    int sum=0;
    while(num)
    {
        sum+=(num%10);
        num/=10;
    }
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    int num;
    cin >> nn;
    // nums.reserve(nn), nums.resize(nn);
    for(int ii=0;ii<nn;ii++)
    {
        cin >> num;
        sums.insert(digitSum(num));
    }
    vector<int> ans;
    for(auto pp: sums)
    {
        ans.push_back(pp);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    cout << ans.front();
    for(int ii=1;ii<ans.size();ii++)
    {
        cout << " " << ans[ii] ;
    }
    return 0;
}