#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;

struct scoreSheet
{
    string id;
    int Gp;
    int Gm;
    int Gf;
    int G;
    scoreSheet(string ss): id(ss), Gp(-1), Gm(-1), Gf(-1), G(0) {};
    bool operator<(scoreSheet obj)
    {
        if (G!=obj.G) return G>obj.G;
        return id<obj.id;
    }
};

int pp, mm, nn;
map<string, scoreSheet*> scores;

int main()
{
    cin >> pp >> mm >> nn;
    string id;
    int score;
    scoreSheet* sheet;
    for(int ii=0;ii<pp;ii++)
    {
        cin >> id >> score;
        sheet = new scoreSheet(id);
        scores[id] = sheet;
        scores[id]->Gp = score;
    }
    for(int ii=0;ii<mm;ii++)
    {
        cin >> id >> score;
        if (scores.find(id)==scores.end())
        {
            sheet = new scoreSheet(id);
            scores[id] = sheet;
        }
        scores[id]->Gm = score;
    }
    for(int ii=0;ii<nn;ii++)
    {
        cin >> id >> score;
        if (scores.find(id)==scores.end())
        {
            sheet = new scoreSheet(id);
            scores[id] = sheet;
        }
        scores[id]->Gf = score;
    }

    vector<scoreSheet*> vScores;
    vScores.reserve(scores.size());
    for(auto ss: scores)
    {
        sheet = ss.second;
        if (sheet->Gm>sheet->Gf)
        {
            if (sheet->Gf!=-1) sheet->G = round(sheet->Gm*0.4+sheet->Gf*0.6);
            else sheet->G = round(sheet->Gm*0.4);
        }
        else{
            sheet->G = sheet->Gf;
        }
        if (sheet->Gp>=200 && sheet->G>=60) vScores.push_back(sheet);
    }
    sort(vScores.begin(), vScores.end(), [] (scoreSheet* ll, scoreSheet* rr) {return *ll<*rr;});
    for(auto ss: vScores)
    {
        // cout << ss->id << " " << ((ss->Gp==0)?-1:ss->Gp) << " " << ((ss->Gm==0)?-1:ss->Gm) << " " << ((ss->Gf==0)?-1:ss->Gf) << " " << ((ss->G==0)?-1:ss->G) << endl;
        cout << ss->id << " " << ss->Gp <<" " << ss->Gm << " " << ss->Gf <<" " <<  ss->G << endl;
    }
    return 0;
}