
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class orgs_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_orgs_RING2_INCLUDED
#define ZZ_orgs_RING2_INCLUDED

class Organization;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class orgs_Ring2Element {
public:
    Organization *next;
    Organization *prev;
    orgs_Ring2Element(){ next=prev=NULL; }
};

class orgs_Ring2 {

    static int debugFun(Organization *tail);
public:
    // standard interface
    static Organization* addHead(Organization *tail, Organization *c); // returns new tail
    static Organization* addTail(Organization *tail, Organization *c); // returns new tail
    static Organization* append(Organization *tail,Organization *c1, Organization *c2); // returns new tail
    static void insert(Organization *c1, Organization *c2); // insert c1 before c2
    static Organization* remove(Organization *tail, Organization *c);  // returns new tail, NULL when empty
    static Organization* const next(Organization *p, Organization *c); // returns NULL when p is the tail
    static Organization* const prev(Organization *p, Organization *c); // returns NULL when p is the head
    static Organization* const nextRing(Organization *c); // next in the ring
    static Organization* const prevRing(Organization *c); // previous in the ring
    static Organization* sort(ZZsortFun cmpFun, Organization *tail); // returns the new tail
    static void merge(Organization *s,Organization *t);

    // historical DOL compatible interface
    static Organization* del(Organization *tail, Organization *c) { return remove(tail,c); }
    static Organization* add(Organization *tail, Organization *c) { return addHead(tail,c); }
    static void ins(Organization *c1, Organization *c2) { insert(c1,c2); }
    static Organization* const fwd(Organization *c){return nextRing(c);}
    static Organization* const bwd(Organization *c){return prevRing(c);}
    
};

class orgs_Ring2Iterator {
    Organization *tail; // NULL when loop finished
    Organization *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    orgs_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    Organization* fromHead(Organization *p);
    virtual Organization* fromTail(Organization *p);
    virtual Organization* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start(Organization *p);
    Organization* const operator++();
    Organization* const operator--();
    orgs_Ring2Iterator(Organization *p){start(p);}
};
    
#endif // ZZ_orgs_RING2_INCLUDED
