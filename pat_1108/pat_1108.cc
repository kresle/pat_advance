// 19:44 ~ 20:08
// 简单。但在一个判断上出错了，下面有说明，太不细心了。没什么回味价值。

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

int nn;
vector<float> nums;

bool isLegal(string num)
{
    if (num.size()>7) return false;
    int sign = 1, dotCnt=0, dotIdx=num.size();
    if (num[0] == '-')
    {
        sign = -1;
        num = num.substr(1);
    }
    for(int ii=0;ii<num.size();ii++)
    {
        if (!((num[ii]>='0'&&num[ii]<='9')||num[ii]=='.')) return false;
        if (num[ii]=='.') 
        {
            dotCnt++;
            dotIdx = ii;
        }
    }
    if (dotCnt>1 || (dotCnt==1 && num.size()-dotIdx>3)) return false; //原来这里有问题。原来这里不判断是不是有小数点(小数点的位置没有初始化，默认为0)，就直接判断小数点位置与末尾的距离
    if (stof(num)>1000) return false;
    return true;
}

int main()
{
    cin >> nn;
    string num;
    float sum = 0;
    while (nn--)
    {
        cin >> num;
        if (isLegal(num))
        {
            nums.push_back(stof(num));
            sum += nums.back();
        }
        else
            cout << "ERROR: " << num << " is not a legal number" << endl;
    }
    if (!nums.empty())
    {
        if (nums.size()>1)
            printf("The average of %lu numbers is %.2f\n", nums.size(), sum / nums.size());
        else
            printf("The average of 1 number is %.2f\n", sum);
    }
    else
        cout << "The average of 0 numbers is Undefined" << endl;
}