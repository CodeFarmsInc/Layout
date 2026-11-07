
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class sources_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_sources_LINKED_LIST2_INCLUDED
#define ZZ_sources_LINKED_LIST2_INCLUDED

class Node;
class Edge;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class sources_LinkedList2Parent {
public:
    Edge* tail;
    sources_LinkedList2Parent(){ tail=NULL; }
};

class sources_LinkedList2Child : public sources_Ring2Element {
public:
    sources_LinkedList2Child() : sources_Ring2Element(){ }
};

// the following class is used when Parent==Child
class sources_LinkedList2ParentLinkedList2Child : public sources_Ring2Element {
public:
    Edge* tail;
    sources_LinkedList2ParentLinkedList2Child() : sources_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class sources_LinkedList2 : sources_Ring2 {

public:
    static Edge* const tail(Node *p);
    static Edge* const head(Node *p);
    static void addHead(Node *p, Edge *c);
    static void addTail(Node *p, Edge *c);
    static void append(Node *p,Edge *c1, Edge *c2);
    static void insert(Edge *c1, Edge *c2);
    static void remove(Node *p, Edge *c);
    static Edge* const next(Node *p, Edge *c);
    static Edge* const prev(Node *p, Edge *c);
    static Edge* const nextRing(Edge *c);
    static Edge* const prevRing(Edge *c);
    static void sort(ZZsortFun cmpFun, Node *p);
    static void merge(Edge *s,Edge *t,Node *p);
    static void setTail(Node* p,Edge* c,int check);

    // historical DOL compatible interface
    static void del(Node *p, Edge *c) { remove(p,c); }
    static void add(Node *p, Edge *c) { addHead(p,c);}
    static void ins(Edge *c1, Edge *c2) { insert(c1,c2); }
    static Edge* child(Node* p);
    static void set(Node* p,Edge* c){ setTail(p,c,0);}
    static Edge* const fwd(Edge *c){return nextRing(c);}
    static Edge* const bwd(Edge *c){return prevRing(c);}
};

class sources_LinkedList2Iterator : public sources_Ring2Iterator {
public:
    sources_LinkedList2Iterator() : sources_Ring2Iterator(){}
    sources_LinkedList2Iterator(const Node *p) : sources_Ring2Iterator(){ start(p); }
    void start(const Node *p);
    Edge* fromHead(Node *p);
    Edge* fromTail(Node *p);
};
    
#endif // ZZ_sources_LINKED_LIST2_INCLUDED
