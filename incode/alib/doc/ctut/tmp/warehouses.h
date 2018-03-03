
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class warehouses_Ring1
// ----------------------------------------------------------
#ifndef ZZ_warehouses_RING1_INCLUDED
#define ZZ_warehouses_RING1_INCLUDED

class Warehouse;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class warehouses_Ring1Element {
public:
    Warehouse *next;
    warehouses_Ring1Element(){ next=NULL; }
};

class warehouses_Ring1 {

public:
    // standard interface
    static Warehouse* addHead(Warehouse *tail, Warehouse *c); // returns new tail
    static Warehouse* addTail(Warehouse *tail, Warehouse *c); // returns new tail
    static Warehouse* append(Warehouse *tail,Warehouse *c1, Warehouse *c2); // returns new tail
    static Warehouse* remove(Warehouse *tail, Warehouse *c);  // returns new tail, NULL when empty
    static Warehouse* const next(Warehouse *p, Warehouse *c); // returns NULL when p is tail
    static Warehouse* const fwd(Warehouse *c); // unprotected raw ring pointer
    static Warehouse* sort(ZZsortFun cmpFun, Warehouse *tail); // returns the new tail
    static void merge(Warehouse *s,Warehouse *t);

    // historical DOL compatible interface
    static Warehouse* del(Warehouse *tail, Warehouse *c) { return remove(tail,c); }
    static Warehouse* add(Warehouse *tail, Warehouse *c) { return addHead(tail,c); }
};

class warehouses_Ring1Iterator {
    Warehouse *tail; // NULL when loop finished
    Warehouse *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    warehouses_Ring1Iterator(){tail=nxt=NULL;}
    virtual Warehouse* fromHead(Warehouse *p);
    virtual Warehouse* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    virtual void start(Warehouse *p);
    virtual Warehouse* const operator++();
    warehouses_Ring1Iterator(Warehouse *p){start(p);}
};
    
#endif // ZZ_warehouses_RING1_INCLUDED
