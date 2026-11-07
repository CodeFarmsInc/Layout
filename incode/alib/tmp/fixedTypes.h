
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class fixedTypes_Ring1
// ----------------------------------------------------------
#ifndef ZZ_fixedTypes_RING1_INCLUDED
#define ZZ_fixedTypes_RING1_INCLUDED

class FixedType;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class fixedTypes_Ring1Element {
public:
    FixedType *next;
    fixedTypes_Ring1Element(){ next=NULL; }
};

class fixedTypes_Ring1 {

public:
    // standard interface
    static FixedType* addHead(FixedType *tail, FixedType *c); // returns new tail
    static FixedType* addTail(FixedType *tail, FixedType *c); // returns new tail
    static FixedType* append(FixedType *tail,FixedType *c1, FixedType *c2); // returns new tail
    static FixedType* remove(FixedType *tail, FixedType *c);  // returns new tail, NULL when empty
    static FixedType* const next(FixedType *p, FixedType *c); // returns NULL when p is tail
    static FixedType* const nextRing(FixedType *c); // unprotected raw ring pointer
    static FixedType* sort(ZZsortFun cmpFun, FixedType *tail); // returns the new tail
    static void merge(FixedType *s,FixedType *t);

    // historical DOL compatible interface
    static FixedType* del(FixedType *tail, FixedType *c) { return remove(tail,c); }
    static FixedType* add(FixedType *tail, FixedType *c) { return addHead(tail,c); }
    static FixedType* const fwd(FixedType *c){ return nextRing(c);}
};

class fixedTypes_Ring1Iterator {
    FixedType *tail; // NULL when loop finished
    FixedType *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    fixedTypes_Ring1Iterator(){tail=nxt=NULL;}
    FixedType* fromHead(FixedType *p);
    FixedType* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(FixedType *p);
    FixedType* const operator++();
    fixedTypes_Ring1Iterator(FixedType *p){start(p);}
};
    
#endif // ZZ_fixedTypes_RING1_INCLUDED
