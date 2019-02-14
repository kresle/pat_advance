#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

bool isStucked[256];
string line;

int main()
{
    int kk;
    cin >> kk;
    cin >> line;
    fill(isStucked, isStucked+256, false);
    int ii=0;
    for(int ii=0;ii<line.size()-kk;)
    // while(ii<line.size()-kk)
    {
        bool isEqual = true;
        for(int jj=ii+1;jj<ii+kk;jj++)
        {
            if (line[jj]!=line[ii])
            {
                isEqual = false;
                break;
            }
        }
        if (isEqual)
        {
            isStucked[line[ii]] = true;
            ii+=kk;
        }
        else
        {
            ii++;
        }
    }
    for(int ii=0;ii<line.size()-1;)
    {
        if (!isStucked[line[ii]]) 
        {
            ii++;
            continue;
        }
        bool isEqual = true;
        for(int jj=ii+1;jj<ii+kk&&jj<line.size();jj++)
        {
            if (line[jj]!=line[ii])
            {
                isEqual = false;
                break;
            }
        }
        if (isEqual){
            ii+=kk;
        }
        else
        {
            isStucked[line[ii]] = false;
        }
    }
    for(int ii=0;ii<256;ii++)
    if (isStucked[ii]) printf("%c", ii);
    cout << endl;
    for(int ii=0;ii<line.size();)
    {
        printf("%c", line[ii]);
        if (isStucked[line[ii]])
        {
            ii+=kk;
        }
        else
        {
            ii++;
        }
    }
    cout << endl;
    return 0;
}