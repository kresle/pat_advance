// 较简单，是比较贱的那种考case的题。同性的时候，可能会出现两者本来就是朋友的情形，这样就要在第一步从各自的同性朋友里交叉组合的时候，
// 就把对方暂时从同性好友里去除掉。
// 此外没任何难度。
// 审题要细心
// 下面friends的使用还是比较巧的，可以多用
// 有个隐藏的失误点，自己没犯：用int读入id，用正负来判断男女时，无法区分-0000和0000，这里自己一开始就用string来读入，恰巧没踩坑，但还是要注意，以后也不要犯

#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

set<int> friends;
set<int> friends_homo[10000];
bool isBoy[10000];

int nn, mm, kk;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> mm;
    string uu, vv;
    int id1, id2;
    fill(isBoy, isBoy + 10000, true);
    for (int ii = 0; ii < mm; ii++)
    {
        cin >> vv >> uu;

        id1 = vv[0] == '-' ? stoi(vv.substr(1)) : stoi(vv);
        isBoy[id1] = vv[0] != '-';

        id2 = uu[0] == '-' ? stoi(uu.substr(1)) : stoi(uu);
        isBoy[id2] = uu[0] != '-';

        friends.insert(id1 * 10000 + id2);
        friends.insert(id2 * 10000 + id1);

        if (isBoy[id1] == isBoy[id2])
            friends_homo[id1].insert(id2), friends_homo[id2].insert(id1);
    }

    vector<pair<int, int>> ans;
    cin >> kk;
    while (kk--)
    {
        ans.clear();
        cin >> vv >> uu;
        id1 = vv[0] == '-' ? stoi(vv.substr(1)) : stoi(vv);
        id2 = uu[0] == '-' ? stoi(uu.substr(1)) : stoi(uu);
        if (isBoy[id1] != isBoy[id2])
        {
            for (auto ff : friends_homo[id1])
                for (auto gg : friends_homo[id2])
                {
                    if (friends.find(ff * 10000 + gg) != friends.end())
                        ans.push_back(make_pair(ff, gg));
                }
        }
        else
        {
            for (auto ff : friends_homo[id1])
            {
                if (ff == id2)
                    continue; //24->AC
                for (auto gg : friends_homo[id2])
                {
                    if (gg == id1)
                        continue; //24->AC
                    if (friends.find(ff * 10000 + gg) != friends.end())
                        ans.push_back(make_pair(ff, gg));
                }
            }
        }
        sort(ans.begin(), ans.end());
        printf("%lu\n", ans.size());
        for (auto pp : ans)
            printf("%04d %04d\n", pp.first, pp.second);
    }
}