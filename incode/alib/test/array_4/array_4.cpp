// -------------------------------------------------------------------------
// This is a test of class BitArray - working with an array of bits
// (for a test similar to the old DOL, see array_5.cpp).

// (1) We set some randomly  selected bits (remaining bits should be 
//     initialized to 0) and print the array.
// (2) Change some bits, and print the array again.
// (2) We set bits outside of the initial array size, and see that we still
//     can access them properly.
//
// WARNING: Results may be different for different hardware architectures,
//          On a PC, integer 5 is represented as 00...101
//                   integer -1               as 11...110
// --------------------------------------------------------------------------

#include <stdio.h>
#include "gen.h"

class Root {     // class under which to store the array
public:
    ZZ_Root ZZds;
    void prtUsed(); // print used part of the array
    void prtBit(int i){
        printf("bit[%d]=%d\n",i,bitArr::getBit(this,i));
    }
};


int main(){
    Root *rp; int sz,cap,incr;

    rp=new Root;
    bitArr::form(rp,100,-2); // initial size=100, increase 2x when needed
    printf("starting: capacity=%d size=%d\n",
                             bitArr::capacity(rp),bitArr::size(rp));

    // test (1): set some bits
    printf("TEST 1:\n");
    bitArr::setBit(rp,1,1);
    bitArr::setBit(rp,5,1);
    bitArr::setBit(rp,32,1);
    bitArr::setBit(rp,40,1);
    bitArr::setBit(rp,41,1);
    bitArr::setBit(rp,42,1);
    bitArr::setBit(rp,44,1);

    rp->prtUsed(); // see that the bits are recorded properly

    // test (2): change some bits
    printf("TEST 2:\n");
    bitArr::setBit(rp,0,1);
    bitArr::setBit(rp,1,1); // no change really
    bitArr::setBit(rp,40,0);
    bitArr::setBit(rp,45,0);// no change really
    bitArr::setBit(rp,46,1);

    rp->prtUsed(); // print the new results

    // test(3): set bits outside of the original range, print values
    printf("TEST 3:\n");
    bitArr::setBit(rp,500,1);
    bitArr::setBit(rp,501,0);
    bitArr::setBit(rp,502,1);

    rp->prtBit(499);
    rp->prtBit(500);
    rp->prtBit(501);
    rp->prtBit(502);

    cap=bitArr::capacity(rp);
    sz=bitArr::size(rp);
    incr=bitArr::increment(rp);
    printf("\ncapacity=%d size=%d incr=%d\n",cap,sz,incr);
    return 0;
}

void Root::prtUsed(){
    int i,k,t,sz; char c;

    // get the size of the used part of the bit array
    sz=bitArr::size(this);

    // print the bits grouped by 8 (as in bytes)
    for(i=k=0; i<sz; i++){
        printf("%d",bitArr::getBit(this,i));
        if(k>=7){printf(" "); k=0;} else k++;
    }
    printf("\n");

    // print markers on bits 10,20,30,...
    for(t=i=k=0; i<sz; i++){
        if(t==0)c='|'; else c=' ';
        printf("%c",c);
        if(t==9)t=0; else t++;

        if(k>=7){printf(" "); k=0;} else k++;
    }
    printf("\n\n");
}

#include "gen.cpp"

