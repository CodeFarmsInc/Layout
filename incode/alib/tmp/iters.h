
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class iters_Ring1
// ----------------------------------------------------------
#ifndef ZZ_iters_RING1_INCLUDED
#define ZZ_iters_RING1_INCLUDED

class Iterator;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class iters_Ring1Element {
public:
    Iterator *next;
    iters_Ring1Element(){ next=NULL; }
};

class iters_Ring1 {

public:
    // standard interface
    static Iterator* addHead(Iterator *tail, Iterator *c); // returns new tail
    static Iterator* addTail(Iterator *tail, Iterator *c); // returns new tail
    static Iterator* append(Iterator *tail,Iterator *c1, Iterator *c2); // returns new tail
    static Iterator* remove(Iterator *tail, Iterator *c);  // returns new tail, NULL when empty
    static Iterator* const next(Iterator *p, Iterator *c); // returns NULL when p is tail
    static Iterator* const nextRing(Iterator *c); // unprotected raw ring pointer
    static Iterator* sort(ZZsortFun cmpFun, Iterator *tail); // returns the new tail
    static void merge(Iterator *s,Iterator *t);

    // historical DOL compatible interface
    static Iterator* del(Iterator *tail, Iterator *c) { return remove(tail,c); }
    static Iterator* add(Iterator *tail, Iterator *c) { return addHead(tail,c); }
    static Iterator* const fwd(Iterator *c){ return nextRing(c);}
};

class iters_Ring1Iterator {
    Iterator *tail; // NULL when loop finished
    Iterator *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    iters_Ring1Iterator(){tail=nxt=NULL;}
    Iterator* fromHead(Iterator *p);
    Iterator* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Iterator *p);
    Iterator* const operator++();
    iters_Ring1Iterator(Iterator *p){start(p);}
};
    
#endif // ZZ_iters_RING1_INCLUDED
