
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class edgeToNodes_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_edgeToNodes_LINKED_LIST1_INCLUDED
#define ZZ_edgeToNodes_LINKED_LIST1_INCLUDED

class Edge;
class NodeRef;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class edgeToNodes_LinkedList1Parent {
public:
    NodeRef* tail;
    edgeToNodes_LinkedList1Parent(){ tail=NULL; }
};

class edgeToNodes_LinkedList1Child : public edgeToNodes_Ring1Element {
public:
    edgeToNodes_LinkedList1Child() : edgeToNodes_Ring1Element(){ }
};

// the following class is used when Parent==Child
class edgeToNodes_LinkedList1ParentLinkedList1Child : public edgeToNodes_Ring1Element {
public:
    NodeRef* tail;
    edgeToNodes_LinkedList1ParentLinkedList1Child() : edgeToNodes_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class edgeToNodes_LinkedList1 : edgeToNodes_Ring1 {

public:
    static NodeRef *tail(Edge *p);
    static NodeRef *head(Edge *p);
    static void addHead(Edge *p, NodeRef *c);
    static void addTail(Edge *p, NodeRef *c);
    static void append(Edge *p,NodeRef *c1, NodeRef *c2);
    static void remove(Edge *p, NodeRef *c);
    static NodeRef* const next(Edge *p,NodeRef *c);
    static NodeRef* const nextRing(NodeRef *c);
    static void sort(ZZsortFun cmpFun, Edge *p);
    static void merge(NodeRef *s,NodeRef *t,Edge *p);
    static void setTail(Edge* p,NodeRef* c,int check);

    // historical DOL compatible interface
    static void del(Edge *p, NodeRef *c){ remove(p,c);}
    static void add(Edge *p, NodeRef *c){ addHead(p,c);}
    static NodeRef* child(Edge *p);
    static void set(Edge* p,NodeRef* c){ setTail(p,c,0);}
    static NodeRef* const fwd(NodeRef *c){ return nextRing(c);}
};

class edgeToNodes_LinkedList1Iterator : public edgeToNodes_Ring1Iterator {
public:
    edgeToNodes_LinkedList1Iterator() : edgeToNodes_Ring1Iterator(){}
    edgeToNodes_LinkedList1Iterator(const Edge *p) : edgeToNodes_Ring1Iterator(){start(p);}
    void start(const Edge *p);
    NodeRef* fromHead(Edge *p);
};
    
#endif // ZZ_edgeToNodes_LINKED_LIST1_INCLUDED
