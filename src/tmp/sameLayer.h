
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class sameLayer_Ring1
// ----------------------------------------------------------
#ifndef ZZ_sameLayer_RING1_INCLUDED
#define ZZ_sameLayer_RING1_INCLUDED

class Node;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class sameLayer_Ring1Element {
public:
    Node *next;
    sameLayer_Ring1Element(){ next=NULL; }
};

class sameLayer_Ring1 {

public:
    // standard interface
    static Node* addHead(Node *tail, Node *c); // returns new tail
    static Node* addTail(Node *tail, Node *c); // returns new tail
    static Node* append(Node *tail,Node *c1, Node *c2); // returns new tail
    static Node* remove(Node *tail, Node *c);  // returns new tail, NULL when empty
    static Node* const next(Node *p, Node *c); // returns NULL when p is tail
    static Node* const nextRing(Node *c); // unprotected raw ring pointer
    static Node* sort(ZZsortFun cmpFun, Node *tail); // returns the new tail
    static void merge(Node *s,Node *t);

    // historical DOL compatible interface
    static Node* del(Node *tail, Node *c) { return remove(tail,c); }
    static Node* add(Node *tail, Node *c) { return addHead(tail,c); }
    static Node* const fwd(Node *c){ return nextRing(c);}
};

class sameLayer_Ring1Iterator {
    Node *tail; // NULL when loop finished
    Node *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    sameLayer_Ring1Iterator(){tail=nxt=NULL;}
    Node* fromHead(Node *p);
    Node* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Node *p);
    Node* const operator++();
    sameLayer_Ring1Iterator(Node *p){start(p);}
};
    
#endif // ZZ_sameLayer_RING1_INCLUDED
