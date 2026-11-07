
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class types_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_types_RING2_INCLUDED
#define ZZ_types_RING2_INCLUDED

class OrgType;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class types_Ring2Element {
public:
    OrgType *next;
    OrgType *prev;
    types_Ring2Element(){ next=prev=NULL; }
};

class types_Ring2 {

    static int debugFun(OrgType *tail);
public:
    // standard interface
    static OrgType* addHead(OrgType *tail, OrgType *c); // returns new tail
    static OrgType* addTail(OrgType *tail, OrgType *c); // returns new tail
    static OrgType* append(OrgType *tail,OrgType *c1, OrgType *c2); // returns new tail
    static void insert(OrgType *c1, OrgType *c2); // insert c1 before c2
    static OrgType* remove(OrgType *tail, OrgType *c);  // returns new tail, NULL when empty
    static OrgType* const next(OrgType *p, OrgType *c); // returns NULL when p is the tail
    static OrgType* const prev(OrgType *p, OrgType *c); // returns NULL when p is the head
    static OrgType* const nextRing(OrgType *c); // next in the ring
    static OrgType* const prevRing(OrgType *c); // previous in the ring
    static OrgType* sort(ZZsortFun cmpFun, OrgType *tail); // returns the new tail
    static void merge(OrgType *s,OrgType *t);

    // historical DOL compatible interface
    static OrgType* del(OrgType *tail, OrgType *c) { return remove(tail,c); }
    static OrgType* add(OrgType *tail, OrgType *c) { return addHead(tail,c); }
    static void ins(OrgType *c1, OrgType *c2) { insert(c1,c2); }
    static OrgType* const fwd(OrgType *c){return nextRing(c);}
    static OrgType* const bwd(OrgType *c){return prevRing(c);}
    
};

class types_Ring2Iterator {
    OrgType *tail; // NULL when loop finished
    OrgType *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    types_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    OrgType* fromHead(OrgType *p);
    virtual OrgType* fromTail(OrgType *p);
    virtual OrgType* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(OrgType *p);
    OrgType* const operator++();
    OrgType* const operator--();
    types_Ring2Iterator(OrgType *p){start(p);}
};
    
#endif // ZZ_types_RING2_INCLUDED
