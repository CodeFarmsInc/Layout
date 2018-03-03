
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class classes_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_classes_ARRAY_INCLUDED
#define ZZ_classes_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class classes_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    void** array;
    classes_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class classes_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxCapacity;  // upper limit on any array, 0=disabled

    static int sizeChange(Generator *hp,const unsigned int newCap,const int exact);
             // exact=1 new size will be exactly newCap, mode=0 grow using incr
    static void** indHeap(Generator *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,Generator *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,Generator *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,Generator *hp,void* *op,int *found);
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap;}
    static void** form(Generator *hp,unsigned int const sz,int const incr);
    static int formed(Generator *hp);
    static void free(Generator *hp);
    static unsigned int capacity(Generator *hp);
    static unsigned int size(Generator *hp);
    static int increment(Generator *hp);
    static void* get(Generator *hp,const unsigned int k);  // a=array[k]
    static void set(Generator *hp,const unsigned int k,void* a); // array[k]=a
    static void extract(Generator *hp,const int k);// remove and shrink array
    static void remove(Generator *hp,const unsigned int k); // fast but order changed
    static void insert(Generator *hp,const int k,void* *t); 
    static int reduce(Generator *hp);             // reduce the array to its used size
    static int reduce(Generator *hp,const unsigned int newCap); // capacity to newCap
    static int grow(Generator *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Generator *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Generator *hp,int i1,int i2);
    static void** ind(Generator *hp,int i);
    static void addOrd(cmpType cmpF,Generator *hp,void* *op);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Generator *hp,void** e);
    static void** pop(Generator *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Generator *hp,void* *e,bck callback);
    static int outHeap(cmpType cmpF,Generator *hp,void* *e,bck callback);
    static void updHeap(cmpType cmpF,Generator *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,Generator *hp,int n,bck callback);

    static void** head(Generator *hp); //fast way of getting array[0]
    static void reset(Generator *hp,int newSz,int incr);
    static void ins(Generator *hp,int k,void** t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Generator *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,Generator *hp,void* *obj);
    static int getBit(Generator *hp,int i);
    static int setBit(Generator *hp,int i,int val);
    static int getOrd(cmpType cmpF,Generator *hp,void* *op,int *found);
};

#endif // ZZ_classes_ARRAY_INCLUDED

