// 喏，就这么简单，不用保存质数列表，也不用做什么优化，直接判断就可以过。
// 自己考试的时候一开始就想的太多，想好好优化，结果反而没优化成，没过。

#include <iostream>
using namespace std;

int nn;

bool isPrime(int nn)
{
    if (nn<2) return false;
    if (nn%2==0) return false;
    for(int ii=3;ii*ii<=nn;ii+=2)
    {
        if (nn%ii==0) return false;
    }
    return true;
}

bool isSexPrime(int nn)
{
    if ((isPrime(nn) && isPrime(nn-6))||(isPrime(nn) && isPrime(nn+6))) return true;
    else return false;
}

int main()
{
    cin >> nn;
    if (isPrime(nn) && isPrime(nn-6)) cout << "Yes\n" << nn-6;
    else if (isPrime(nn) && isPrime(nn+6)) cout << "Yes\n" << nn+6;
    else
    {
        cout << "No" << endl;
        for(int ii=nn+1;;ii++)
            if (isSexPrime(ii))
            {
                cout << ii; 
                break;
            }
    }
}