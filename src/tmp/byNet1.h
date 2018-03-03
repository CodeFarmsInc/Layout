
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class byNet_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_byNet_LINKED_LIST2_INCLUDED
#define ZZ_byNet_LINKED_LIST2_INCLUDED

class Net;
class Edge;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class byNet_LinkedList2Parent {
public:
    Edge* tail;
    byNet_LinkedList2Parent(){ tail=NULL; }
};

class byNet_LinkedList2Child : public byNet_Ring2Element {
public:
    byNet_LinkedList2Child() : byNet_Ring2Element(){ }
};

// the following class is used when Parent==Child
class byNet_LinkedList2ParentLinkedList2Child : public byNet_Ring2Element {
public:
    Edge* tail;
    byNet_LinkedList2ParentLinkedList2Child() : byNet_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class byNet_LinkedList2 : byNet_Ring2 {

public:
    static Edge* const tail(Net *p);
    static Edge* const head(Net *p);
    static void addHead(Net *p, Edge *c);
    static void addTail(Net *p, Edge *c);
    static void append(Net *p,Edge *c1, Edge *c2);
    static void insert(Edge *c1, Edge *c2);
    static void remove(Net *p, Edge *c);
    static Edge* const next(Net *p, Edge *c);
    static Edge* const prev(Net *p, Edge *c);
    static Edge* const nextRing(Edge *c);
    static Edge* const prevRing(Edge *c);
    static void sort(ZZsortFun cmpFun, Net *p);
    static void merge(Edge *s,Edge *t,Net *p);
    static void setTail(Net* p,Edge* c,int check);

    // historical DOL compatible interface
    static void del(Net *p, Edge *c) { remove(p,c); }
    static void add(Net *p, Edge *c) { addHead(p,c);}
    static void ins(Edge *c1, Edge *c2) { insert(c1,c2); }
    static Edge* child(Net* p);
    static void set(Net* p,Edge* c){ setTail(p,c,0);}
    static Edge* const fwd(Edge *c){return nextRing(c);}
    static Edge* const bwd(Edge *c){return prevRing(c);}
};

class byNet_LinkedList2Iterator : public byNet_Ring2Iterator {
public:
    byNet_LinkedList2Iterator() : byNet_Ring2Iterator(){}
    byNet_LinkedList2Iterator(const Net *p) : byNet_Ring2Iterator(){ start(p); }
    void start(const Net *p);
    Edge* fromHead(Net *p);
    Edge* fromTail(Net *p);
};
    
#endif // ZZ_byNet_LINKED_LIST2_INCLUDED
