
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
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


#ifndef ZZ_eArr_ARRAY_INCLUDED
#define ZZ_eArr_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class eArr_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    void** array;
    eArr_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class eArr_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxCapacity;  // upper limit on any array, 0=disabled

    static int sizeChange(Department *hp,const unsigned int newCap,const int exact);
             // exact=1 new size will be exactly newCap, mode=0 grow using incr
    static void** indHeap(Department *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,Department *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,Department *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,Department *hp,void* *op,int *found);
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap;}
    static void** form(Department *hp,unsigned int const sz,int const incr);
    static int formed(Department *hp);
    static void free(Department *hp);
    static unsigned int capacity(Department *hp);
    static unsigned int size(Department *hp);
    static int increment(Department *hp);
    static void* get(Department *hp,const unsigned int k);  // a=array[k]
    static void set(Department *hp,const unsigned int k,void* a); // array[k]=a
    static void extract(Department *hp,const int k);// remove and shrink array
    static void remove(Department *hp,const unsigned int k); // fast but order changed
    static void insert(Department *hp,const int k,void* *t); 
    static int reduce(Department *hp);             // reduce the array to its used size
    static int reduce(Department *hp,const unsigned int newCap); // capacity to newCap
    static int grow(Department *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Department *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Department *hp,int i1,int i2);
    static void** ind(Department *hp,int i);
    static void addOrd(cmpType cmpF,Department *hp,void* *op);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Department *hp,void** e);
    static void** pop(Department *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Department *hp,void* *e,bck callback);
    static int outHeap(cmpType cmpF,Department *hp,void* *e,bck callback);
    static void updHeap(cmpType cmpF,Department *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,Department *hp,int n,bck callback);

    static void** head(Department *hp); //fast way of getting array[0]
    static void reset(Department *hp,int newSz,int incr);
    static void ins(Department *hp,int k,void** t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Department *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,Department *hp,void* *obj);
    static int getBit(Department *hp,int i);
    static int setBit(Department *hp,int i,int val);
    static int getOrd(cmpType cmpF,Department *hp,void* *op,int *found);
};

#endif // ZZ_eArr_ARRAY_INCLUDED

