
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class nodes_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_nodes_LINKED_LIST1_INCLUDED
#define ZZ_nodes_LINKED_LIST1_INCLUDED

class Layout;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class nodes_LinkedList1Parent {
public:
    Node* tail;
    nodes_LinkedList1Parent(){ tail=NULL; }
};

class nodes_LinkedList1Child : public nodes_Ring1Element {
public:
    nodes_LinkedList1Child() : nodes_Ring1Element(){ }
};

// the following class is used when Parent==Child
class nodes_LinkedList1ParentLinkedList1Child : public nodes_Ring1Element {
public:
    Node* tail;
    nodes_LinkedList1ParentLinkedList1Child() : nodes_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class nodes_LinkedList1 : nodes_Ring1 {

public:
    static Node *tail(Layout *p);
    static Node *head(Layout *p);
    static void addHead(Layout *p, Node *c);
    static void addTail(Layout *p, Node *c);
    static void append(Layout *p,Node *c1, Node *c2);
    static void remove(Layout *p, Node *c);
    static Node* const next(Layout *p,Node *c);
    static Node* const nextRing(Node *c);
    static void sort(ZZsortFun cmpFun, Layout *p);
    static void merge(Node *s,Node *t,Layout *p);
    static void setTail(Layout* p,Node* c,int check);

    // historical DOL compatible interface
    static void del(Layout *p, Node *c){ remove(p,c);}
    static void add(Layout *p, Node *c){ addHead(p,c);}
    static Node* child(Layout *p);
    static void set(Layout* p,Node* c){ setTail(p,c,0);}
    static Node* const fwd(Node *c){ return nextRing(c);}
};

class nodes_LinkedList1Iterator : public nodes_Ring1Iterator {
public:
    nodes_LinkedList1Iterator() : nodes_Ring1Iterator(){}
    nodes_LinkedList1Iterator(const Layout *p) : nodes_Ring1Iterator(){start(p);}
    void start(const Layout *p);
    Node* fromHead(Layout *p);
};
    
#endif // ZZ_nodes_LINKED_LIST1_INCLUDED
