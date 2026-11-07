
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class nets_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_nets_LINKED_LIST2_INCLUDED
#define ZZ_nets_LINKED_LIST2_INCLUDED

class Layout;
class Net;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class nets_LinkedList2Parent {
public:
    Net* tail;
    nets_LinkedList2Parent(){ tail=NULL; }
};

class nets_LinkedList2Child : public nets_Ring2Element {
public:
    nets_LinkedList2Child() : nets_Ring2Element(){ }
};

// the following class is used when Parent==Child
class nets_LinkedList2ParentLinkedList2Child : public nets_Ring2Element {
public:
    Net* tail;
    nets_LinkedList2ParentLinkedList2Child() : nets_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class nets_LinkedList2 : nets_Ring2 {

public:
    static Net* const tail(Layout *p);
    static Net* const head(Layout *p);
    static void addHead(Layout *p, Net *c);
    static void addTail(Layout *p, Net *c);
    static void append(Layout *p,Net *c1, Net *c2);
    static void insert(Net *c1, Net *c2);
    static void remove(Layout *p, Net *c);
    static Net* const next(Layout *p, Net *c);
    static Net* const prev(Layout *p, Net *c);
    static Net* const nextRing(Net *c);
    static Net* const prevRing(Net *c);
    static void sort(ZZsortFun cmpFun, Layout *p);
    static void merge(Net *s,Net *t,Layout *p);
    static void setTail(Layout* p,Net* c,int check);

    // historical DOL compatible interface
    static void del(Layout *p, Net *c) { remove(p,c); }
    static void add(Layout *p, Net *c) { addHead(p,c);}
    static void ins(Net *c1, Net *c2) { insert(c1,c2); }
    static Net* child(Layout* p);
    static void set(Layout* p,Net* c){ setTail(p,c,0);}
    static Net* const fwd(Net *c){return nextRing(c);}
    static Net* const bwd(Net *c){return prevRing(c);}
};

class nets_LinkedList2Iterator : public nets_Ring2Iterator {
public:
    nets_LinkedList2Iterator() : nets_Ring2Iterator(){}
    nets_LinkedList2Iterator(const Layout *p) : nets_Ring2Iterator(){ start(p); }
    void start(const Layout *p);
    Net* fromHead(Layout *p);
    Net* fromTail(Layout *p);
};
    
#endif // ZZ_nets_LINKED_LIST2_INCLUDED
