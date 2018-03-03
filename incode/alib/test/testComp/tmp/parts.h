
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class parts_Ring1
// ----------------------------------------------------------
#ifndef ZZ_parts_RING1_INCLUDED
#define ZZ_parts_RING1_INCLUDED

class Graphics;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class parts_Ring1Element {
public:
    Graphics *next;
    parts_Ring1Element(){ next=NULL; }
};

class parts_Ring1 {

public:
    // standard interface
    static Graphics* addHead(Graphics *tail, Graphics *c); // returns new tail
    static Graphics* addTail(Graphics *tail, Graphics *c); // returns new tail
    static Graphics* append(Graphics *tail,Graphics *c1, Graphics *c2); // returns new tail
    static Graphics* remove(Graphics *tail, Graphics *c);  // returns new tail, NULL when empty
    static Graphics* const next(Graphics *p, Graphics *c); // returns NULL when p is tail
    static Graphics* const nextRing(Graphics *c); // unprotected raw ring pointer
    static Graphics* sort(ZZsortFun cmpFun, Graphics *tail); // returns the new tail
    static void merge(Graphics *s,Graphics *t);

    // historical DOL compatible interface
    static Graphics* del(Graphics *tail, Graphics *c) { return remove(tail,c); }
    static Graphics* add(Graphics *tail, Graphics *c) { return addHead(tail,c); }
    static Graphics* const fwd(Graphics *c){ return nextRing(c);}
};

class parts_Ring1Iterator {
    Graphics *tail; // NULL when loop finished
    Graphics *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    parts_Ring1Iterator(){tail=nxt=NULL;}
    Graphics* fromHead(Graphics *p);
    Graphics* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Graphics *p);
    Graphics* const operator++();
    parts_Ring1Iterator(Graphics *p){start(p);}
};
    
#endif // ZZ_parts_RING1_INCLUDED
