#include <iostream>
#include <map>
#include <set>
using namespace std;

struct Item
{
    int id;
    int app;
    Item(int ip) : id(ip), app(1){};
    bool operator<(Item obj)
    {
        if (app != obj.app)
            return app > obj.app;
        return id < obj.id;
    };
};
struct item_cmp
{
    bool operator()(Item *ll, Item *rr)
    {
        return *ll < *rr;
    };
};

int nn, kk;
map<int, Item *> depot;
set<Item *, item_cmp> set_ans;

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> nn >> kk;
    int id;

    for (int ii = 0; ii < nn; ii++)
    {
        cin >> id;

        if (set_ans.size() > 0)
        {
            cout << id << ":";
            int jj = 0;
            for (auto aa = set_ans.begin(); aa != set_ans.end(); aa++)
            {
                if (++jj > kk)
                    break;
                cout << " " << (*aa)->id; // << "[app:" << (*aa)->app << "]";
            }
            cout << endl;
        }

        if (depot.find(id) == depot.end())
        {
            Item *it = new Item(id);
            depot.insert(make_pair(id, it));
        }
        else
        {
            set_ans.erase(depot[id]);
            depot[id]->app++;
        }
        set_ans.insert(depot[id]);
    }
    return 0;
}