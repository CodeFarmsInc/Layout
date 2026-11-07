
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class edgeToNodes_Ring1
// ----------------------------------------------------------
#ifndef ZZ_edgeToNodes_RING1_INCLUDED
#define ZZ_edgeToNodes_RING1_INCLUDED

class NodeRef;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class edgeToNodes_Ring1Element {
public:
    NodeRef *next;
    edgeToNodes_Ring1Element(){ next=NULL; }
};

class edgeToNodes_Ring1 {

public:
    // standard interface
    static NodeRef* addHead(NodeRef *tail, NodeRef *c); // returns new tail
    static NodeRef* addTail(NodeRef *tail, NodeRef *c); // returns new tail
    static NodeRef* append(NodeRef *tail,NodeRef *c1, NodeRef *c2); // returns new tail
    static NodeRef* remove(NodeRef *tail, NodeRef *c);  // returns new tail, NULL when empty
    static NodeRef* const next(NodeRef *p, NodeRef *c); // returns NULL when p is tail
    static NodeRef* const nextRing(NodeRef *c); // unprotected raw ring pointer
    static NodeRef* sort(ZZsortFun cmpFun, NodeRef *tail); // returns the new tail
    static void merge(NodeRef *s,NodeRef *t);

    // historical DOL compatible interface
    static NodeRef* del(NodeRef *tail, NodeRef *c) { return remove(tail,c); }
    static NodeRef* add(NodeRef *tail, NodeRef *c) { return addHead(tail,c); }
    static NodeRef* const fwd(NodeRef *c){ return nextRing(c);}
};

class edgeToNodes_Ring1Iterator {
    NodeRef *tail; // NULL when loop finished
    NodeRef *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    edgeToNodes_Ring1Iterator(){tail=nxt=NULL;}
    NodeRef* fromHead(NodeRef *p);
    NodeRef* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(NodeRef *p);
    NodeRef* const operator++();
    edgeToNodes_Ring1Iterator(NodeRef *p){start(p);}
};
    
#endif // ZZ_edgeToNodes_RING1_INCLUDED
