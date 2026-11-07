
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class byYear_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_byYear_RING2_INCLUDED
#define ZZ_byYear_RING2_INCLUDED

class Took;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class byYear_Ring2Element {
public:
    Took *next;
    Took *prev;
    byYear_Ring2Element(){ next=prev=NULL; }
};

class byYear_Ring2 {

    static int debugFun(Took *tail);
public:
    // standard interface
    static Took* addHead(Took *tail, Took *c); // returns new tail
    static Took* addTail(Took *tail, Took *c); // returns new tail
    static Took* append(Took *tail,Took *c1, Took *c2); // returns new tail
    static void insert(Took *c1, Took *c2); // insert c1 before c2
    static Took* remove(Took *tail, Took *c);  // returns new tail, NULL when empty
    static Took* const next(Took *p, Took *c); // returns NULL when p is the tail
    static Took* const prev(Took *p, Took *c); // returns NULL when p is the head
    static Took* const nextRing(Took *c); // next in the ring
    static Took* const prevRing(Took *c); // previous in the ring
    static Took* sort(ZZsortFun cmpFun, Took *tail); // returns the new tail
    static void merge(Took *s,Took *t);

    // historical DOL compatible interface
    static Took* del(Took *tail, Took *c) { return remove(tail,c); }
    static Took* add(Took *tail, Took *c) { return addHead(tail,c); }
    static void ins(Took *c1, Took *c2) { insert(c1,c2); }
    static Took* const fwd(Took *c){return nextRing(c);}
    static Took* const bwd(Took *c){return prevRing(c);}
    
};

class byYear_Ring2Iterator {
    Took *tail; // NULL when loop finished
    Took *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    byYear_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Took* fromHead(Took *p);
    virtual Took* fromTail(Took *p);
    virtual Took* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Took *p);
    Took* const operator++();
    Took* const operator--();
    byYear_Ring2Iterator(Took *p){start(p);}
};
    
#endif // ZZ_byYear_RING2_INCLUDED
