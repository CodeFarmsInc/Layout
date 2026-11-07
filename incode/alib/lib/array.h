
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
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


#ifndef ZZ_$$_ARRAY_INCLUDED
#define ZZ_$$_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    $2* array;
    $$_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class $$_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxCapacity;  // upper limit on any array, 0=disabled

    static int sizeChange($1 *hp,const unsigned int newCap,const int exact);
             // exact=1 new size will be exactly newCap, mode=0 grow using incr
    static $2* indHeap($1 *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,$1 *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,$1 *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,$1 *hp,$2 *op,int *found);
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap;}
    static $2* form($1 *hp,unsigned int const sz,int const incr);
    static int formed($1 *hp);
    static void free($1 *hp);
    static unsigned int capacity($1 *hp);
    static unsigned int size($1 *hp);
    static int increment($1 *hp);
    static $2 get($1 *hp,const unsigned int k);  // a=array[k]
    static void set($1 *hp,const unsigned int k,$2 a); // array[k]=a
    static void extract($1 *hp,const int k);// remove and shrink array
    static void remove($1 *hp,const unsigned int k); // fast but order changed
    static void insert($1 *hp,const int k,$2 *t); 
    static int reduce($1 *hp);             // reduce the array to its used size
    static int reduce($1 *hp,const unsigned int newCap); // capacity to newCap
    static int grow($1 *hp,const unsigned int newCap);
    static void sort(cmpType cmp,$1 *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,$1 *hp,int i1,int i2);
    static $2* ind($1 *hp,int i);
    static void addOrd(cmpType cmpF,$1 *hp,$2 *op);

    // array as a stack 
    // ------------------------------------------------------------
    static void push($1 *hp,$2* e);
    static $2* pop($1 *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,$1 *hp,$2 *e,bck callback);
    static int outHeap(cmpType cmpF,$1 *hp,$2 *e,bck callback);
    static void updHeap(cmpType cmpF,$1 *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,$1 *hp,int n,bck callback);

    static $2* head($1 *hp); //fast way of getting array[0]
    static void reset($1 *hp,int newSz,int incr);
    static void ins($1 *hp,int k,$2* t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,$1 *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,$1 *hp,$2 *obj);
    static int getBit($1 *hp,int i);
    static int setBit($1 *hp,int i,int val);
    static int getOrd(cmpType cmpF,$1 *hp,$2 *op,int *found);
};

#endif // ZZ_$$_ARRAY_INCLUDED

