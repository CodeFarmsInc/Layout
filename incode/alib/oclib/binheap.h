
// -------- data structure PARTIALLY SORTED BINARY HEAP ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_BinaryHeap
// ----------------------------------------------------------
#ifndef ZZ_$$_HEAP_INCLUDED
#define ZZ_$$_HEAP_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_HeapHolder : public $$_ArrayHolder {
public:
    $$_HeapHolder() : $$_ArrayHolder(){}
};

// ----------------------------------------------------------

class $$_BinaryHeap : public $$_Array {
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    typedef void (*bck)(void *, int); // callback function for heap operations
public:
    static void inHeap(cmpType cmpF,$1 *hp,$2 *e,bck callback){
        $$_Array::inHeap(cmpF,hp,e,callback);
    }
    static int outHeap(cmpType cmpF,$1 *hp,$2 *e,bck callback){
        return $$_Array::outHeap(cmpF,hp,e,callback);
    }
    static void updHeap(cmpType cmpF,$1 *hp,int n,bck callback){
        $$_Array::updHeap(cmpF,hp,n,callback);
    }
    static void delHeap(cmpType cmpF,$1 *hp,int n,bck callback){
        $$_Array::delHeap(cmpF,hp,n,callback);
    }

    static $2* form($1 *hp,unsigned int const sz,int const incr){
        return $$_Array::form(hp,sz,incr);
    }
    static void free($1 *hp){
        $$_Array::free(hp);
    }
    static int size($1 *hp){
        return $$_Array::size(hp);
    }
    static int capacity($1 *hp){
        return $$_Array::capacity(hp);
    }
    static $2* ind($1 *hp,int i){ return $$_Array::ind(hp,i); }
};

#endif // ZZ_$$_HEAP_INCLUDED
