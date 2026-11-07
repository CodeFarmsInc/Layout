
// -------- data structure DYNAMICALLY ADJUSTABLE LINKARRAY ---------------
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


#ifndef ZZ_$$_LINKARRAY_INCLUDED
#define ZZ_$$_LINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_LinkArrayHolder : public $$_ArrayHolder {
};

// ----------------------------------------------------------

class $$_LinkArray : public $$_Array {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static $2** form($1 *hp,unsigned int const cap,int const incr);
    static $2* get($1 *hp,const unsigned int k);  // a=array[k]
    static void set($1 *hp,const unsigned int k,$2 *a); // array[k]=a
    static void insert($1 *hp,const int k,$2 *t); 
    static void sort(cmpType cmp,$1 *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,$1 *hp,int i1,int i2); 
    static $2** ind($1 *hp,int i);
    static void addOrd(cmpType cmpF,$1 *hp,$2 *op);

    static void setMaxCap(unsigned int maxCap);
    static int formed($1 *hp);
    static void free($1 *hp);
    static unsigned int capacity($1 *hp);
    static unsigned int size($1 *hp);
    static int increment($1 *hp);
    static void remove($1 *hp,const unsigned int k); // fast but order changed
    static int reduce($1 *hp);             // reduce the array to its used size
    static int reduce($1 *hp,const unsigned int newCap); // reduce size to newSz
    static int grow($1 *hp,const unsigned int newCap);
    static void reset($1 *hp,int newSz,int incr);
    static void addTail($1 *hp,$2 *a);
    static void init($1 *hp);

    // array as a stack 
    // ------------------------------------------------------------
    static void push($1 *hp,$2* e);
    static $2* pop($1 *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,$1 *hp,$2 *e,bck callback);
    static int outHeap(cmpType cmpF,$1 *hp,$2 **e,bck callback);

    static $2** head($1 *hp); // fast way of getting array[0]
    static void ins($1 *hp,int k,$2* t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,$1 *hp,$2 *obj);
    static int getOrd(cmpType cmpF,$1 *hp,$2 *op,int *found);
};

#endif // ZZ_$$_LINKARRAY_INCLUDED

