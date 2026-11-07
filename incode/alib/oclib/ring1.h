
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class $$_Ring1
// ----------------------------------------------------------
#ifndef ZZ_$$_RING1_INCLUDED
#define ZZ_$$_RING1_INCLUDED

class $1;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Ring1Element {
public:
    $1 *next;
    $$_Ring1Element(){ next=NULL; }
};

class $$_Ring1 {

public:
    // standard interface
    static $1* addHead($1 *tail, $1 *c); // returns new tail
    static $1* addTail($1 *tail, $1 *c); // returns new tail
    static $1* append($1 *tail,$1 *c1, $1 *c2); // returns new tail
    static $1* remove($1 *tail, $1 *c);  // returns new tail, NULL when empty
    static $1* const next($1 *p, $1 *c); // returns NULL when p is tail
    static $1* const nextRing($1 *c); // unprotected raw ring pointer
    static $1* sort(ZZsortFun cmpFun, $1 *tail); // returns the new tail
    static void merge($1 *s,$1 *t);

    // historical DOL compatible interface
    static $1* del($1 *tail, $1 *c) { return remove(tail,c); }
    static $1* add($1 *tail, $1 *c) { return addHead(tail,c); }
    static $1* const fwd($1 *c){ return nextRing(c);}
};

class $$_Ring1Iterator {
    $1 *tail; // NULL when loop finished
    $1 *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    $$_Ring1Iterator(){tail=nxt=NULL;}
    $1* fromHead($1 *p);
    $1* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start($1 *p);
    $1* const operator++();
    $$_Ring1Iterator($1 *p){start(p);}
};
    
#endif // ZZ_$$_RING1_INCLUDED
