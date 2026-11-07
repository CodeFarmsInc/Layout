
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class nodeToEdges_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_nodeToEdges_LINKED_LIST1_INCLUDED
#define ZZ_nodeToEdges_LINKED_LIST1_INCLUDED

class Node;
class EdgeRef;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class nodeToEdges_LinkedList1Parent {
public:
    EdgeRef* tail;
    nodeToEdges_LinkedList1Parent(){ tail=NULL; }
};

class nodeToEdges_LinkedList1Child : public nodeToEdges_Ring1Element {
public:
    nodeToEdges_LinkedList1Child() : nodeToEdges_Ring1Element(){ }
};

// the following class is used when Parent==Child
class nodeToEdges_LinkedList1ParentLinkedList1Child : public nodeToEdges_Ring1Element {
public:
    EdgeRef* tail;
    nodeToEdges_LinkedList1ParentLinkedList1Child() : nodeToEdges_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class nodeToEdges_LinkedList1 : nodeToEdges_Ring1 {

public:
    static EdgeRef *tail(Node *p);
    static EdgeRef *head(Node *p);
    static void addHead(Node *p, EdgeRef *c);
    static void addTail(Node *p, EdgeRef *c);
    static void append(Node *p,EdgeRef *c1, EdgeRef *c2);
    static void remove(Node *p, EdgeRef *c);
    static EdgeRef* const next(Node *p,EdgeRef *c);
    static EdgeRef* const nextRing(EdgeRef *c);
    static void sort(ZZsortFun cmpFun, Node *p);
    static void merge(EdgeRef *s,EdgeRef *t,Node *p);
    static void setTail(Node* p,EdgeRef* c,int check);

    // historical DOL compatible interface
    static void del(Node *p, EdgeRef *c){ remove(p,c);}
    static void add(Node *p, EdgeRef *c){ addHead(p,c);}
    static EdgeRef* child(Node *p);
    static void set(Node* p,EdgeRef* c){ setTail(p,c,0);}
    static EdgeRef* const fwd(EdgeRef *c){ return nextRing(c);}
};

class nodeToEdges_LinkedList1Iterator : public nodeToEdges_Ring1Iterator {
public:
    nodeToEdges_LinkedList1Iterator() : nodeToEdges_Ring1Iterator(){}
    nodeToEdges_LinkedList1Iterator(const Node *p) : nodeToEdges_Ring1Iterator(){start(p);}
    void start(const Node *p);
    EdgeRef* fromHead(Node *p);
};
    
#endif // ZZ_nodeToEdges_LINKED_LIST1_INCLUDED
