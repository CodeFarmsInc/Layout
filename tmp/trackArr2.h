
// -------- data structure DYNAMICALLY ADJUSTABLE INDEXEDLINKARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class trackArr_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_trackArr_INDEXEDLINKARRAY_INCLUDED
#define ZZ_trackArr_INDEXEDLINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class trackArr_IndexedLinkArrayHolder : public trackArr_LinkArrayHolder {
};

class trackArr_IndexedLinkArrayElement {
public:
    int index; // index back to the array, -1 as unused
    trackArr_IndexedLinkArrayElement(){index= -1;}
};

// ----------------------------------------------------------

class trackArr_IndexedLinkArray : private trackArr_LinkArray {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static void setMaxCap(unsigned int maxCap);
    static int form(Layout *hp,unsigned int const cap,int const incr);
    static int formed(Layout *hp);
    static void free(Layout *hp);
    static unsigned int capacity(Layout *hp);
    static unsigned int size(Layout *hp);
    static int increment(Layout *hp);
    static Track* get(Layout *hp,const unsigned int k);  // a=array[k]
    static void set(Layout *hp,const unsigned int k,Track *a); // array[k]=a
    static void remove(Layout *hp,const unsigned int k); // fast but order changed
    static void insert(Layout *hp,const int k,Track *t); 
    static int reduce(Layout *hp);             // reduce the array to its used size
    static int reduce(Layout *hp,const unsigned int newCap); // reduce size to newSz
    static int grow(Layout *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Layout *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Layout *hp,int i1,int i2); 
    static void reset(Layout *hp,int newSz,int incr);
    static void addTail(Layout *hp,Track *a);
    static int getIndex(Track *e);
    static void init(Layout *hp); 
    
    // if this data structure is properly used, this init() is not needed:
    static void init(Track *e);
};

#endif // ZZ_trackArr_INDEXEDLINKARRAY_INCLUDED

