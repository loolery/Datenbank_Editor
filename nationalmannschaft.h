#ifndef NATIONALMANNSCHAFT_H
#define NATIONALMANNSCHAFT_H
#include <cstdio>
#include <vector>
#include <string>
#include <land.h>
using namespace std;

class nationalteam : public land {
    string trainer, cotrainer, arzt;

    public:
    nationalteam(int id, float fl, int ei, string na, string fa, string la, string tr, string cotr, string ar) :
        land(id, fl, ei, na, fa, la),
        trainer(tr),
        cotrainer(cotr),
        arzt(ar)
        {}
    void setTrainer(string tr){
        trainer = tr;
    }string getTrainer(){
        return trainer;
    }
    void setCotrainer(string cotr){
        cotrainer = cotr;
    }string getCotrainer(){
        return cotrainer;
    }
    void setArzt(string ar){
        arzt = ar;
    }string getArzt(){
        return arzt;
    }
};

#endif // NATIONALMANNSCHAFT_H
