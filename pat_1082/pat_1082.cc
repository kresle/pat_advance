// 感觉可能用了将近两个小时吧
// 感觉写得好丑陋。主要是规则太多。
// 第一次提交，有一个错误，是忘了考虑0的情形。

#include <iostream>
#include <string>
using namespace std;

string pronunciation[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};
string num;

string lt4digitToChinese(string ss)
{
    int num = stoi(ss);
    string res;
    bool midZero = false;
    if (num>=1000) res+= pronunciation[num/1000] + " Qian ";
    num = num - num/1000*1000;
    if (num>=100) res += pronunciation[num/100] + " Bai ";
    else
    {
        if (!res.empty()) res+="ling ", midZero = true;
    }
    num = num - num/100*100;
    if (num>=10) res += pronunciation[num/10] + " Shi ", midZero = false;
    else
    {
        if (!res.empty() && !midZero) res+="ling ", midZero = true;
    }
    num = num - num/10*10;
    if (num>0) res += pronunciation[num];
    if (res.size()>5 && res.substr(res.size()-5,4)=="ling") res = res.substr(0, res.size()-6);
    if (res.back()==' ') res.pop_back();
    return res;
}

string digitToChinese(string ss)
{
    if (ss=="0") return "ling";
    string res;
    if (ss[0] == '-') res = "Fu ", ss = ss.substr(1);

    string ssp[3];
    if (ss.size()>=4) ssp[2] = ss.substr(ss.size()-4), ss = ss.substr(0, ss.size()-4);
    else ssp[2] = ss, ss="";
    if (ss.size()>=4) ssp[1] = ss.substr(ss.size()-4), ss = ss.substr(0, ss.size()-4);
    else ssp[1] = ss, ss="";
    if (ss.size()>0) ssp[0] = ss;

    if (ssp[0].size()>0) res += lt4digitToChinese(ssp[0]) + " Yi ";
    if (res.size()>0 && ssp[1][0]=='0') res+= "ling ";
    if (ssp[1].size()>0) res += lt4digitToChinese(ssp[1]) + " Wan ";
    if (res.size()>0 && res.substr(res.size()-5,4)!="ling" && (ssp[1].back()=='0' || ssp[2][0]=='0')) res += "ling ";
    if (ssp[2].size()>0) res += lt4digitToChinese(ssp[2]);
    
    while (res.back()==' ') res.pop_back();
    
    return res;
}

int main()
{
    cin >> num;
    cout << digitToChinese(num);
}