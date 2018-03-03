
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class marks_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_marks_RING2_INCLUDED
#define ZZ_marks_RING2_INCLUDED

class Mark;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class marks_Ring2Element {
public:
    Mark *next;
    Mark *prev;
    marks_Ring2Element(){ next=prev=NULL; }
};

class marks_Ring2 {

    static int debugFun(Mark *tail);
public:
    // standard interface
    static Mark* addHead(Mark *tail, Mark *c); // returns new tail
    static Mark* addTail(Mark *tail, Mark *c); // returns new tail
    static Mark* append(Mark *tail,Mark *c1, Mark *c2); // returns new tail
    static void insert(Mark *c1, Mark *c2); // insert c1 before c2
    static Mark* remove(Mark *tail, Mark *c);  // returns new tail, NULL when empty
    static Mark* const next(Mark *p, Mark *c); // returns NULL when p is the tail
    static Mark* const prev(Mark *p, Mark *c); // returns NULL when p is the head
    static Mark* const nextRing(Mark *c); // next in the ring
    static Mark* const prevRing(Mark *c); // previous in the ring
    static Mark* sort(ZZsortFun cmpFun, Mark *tail); // returns the new tail
    static void merge(Mark *s,Mark *t);

    // historical DOL compatible interface
    static Mark* del(Mark *tail, Mark *c) { return remove(tail,c); }
    static Mark* add(Mark *tail, Mark *c) { return addHead(tail,c); }
    static void ins(Mark *c1, Mark *c2) { insert(c1,c2); }
    static Mark* const fwd(Mark *c){return nextRing(c);}
    static Mark* const bwd(Mark *c){return prevRing(c);}
    
};

class marks_Ring2Iterator {
    Mark *tail; // NULL when loop finished
    Mark *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    marks_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Mark* fromHead(Mark *p);
    virtual Mark* fromTail(Mark *p);
    virtual Mark* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Mark *p);
    Mark* const operator++();
    Mark* const operator--();
    marks_Ring2Iterator(Mark *p){start(p);}
};
    
#endif // ZZ_marks_RING2_INCLUDED
