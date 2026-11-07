
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class bitArr_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_bitArr_ARRAY_INCLUDED
#define ZZ_bitArr_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class bitArr_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    char* array;
    bitArr_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class bitArr_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxCapacity;  // upper limit on any array, 0=disabled

    static int sizeChange(Root *hp,const unsigned int newCap,const int exact);
             // exact=1 new size will be exactly newCap, mode=0 grow using incr
    static char* indHeap(Root *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,Root *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,Root *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,Root *hp,char *op,int *found);
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap;}
    static char* form(Root *hp,unsigned int const sz,int const incr);
    static int formed(Root *hp);
    static void free(Root *hp);
    static unsigned int capacity(Root *hp);
    static unsigned int size(Root *hp);
    static int increment(Root *hp);
    static char get(Root *hp,const unsigned int k);  // a=array[k]
    static void set(Root *hp,const unsigned int k,char a); // array[k]=a
    static void extract(Root *hp,const int k);// remove and shrink array
    static void remove(Root *hp,const unsigned int k); // fast but order changed
    static void insert(Root *hp,const int k,char *t); 
    static int reduce(Root *hp);             // reduce the array to its used size
    static int reduce(Root *hp,const unsigned int newCap); // capacity to newCap
    static int grow(Root *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Root *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Root *hp,int i1,int i2);
    static char* ind(Root *hp,int i);
    static void addOrd(cmpType cmpF,Root *hp,char *op);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Root *hp,char* e);
    static char* pop(Root *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Root *hp,char *e,bck callback);
    static int outHeap(cmpType cmpF,Root *hp,char *e,bck callback);
    static void updHeap(cmpType cmpF,Root *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,Root *hp,int n,bck callback);

    static char* head(Root *hp); //fast way of getting array[0]
    static void reset(Root *hp,int newSz,int incr);
    static void ins(Root *hp,int k,char* t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Root *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,Root *hp,char *obj);
    static int getBit(Root *hp,int i);
    static int setBit(Root *hp,int i,int val);
    static int getOrd(cmpType cmpF,Root *hp,char *op,int *found);
};

#endif // ZZ_bitArr_ARRAY_INCLUDED

