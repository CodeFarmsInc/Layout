// -------------------------------------------------------------------------
// This is a test of classes Bag and/or Uni1toX.
// Look for NOTE to see two places which allow to test different options,
// depending on which line you comment out.
// --------------------------------------------------------------------------

#include <stdio.h>
#include "gen.h"

class Part {     // class under which to store the array
    int id;
public:
    ZZ_Part ZZds;
    Part(){id=0;}
    Part(int i){id=i;}
    void prt(){printf("part=%d\n",id);}
    int getID(){return id;}
};


class Root {     // class under which to store the array
public:
    ZZ_Root ZZds;
    Root();
    ~Root();
    void prt(); // print all Parts
    void eliminate(int partID);
};


// ----------------------------------------------------
// Start with a small initial array for every Root
// ----------------------------------------------------
Root::Root(){
    // NOTE: You can either specify the initial size, or leave it to default
    // myBag::form(this,3,-2); // initial size=3, increase 2x when needed
}

// ----------------------------------------------------
// First destroy all the Parts, then free the array
// ----------------------------------------------------
Root::~Root(){
    Part *p,*first;
    myBag_Iterator it;


    while(myBag::count(this)>0){
        first=NULL;
        p=it.first(this); // pick up the first Part
        myBag::remove(this,p);   // remove all references to it
        delete p;
    }
    myBag::free(this); // remove the internal array
}


// ----------------------------------------------------
// Print the current array
// ----------------------------------------------------
void Root::prt(){
    Part *p;
    myBag_Iterator it;

    for(p=it.first(this); p; p=it.next()){
        p->prt();
    }
}


// ----------------------------------------------------
// Remove and destroy the given part. Since our data 
// organization is a bag, we have to search for the part
// before removing it from the array and then destroying it.
// ----------------------------------------------------
void Root::eliminate(int partID){
    Part *p;

    myBag_Iterator it;

    for(p=it.first(this); p; p=it.next()){
        if(p->getID()==partID)break;
    }
    if(p)myBag::remove(this,p);
    else printf("not in myBag: partID=%d\n",partID);
}
// ----------------------------------------------------
int main(){
    Root *r; Part *p; int i;
    Part** parts=new Part*[11];

    r=new Root;

    // generate parts with id=100,...,110
    for(i=0; i<=10; i++){
        parts[i]=new Part(100+i);
        myBag::add(r,parts[i]);
    }
 
    // add some parts multiple times
    myBag::add(r,parts[0]);
    myBag::add(r,parts[2]);
    myBag::add(r,parts[2]);
    myBag::add(r,parts[0]);
    myBag::add(r,parts[5]);

    // create one additional part without adding it to the array
    p=new Part(99);

    // attempt to remove parts 99, 108 and 100
    r->eliminate(99);
    r->eliminate(108);
    r->eliminate(100);

    // print all the remaining parts
    r->prt();

    // destroy all the data
    delete r;
    return 0;
}

#include "gen.cpp"

