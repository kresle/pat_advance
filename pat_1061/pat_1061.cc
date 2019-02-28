
// 没难度，就是考阅读理解和细心。没有回味价值
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

string weekRpr[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

bool isWeek(char cc)
{
    return cc >= 'A' && cc <= 'G';
}

bool isHour(char cc)
{
    return (cc >= 'A' && cc <= 'N') || (cc >= '0' && cc <= '9');
}

bool isLower(char cc)
{
    return cc >= 'a' && cc <= 'z';
}

int main(int argc, char const *argv[])
{
    string s0, s1, s2, s3;
    char day = 'Z', hour = 'Z';
    int minute;
    cin >> s0 >> s1 >> s2 >> s3;
    int ii = 0;
    for (; s0[ii] != s1[ii] || !isWeek(s0[ii]); ii++)
        ;
    day = s0[ii++];
    for (; s0[ii] != s1[ii] || !isHour(s0[ii]); ii++)
        ;
    hour = s0[ii];
    for (ii = 0; s2[ii] != s3[ii] || !isalpha(s2[ii]); ii++) //这里题目很明确的说了是english letter,不知道为什么自己之前还是理解成了小写字母
        ;
    minute = ii;
    printf("%s %02d:%02d\n", weekRpr[day - 'A'].c_str(), (hour >= 'A' && hour <= 'N' ? hour - 'A' + 10 : hour - '0'), minute);
    return 0;
}
