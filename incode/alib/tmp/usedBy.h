
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class usedBy_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_usedBy_RING2_INCLUDED
#define ZZ_usedBy_RING2_INCLUDED

class Participant;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class usedBy_Ring2Element {
public:
    Participant *next;
    Participant *prev;
    usedBy_Ring2Element(){ next=prev=NULL; }
};

class usedBy_Ring2 {

    static int debugFun(Participant *tail);
public:
    // standard interface
    static Participant* addHead(Participant *tail, Participant *c); // returns new tail
    static Participant* addTail(Participant *tail, Participant *c); // returns new tail
    static Participant* append(Participant *tail,Participant *c1, Participant *c2); // returns new tail
    static void insert(Participant *c1, Participant *c2); // insert c1 before c2
    static Participant* remove(Participant *tail, Participant *c);  // returns new tail, NULL when empty
    static Participant* const next(Participant *p, Participant *c); // returns NULL when p is the tail
    static Participant* const prev(Participant *p, Participant *c); // returns NULL when p is the head
    static Participant* const nextRing(Participant *c); // next in the ring
    static Participant* const prevRing(Participant *c); // previous in the ring
    static Participant* sort(ZZsortFun cmpFun, Participant *tail); // returns the new tail
    static void merge(Participant *s,Participant *t);

    // historical DOL compatible interface
    static Participant* del(Participant *tail, Participant *c) { return remove(tail,c); }
    static Participant* add(Participant *tail, Participant *c) { return addHead(tail,c); }
    static void ins(Participant *c1, Participant *c2) { insert(c1,c2); }
    static Participant* const fwd(Participant *c){return nextRing(c);}
    static Participant* const bwd(Participant *c){return prevRing(c);}
    
};

class usedBy_Ring2Iterator {
    Participant *tail; // NULL when loop finished
    Participant *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    usedBy_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Participant* fromHead(Participant *p);
    virtual Participant* fromTail(Participant *p);
    virtual Participant* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Participant *p);
    Participant* const operator++();
    Participant* const operator--();
    usedBy_Ring2Iterator(Participant *p){start(p);}
};
    
#endif // ZZ_usedBy_RING2_INCLUDED
