// 还是因为粗心造成之前没能AC。
// 一是边界写错
// 二是输出顺序有误

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
using namespace std;

bool isStucked[256];
string line;
set<char> normalKeys;
set<char> stuckKeys;

int main()
{
    int kk;
    cin >> kk;
    cin >> line;
    fill(isStucked, isStucked + 256, false);
    int ii = 0;
    for (int ii = 0; ii <= line.size() - kk;) //原来这里的结束条件是<而不是<=，这种小细节，一定要在写的时候就发现，找起来太麻烦了
    // while(ii<line.size()-kk)
    {
        bool isEqual = true;
        for (int jj = ii + 1; jj < ii + kk; jj++)
        {
            if (line[jj] != line[ii])
            {
                isEqual = false;
                break;
            }
        }
        if (isEqual)
        {
            isStucked[line[ii]] = true;
            stuckKeys.insert(line[ii]);
            ii += kk;
        }
        else
        {
            normalKeys.insert(line[ii]);
            ii++;
        }
    }
    for (auto cc : stuckKeys) //修改了排除误认为是stuckedkey的那些情况，就是在别的地方是好的，逻辑上和原来没变
        if (normalKeys.find(cc) != normalKeys.end())
        {
            stuckKeys.erase(cc);
            isStucked[cc] = false;
        }
    for (int ii = 0; ii < line.size(); ii++)
        if (stuckKeys.find(line[ii]) != stuckKeys.end())
        {
            printf("%c", line[ii]);
            stuckKeys.erase(line[ii]);
        }
    printf("\n");

    for (int ii = 0; ii < line.size();)
    {
        printf("%c", line[ii]);
        ii += isStucked[line[ii]] ? kk : 1;
    }
    return 0;
}