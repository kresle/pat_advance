#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int nn;
vector<int> leftId, rightId;
string result;

void postorder(int idx)
{
    if (idx==-1){return;}
    postorder(leftId[idx]);
    postorder(rightId[idx]);
    result.append(to_string(idx)+" ");
}

int main(int argc, char const *argv[])
{
    cin >> nn;
    string cmd;
    int id, pid=-1,root=-1;
    stack<int> st;
    leftId.resize(nn+1, -1);
    rightId.resize(nn+1, -1);
    for(int ii=0;ii<2*nn;ii++)
    {
        cin >> cmd;
        if (cmd=="Push")
        {
            cin >> id;
            if (root==-1) root=id;
            if (pid!=-1)
            {
                if (leftId[pid]==-1) leftId[pid] = id;
                else rightId[pid] = id;
            }
            st.push(id);
            pid = id;
        }
        if (cmd=="Pop")
        {
            pid = st.top();
            st.pop();
        }
    }
    postorder(root);
    cout << result.substr(0,result.size()-1);
    return 0;
}

