#include <iostream.h>
#include "gen.h"

class Widget {
    int val;
public:
    ZZ_Widget ZZds;
    Widget(int i = 0){val=i;}
    void prt(){cout << val <<"\n";}

};

class Holder {
public:
    ZZ_Holder ZZds;
};


int main() {
    wVect::iterator it;
    Holder* hp=new Holder;

    for (int j = 0; j < 10; ++j) {	// insert some Widgets
        wVect::push_back(hp, &Widget(j));
    }

    for(it=wVect::begin(hp); it!=wVect::end(hp); ++it){
        it->prt();
    }
    return 0;
}

#include "gen.cpp"
