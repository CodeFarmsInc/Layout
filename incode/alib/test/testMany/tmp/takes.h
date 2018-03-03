
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class takes_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_takes_RING2_INCLUDED
#define ZZ_takes_RING2_INCLUDED

class Takes;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class takes_Ring2Element {
public:
    Takes *next;
    Takes *prev;
    takes_Ring2Element(){ next=prev=NULL; }
};

class takes_Ring2 {

    static int debugFun(Takes *tail);
public:
    // standard interface
    static Takes* addHead(Takes *tail, Takes *c); // returns new tail
    static Takes* addTail(Takes *tail, Takes *c); // returns new tail
    static Takes* append(Takes *tail,Takes *c1, Takes *c2); // returns new tail
    static void insert(Takes *c1, Takes *c2); // insert c1 before c2
    static Takes* remove(Takes *tail, Takes *c);  // returns new tail, NULL when empty
    static Takes* const next(Takes *p, Takes *c); // returns NULL when p is the tail
    static Takes* const prev(Takes *p, Takes *c); // returns NULL when p is the head
    static Takes* const nextRing(Takes *c); // next in the ring
    static Takes* const prevRing(Takes *c); // previous in the ring
    static Takes* sort(ZZsortFun cmpFun, Takes *tail); // returns the new tail
    static void merge(Takes *s,Takes *t);

    // historical DOL compatible interface
    static Takes* del(Takes *tail, Takes *c) { return remove(tail,c); }
    static Takes* add(Takes *tail, Takes *c) { return addHead(tail,c); }
    static void ins(Takes *c1, Takes *c2) { insert(c1,c2); }
    static Takes* const fwd(Takes *c){return nextRing(c);}
    static Takes* const bwd(Takes *c){return prevRing(c);}
    
};

class takes_Ring2Iterator {
    Takes *tail; // NULL when loop finished
    Takes *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    takes_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Takes* fromHead(Takes *p);
    virtual Takes* fromTail(Takes *p);
    virtual Takes* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Takes *p);
    Takes* const operator++();
    Takes* const operator--();
    takes_Ring2Iterator(Takes *p){start(p);}
};
    
#endif // ZZ_takes_RING2_INCLUDED
