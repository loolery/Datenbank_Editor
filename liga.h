#ifndef LIGA_H
#define LIGA_H
#include <cstdio>
#include <vector>
#include <string>
#include <land.h>
using namespace std;

class liga : public land {
    string liganame;
    int unsigned plaetze, ligarang;

    public:
    liga(int id, float fl, int ei, string na, string fa, string la,string lina, int pl, int lira) :
        land(id, fl, ei, na, fa, la),
        liganame(lina),
        plaetze(pl),
        ligarang(lira)
        {}

    void setLiganame(string lana){
        liganame = lana;
    }string getLiganame(){
        return liganame;
    }
    void setPlaetze(int pl) {
        plaetze = pl;
    }int getPlaetze(){
        return plaetze;
    }
    void setLigarang(int lira){
        ligarang = lira;
    }int getLigarang(){
        return ligarang;
    }

    public:
    int saison_planer(int saison_spieltage[18][9][2], int teams_bundesliga[18]){
        int twechsel, t2wechsel;
        for(int i=0; i<=16; i++){
            twechsel = i;
            for(int ii=0; ii<=8; ii++){
                if(twechsel<17){
                    t2wechsel=twechsel+1;
                }else{
                    t2wechsel=0;
                }
                saison_spieltage[i][ii][0] = teams_bundesliga[twechsel];
                saison_spieltage[i][ii][1] = teams_bundesliga[t2wechsel];
                twechsel++;
                if(twechsel>17){
                    twechsel=0;
                }
            }
        }
        return saison_spieltage[18][9][2];
    }
};

#endif // LIGA_H
