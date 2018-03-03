// -------------------------------------------------------------------------
// This is a test of accessing bits of Array - coded in the DOL style.
// Since this library has a special class for this purpose (BitArray), 
// this approach is not recommended unless you are converting old DOL code.
// The results should be identical with the results of test59 from
// the DOL regression suite, and the results
//  NOTE: The old style where array of int's or char's is treated as
//        an array of bits:                  BinArray<Root,int> bitArr; 
//        The new style, array of bits:      BitArray<Root> bitArr;

// (1) We initial array of integers by some arbitrary numbers, and then
// see that we can access the bits properly.
// (2) We change some of the bits and see what effect it has on the integers.
// (3) We set bits outside of the initial array size, and see that we still
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
    void prt(); // print the current bit array
};


int main(){
    Root *rp; int i,k,sz,cap,incr,*iPtr;

    rp=new Root;
    bitArr.form(rp,3,-2); // initial size=3, increase 2x when needed
    cap=bitArr.capacity(rp);
    sz=bitArr.size(rp);
    incr=bitArr.increment(rp);
    printf("starting: capacity=%d size=%d incr=%d\n",cap,sz,incr);

    // test (1): set some numbers
    printf("TEST 1:\n");
    iPtr=bitArr.ind(rp,0); *iPtr= 34;   // bits 1 and 5
    iPtr=bitArr.ind(rp,1); *iPtr=257;   // bits 32 and 40
    iPtr=bitArr.ind(rp,2); *iPtr= -1;   // all bits from 64 to 95

    // see that the bits are interpreted properly
    rp->prt();

    unsigned char * p=(unsigned char*)bitArr.ind(rp,0);
    for(i=0; i<12; i++, p++)printf("%o ",*p); printf("\n");

    // test (2): change some bits, see the result on the integers
    printf("\nTEST 2:\n");
    printf("\n");
    bitArr.setBit(rp,0,1);
    bitArr.setBit(rp,1,1); // no change really
    bitArr.setBit(rp,40,0);
    bitArr.setBit(rp,94,0);
    bitArr.setBit(rp,95,0);

    rp->prt();

    // test(3): set bits outside of the original range, print values
    printf("\nTEST 3:\n");
    bitArr.setBit(rp,500,1);
    bitArr.setBit(rp,501,0);
    bitArr.setBit(rp,502,1);
    printf("%d",bitArr.getBit(rp,500));
    printf("%d",bitArr.getBit(rp,501));
    printf("%d",bitArr.getBit(rp,502));

    cap=bitArr.capacity(rp);
    sz=bitArr.size(rp);
    incr=bitArr.increment(rp);
    printf(" capacity=%d size=%d incr=%d\n",cap,sz,incr);

    rp->prt();
    bitArr.free(rp);
    delete rp;
    return 0;
}

// ----------------------------------------------------
// Print the current bit array
// ----------------------------------------------------
void Root::prt(){
    int i,k,sz,v;

    sz=bitArr.size(this);
    for(i=0; i<sz; i++){
        for(k=0; k<32; k++){
            v=bitArr.getBit(this,i*32+k);
            printf("%d",v);
        }
        printf("\n");
    }
    printf("\n");
}

#include "gen.cpp"

