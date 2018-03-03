
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class assemble_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_assemble_ARRAY_INCLUDED
#define ZZ_assemble_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class assemble_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    void** array;
    assemble_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class assemble_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxSz;   // upper limit on any array, 0=disabled

    static int sizeChange(Assembly *hp,const unsigned int newSz,const int exact);
             // exact=1 new size will be exactly newSz, mode=0 grow using incr
    static void** indHeap(Assembly *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,Assembly *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,Assembly *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,Assembly *hp,void* *op,int *found);
public:
    static void setMaxSize(unsigned int maxSize){maxSz=maxSize;}
    static void** form(Assembly *hp,unsigned int const sz,int const incr);
    static int formed(Assembly *hp);
    static void free(Assembly *hp);
    static unsigned int capacity(Assembly *hp);
    static unsigned int size(Assembly *hp);
    static int increment(Assembly *hp);
    static void* get(Assembly *hp,const unsigned int k);  // a=array[k]
    static void set(Assembly *hp,const unsigned int k,void* a); // array[k]=a
    static void extract(Assembly *hp,const int k);// remove and shrink array
    static void remove(Assembly *hp,const unsigned int k); // fast but order changed
    static void insert(Assembly *hp,const int k,void* *t); 
    static int reduce(Assembly *hp);             // reduce the array to its used size
    static int reduce(Assembly *hp,const unsigned int newSz); // reduce size to newSz
    static int grow(Assembly *hp,const unsigned int newSz);
    static void sort(Assembly *hp,cmpType cmp);   // sort the array using qsort
    static void** ind(Assembly *hp,int i);
    static void addOrd(cmpType cmpF,Assembly *hp,void* *op);

    // additional (historical) DOL compatible interface:
    // ------------------------------------------------
    static void sort(cmpType cmp,Assembly *hp){sort(hp,cmp);}

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Assembly *hp,void** e);
    static void** pop(Assembly *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Assembly *hp,void* *e,bck callback);
    static int outHeap(cmpType cmpF,Assembly *hp,void* *e,bck callback);
    static void updHeap(cmpType cmpF,Assembly *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,Assembly *hp,int n,bck callback);

    static void** head(Assembly *hp); //fast way of getting array[0]
    static void reset(Assembly *hp,int newSz,int incr);
    static void ins(Assembly *hp,int k,void** t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Assembly *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,Assembly *hp,void* *obj);
    static int getBit(Assembly *hp,int i);
    static int setBit(Assembly *hp,int i,int val);
    static int getOrd(cmpType cmpF,Assembly *hp,void* *op,int *found);
};

#endif // ZZ_assemble_ARRAY_INCLUDED

