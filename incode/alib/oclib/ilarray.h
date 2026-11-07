
// -------- data structure DYNAMICALLY ADJUSTABLE INDEXEDLINKARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_$$_INDEXEDLINKARRAY_INCLUDED
#define ZZ_$$_INDEXEDLINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_IndexedLinkArrayHolder : public $$_LinkArrayHolder {
};

class $$_IndexedLinkArrayElement {
public:
    int index; // index back to the array, -1 as unused
    $$_IndexedLinkArrayElement(){index= -1;}
};

// ----------------------------------------------------------

class $$_IndexedLinkArray : private $$_LinkArray {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static void setMaxCap(unsigned int maxCap);
    static int form($1 *hp,unsigned int const cap,int const incr);
    static int formed($1 *hp);
    static void free($1 *hp);
    static unsigned int capacity($1 *hp);
    static unsigned int size($1 *hp);
    static int increment($1 *hp);
    static $2* get($1 *hp,const unsigned int k);  // a=array[k]
    static void set($1 *hp,const unsigned int k,$2 *a); // array[k]=a
    static void remove($1 *hp,const unsigned int k); // fast but order changed
    static void insert($1 *hp,const int k,$2 *t); 
    static int reduce($1 *hp);             // reduce the array to its used size
    static int reduce($1 *hp,const unsigned int newCap); // reduce size to newSz
    static int grow($1 *hp,const unsigned int newCap);
    static void sort(cmpType cmp,$1 *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,$1 *hp,int i1,int i2); 
    static void reset($1 *hp,int newSz,int incr);
    static void addTail($1 *hp,$2 *a);
    static int getIndex($2 *e);
    static void init($1 *hp); 
    
    // if this data structure is properly used, this init() is not needed:
    static void init($2 *e);
};

#endif // ZZ_$$_INDEXEDLINKARRAY_INCLUDED

