
// -------- data structure DYNAMICALLY ADJUSTABLE LINKARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class hArr_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_hArr_LINKARRAY_INCLUDED
#define ZZ_hArr_LINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class hArr_LinkArrayHolder : public hArr_ArrayHolder {
};

// ----------------------------------------------------------

class hArr_LinkArray : public hArr_Array {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static Employee** form(Header *hp,unsigned int const cap,int const incr);
    static Employee* get(Header *hp,const unsigned int k);  // a=array[k]
    static void set(Header *hp,const unsigned int k,Employee *a); // array[k]=a
    static void insert(Header *hp,const int k,Employee *t); 
    static void sort(cmpType cmp,Header *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Header *hp,int i1,int i2); 
    static Employee** ind(Header *hp,int i);
    static void addOrd(cmpType cmpF,Header *hp,Employee *op);

    static void setMaxCap(unsigned int maxCap);
    static int formed(Header *hp);
    static void free(Header *hp);
    static unsigned int capacity(Header *hp);
    static unsigned int size(Header *hp);
    static int increment(Header *hp);
    static void remove(Header *hp,const unsigned int k); // fast but order changed
    static int reduce(Header *hp);             // reduce the array to its used size
    static int reduce(Header *hp,const unsigned int newCap); // reduce size to newSz
    static int grow(Header *hp,const unsigned int newCap);
    static void reset(Header *hp,int newSz,int incr);
    static void addTail(Header *hp,Employee *a);
    static void init(Header *hp);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Header *hp,Employee* e);
    static Employee* pop(Header *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Header *hp,Employee *e,bck callback);
    static int outHeap(cmpType cmpF,Header *hp,Employee **e,bck callback);

    static Employee** head(Header *hp); // fast way of getting array[0]
    static void ins(Header *hp,int k,Employee* t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Header *hp,Employee *obj);
    static int getOrd(cmpType cmpF,Header *hp,Employee *op,int *found);
};

#endif // ZZ_hArr_LINKARRAY_INCLUDED

