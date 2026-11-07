
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class pairs_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_pairs_LINKED_LIST1_INCLUDED
#define ZZ_pairs_LINKED_LIST1_INCLUDED

class Layout;
class Pair;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class pairs_LinkedList1Parent {
public:
    Pair* tail;
    pairs_LinkedList1Parent(){ tail=NULL; }
};

class pairs_LinkedList1Child : public pairs_Ring1Element {
public:
    pairs_LinkedList1Child() : pairs_Ring1Element(){ }
};

// the following class is used when Parent==Child
class pairs_LinkedList1ParentLinkedList1Child : public pairs_Ring1Element {
public:
    Pair* tail;
    pairs_LinkedList1ParentLinkedList1Child() : pairs_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class pairs_LinkedList1 : pairs_Ring1 {

public:
    static Pair *tail(Layout *p);
    static Pair *head(Layout *p);
    static void addHead(Layout *p, Pair *c);
    static void addTail(Layout *p, Pair *c);
    static void append(Layout *p,Pair *c1, Pair *c2);
    static void remove(Layout *p, Pair *c);
    static Pair* const next(Layout *p,Pair *c);
    static Pair* const nextRing(Pair *c);
    static void sort(ZZsortFun cmpFun, Layout *p);
    static void merge(Pair *s,Pair *t,Layout *p);
    static void setTail(Layout* p,Pair* c,int check);

    // historical DOL compatible interface
    static void del(Layout *p, Pair *c){ remove(p,c);}
    static void add(Layout *p, Pair *c){ addHead(p,c);}
    static Pair* child(Layout *p);
    static void set(Layout* p,Pair* c){ setTail(p,c,0);}
    static Pair* const fwd(Pair *c){ return nextRing(c);}
};

class pairs_LinkedList1Iterator : public pairs_Ring1Iterator {
public:
    pairs_LinkedList1Iterator() : pairs_Ring1Iterator(){}
    pairs_LinkedList1Iterator(const Layout *p) : pairs_Ring1Iterator(){start(p);}
    void start(const Layout *p);
    Pair* fromHead(Layout *p);
};
    
#endif // ZZ_pairs_LINKED_LIST1_INCLUDED
