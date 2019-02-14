#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

string weekRpr[] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

bool isLetter(char cc)
{
    return ((cc>='a'&&cc<='z')||(cc>='A'&&cc<='Z'));
}

int main(int argc, char const *argv[])
{
    string s0, s1, s2, s3;
    char day='Z', hour='Z';
    int minute;
    cin >> s0 >> s1 >> s2 >> s3;
    for(int ii=0;ii<min(s0.size(), s1.size())&&hour=='Z';ii++)
    {
        if (s0[ii]!=s1[ii]) continue;
        if (!isLetter(s0[ii])) continue;
        if (day=='Z')
        {
            day = s0[ii];
        }
        else{
            hour = s0[ii];
        }
    }
    for(int ii=0;ii<min(s2.size(), s3.size());ii++)
    {
        if (!isLetter(s2[ii])) continue;
        if (s2[ii]==s3[ii])
        {
            minute = ii;
            break;
        }
    }
    cout << weekRpr[day-'A'] << " " << ((isLetter(hour))?hour-'A'+10:hour-'0') << ":";
    printf("%02d\n", minute);
    return 0;
}

