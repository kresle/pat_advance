
// 这道题，don't want to 想递推公式，拖了好久，今天也花了很大力气都写出来，确实不擅长搞推导。
// 貌似是有简便方法，待会儿再看。
// 遇到的问题，一开始对前缀0不处理，导致像'001'这样的串也会给出很大的解来。花了很久才找到这个bug。
// 这个bug也是因为下面用了ss.size()来推断pivot的大小。总之不太好。
// 下面的推导公式还是不错的，虽然花了不少时间，但起码写出来了。找到的github上，也有类似自己的思路，不同在于，他直接选的[0,99],[0,999]这样的来记录，自己选的100，1000等等，还要先减1才行。
// 分情况讨论的思想，就是严谨思维，不放过任何一种情况，每一种情况都做对。尽可能减少情况数

#include <iostream>
#include <map>
#include <string>
using namespace std;

int nn;
string ss;
map<int, int> pivotVals;

int oneCnts(string ss)
{
    auto idx = ss.find_first_not_of('0');
    if (idx == ss.npos) return 0;
    ss = ss.substr(idx);

    if (ss.size() == 1)
        return 1;
    int num = stoi(ss);
    if (pivotVals.find(num) != pivotVals.end())
        return pivotVals[num];
    int cnt = 0;
    int pivot = 1;
    for (int ii = 0; ii < ss.size() - 1; ii++)
        pivot *= 10;

    //以361为例
    //pivot==100

    cnt += (ss[0]-'0')*(pivotVals[pivot]-1);    //[0,99],[100,199],[200,299]这些数，除最高位上的1的个数
    cnt += oneCnts(ss.substr(1));               //[300,361]这些数，除最高位上的1的个数==[0,61]
    if (ss[0] == '1')                           //取最高位上1的个数：[100,199]
        cnt += stoi(ss.substr(1))+1;            //[100,1xx]
    else
        cnt += pivot;                           //[100,199]

    return cnt;
}

int main()
{
    int pivot = 1;
    int cnt = 1;
    pivotVals[pivot] = cnt;
    pivot *= 10;
    while (pivot < INT32_MAX && pivot % 10 == 0)
    {
        cnt = (cnt - 1) * 10 + 1 + pivot / 10; //10个是[0,99]..[900,999]这群里的不包括百位的；1是1000；pivot/10是[100,199]这些里百位上的。
        pivotVals[pivot] = cnt;
        pivot *= 10;
    }
    while(cin >> ss)
    {
        cout << oneCnts(ss) << endl;
    }
}