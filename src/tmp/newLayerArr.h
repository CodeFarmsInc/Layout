
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class newLayerArr_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_newLayerArr_ARRAY_INCLUDED
#define ZZ_newLayerArr_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class newLayerArr_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    void** array;
    newLayerArr_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class newLayerArr_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxCapacity;  // upper limit on any array, 0=disabled

    static int sizeChange(Layout *hp,const unsigned int newCap,const int exact);
             // exact=1 new size will be exactly newCap, mode=0 grow using incr
    static void** indHeap(Layout *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,Layout *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,Layout *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,Layout *hp,void* *op,int *found);
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap;}
    static void** form(Layout *hp,unsigned int const sz,int const incr);
    static int formed(Layout *hp);
    static void free(Layout *hp);
    static unsigned int capacity(Layout *hp);
    static unsigned int size(Layout *hp);
    static int increment(Layout *hp);
    static void* get(Layout *hp,const unsigned int k);  // a=array[k]
    static void set(Layout *hp,const unsigned int k,void* a); // array[k]=a
    static void extract(Layout *hp,const int k);// remove and shrink array
    static void remove(Layout *hp,const unsigned int k); // fast but order changed
    static void insert(Layout *hp,const int k,void* *t); 
    static int reduce(Layout *hp);             // reduce the array to its used size
    static int reduce(Layout *hp,const unsigned int newCap); // capacity to newCap
    static int grow(Layout *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Layout *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Layout *hp,int i1,int i2);
    static void** ind(Layout *hp,int i);
    static void addOrd(cmpType cmpF,Layout *hp,void* *op);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Layout *hp,void** e);
    static void** pop(Layout *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Layout *hp,void* *e,bck callback);
    static int outHeap(cmpType cmpF,Layout *hp,void* *e,bck callback);
    static void updHeap(cmpType cmpF,Layout *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,Layout *hp,int n,bck callback);

    static void** head(Layout *hp); //fast way of getting array[0]
    static void reset(Layout *hp,int newSz,int incr);
    static void ins(Layout *hp,int k,void** t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Layout *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,Layout *hp,void* *obj);
    static int getBit(Layout *hp,int i);
    static int setBit(Layout *hp,int i,int val);
    static int getOrd(cmpType cmpF,Layout *hp,void* *op,int *found);
};

#endif // ZZ_newLayerArr_ARRAY_INCLUDED

