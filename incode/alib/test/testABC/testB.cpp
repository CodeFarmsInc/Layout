#include <iostream>
using namespace std;
#include "gen.h"

class A;
class B;
class C;
#include "testb.h"
#include "testc.h"

// This function has been expanded to print also all the associated G's

void B::prt(void){
    BtoC_Iterator itBC;
    A *ap; C *cp; 

    ap=AtoB::parent(this); // no action, just to test data structure access

    cout << "  B=" << bb << "\n";
    itBC.start(this);
    ITERATE(itBC,cp){
        cp->prt(); 
    }
};
