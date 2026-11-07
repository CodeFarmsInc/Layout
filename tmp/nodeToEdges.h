
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class nodeToEdges_Ring1
// ----------------------------------------------------------
#ifndef ZZ_nodeToEdges_RING1_INCLUDED
#define ZZ_nodeToEdges_RING1_INCLUDED

class EdgeRef;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class nodeToEdges_Ring1Element {
public:
    EdgeRef *next;
    nodeToEdges_Ring1Element(){ next=NULL; }
};

class nodeToEdges_Ring1 {

public:
    // standard interface
    static EdgeRef* addHead(EdgeRef *tail, EdgeRef *c); // returns new tail
    static EdgeRef* addTail(EdgeRef *tail, EdgeRef *c); // returns new tail
    static EdgeRef* append(EdgeRef *tail,EdgeRef *c1, EdgeRef *c2); // returns new tail
    static EdgeRef* remove(EdgeRef *tail, EdgeRef *c);  // returns new tail, NULL when empty
    static EdgeRef* const next(EdgeRef *p, EdgeRef *c); // returns NULL when p is tail
    static EdgeRef* const nextRing(EdgeRef *c); // unprotected raw ring pointer
    static EdgeRef* sort(ZZsortFun cmpFun, EdgeRef *tail); // returns the new tail
    static void merge(EdgeRef *s,EdgeRef *t);

    // historical DOL compatible interface
    static EdgeRef* del(EdgeRef *tail, EdgeRef *c) { return remove(tail,c); }
    static EdgeRef* add(EdgeRef *tail, EdgeRef *c) { return addHead(tail,c); }
    static EdgeRef* const fwd(EdgeRef *c){ return nextRing(c);}
};

class nodeToEdges_Ring1Iterator {
    EdgeRef *tail; // NULL when loop finished
    EdgeRef *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    nodeToEdges_Ring1Iterator(){tail=nxt=NULL;}
    EdgeRef* fromHead(EdgeRef *p);
    EdgeRef* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(EdgeRef *p);
    EdgeRef* const operator++();
    nodeToEdges_Ring1Iterator(EdgeRef *p){start(p);}
};
    
#endif // ZZ_nodeToEdges_RING1_INCLUDED
