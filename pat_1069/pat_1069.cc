#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
using namespace std;

inline int realValue(vector<int>& nums)
{
    return nums[0]*1000+nums[1]*100+nums[2]*10+nums[3];
}
void numToVector(int num, vector<int>& nums)
{
    for(int ii=0;ii<4;ii++)
    {
        nums[3-ii] = num%10;
        num/=10;
    }
}

int main()
{
    vector<int> nums(4);
    int num;
    cin >> num;
    do{
        numToVector(num, nums);
        int n1, n2;
        sort(nums.rbegin(),nums.rend());
        n1 = realValue(nums);
        sort(nums.begin(),nums.end());
        n2 = realValue(nums);
        num = n1-n2;
        printf("%04d - %04d = %04d\n", n1,n2,num);
    }while(num!=6174&&num!=0);
    return 0;
}