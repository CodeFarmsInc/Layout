
// -------- data structure PARTIALLY SORTED BINARY HEAP ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class bitArr_BitArray 
// ----------------------------------------------------------
#ifndef ZZ_bitArr_BITARRAY_INCLUDED
#define ZZ_bitArr_BITARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class bitArr_BitArrayHolder : public bitArr_ArrayHolder {
public:
    int maxIndex;
    bitArr_BitArrayHolder() : bitArr_ArrayHolder(){maxIndex= -1;}
};

// ----------------------------------------------------------

class bitArr_BitArray : public bitArr_Array {
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap/8+1;}
    static char* form(Root *hp,unsigned int const cap,int const incr);
    static int formed(Root *hp){ return bitArr_Array::formed(hp); }
    static void free(Root *hp){ bitArr_Array::free(hp); }
    static unsigned int size(Root *hp);
    static unsigned int capacity(Root *hp);
    static int increment(Root *hp);

    static int getBit(Root *hp,int i);
    static int setBit(Root *hp,int i,int val);
};

#endif // ZZ_bitArr_BITARRAY_INCLUDED
