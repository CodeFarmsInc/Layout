#include <iostream.h>
#include "gen.h"

class A;
class B;
class C;

class A {
    int aa;
public:
    ZZ_A ZZds;
    A(int i){aa=i;}
    void prt(void){cout << "A=" << aa << "\n";}
};

class B {
    int bb;
public:
    ZZ_B ZZds;
    B(int i){bb=i;}
    void prt(void){cout << "  B=" << bb << "\n";}
};

class C {
    int cc;
public:
    ZZ_C ZZds;
    C(int i){cc=i;}
    void prt(void){cout << "    C=" << cc << "\n";}
};

// ----------------------------------------------
// definition of the data structures
// one-to-one correspondence with the UML diagram
// ----------------------------------------------
DataStructure Aggregate2<A,B> AtoB;
DataStructure LinkedList2<B,C> BtoC;
// ----------------------------------------------

int main(void){
    int i,k,n;
    // iterators are automatically provided
    AtoB_Iterator itAB;
    BtoC_Iterator itBC;
    A *ap; B *bp; C *cp;
    
    // create test data one A, three B with two C each.
    ap=new A(0);
    n=1; // for marking all objects
    for(i=1;i<=3;i++){
        bp=new B(n); n++;
        AtoB::addTail(ap,bp);
        for(k=1;k<=2;k++){
           cp=new C(n); n++;
           BtoC::addTail(bp,cp);
        }
    }

    // print the data
    ap->prt();
    itAB.start(ap);
    ITERATE(itAB,bp){
        bp->prt();
        itBC.start(bp);
        ITERATE(itBC,cp){
            cp->prt(); 
        }
    }
    return(0);
}

#include "gen.cpp"
