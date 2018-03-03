
// -------- data structure DYNAMICALLY ADJUSTABLE INDEXEDLINKARRAY ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class floatingNodeArr_Array
// --------------------------------------------------------------------
// Implementation note:
// Internally, this class works with:
//    sz =presently allocated size
//    num=highest valid index of the array (highest index used)
// The external interface conforms to the commonly used parameters of Vectors:
//    capacity=allocated size (capacity=sz)
//    size    =size actually used (size=num+1)
// --------------------------------------------------------------------


#ifndef ZZ_floatingNodeArr_INDEXEDLINKARRAY_INCLUDED
#define ZZ_floatingNodeArr_INDEXEDLINKARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class floatingNodeArr_IndexedLinkArrayHolder : public floatingNodeArr_LinkArrayHolder {
};

class floatingNodeArr_IndexedLinkArrayElement {
public:
    int index; // index back to the array, -1 as unused
    floatingNodeArr_IndexedLinkArrayElement(){index= -1;}
};

// ----------------------------------------------------------

class floatingNodeArr_IndexedLinkArray : private floatingNodeArr_LinkArray {
public:
    typedef int (*cmpType)(const void *, const void *); // compare for sort,heap
    static void setMaxSize(unsigned int maxSize);
    static int form(Layout *hp,unsigned int const sz,int const incr);
    static int formed(Layout *hp);
    static void free(Layout *hp);
    static unsigned int capacity(Layout *hp);
    static unsigned int size(Layout *hp);
    static int increment(Layout *hp);
    static Node* get(Layout *hp,const unsigned int k);  // a=array[k]
    static void set(Layout *hp,const unsigned int k,Node *a); // array[k]=a
    static void remove(Layout *hp,const unsigned int k); // fast but order changed
    static void insert(Layout *hp,const int k,Node *t); 
    static int reduce(Layout *hp);             // reduce the array to its used size
    static int reduce(Layout *hp,const unsigned int newSz); // reduce size to newSz
    static int grow(Layout *hp,const unsigned int newSz);
    static void sort(Layout *hp,cmpType cmp);   // sort the array using qsort
    static void reset(Layout *hp,int newSz,int incr);
    static void addTail(Layout *hp,Node *a);
    static int getIndex(Node *e);
};

#endif // ZZ_floatingNodeArr_INDEXEDLINKARRAY_INCLUDED

