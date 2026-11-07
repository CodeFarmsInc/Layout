
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class dHier_Ring1
// ----------------------------------------------------------
#ifndef ZZ_dHier_RING1_INCLUDED
#define ZZ_dHier_RING1_INCLUDED

class Department;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class dHier_Ring1Element {
public:
    Department *next;
    dHier_Ring1Element(){ next=NULL; }
};

class dHier_Ring1 {

public:
    // standard interface
    static Department* addHead(Department *tail, Department *c); // returns new tail
    static Department* addTail(Department *tail, Department *c); // returns new tail
    static Department* append(Department *tail,Department *c1, Department *c2); // returns new tail
    static Department* remove(Department *tail, Department *c);  // returns new tail, NULL when empty
    static Department* const next(Department *p, Department *c); // returns NULL when p is tail
    static Department* const fwd(Department *c); // unprotected raw ring pointer
    static Department* sort(ZZsortFun cmpFun, Department *tail); // returns the new tail
    static void merge(Department *s,Department *t);

    // historical DOL compatible interface
    static Department* del(Department *tail, Department *c) { return remove(tail,c); }
    static Department* add(Department *tail, Department *c) { return addHead(tail,c); }
};

class dHier_Ring1Iterator {
    Department *tail; // NULL when loop finished
    Department *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    dHier_Ring1Iterator(){tail=nxt=NULL;}
    virtual Department* fromHead(Department *p);
    virtual Department* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    virtual void start(Department *p);
    virtual Department* const operator++();
    dHier_Ring1Iterator(Department *p){start(p);}
};
    
#endif // ZZ_dHier_RING1_INCLUDED
