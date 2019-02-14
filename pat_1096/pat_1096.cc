#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<int> prime;
vector<int> result;
int nn;

int main()
{
    cin >> nn;
//     prime.push_back(2);
//     for(int ii=3;ii<=sqrt(nn);ii++)
//     {
//         bool isPrime = true;
//         for(int jj=0;jj<prime.size();jj++)
//         {
//             if (nn%prime[jj]==0)
//             {
//                 isPrime = false;
//                 break;
//             }
//         }
//         if (isPrime) prime.push_back(ii);
//     }
    int ii=1, st=-1;
    for(;ii<nn;ii++) //长度
    {
        bool found = false;
        for(int jj=2;jj<=sqrt(nn)-ii+1;jj++) //起始点。结束点必须是sqrt(nn)-ii+1]，不然pat的过不了。
        {
            int mul=1;
            for(int kk=0;kk<ii;kk++)//连乘
                mul*=(jj+kk);
            if (nn%mul==0) {
                found = true;
                st = jj;
                break;
            }
        }
        if (!found) break;
    }
    if (ii-1>=1)
    {
        cout << (ii-1) << endl;
        cout << st;
        for(int jj=1;jj<ii-1;jj++)
        {
            cout << "*" << st+jj;
        }
    }
    else
    {
        cout << 1 << endl;
        cout << nn;
    }
    
    return 0;
}