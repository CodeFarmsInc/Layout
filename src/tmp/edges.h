
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class edges_Ring1
// ----------------------------------------------------------
#ifndef ZZ_edges_RING1_INCLUDED
#define ZZ_edges_RING1_INCLUDED

class Edge;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class edges_Ring1Element {
public:
    Edge *next;
    edges_Ring1Element(){ next=NULL; }
};

class edges_Ring1 {

public:
    // standard interface
    static Edge* addHead(Edge *tail, Edge *c); // returns new tail
    static Edge* addTail(Edge *tail, Edge *c); // returns new tail
    static Edge* append(Edge *tail,Edge *c1, Edge *c2); // returns new tail
    static Edge* remove(Edge *tail, Edge *c);  // returns new tail, NULL when empty
    static Edge* const next(Edge *p, Edge *c); // returns NULL when p is tail
    static Edge* const nextRing(Edge *c); // unprotected raw ring pointer
    static Edge* sort(ZZsortFun cmpFun, Edge *tail); // returns the new tail
    static void merge(Edge *s,Edge *t);

    // historical DOL compatible interface
    static Edge* del(Edge *tail, Edge *c) { return remove(tail,c); }
    static Edge* add(Edge *tail, Edge *c) { return addHead(tail,c); }
    static Edge* const fwd(Edge *c){ return nextRing(c);}
};

class edges_Ring1Iterator {
    Edge *tail; // NULL when loop finished
    Edge *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    edges_Ring1Iterator(){tail=nxt=NULL;}
    Edge* fromHead(Edge *p);
    Edge* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Edge *p);
    Edge* const operator++();
    edges_Ring1Iterator(Edge *p){start(p);}
};
    
#endif // ZZ_edges_RING1_INCLUDED
