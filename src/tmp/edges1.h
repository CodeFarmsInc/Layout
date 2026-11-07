
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class edges_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_edges_LINKED_LIST1_INCLUDED
#define ZZ_edges_LINKED_LIST1_INCLUDED

class Layout;
class Edge;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class edges_LinkedList1Parent {
public:
    Edge* tail;
    edges_LinkedList1Parent(){ tail=NULL; }
};

class edges_LinkedList1Child : public edges_Ring1Element {
public:
    edges_LinkedList1Child() : edges_Ring1Element(){ }
};

// the following class is used when Parent==Child
class edges_LinkedList1ParentLinkedList1Child : public edges_Ring1Element {
public:
    Edge* tail;
    edges_LinkedList1ParentLinkedList1Child() : edges_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class edges_LinkedList1 : edges_Ring1 {

public:
    static Edge *tail(Layout *p);
    static Edge *head(Layout *p);
    static void addHead(Layout *p, Edge *c);
    static void addTail(Layout *p, Edge *c);
    static void append(Layout *p,Edge *c1, Edge *c2);
    static void remove(Layout *p, Edge *c);
    static Edge* const next(Layout *p,Edge *c);
    static Edge* const nextRing(Edge *c);
    static void sort(ZZsortFun cmpFun, Layout *p);
    static void merge(Edge *s,Edge *t,Layout *p);
    static void setTail(Layout* p,Edge* c,int check);

    // historical DOL compatible interface
    static void del(Layout *p, Edge *c){ remove(p,c);}
    static void add(Layout *p, Edge *c){ addHead(p,c);}
    static Edge* child(Layout *p);
    static void set(Layout* p,Edge* c){ setTail(p,c,0);}
    static Edge* const fwd(Edge *c){ return nextRing(c);}
};

class edges_LinkedList1Iterator : public edges_Ring1Iterator {
public:
    edges_LinkedList1Iterator() : edges_Ring1Iterator(){}
    edges_LinkedList1Iterator(const Layout *p) : edges_Ring1Iterator(){start(p);}
    void start(const Layout *p);
    Edge* fromHead(Layout *p);
};
    
#endif // ZZ_edges_LINKED_LIST1_INCLUDED
