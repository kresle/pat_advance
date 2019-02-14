#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
using namespace std;

int main(int argc, char const *argv[])
{
    int sum;
    int A[3],B[3],res[3];
    char tmp;
    cin >> A[0] >> tmp >> A[1] >> tmp >> A[2];
    cin >> B[0] >> tmp >> B[1] >> tmp >> B[2];
    sum = A[2]+B[2];
    res[2] = sum%29;
    sum/=29;
    sum+=(A[1]+B[1]);
    res[1] = sum%17;
    sum/=17;
    sum+=(A[0]+B[0]);
    res[0]=sum;
    printf("%d.%d.%d",res[0],res[1],res[2]);
    return 0;
}
