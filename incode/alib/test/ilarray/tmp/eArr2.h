
// -------- data structure DYNAMICALLY ADJUSTABLE INDEXEDLINKARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class eArr_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_eArr_INDEXEDLINKARRAY_INCLUDED
#define ZZ_eArr_INDEXEDLINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class eArr_IndexedLinkArrayHolder : public eArr_LinkArrayHolder {
};

class eArr_IndexedLinkArrayElement {
public:
    int index; // index back to the array, -1 as unused
    eArr_IndexedLinkArrayElement(){index= -1;}
};

// ----------------------------------------------------------

class eArr_IndexedLinkArray : private eArr_LinkArray {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static void setMaxCap(unsigned int maxCap);
    static int form(Department *hp,unsigned int const cap,int const incr);
    static int formed(Department *hp);
    static void free(Department *hp);
    static unsigned int capacity(Department *hp);
    static unsigned int size(Department *hp);
    static int increment(Department *hp);
    static Employee* get(Department *hp,const unsigned int k);  // a=array[k]
    static void set(Department *hp,const unsigned int k,Employee *a); // array[k]=a
    static void remove(Department *hp,const unsigned int k); // fast but order changed
    static void insert(Department *hp,const int k,Employee *t); 
    static int reduce(Department *hp);             // reduce the array to its used size
    static int reduce(Department *hp,const unsigned int newCap); // reduce size to newSz
    static int grow(Department *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Department *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Department *hp,int i1,int i2); 
    static void reset(Department *hp,int newSz,int incr);
    static void addTail(Department *hp,Employee *a);
    static int getIndex(Employee *e);
    static void init(Department *hp); 
    
    // if this data structure is properly used, this init() is not needed:
    static void init(Employee *e);
};

#endif // ZZ_eArr_INDEXEDLINKARRAY_INCLUDED

