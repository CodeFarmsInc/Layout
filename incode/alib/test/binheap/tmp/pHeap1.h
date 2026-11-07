
// -------- data structure PARTIALLY SORTED BINARY HEAP ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class pHeap_BinaryHeap
// ----------------------------------------------------------
#ifndef ZZ_pHeap_HEAP_INCLUDED
#define ZZ_pHeap_HEAP_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class pHeap_HeapHolder : public pHeap_ArrayHolder {
public:
    pHeap_HeapHolder() : pHeap_ArrayHolder(){}
};

// ----------------------------------------------------------

class pHeap_BinaryHeap : public pHeap_Array {
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
public:
    static void inHeap(cmpType cmpF,Header *hp,Employee* *e,bck callback){
        pHeap_Array::inHeap(cmpF,hp,e,callback);
    }
    static int outHeap(cmpType cmpF,Header *hp,Employee* *e,bck callback){
        return pHeap_Array::outHeap(cmpF,hp,e,callback);
    }
    static void updHeap(cmpType cmpF,Header *hp,int n,bck callback){
        pHeap_Array::updHeap(cmpF,hp,n,callback);
    }
    static void delHeap(cmpType cmpF,Header *hp,int n,bck callback){
        pHeap_Array::delHeap(cmpF,hp,n,callback);
    }

    static Employee** form(Header *hp,unsigned int const sz,int const incr){
        return pHeap_Array::form(hp,sz,incr);
    }
    static void free(Header *hp){
        pHeap_Array::free(hp);
    }
    static int size(Header *hp){
        return pHeap_Array::size(hp);
    }
    static int capacity(Header *hp){
        return pHeap_Array::capacity(hp);
    }
    static Employee** ind(Header *hp,int i){ return pHeap_Array::ind(hp,i); }
};

#endif // ZZ_pHeap_HEAP_INCLUDED
