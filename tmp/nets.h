
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class nets_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_nets_RING2_INCLUDED
#define ZZ_nets_RING2_INCLUDED

class Net;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class nets_Ring2Element {
public:
    Net *next;
    Net *prev;
    nets_Ring2Element(){ next=prev=NULL; }
};

class nets_Ring2 {

    static int debugFun(Net *tail);
public:
    // standard interface
    static Net* addHead(Net *tail, Net *c); // returns new tail
    static Net* addTail(Net *tail, Net *c); // returns new tail
    static Net* append(Net *tail,Net *c1, Net *c2); // returns new tail
    static void insert(Net *c1, Net *c2); // insert c1 before c2
    static Net* remove(Net *tail, Net *c);  // returns new tail, NULL when empty
    static Net* const next(Net *p, Net *c); // returns NULL when p is the tail
    static Net* const prev(Net *p, Net *c); // returns NULL when p is the head
    static Net* const nextRing(Net *c); // next in the ring
    static Net* const prevRing(Net *c); // previous in the ring
    static Net* sort(ZZsortFun cmpFun, Net *tail); // returns the new tail
    static void merge(Net *s,Net *t);

    // historical DOL compatible interface
    static Net* del(Net *tail, Net *c) { return remove(tail,c); }
    static Net* add(Net *tail, Net *c) { return addHead(tail,c); }
    static void ins(Net *c1, Net *c2) { insert(c1,c2); }
    static Net* const fwd(Net *c){return nextRing(c);}
    static Net* const bwd(Net *c){return prevRing(c);}
    
};

class nets_Ring2Iterator {
    Net *tail; // NULL when loop finished
    Net *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    nets_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Net* fromHead(Net *p);
    virtual Net* fromTail(Net *p);
    virtual Net* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Net *p);
    Net* const operator++();
    Net* const operator--();
    nets_Ring2Iterator(Net *p){start(p);}
};
    
#endif // ZZ_nets_RING2_INCLUDED
