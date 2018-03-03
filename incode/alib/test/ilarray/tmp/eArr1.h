
// -------- data structure DYNAMICALLY ADJUSTABLE LINKARRAY ---------------
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


#ifndef ZZ_eArr_LINKARRAY_INCLUDED
#define ZZ_eArr_LINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class eArr_LinkArrayHolder : public eArr_ArrayHolder {
};

// ----------------------------------------------------------

class eArr_LinkArray : public eArr_Array {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static Employee** form(Department *hp,unsigned int const cap,int const incr);
    static Employee* get(Department *hp,const unsigned int k);  // a=array[k]
    static void set(Department *hp,const unsigned int k,Employee *a); // array[k]=a
    static void insert(Department *hp,const int k,Employee *t); 
    static void sort(cmpType cmp,Department *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Department *hp,int i1,int i2); 
    static Employee** ind(Department *hp,int i);
    static void addOrd(cmpType cmpF,Department *hp,Employee *op);

    static void setMaxCap(unsigned int maxCap);
    static int formed(Department *hp);
    static void free(Department *hp);
    static unsigned int capacity(Department *hp);
    static unsigned int size(Department *hp);
    static int increment(Department *hp);
    static void remove(Department *hp,const unsigned int k); // fast but order changed
    static int reduce(Department *hp);             // reduce the array to its used size
    static int reduce(Department *hp,const unsigned int newCap); // reduce size to newSz
    static int grow(Department *hp,const unsigned int newCap);
    static void reset(Department *hp,int newSz,int incr);
    static void addTail(Department *hp,Employee *a);
    static void init(Department *hp);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Department *hp,Employee* e);
    static Employee* pop(Department *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Department *hp,Employee *e,bck callback);
    static int outHeap(cmpType cmpF,Department *hp,Employee **e,bck callback);

    static Employee** head(Department *hp); // fast way of getting array[0]
    static void ins(Department *hp,int k,Employee* t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Department *hp,Employee *obj);
    static int getOrd(cmpType cmpF,Department *hp,Employee *op,int *found);
};

#endif // ZZ_eArr_LINKARRAY_INCLUDED

