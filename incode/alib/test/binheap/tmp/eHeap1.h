
// -------- data structure PARTIALLY SORTED BINARY HEAP ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class eHeap_BinaryHeap
// ----------------------------------------------------------
#ifndef ZZ_eHeap_HEAP_INCLUDED
#define ZZ_eHeap_HEAP_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class eHeap_HeapHolder : public eHeap_ArrayHolder {
public:
    eHeap_HeapHolder() : eHeap_ArrayHolder(){}
};

// ----------------------------------------------------------

class eHeap_BinaryHeap : public eHeap_Array {
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
public:
    static void inHeap(cmpType cmpF,Header *hp,Employee *e,bck callback){
        eHeap_Array::inHeap(cmpF,hp,e,callback);
    }
    static int outHeap(cmpType cmpF,Header *hp,Employee *e,bck callback){
        return eHeap_Array::outHeap(cmpF,hp,e,callback);
    }
    static void updHeap(cmpType cmpF,Header *hp,int n,bck callback){
        eHeap_Array::updHeap(cmpF,hp,n,callback);
    }
    static void delHeap(cmpType cmpF,Header *hp,int n,bck callback){
        eHeap_Array::delHeap(cmpF,hp,n,callback);
    }

    static Employee* form(Header *hp,unsigned int const sz,int const incr){
        return eHeap_Array::form(hp,sz,incr);
    }
    static void free(Header *hp){
        eHeap_Array::free(hp);
    }
    static int size(Header *hp){
        return eHeap_Array::size(hp);
    }
    static int capacity(Header *hp){
        return eHeap_Array::capacity(hp);
    }
    static Employee* ind(Header *hp,int i){ return eHeap_Array::ind(hp,i); }
};

#endif // ZZ_eHeap_HEAP_INCLUDED
