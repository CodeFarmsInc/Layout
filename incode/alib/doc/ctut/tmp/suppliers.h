
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class suppliers_Ring1
// ----------------------------------------------------------
#ifndef ZZ_suppliers_RING1_INCLUDED
#define ZZ_suppliers_RING1_INCLUDED

class Supplier;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class suppliers_Ring1Element {
public:
    Supplier *next;
    suppliers_Ring1Element(){ next=NULL; }
};

class suppliers_Ring1 {

public:
    // standard interface
    static Supplier* addHead(Supplier *tail, Supplier *c); // returns new tail
    static Supplier* addTail(Supplier *tail, Supplier *c); // returns new tail
    static Supplier* append(Supplier *tail,Supplier *c1, Supplier *c2); // returns new tail
    static Supplier* remove(Supplier *tail, Supplier *c);  // returns new tail, NULL when empty
    static Supplier* const next(Supplier *p, Supplier *c); // returns NULL when p is tail
    static Supplier* const fwd(Supplier *c); // unprotected raw ring pointer
    static Supplier* sort(ZZsortFun cmpFun, Supplier *tail); // returns the new tail
    static void merge(Supplier *s,Supplier *t);

    // historical DOL compatible interface
    static Supplier* del(Supplier *tail, Supplier *c) { return remove(tail,c); }
    static Supplier* add(Supplier *tail, Supplier *c) { return addHead(tail,c); }
};

class suppliers_Ring1Iterator {
    Supplier *tail; // NULL when loop finished
    Supplier *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    suppliers_Ring1Iterator(){tail=nxt=NULL;}
    virtual Supplier* fromHead(Supplier *p);
    virtual Supplier* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    virtual void start(Supplier *p);
    virtual Supplier* const operator++();
    suppliers_Ring1Iterator(Supplier *p){start(p);}
};
    
#endif // ZZ_suppliers_RING1_INCLUDED
