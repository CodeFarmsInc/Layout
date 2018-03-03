
// -------- data structure DOUBLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class $$_Ring2
// ----------------------------------------------------------
// Ring2 could be derived from Ring2 through inheritance, but
//  (a) The complex functions (sort, remove, merge) are different anyway,
//  (b) we want to minimize the nubmer of classes which will be code generated.
// For these two reasons, Ring2 is coded as a base class.
// ----------------------------------------------------------
#ifndef ZZ_$$_RING2_INCLUDED
#define ZZ_$$_RING2_INCLUDED

class $1;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Ring2Element {
public:
    $1 *next;
    $1 *prev;
    $$_Ring2Element(){ next=prev=NULL; }
};

class $$_Ring2 {

    static int debugFun($1 *tail);
public:
    // standard interface
    static $1* addHead($1 *tail, $1 *c); // returns new tail
    static $1* addTail($1 *tail, $1 *c); // returns new tail
    static $1* append($1 *tail,$1 *c1, $1 *c2); // returns new tail
    static void insert($1 *c1, $1 *c2); // insert c1 before c2
    static $1* remove($1 *tail, $1 *c);  // returns new tail, NULL when empty
    static $1* const next($1 *p, $1 *c); // returns NULL when p is the tail
    static $1* const prev($1 *p, $1 *c); // returns NULL when p is the head
    static $1* const nextRing($1 *c); // next in the ring
    static $1* const prevRing($1 *c); // previous in the ring
    static $1* sort(ZZsortFun cmpFun, $1 *tail); // returns the new tail
    static void merge($1 *s,$1 *t);

    // historical DOL compatible interface
    static $1* del($1 *tail, $1 *c) { return remove(tail,c); }
    static $1* add($1 *tail, $1 *c) { return addHead(tail,c); }
    static void ins($1 *c1, $1 *c2) { insert(c1,c2); }
    static $1* const fwd($1 *c){return nextRing(c);}
    static $1* const bwd($1 *c){return prevRing(c);}
    
};

class $$_Ring2Iterator {
    $1 *tail; // NULL when loop finished
    $1 *nxt;  // NULL when starting a new loop
    int dir;  // 0=from head, 1=from tail
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    //                              for(p=it.fromTail(x); p; p=it.next()){...}
    $$_Ring2Iterator(){tail=nxt=NULL; dir=0;}
    $1* fromHead($1 *p);
    virtual $1* fromTail($1 *p);
    virtual $1* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    //                              it.start(x); for(p= --it; p; p= --it){...}
    void start($1 *p);
    $1* const operator++();
    $1* const operator--();
    $$_Ring2Iterator($1 *p){start(p);}
};
    
#endif // ZZ_$$_RING2_INCLUDED
