#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int nn;
vector<int> nums;
vector<bool> biggerThanAllLeft, smallerThanAllRight;

int main(int argc, char const *argv[])
{
    cin >> nn;
    nums.reserve(nn);
    nums.resize(nn);
    biggerThanAllLeft.reserve(nn);
    biggerThanAllLeft.resize(nn, false);
    biggerThanAllLeft.front() = true;
    smallerThanAllRight.reserve(nn);
    smallerThanAllRight.resize(nn, false);
    smallerThanAllRight.back() = true;
    for(int ii=0;ii<nn;ii++) cin >> nums[ii];
    int biggestLeft = nums.front(), smallestRight = nums.back();
    for(int ii=1;ii<nn;ii++)
    {
        if (nums[ii]>biggestLeft)
        {
            biggerThanAllLeft[ii] = true;
            biggestLeft = nums[ii];
        }
        else{
            biggerThanAllLeft[ii] = false;
        }
    }
    for(int ii=nn-2;ii>=0;ii--)
    {
        if (nums[ii]<smallestRight)
        {
            smallerThanAllRight[ii] = true;
            smallestRight = nums[ii];
        }
        else{
            smallerThanAllRight[ii] = false;
        }
    }
    vector<int> ans;
    for(int ii=0;ii<nn;ii++)
    {
        if (smallerThanAllRight[ii]&&biggerThanAllLeft[ii])
        {
            ans.push_back(nums[ii]);
        }
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << endl;
    if (!ans.empty()) cout << ans.front();
    for(int ii=1; ii< ans.size(); ii++)
    {
        cout << " " << ans[ii];
    }
    cout << endl;
    return 0;
}
