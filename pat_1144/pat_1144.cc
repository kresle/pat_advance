#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int nn;
vector<int> nums;

int main(int argc, char const *argv[])
{
    cin >> nn;
    nums.resize(nn, 0);
    int num;
    for(int ii=0;ii<nn;ii++)
    {
        cin >> num;
        if (num<0) continue;
        nums[ii] = num;
    }
    sort(nums.begin(), nums.end());
    int ans = 0, ii=0;
    while(ii<nn&&(nums[ii]==ans||nums[ii]==ans+1))
    {
        if (nums[ii]==ans+1) ans++;
        ii++;
    }
    cout << ans+1;
    return 0;
}
