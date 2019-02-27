// 差不多22多一点开始写的 ->22:52(AC)
// 不算难吧，就是考细心
// 判断能录取的第二个条件，感觉写得还是不错的。（即与队尾排名相同）
// ranking的写法，判断是否相等那块也还是不错的，不过还是要理解，对于有相等元素的情形，只给定<操作符的排序
// 各学校录取榜的排序也写得不错，
// 就整个学生id什么的转化写得不错，没有用额外的map，而是用sort以后的allstudents内的下标做编号，再用此编号读allstudents对应的学生，再得到其真实编号

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct student
{
    int id;
    int ge, gi, gf;
    int ranking;
    int prefer[5];
    bool operator<(student obj) //要想想，要是给的 < 操作符，对有些pair没法给出正确的值，sort会是什么后果？
    {
        if (gf != obj.gf)
            return gf > obj.gf;
        return ge > obj.ge;
    }
};

int nn, mm, kk;

vector<student> allStudents;
vector<int> quota;
vector<vector<int>> skAdmission;

int main()
{
    cin >> nn >> mm >> kk;
    allStudents.reserve(nn), allStudents.resize(nn);
    quota.resize(mm);
    skAdmission.resize(mm);
    for (int ii = 0; ii < mm; ii++)
        cin >> quota[ii];
    for (int ii = 0; ii < nn; ii++)
    {
        allStudents[ii].id = ii;
        cin >> allStudents[ii].ge >> allStudents[ii].gi;
        allStudents[ii].gf = (allStudents[ii].ge + allStudents[ii].gi) / 2;
        for (int jj = 0; jj < kk; jj++)
            cin >> allStudents[ii].prefer[jj];
    }
    sort(allStudents.begin(), allStudents.end());
    allStudents[0].ranking = 0;
    for (int ii = 1, jj = 0; ii < nn; ii++)
    {
        // if (s1==s2) !s1<s2 && !s2<s1
        if (allStudents[ii - 1] < allStudents[ii]) //不相等，这个判断挺巧妙的。值得回味。不知道自己怎么就写出这么好的代码来了^_^
            jj = ii;
        allStudents[ii].ranking = jj;
    }

    int skid;
    for (int ii = 0; ii < nn; ii++)
        for (int jj = 0; jj < kk; jj++)
        {
            skid = allStudents[ii].prefer[jj];
            if (quota[skid] > 0) //有富余，直接录取
            {
                quota[skid]--;
                skAdmission[skid].push_back(ii);
                break;
            }
            else if (!skAdmission[skid].empty() && allStudents[skAdmission[skid].back()].ranking == allStudents[ii].ranking) //没有富余的情况下，看最后录取的学生的ranking，如果和其相等，那也要录取
            {
                quota[skid]--;
                skAdmission[skid].push_back(ii);
                break;
            }
        }

    for (int ii = 0; ii < mm; ii++)
    {
        sort(skAdmission[ii].begin(), skAdmission[ii].end(), [](int ll, int rr) { return allStudents[ll].id < allStudents[rr].id; });
        if (!skAdmission[ii].empty())
            cout << allStudents[skAdmission[ii][0]].id;
        for (int jj = 1; jj < skAdmission[ii].size(); jj++)
            cout << " " << allStudents[skAdmission[ii][jj]].id;
        cout << endl;
    }
}