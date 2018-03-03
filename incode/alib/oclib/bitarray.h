
// -------- data structure PARTIALLY SORTED BINARY HEAP ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_BitArray 
// ----------------------------------------------------------
#ifndef ZZ_$$_BITARRAY_INCLUDED
#define ZZ_$$_BITARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_BitArrayHolder : public $$_ArrayHolder {
public:
    int maxIndex;
    $$_BitArrayHolder() : $$_ArrayHolder(){maxIndex= -1;}
};

// ----------------------------------------------------------

class $$_BitArray : public $$_Array {
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap/8+1;}
    static char* form($1 *hp,unsigned int const cap,int const incr);
    static int formed($1 *hp){ return $$_Array::formed(hp); }
    static void free($1 *hp){ $$_Array::free(hp); }
    static unsigned int size($1 *hp);
    static unsigned int capacity($1 *hp);
    static int increment($1 *hp);

    static int getBit($1 *hp,int i);
    static int setBit($1 *hp,int i,int val);
};

#endif // ZZ_$$_BITARRAY_INCLUDED
