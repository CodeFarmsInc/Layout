
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class $$_Aggregate :
//                                   public $$_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_$$_AGGREGATE2_INCLUDED
#define ZZ_$$_AGGREGATE2_INCLUDED

class $1;
class $2;

// description of the cooperating classes
class $$_Aggregate2Parent : public $$_LinkedList2Parent {
public:
    $$_Aggregate2Parent() : $$_LinkedList2Parent(){ }
};

class $$_Aggregate2Child : public $$_LinkedList2Child {
public:
    $1* parent;
    $$_Aggregate2Child() : $$_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class $$_Aggregate2ParentAggregate2Child 
       : public $$_LinkedList2ParentLinkedList2Child {
public:
    $1* parent;
    $$_Aggregate2ParentAggregate2Child()
       : $$_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class $$_Aggregate2 : public $$_LinkedList2 {

public:
    static void addHead($1 *p, $2 *c);
    static void addTail($1 *p, $2 *c);
    static void append($2 *c1, $2 *c2); // has a different syntax
    static void insert($2 *c1, $2 *c2); 
    static void remove($2 *c);             // has a different syntax
    static $1* const parent($2 *c);    // is new
    static $2* const next($2 *c){ // returns NULL when s is the tail
        return $$_LinkedList2::next(parent(c),c);
    }
    static $2* const prev($2 *c){ // returns NULL when s is the head
        return $$_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class $$_Aggregate2Iterator : public $$_LinkedList2Iterator {
};

#endif // ZZ_$$_AGGREGATE2_INCLUDED

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

// -------- data structure PARTIALLY SORTED BINARY HEAP ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_BitArray 
// ----------------------------------------------------------
#ifndef ZZ_$$_BITARRAY_INCLUDED
#define ZZ_$$_BITARRAY_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_BitArrayHolder : public $$_ArrayHolder {
public:
    int maxIndex;
    $$_BitArrayHolder() : $$_ArrayHolder(){maxIndex= -1;}
};

// ----------------------------------------------------------

class $$_BitArray : public $$_Array {
public:
    static void setMaxCap(unsigned int maxCap){maxCapacity=maxCap/8+1;}
    static char* form($1 *hp,unsigned int const cap,int const incr);
    static int formed($1 *hp){ return $$_Array::formed(hp); }
    static void free($1 *hp){ $$_Array::free(hp); }
    static unsigned int size($1 *hp);
    static unsigned int capacity($1 *hp);
    static int increment($1 *hp);

    static int getBit($1 *hp,int i);
    static int setBit($1 *hp,int i,int val);
};

#endif // ZZ_$$_BITARRAY_INCLUDED

// -------- data structure DOUBLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class $$_DoubleLink 
// ---------------------------------------------------
#ifndef ZZ_$$_DOUBLE_LINK_INCLUDED
#define ZZ_$$_DOUBLE_LINK_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_DoubleLinkParent : public $$_SingleLinkParent {
public:
    $$_DoubleLinkParent() : $$_SingleLinkParent(){};
};

class $$_DoubleLinkChild : $$_SingleLinkChild {
public:
    $1* linkFrom;
    $$_DoubleLinkChild(){linkFrom=NULL;}
};

// The following class is used when Parent==Child
class $$_DoubleLinkParentDoubleLinkChild :
                             $$_SingleLinkParentSingleLinkChild {
public:
    $1* linkFrom;
    $$_DoubleLinkParentDoubleLinkChild() :
             $$_SingleLinkParentSingleLinkChild(){ linkFrom=NULL; }
};
// ----------------------------------------------------------

class $$_DoubleLink {

public:
    static void add($1 *p,$2 *c);
    static void remove($1 *p);
    static $2* const target($1 *p);
    static $1* const source($2 *p);

    // historical DOL and other interfaces
    static void del($1 *p){ remove(p); }
    static $2* const fwd($1 *p){ return target(p); }
    static $2* const next($1 *p){ return target(p); }
    static $1* const bwd($2 *p){ return source(p); }
};
    
#endif // ZZ_$$_DOUBLE_LINK_INCLUDED
#include <stdio.h>

// Only some classes in this library have ++ or -- operators,
// This style of traversal is left in the library for historical
// reasons, mostly because codegen uses it internally.

#define ITERATE(IT,X) for(X= ++IT; X; X= ++IT)
#define RETRACE(IT,X) for(X= --IT; X; X= --IT)

// We recommended you to use the 'from' and 'next' methods
// when traversing the data. It is more direct, and the interface is
// the same in voth C++ and in Java:

//    id_Iterator it;
//    for(c=it.fromHead(p); !c; c=it.next()){...}

// On the other hand, if you like the ITERATE and RETRACE macros
// and/or the use of operators ++ and --, it is easy to code
// these operators using the existing functions such as fromHead() and next().
// For an example of how to do that, look at the code of the iterator
// in aggreg2.h and aggreg2.cpp in this directory.

// -------- data structure HASH TABLE ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_Hash 
// ----------------------------------------------------------
#ifndef ZZ_$$_HASH1_INCLUDED
#define ZZ_$$_HASH1_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_HashHolder : public $$_ArrayHolder {
public:
    int count; // population count
    $$_HashHolder() : $$_ArrayHolder(){count=0;}
};

class $$_HashElement {
public:
    $2* next; // ring of elements in the same bucket
    $$_HashElement(){next=NULL;}
};


class $$_Hash : public $$_Array {
public:
    static void** form($1 *hp,int const sz);
    static int formed($1 *hp){ return $$_Array::formed(hp); }
    static int size($1 *hp, int *popCount);
    static void free($1 *hp);
    static int resize($1 *hp, int newSz);
    static $2* get($1 *hp, $2 *obj); // obj = temp.object with the required key
    static int add($1 *hp, $2 *obj); // obj = object to load into the hash table
    static $2* remove($1 *hp, $2 *obj); 
            // obj = object with the key to be removed or the object itself

    // functions that must be provided by the application
    // --------------------------------------------------
    static int cmp($2 *p1,$2 *p2); // return 0 if the objects have the same key
    static int hash($2 *p,int hashSz); // converts key to the bucket number

    // convenient functions to use when coding hash()
    // --------------------------------------------------
    static int hashString(char *s,int hashSz);
    static int hashInt(int val,int hashSz);

    // historical DOL interface
    // --------------------------------------------------
    static $2* del($1 *hp, $2 *obj){return remove(hp,obj);}
    static $2* slot($1 *hp, int i);
    static int ZZhashString(char *s,int hashSz){return hashString(s,hashSz);}
    static int ZZhashInt(int val,int hashSz){return hashInt(val,hashSz);}
};


class $$_HashIterator {
    int all; // 1=all buckets, 0=just one given bucket
    int bucket;
    $2 *tail;
    $2 *nxt;
    $1 *holder;
public:
    $$_HashIterator(){all=0; bucket= -1; nxt=NULL; holder=NULL;}

    // standard iterator interface:   for(p=it.first(hp,i); p; p=it.next()){...}
    // -----------------------------------------------------------------
    $2* first($1 *hp,int i);  // traverse bucket i, for i<0 traverse all buckets
    $2* const next();

    // historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
    // -----------------------------------------------------------------
    void start($2 *p){tail=p; nxt=NULL; all=bucket=0; holder=NULL;}
    $2* const operator++();
    $$_HashIterator($2 *p){start(p);}
};

#endif // ZZ_$$_HASH1_INCLUDED

// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class $$_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_$$_LINKED_LIST1_INCLUDED
#define ZZ_$$_LINKED_LIST1_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_LinkedList1Parent {
public:
    $2* tail;
    $$_LinkedList1Parent(){ tail=NULL; }
};

class $$_LinkedList1Child : public $$_Ring1Element {
public:
    $$_LinkedList1Child() : $$_Ring1Element(){ }
};

// the following class is used when Parent==Child
class $$_LinkedList1ParentLinkedList1Child : public $$_Ring1Element {
public:
    $2* tail;
    $$_LinkedList1ParentLinkedList1Child() : $$_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class $$_LinkedList1 : $$_Ring1 {

public:
    static $2 *tail($1 *p);
    static $2 *head($1 *p);
    static void addHead($1 *p, $2 *c);
    static void addTail($1 *p, $2 *c);
    static void append($1 *p,$2 *c1, $2 *c2);
    static void remove($1 *p, $2 *c);
    static $2* const next($1 *p,$2 *c);
    static $2* const nextRing($2 *c);
    static void sort(ZZsortFun cmpFun, $1 *p);
    static void merge($2 *s,$2 *t,$1 *p);
    static void setTail($1* p,$2* c,int check);

    // historical DOL compatible interface
    static void del($1 *p, $2 *c){ remove(p,c);}
    static void add($1 *p, $2 *c){ addHead(p,c);}
    static $2* child($1 *p);
    static void set($1* p,$2* c){ setTail(p,c,0);}
    static $2* const fwd($2 *c){ return nextRing(c);}
};

class $$_LinkedList1Iterator : public $$_Ring1Iterator {
public:
    $$_LinkedList1Iterator() : $$_Ring1Iterator(){}
    $$_LinkedList1Iterator(const $1 *p) : $$_Ring1Iterator(){start(p);}
    void start(const $1 *p);
    $2* fromHead($1 *p);
};
    
#endif // ZZ_$$_LINKED_LIST1_INCLUDED

// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class $$_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_$$_LINKED_LIST2_INCLUDED
#define ZZ_$$_LINKED_LIST2_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_LinkedList2Parent {
public:
    $2* tail;
    $$_LinkedList2Parent(){ tail=NULL; }
};

class $$_LinkedList2Child : public $$_Ring2Element {
public:
    $$_LinkedList2Child() : $$_Ring2Element(){ }
};

// the following class is used when Parent==Child
class $$_LinkedList2ParentLinkedList2Child : public $$_Ring2Element {
public:
    $2* tail;
    $$_LinkedList2ParentLinkedList2Child() : $$_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class $$_LinkedList2 : $$_Ring2 {

public:
    static $2* const tail($1 *p);
    static $2* const head($1 *p);
    static void addHead($1 *p, $2 *c);
    static void addTail($1 *p, $2 *c);
    static void append($1 *p,$2 *c1, $2 *c2);
    static void insert($2 *c1, $2 *c2);
    static void remove($1 *p, $2 *c);
    static $2* const next($1 *p, $2 *c);
    static $2* const prev($1 *p, $2 *c);
    static $2* const nextRing($2 *c);
    static $2* const prevRing($2 *c);
    static void sort(ZZsortFun cmpFun, $1 *p);
    static void merge($2 *s,$2 *t,$1 *p);
    static void setTail($1* p,$2* c,int check);

    // historical DOL compatible interface
    static void del($1 *p, $2 *c) { remove(p,c); }
    static void add($1 *p, $2 *c) { addHead(p,c);}
    static void ins($2 *c1, $2 *c2) { insert(c1,c2); }
    static $2* child($1* p);
    static void set($1* p,$2* c){ setTail(p,c,0);}
    static $2* const fwd($2 *c){return nextRing(c);}
    static $2* const bwd($2 *c){return prevRing(c);}
};

class $$_LinkedList2Iterator : public $$_Ring2Iterator {
public:
    $$_LinkedList2Iterator() : $$_Ring2Iterator(){}
    $$_LinkedList2Iterator(const $1 *p) : $$_Ring2Iterator(){ start(p); }
    void start(const $1 *p);
    $2* fromHead($1 *p);
    $2* fromTail($1 *p);
};
    
#endif // ZZ_$$_LINKED_LIST2_INCLUDED
#ifndef ZZ_$$_NAME_INCLUDED
#define ZZ_$$_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class $$_Name {
// ----------------------------------------------------------

class $1;

// description of the cooperating classes
class $$_NameParent {
public:
    char* name;
    $$_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class $$_Name {

public:
    static void add($1 *p, char *c);     // add link to
    static void addNew($1 *p, char *c);  // allocate string, add link
    static char* get($1 *p);
    static char* remove($1 *p);
    static int compare($1 *p1,$1 *p2);
    // ...
    // historical DOL interface
    static char* del($1 *p){char* s=get(p); remove(p); return s;}
    static char* fwd($1 *p){return get(p);}
};
    
#endif // ZZ_$$_NAME_INCLUDED

// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class $$_Ring1
// ----------------------------------------------------------
#ifndef ZZ_$$_RING1_INCLUDED
#define ZZ_$$_RING1_INCLUDED

class $1;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Ring1Element {
public:
    $1 *next;
    $$_Ring1Element(){ next=NULL; }
};

class $$_Ring1 {

public:
    // standard interface
    static $1* addHead($1 *tail, $1 *c); // returns new tail
    static $1* addTail($1 *tail, $1 *c); // returns new tail
    static $1* append($1 *tail,$1 *c1, $1 *c2); // returns new tail
    static $1* remove($1 *tail, $1 *c);  // returns new tail, NULL when empty
    static $1* const next($1 *p, $1 *c); // returns NULL when p is tail
    static $1* const nextRing($1 *c); // unprotected raw ring pointer
    static $1* sort(ZZsortFun cmpFun, $1 *tail); // returns the new tail
    static void merge($1 *s,$1 *t);

    // historical DOL compatible interface
    static $1* del($1 *tail, $1 *c) { return remove(tail,c); }
    static $1* add($1 *tail, $1 *c) { return addHead(tail,c); }
    static $1* const fwd($1 *c){ return nextRing(c);}
};

class $$_Ring1Iterator {
    $1 *tail; // NULL when loop finished
    $1 *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    $$_Ring1Iterator(){tail=nxt=NULL;}
    $1* fromHead($1 *p);
    $1* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start($1 *p);
    $1* const operator++();
    $$_Ring1Iterator($1 *p){start(p);}
};
    
#endif // ZZ_$$_RING1_INCLUDED

// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class $$_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_$$_RING2_INCLUDED
#define ZZ_$$_RING2_INCLUDED

class $1;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Ring2Element {
public:
    $1 *next;
    $1 *prev;
    $$_Ring2Element(){ next=prev=NULL; }
};

class $$_Ring2 {

    static int debugFun($1 *tail);
public:
    // standard interface
    static $1* addHead($1 *tail, $1 *c); // returns new tail
    static $1* addTail($1 *tail, $1 *c); // returns new tail
    static $1* append($1 *tail,$1 *c1, $1 *c2); // returns new tail
    static void insert($1 *c1, $1 *c2); // insert c1 before c2
    static $1* remove($1 *tail, $1 *c);  // returns new tail, NULL when empty
    static $1* const next($1 *p, $1 *c); // returns NULL when p is the tail
    static $1* const prev($1 *p, $1 *c); // returns NULL when p is the head
    static $1* const nextRing($1 *c); // next in the ring
    static $1* const prevRing($1 *c); // previous in the ring
    static $1* sort(ZZsortFun cmpFun, $1 *tail); // returns the new tail
    static void merge($1 *s,$1 *t);

    // historical DOL compatible interface
    static $1* del($1 *tail, $1 *c) { return remove(tail,c); }
    static $1* add($1 *tail, $1 *c) { return addHead(tail,c); }
    static void ins($1 *c1, $1 *c2) { insert(c1,c2); }
    static $1* const fwd($1 *c){return nextRing(c);}
    static $1* const bwd($1 *c){return prevRing(c);}
    
};

class $$_Ring2Iterator {
    $1 *tail; // NULL when loop finished
    $1 *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    $$_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    $1* fromHead($1 *p);
    virtual $1* fromTail($1 *p);
    virtual $1* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start($1 *p);
    $1* const operator++();
    $1* const operator--();
    $$_Ring2Iterator($1 *p){start(p);}
};
    
#endif // ZZ_$$_RING2_INCLUDED

// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class $$_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_$$_SINGLE_LINK_INCLUDED
#define ZZ_$$_SINGLE_LINK_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_SingleLinkParent {
public:
    $2* linkTo;
    $$_SingleLinkParent(){ linkTo=NULL; }
};

class $$_SingleLinkChild {
};

// The following class is used when Parent==Child
class $$_SingleLinkParentSingleLinkChild {
public:
    $2* linkTo;
    $$_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class $$_SingleLink {

public:
    static void add($1 *p,$2 *c);
    static void remove($1 *p);
    static $2* const target($1 *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del($1 *p){ remove(p); }
    static $2* const fwd($1 *p){ return target(p); }
    static $2* const next($1 *p){ return target(p); }
};
    
#endif // ZZ_$$_SINGLE_LINK_INCLUDED

// -------- data structure: array based stack ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_Stack
// ----------------------------------------------------------
#ifndef ZZ_$$_STACK_INCLUDED
#define ZZ_$$_STACK_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_StackHolder : public $$_ArrayHolder {
public:
    $$_StackHolder() : $$_ArrayHolder(){}
};

// ----------------------------------------------------------

class $$_Stack {
public:
    static void push($1 *hp,$2* e){
        $$_Array::push(hp,e);
    }
    static $2* pop($1 *hp){
        return $$_Array::pop(hp);
    }
    static $2* form($1 *hp,unsigned int const sz,int const incr){
        return $$_Array::form(hp,sz,incr);
    }
    static void free($1 *hp){
        $$_Array::free(hp);
    }
    static int size($1 *hp,int* wMark,int* incr){
        return $$_Array::size(hp,wMark,incr);
    }
};

#endif // ZZ_$$_STACK_INCLUDED


// ----------------------------------------------------------
// -------- aLib interpretation of the STL vector<T> ---------------
// ----------------------------------------------------------
// WARNING: This is only a "how-to-do-it" skeleton with a few methods such as 
//          push_back() and iterator


#ifndef ZZ_$$_VECTOR1_INCLUDED
#define ZZ_$$_VECTOR1_INCLUDED

#include <vector>
using namespace std;
class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Vector1Parent {
public:
    vector<$2> vect;
    $$_Vector1Parent(){ }
};

class $$_Vector1Child {
};
// ----------------------------------------------------------

class $$_Vector1 {
public:
    // typedef $2* iterator;
    typedef vector<$2>::iterator iterator;
    static iterator begin($1 *p);
    static iterator end($1 *p);

    static void push_back($1 *p, $2 *c);
    // .. all other methods of STL vector

};

#endif // ZZ_$$_VECTOR1_INCLUDED

// ----------------------------------------------------------
// -------- bi-directional one-to-many based on the STL vector<T> ---------------
// ----------------------------------------------------------
// WARNING: This is only a "how-to-do-it" skeleton with a few methods such as 
//          push_back() and iterator


#ifndef ZZ_$$_VECTOR2_INCLUDED
#define ZZ_$$_VECTOR2_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Vector2Parent : public $$_Vector1Parent {
friend class $$_Vector2;
};

class $$_Vector2Child : public $$_Vector1Child {
friend class $$_Vector2;
    $1 *parent;
public:
    $$_Vector2Child():$$_Vector1Child(){parent=NULL;}
};
// ----------------------------------------------------------

class $$_Vector2 : public $$_Vector1 {
public:
    static $1 *getParent($2 *c);

    static void push_back($1 *p, $2 *c);
    // .. all other methods of STL vector
};
    
#endif // ZZ_$$_VECTOR2_INCLUDED
