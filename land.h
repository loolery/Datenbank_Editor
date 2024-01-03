#ifndef LAND_H
#define LAND_H
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

class land {
    int unsigned landid;
    float flaeche;
    int unsigned einwohner;
    string name, fahne, landkarte;

    public:
    land(int id, float fl, int ei, string na, string fa, string la) :
        landid(id),
        flaeche(fl),
        einwohner(ei),
        name(na),
        fahne(fa),
        landkarte(la)
        {}
    int getLandid(){
        return landid;
    }
    void setFlaeche(float f){
        flaeche = f;
    }float getFlaeche(){
        return flaeche;
    }
    void setEinwohner(int e){
        einwohner = e;
    }int getEinwohner(){
        return einwohner;
    }
    void setFahne(string f){
        fahne = f;
    }string getFahne(){
        return fahne;
    }
    void setLandkarte(string l){
        landkarte = l;
    }string getLandkarte(){
        return landkarte;
    }
    void setName(string ln){
        name = ln;
    }string getName(){
        return name;
    }

};

#endif // LAND_H
