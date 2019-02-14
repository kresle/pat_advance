#include <iostream>
#include <string>
#include <vector>
using namespace std;

string num2eng[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main(int argc, char const *argv[])
{
    string num;
    cin >> num;
    int sum=0;
    for(int ii=0;ii<num.size();ii++) sum+=(num[ii]-'0');
    vector<int> res;
    while(sum!=0)
    {
        res.push_back(sum%10);
        sum/=10;
    }
    if (res.size()==0) res.push_back(0);
    cout << num2eng[res[res.size()-1]];
    for(int ii=res.size()-2;ii>=0;ii--)
    {
        cout << " " << num2eng[res[ii]];
    }
    return 0;
}
