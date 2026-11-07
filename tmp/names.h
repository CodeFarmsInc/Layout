
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class names_Ring1
// ----------------------------------------------------------
#ifndef ZZ_names_RING1_INCLUDED
#define ZZ_names_RING1_INCLUDED

class Name;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class names_Ring1Element {
public:
    Name *next;
    names_Ring1Element(){ next=NULL; }
};

class names_Ring1 {

public:
    // standard interface
    static Name* addHead(Name *tail, Name *c); // returns new tail
    static Name* addTail(Name *tail, Name *c); // returns new tail
    static Name* append(Name *tail,Name *c1, Name *c2); // returns new tail
    static Name* remove(Name *tail, Name *c);  // returns new tail, NULL when empty
    static Name* const next(Name *p, Name *c); // returns NULL when p is tail
    static Name* const nextRing(Name *c); // unprotected raw ring pointer
    static Name* sort(ZZsortFun cmpFun, Name *tail); // returns the new tail
    static void merge(Name *s,Name *t);

    // historical DOL compatible interface
    static Name* del(Name *tail, Name *c) { return remove(tail,c); }
    static Name* add(Name *tail, Name *c) { return addHead(tail,c); }
    static Name* const fwd(Name *c){ return nextRing(c);}
};

class names_Ring1Iterator {
    Name *tail; // NULL when loop finished
    Name *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    names_Ring1Iterator(){tail=nxt=NULL;}
    Name* fromHead(Name *p);
    Name* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Name *p);
    Name* const operator++();
    names_Ring1Iterator(Name *p){start(p);}
};
    
#endif // ZZ_names_RING1_INCLUDED
