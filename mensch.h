#ifndef MENSCH_H
#define MENSCH_H
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

class mensch {
    int unsigned id;
    string vorname, nachname;
    int unsigned groesse, gewicht, alter;

    public:
    mensch(int id, string vorn, string nachn, int gr, int ge, int al) :
        id(id),
        vorname(vorn),
        nachname(nachn),
        groesse(gr),
        gewicht(ge),
        alter(al)
        {}

    int getId(){
        return id;
    }
    void setVorname(string vorn){
        vorname = vorn;
    } string getVorname(){
        return vorname;
    }
    void setNachname(string nachn){
        nachname = nachn;
    } string getNachname(){
        return nachname;
    }
    void setGroesse(int gr){
        groesse = gr;
    } int getGroesse(){
        return groesse;
    }
    void setGewicht(int ge){
        gewicht = ge;
    } int getGewicht(){
        return gewicht;
    }
    void setAlter(int al){
        alter = al;
    } int getAlter(){
        return alter;
    }

    private:
    void setid(){
        /* CODE */
    }
};

class spieler : public mensch {
    int unsigned staerke, position;

    public:
    spieler(int id, string vorn, string nachn, int gr, int ge, int al,int st, int po) :
        mensch(id, vorn, nachn, gr, ge, al),
        staerke(st),
        position(po)
        {}

    void setStaerke(int st){
        staerke = st;
    } int getStaerke(){
        return staerke;
    }
    void setPosition(int po){
        position = po;
    } int getPosition(){
        return position;
    } string getPositionName(){
        switch(position){
            case 0: return "Torwart";
            case 1: return "Abwehr";
            case 2: return "Mittelfeld";
            case 3: return "Sturm";
            default: return "None";
        }
    }
};

class trainer : public mensch {

};

class arzt : public mensch{

};


#endif // MENSCH_H
