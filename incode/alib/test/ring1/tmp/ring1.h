
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class ring1_Ring1
// ----------------------------------------------------------
#ifndef ZZ_ring1_RING1_INCLUDED
#define ZZ_ring1_RING1_INCLUDED

class A;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class ring1_Ring1Element {
public:
    A *next;
    ring1_Ring1Element(){ next=NULL; }
};

class ring1_Ring1 {

public:
    // standard interface
    static A* addHead(A *tail, A *c); // returns new tail
    static A* addTail(A *tail, A *c); // returns new tail
    static A* append(A *tail,A *c1, A *c2); // returns new tail
    static A* remove(A *tail, A *c);  // returns new tail, NULL when empty
    static A* const next(A *p, A *c); // returns NULL when p is tail
    static A* const nextRing(A *c); // unprotected raw ring pointer
    static A* sort(ZZsortFun cmpFun, A *tail); // returns the new tail
    static void merge(A *s,A *t);

    // historical DOL compatible interface
    static A* del(A *tail, A *c) { return remove(tail,c); }
    static A* add(A *tail, A *c) { return addHead(tail,c); }
    static A* const fwd(A *c){ return nextRing(c);}
};

class ring1_Ring1Iterator {
    A *tail; // NULL when loop finished
    A *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    ring1_Ring1Iterator(){tail=nxt=NULL;}
    A* fromHead(A *p);
    A* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(A *p);
    A* const operator++();
    ring1_Ring1Iterator(A *p){start(p);}
};
    
#endif // ZZ_ring1_RING1_INCLUDED
