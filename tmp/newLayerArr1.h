
// -------- data structure DYNAMICALLY ADJUSTABLE LINKARRAY ---------------
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


#ifndef ZZ_newLayerArr_LINKARRAY_INCLUDED
#define ZZ_newLayerArr_LINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class newLayerArr_LinkArrayHolder : public newLayerArr_ArrayHolder {
};

// ----------------------------------------------------------

class newLayerArr_LinkArray : public newLayerArr_Array {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static Node** form(Layout *hp,unsigned int const cap,int const incr);
    static Node* get(Layout *hp,const unsigned int k);  // a=array[k]
    static void set(Layout *hp,const unsigned int k,Node *a); // array[k]=a
    static void insert(Layout *hp,const int k,Node *t); 
    static void sort(cmpType cmp,Layout *hp);   // sort the array using qsort
    static void sortSubset(cmpType cmp,Layout *hp,int i1,int i2); 
    static Node** ind(Layout *hp,int i);
    static void addOrd(cmpType cmpF,Layout *hp,Node *op);

    static void setMaxCap(unsigned int maxCap);
    static int formed(Layout *hp);
    static void free(Layout *hp);
    static unsigned int capacity(Layout *hp);
    static unsigned int size(Layout *hp);
    static int increment(Layout *hp);
    static void remove(Layout *hp,const unsigned int k); // fast but order changed
    static int reduce(Layout *hp);             // reduce the array to its used size
    static int reduce(Layout *hp,const unsigned int newCap); // reduce size to newSz
    static int grow(Layout *hp,const unsigned int newCap);
    static void reset(Layout *hp,int newSz,int incr);
    static void addTail(Layout *hp,Node *a);
    static void init(Layout *hp);

    // array as a stack 
    // ------------------------------------------------------------
    static void push(Layout *hp,Node* e);
    static Node* pop(Layout *hp);

    // array as a partially sorted, binary heap
    // -----------------------------------------
    static void inHeap(cmpType cmpF,Layout *hp,Node *e,bck callback);
    static int outHeap(cmpType cmpF,Layout *hp,Node **e,bck callback);

    static Node** head(Layout *hp); // fast way of getting array[0]
    static void ins(Layout *hp,int k,Node* t){insert(hp,k,t);}
    static void delOrd(cmpType cmpF,Layout *hp,Node *obj);
    static int getOrd(cmpType cmpF,Layout *hp,Node *op,int *found);
};

#endif // ZZ_newLayerArr_LINKARRAY_INCLUDED

