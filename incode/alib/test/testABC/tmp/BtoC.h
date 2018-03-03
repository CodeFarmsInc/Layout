
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class BtoC_Ring1
// ----------------------------------------------------------
#ifndef ZZ_BtoC_RING1_INCLUDED
#define ZZ_BtoC_RING1_INCLUDED

class C;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class BtoC_Ring1Element {
public:
    C *next;
    BtoC_Ring1Element(){ next=NULL; }
};

class BtoC_Ring1 {

public:
    // standard interface
    static C* addHead(C *tail, C *c); // returns new tail
    static C* addTail(C *tail, C *c); // returns new tail
    static C* append(C *tail,C *c1, C *c2); // returns new tail
    static C* remove(C *tail, C *c);  // returns new tail, NULL when empty
    static C* const next(C *p, C *c); // returns NULL when p is tail
    static C* const nextRing(C *c); // unprotected raw ring pointer
    static C* sort(ZZsortFun cmpFun, C *tail); // returns the new tail
    static void merge(C *s,C *t);

    // historical DOL compatible interface
    static C* del(C *tail, C *c) { return remove(tail,c); }
    static C* add(C *tail, C *c) { return addHead(tail,c); }
    static C* const fwd(C *c){ return nextRing(c);}
};

class BtoC_Ring1Iterator {
    C *tail; // NULL when loop finished
    C *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    BtoC_Ring1Iterator(){tail=nxt=NULL;}
    C* fromHead(C *p);
    C* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(C *p);
    C* const operator++();
    BtoC_Ring1Iterator(C *p){start(p);}
};
    
#endif // ZZ_BtoC_RING1_INCLUDED
