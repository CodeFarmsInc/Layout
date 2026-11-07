
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class ring2_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_ring2_RING2_INCLUDED
#define ZZ_ring2_RING2_INCLUDED

class A;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class ring2_Ring2Element {
public:
    A *next;
    A *prev;
    ring2_Ring2Element(){ next=prev=NULL; }
};

class ring2_Ring2 {

    static int debugFun(A *tail);
public:
    // standard interface
    static A* addHead(A *tail, A *c); // returns new tail
    static A* addTail(A *tail, A *c); // returns new tail
    static A* append(A *tail,A *c1, A *c2); // returns new tail
    static void insert(A *c1, A *c2); // insert c1 before c2
    static A* remove(A *tail, A *c);  // returns new tail, NULL when empty
    static A* const next(A *p, A *c); // returns NULL when p is the tail
    static A* const prev(A *p, A *c); // returns NULL when p is the head
    static A* const nextRing(A *c); // next in the ring
    static A* const prevRing(A *c); // previous in the ring
    static A* sort(ZZsortFun cmpFun, A *tail); // returns the new tail
    static void merge(A *s,A *t);

    // historical DOL compatible interface
    static A* del(A *tail, A *c) { return remove(tail,c); }
    static A* add(A *tail, A *c) { return addHead(tail,c); }
    static void ins(A *c1, A *c2) { insert(c1,c2); }
    static A* const fwd(A *c){return nextRing(c);}
    static A* const bwd(A *c){return prevRing(c);}
    
};

class ring2_Ring2Iterator {
    A *tail; // NULL when loop finished
    A *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    ring2_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    A* fromHead(A *p);
    virtual A* fromTail(A *p);
    virtual A* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(A *p);
    A* const operator++();
    A* const operator--();
    ring2_Ring2Iterator(A *p){start(p);}
};
    
#endif // ZZ_ring2_RING2_INCLUDED
