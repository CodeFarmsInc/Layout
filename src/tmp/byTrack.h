
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class byTrack_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_byTrack_RING2_INCLUDED
#define ZZ_byTrack_RING2_INCLUDED

class Edge;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class byTrack_Ring2Element {
public:
    Edge *next;
    Edge *prev;
    byTrack_Ring2Element(){ next=prev=NULL; }
};

class byTrack_Ring2 {

    static int debugFun(Edge *tail);
public:
    // standard interface
    static Edge* addHead(Edge *tail, Edge *c); // returns new tail
    static Edge* addTail(Edge *tail, Edge *c); // returns new tail
    static Edge* append(Edge *tail,Edge *c1, Edge *c2); // returns new tail
    static void insert(Edge *c1, Edge *c2); // insert c1 before c2
    static Edge* remove(Edge *tail, Edge *c);  // returns new tail, NULL when empty
    static Edge* const next(Edge *p, Edge *c); // returns NULL when p is the tail
    static Edge* const prev(Edge *p, Edge *c); // returns NULL when p is the head
    static Edge* const nextRing(Edge *c); // next in the ring
    static Edge* const prevRing(Edge *c); // previous in the ring
    static Edge* sort(ZZsortFun cmpFun, Edge *tail); // returns the new tail
    static void merge(Edge *s,Edge *t);

    // historical DOL compatible interface
    static Edge* del(Edge *tail, Edge *c) { return remove(tail,c); }
    static Edge* add(Edge *tail, Edge *c) { return addHead(tail,c); }
    static void ins(Edge *c1, Edge *c2) { insert(c1,c2); }
    static Edge* const fwd(Edge *c){return nextRing(c);}
    static Edge* const bwd(Edge *c){return prevRing(c);}
    
};

class byTrack_Ring2Iterator {
    Edge *tail; // NULL when loop finished
    Edge *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    byTrack_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Edge* fromHead(Edge *p);
    virtual Edge* fromTail(Edge *p);
    virtual Edge* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Edge *p);
    Edge* const operator++();
    Edge* const operator--();
    byTrack_Ring2Iterator(Edge *p){start(p);}
};
    
#endif // ZZ_byTrack_RING2_INCLUDED
