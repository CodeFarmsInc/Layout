
// -------- data structure DYNAMICALLY ADJUSTABLE ARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class arr_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_arr_ARRAY_INCLUDED
#define ZZ_arr_ARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class arr_ArrayHolder {
public:
    unsigned int sz; // present size
    int num,incr; // higest valid index,increment
    Couple* array;
    arr_ArrayHolder(){ sz=0; num= -1; incr=0; array=NULL;}
};
// NOTE: incr=0 fixed size (attempt to change the size treated as error)
//       incr>0    sz=sz+incr
//       incr<0    sz=sz*(-incr)

// ----------------------------------------------------------

class arr_Array {
protected:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
    static unsigned int maxCapacity;  // upper limit on any array, 0=disabled

    static int sizeChange(Header *hp,const unsigned int newCap,const int exact);
             // exact=1 new size will be exactly newCap, mode=0 grow using incr
    static Couple* indHeap(Header *hp,int i,bck callback); // like ind() but callback
    static void upHeap(cmpType cmpF,Header *hp,int n,bck callback);
    static void downHeap(cmpType cmpF,Header *hp,int n,bck callback);
    static int binSearch(cmpType cmpF,Header *hp,Couple *op,int *found);
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap;}
    static Couple* form(Header *hp,unsigned int const sz,int const incr);
    static int formed(Header *hp);
    static void free(Header *hp);
    static unsigned int capacity(Header *hp);
    static unsigned int size(Header *hp);
    static int increment(Header *hp);
    static Couple get(Header *hp,const unsigned int k);  // a=array[k]
    static void set(Header *hp,const unsigned int k,Couple a); // array[k]=a
    static void extract(Header *hp,const int k);// remove and shrink array
    static void remove(Header *hp,const unsigned int k); // fast but order changed
    static void insert(Header *hp,const int k,Couple *t); 
    static int reduce(Header *hp);             // reduce the array to its used size
    static int reduce(Header *hp,const unsigned int newCap); // capacity to newCap
    static int grow(Header *hp,const unsigned int newCap);
    static void sort(cmpType cmp,Header *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Header *hp,int i1,int i2);
    static Couple* ind(Header *hp,int i);
    static void addOrd(cmpType cmpF,Header *hp,Couple *op);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Header *hp,Couple* e);
    static Couple* pop(Header *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Header *hp,Couple *e,bck callback);
    static int outHeap(cmpType cmpF,Header *hp,Couple *e,bck callback);
    static void updHeap(cmpType cmpF,Header *hp,int n,bck callback);
    static void delHeap(cmpType cmpF,Header *hp,int n,bck callback);

    static Couple* head(Header *hp); //fast way of getting array[0]
    static void reset(Header *hp,int newSz,int incr);
    static void ins(Header *hp,int k,Couple* t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Header *hp,int k){ extract(hp,k); }
    static void delOrd(cmpType cmpF,Header *hp,Couple *obj);
    static int getBit(Header *hp,int i);
    static int setBit(Header *hp,int i,int val);
    static int getOrd(cmpType cmpF,Header *hp,Couple *op,int *found);
};

#endif // ZZ_arr_ARRAY_INCLUDED

