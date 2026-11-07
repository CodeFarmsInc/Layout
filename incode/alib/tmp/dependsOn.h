
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class dependsOn_Ring1
// ----------------------------------------------------------
#ifndef ZZ_dependsOn_RING1_INCLUDED
#define ZZ_dependsOn_RING1_INCLUDED

class ClassLink;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class dependsOn_Ring1Element {
public:
    ClassLink *next;
    dependsOn_Ring1Element(){ next=NULL; }
};

class dependsOn_Ring1 {

public:
    // standard interface
    static ClassLink* addHead(ClassLink *tail, ClassLink *c); // returns new tail
    static ClassLink* addTail(ClassLink *tail, ClassLink *c); // returns new tail
    static ClassLink* append(ClassLink *tail,ClassLink *c1, ClassLink *c2); // returns new tail
    static ClassLink* remove(ClassLink *tail, ClassLink *c);  // returns new tail, NULL when empty
    static ClassLink* const next(ClassLink *p, ClassLink *c); // returns NULL when p is tail
    static ClassLink* const nextRing(ClassLink *c); // unprotected raw ring pointer
    static ClassLink* sort(ZZsortFun cmpFun, ClassLink *tail); // returns the new tail
    static void merge(ClassLink *s,ClassLink *t);

    // historical DOL compatible interface
    static ClassLink* del(ClassLink *tail, ClassLink *c) { return remove(tail,c); }
    static ClassLink* add(ClassLink *tail, ClassLink *c) { return addHead(tail,c); }
    static ClassLink* const fwd(ClassLink *c){ return nextRing(c);}
};

class dependsOn_Ring1Iterator {
    ClassLink *tail; // NULL when loop finished
    ClassLink *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    dependsOn_Ring1Iterator(){tail=nxt=NULL;}
    ClassLink* fromHead(ClassLink *p);
    ClassLink* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(ClassLink *p);
    ClassLink* const operator++();
    dependsOn_Ring1Iterator(ClassLink *p){start(p);}
};
    
#endif // ZZ_dependsOn_RING1_INCLUDED
