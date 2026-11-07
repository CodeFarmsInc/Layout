
// -------- data structure PARTIALLY SORTED BINARY HEAP ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class hHeap_BinaryHeap
// ----------------------------------------------------------
#ifndef ZZ_hHeap_HEAP_INCLUDED
#define ZZ_hHeap_HEAP_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class hHeap_HeapHolder : public hHeap_ArrayHolder {
public:
    hHeap_HeapHolder() : hHeap_ArrayHolder(){}
};

// ----------------------------------------------------------

class hHeap_BinaryHeap : public hHeap_Array {
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
public:
    static void inHeap(cmpType cmpF,Header *hp,PtrEmpl *e,bck callback){
        hHeap_Array::inHeap(cmpF,hp,e,callback);
    }
    static int outHeap(cmpType cmpF,Header *hp,PtrEmpl *e,bck callback){
        return hHeap_Array::outHeap(cmpF,hp,e,callback);
    }
    static void updHeap(cmpType cmpF,Header *hp,int n,bck callback){
        hHeap_Array::updHeap(cmpF,hp,n,callback);
    }
    static void delHeap(cmpType cmpF,Header *hp,int n,bck callback){
        hHeap_Array::delHeap(cmpF,hp,n,callback);
    }

    static PtrEmpl* form(Header *hp,unsigned int const sz,int const incr){
        return hHeap_Array::form(hp,sz,incr);
    }
    static void free(Header *hp){
        hHeap_Array::free(hp);
    }
    static int size(Header *hp){
        return hHeap_Array::size(hp);
    }
    static int capacity(Header *hp){
        return hHeap_Array::capacity(hp);
    }
    static PtrEmpl* ind(Header *hp,int i){ return hHeap_Array::ind(hp,i); }
};

#endif // ZZ_hHeap_HEAP_INCLUDED
