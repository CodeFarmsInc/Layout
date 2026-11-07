
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class pairs_Ring1
// ----------------------------------------------------------
#ifndef ZZ_pairs_RING1_INCLUDED
#define ZZ_pairs_RING1_INCLUDED

class Pair;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class pairs_Ring1Element {
public:
    Pair *next;
    pairs_Ring1Element(){ next=NULL; }
};

class pairs_Ring1 {

public:
    // standard interface
    static Pair* addHead(Pair *tail, Pair *c); // returns new tail
    static Pair* addTail(Pair *tail, Pair *c); // returns new tail
    static Pair* append(Pair *tail,Pair *c1, Pair *c2); // returns new tail
    static Pair* remove(Pair *tail, Pair *c);  // returns new tail, NULL when empty
    static Pair* const next(Pair *p, Pair *c); // returns NULL when p is tail
    static Pair* const nextRing(Pair *c); // unprotected raw ring pointer
    static Pair* sort(ZZsortFun cmpFun, Pair *tail); // returns the new tail
    static void merge(Pair *s,Pair *t);

    // historical DOL compatible interface
    static Pair* del(Pair *tail, Pair *c) { return remove(tail,c); }
    static Pair* add(Pair *tail, Pair *c) { return addHead(tail,c); }
    static Pair* const fwd(Pair *c){ return nextRing(c);}
};

class pairs_Ring1Iterator {
    Pair *tail; // NULL when loop finished
    Pair *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    pairs_Ring1Iterator(){tail=nxt=NULL;}
    Pair* fromHead(Pair *p);
    Pair* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Pair *p);
    Pair* const operator++();
    pairs_Ring1Iterator(Pair *p){start(p);}
};
    
#endif // ZZ_pairs_RING1_INCLUDED
