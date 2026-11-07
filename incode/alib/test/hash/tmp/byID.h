
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class byID_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_byID_ARRAY_INCLUDED
#define ZZ_byID_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class byID_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    void** array;
    byID_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class byID_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxCapacity;  // upper limit on any array, 0=disabled

    static int sizeChange(Company *hp,const unsigned int newCap,const int exact);
             // exact=1 new size will be exactly newCap, mode=0 grow using incr
    static void** indHeap(Company *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,Company *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,Company *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,Company *hp,void* *op,int *found);
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap;}
    static void** form(Company *hp,unsigned int const sz,int const incr);
    static int formed(Company *hp);
    static void free(Company *hp);
    static unsigned int capacity(Company *hp);
    static unsigned int size(Company *hp);
    static int increment(Company *hp);
    static void* get(Company *hp,const unsigned int k);  // a=array[k]
    static void set(Company *hp,const unsigned int k,void* a); // array[k]=a
    static void extract(Company *hp,const int k);// remove and shrink array
    static void remove(Company *hp,const unsigned int k); // fast but order changed
    static void insert(Company *hp,const int k,void* *t); 
    static int reduce(Company *hp);             // reduce the array to its used size
    static int reduce(Company *hp,const unsigned int newCap); // capacity to newCap
    static int grow(Company *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Company *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Company *hp,int i1,int i2);
    static void** ind(Company *hp,int i);
    static void addOrd(cmpType cmpF,Company *hp,void* *op);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Company *hp,void** e);
    static void** pop(Company *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Company *hp,void* *e,bck callback);
    static int outHeap(cmpType cmpF,Company *hp,void* *e,bck callback);
    static void updHeap(cmpType cmpF,Company *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,Company *hp,int n,bck callback);

    static void** head(Company *hp); //fast way of getting array[0]
    static void reset(Company *hp,int newSz,int incr);
    static void ins(Company *hp,int k,void** t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Company *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,Company *hp,void* *obj);
    static int getBit(Company *hp,int i);
    static int setBit(Company *hp,int i,int val);
    static int getOrd(cmpType cmpF,Company *hp,void* *op,int *found);
};

#endif // ZZ_byID_ARRAY_INCLUDED

