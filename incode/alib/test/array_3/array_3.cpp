// --------------------------------------------------------------------
// This is test53 from the DOL regression suite, and the results
// should be identical. 
// It tests sorting an array and then adding and removing objects
// while maintaining the order.
// For this program, codegen must be called with the 'dol' option.
// --------------------------------------------------------------------
#include <stdio.h>
#include "gen.h"

class Header {
public:
    ZZ_Header ZZds;
};

class Entry {
public:
    ZZ_Entry ZZds;
    int  value;
    static int cmp(const void *e1,const void *e2){
        return ((Entry*)e1)->value - ((Entry*)e2)->value;}
};


int main(){
    int side,i,i1,i2,sz,found; Entry e,*ep; Header *hp;

    printf("ORDER TEST:\n");
    hp=new Header;
    myArray.form(hp,200,-2);
    for(i1=0, i2=9, side=0; i2>=i1; side=1-side ){ // load varying values
        if(side==0){i=i1; i1++;}
        else       {i=i2; i2--;}
        e.value=i;
        myArray.addOrd(Entry::cmp,hp,&e);
    }
    sz=myArray.size(hp);
    for(i=0; i<sz; i++){  // print the result
        ep=myArray.ind(hp,i);
        if(ep)printf("%d ",ep->value);
    }
    printf("\n");

    // remove three items
    e.value=7; myArray.delOrd(Entry::cmp,hp,&e);
    e.value=8; myArray.delOrd(Entry::cmp,hp,&e);
    e.value=0; myArray.delOrd(Entry::cmp,hp,&e);
    e.value=3; myArray.delOrd(Entry::cmp,hp,&e);
    sz=myArray.size(hp);
    for(i=0; i<sz; i++){  // print the result
        ep=myArray.ind(hp,i);
        if(ep)printf("%d ",ep->value);
    }
    printf("\n");

    // add a few new entries
    e.value=7; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=6; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=11; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=13; myArray.addOrd(Entry::cmp,hp,&e);
    e.value=10; myArray.addOrd(Entry::cmp,hp,&e);
    sz=myArray.size(hp);
    for(i=0; i<sz; i++){  // print the result
        ep=myArray.ind(hp,i);
        if(ep)printf("%d ",ep->value);
    }
    printf("\n");
    e.value=5; i=myArray.getOrd(Entry::cmp,hp,&e,&found);
    if(found)printf("found value=%d index=%d\n",e.value,i);
    return 0;
}    

#include "gen.cpp"
