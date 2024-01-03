#ifndef VEREIN_H
#define VEREIN_H
#include <cstdio>
#include <vector>
#include <string>
#include <liga.h>
using namespace std;

class verein : public liga {
    int vereinid;
    string vereinname;
    float vereingeld;

    public:
    verein(int id, float fl, int ei, string na, string fa, string la,string lina, int pl, int lira, int tid, string tna, float tge) :
        liga(id, fl, ei, na, fa, la, lina, pl, lira),
        vereinid(tid),
        vereinname(tna),
        vereingeld(tge)
        {}

    void setVereinId(int tid){
        vereinid = tid;
    } int getvereinid(){
        return vereinid;
    }
    void setVereinName(int tna){
        vereinname = tna;
    } string getvereinname(){
        return vereinname;
    }
    void setVereinGeld(float tge){
        vereingeld = tge;
    } float getvereingeld(){
        return vereingeld;
    }
};

#endif // VEREIN_H
