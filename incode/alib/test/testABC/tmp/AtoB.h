
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class AtoB_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_AtoB_RING2_INCLUDED
#define ZZ_AtoB_RING2_INCLUDED

class B;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class AtoB_Ring2Element {
public:
    B *next;
    B *prev;
    AtoB_Ring2Element(){ next=prev=NULL; }
};

class AtoB_Ring2 {

    static int debugFun(B *tail);
public:
    // standard interface
    static B* addHead(B *tail, B *c); // returns new tail
    static B* addTail(B *tail, B *c); // returns new tail
    static B* append(B *tail,B *c1, B *c2); // returns new tail
    static void insert(B *c1, B *c2); // insert c1 before c2
    static B* remove(B *tail, B *c);  // returns new tail, NULL when empty
    static B* const next(B *p, B *c); // returns NULL when p is the tail
    static B* const prev(B *p, B *c); // returns NULL when p is the head
    static B* const nextRing(B *c); // next in the ring
    static B* const prevRing(B *c); // previous in the ring
    static B* sort(ZZsortFun cmpFun, B *tail); // returns the new tail
    static void merge(B *s,B *t);

    // historical DOL compatible interface
    static B* del(B *tail, B *c) { return remove(tail,c); }
    static B* add(B *tail, B *c) { return addHead(tail,c); }
    static void ins(B *c1, B *c2) { insert(c1,c2); }
    static B* const fwd(B *c){return nextRing(c);}
    static B* const bwd(B *c){return prevRing(c);}
    
};

class AtoB_Ring2Iterator {
    B *tail; // NULL when loop finished
    B *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    AtoB_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    B* fromHead(B *p);
    virtual B* fromTail(B *p);
    virtual B* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(B *p);
    B* const operator++();
    B* const operator--();
    AtoB_Ring2Iterator(B *p){start(p);}
};
    
#endif // ZZ_AtoB_RING2_INCLUDED
