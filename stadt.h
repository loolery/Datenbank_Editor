#ifndef STADT_H
#define STADT_H
#include <cstdio>
#include <vector>
#include <string>
#include <land.h>
using namespace std;

class stadt : public land {
    int unsigned stadtid;
    int unsigned stadteinwohner;
    string stadtname, stadtfahne;

    public:
    stadt(int id, float fl, int ei, string na, string fa, string la, int stid, int stei, string stna, string stfa) :
        land(id, fl, ei, na, fa, la),
        stadtid(stid),
        stadteinwohner(stei),
        stadtname(stna),
        stadtfahne(stfa)
        {}
    int getStadtid(){
        return stadtid;
    }
    void setStadteinwohner(int ste){
        stadteinwohner = ste;
    }int getStadteinwohner(){
        return stadteinwohner;
    }
    void setStadtfahne(string stf){
        stadtfahne = stf;
    }string getStadtfahne(){
        return stadtfahne;
    }
    void setStadtname(string stln){
        stadtname = stln;
    }string getStadtname(){
        return stadtname;
    }

};

#endif // STADT_H
