
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class AtoB_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_AtoB_LINKED_LIST2_INCLUDED
#define ZZ_AtoB_LINKED_LIST2_INCLUDED

class A;
class B;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class AtoB_LinkedList2Parent {
public:
    B* tail;
    AtoB_LinkedList2Parent(){ tail=NULL; }
};

class AtoB_LinkedList2Child : public AtoB_Ring2Element {
public:
    AtoB_LinkedList2Child() : AtoB_Ring2Element(){ }
};

// the following class is used when Parent==Child
class AtoB_LinkedList2ParentLinkedList2Child : public AtoB_Ring2Element {
public:
    B* tail;
    AtoB_LinkedList2ParentLinkedList2Child() : AtoB_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class AtoB_LinkedList2 : AtoB_Ring2 {

public:
    static B* const tail(A *p);
    static B* const head(A *p);
    static void addHead(A *p, B *c);
    static void addTail(A *p, B *c);
    static void append(A *p,B *c1, B *c2);
    static void insert(B *c1, B *c2);
    static void remove(A *p, B *c);
    static B* const next(A *p, B *c);
    static B* const prev(A *p, B *c);
    static B* const nextRing(B *c);
    static B* const prevRing(B *c);
    static void sort(ZZsortFun cmpFun, A *p);
    static void merge(B *s,B *t,A *p);
    static void setTail(A* p,B* c,int check);

    // historical DOL compatible interface
    static void del(A *p, B *c) { remove(p,c); }
    static void add(A *p, B *c) { addHead(p,c);}
    static void ins(B *c1, B *c2) { insert(c1,c2); }
    static B* child(A* p);
    static void set(A* p,B* c){ setTail(p,c,0);}
    static B* const fwd(B *c){return nextRing(c);}
    static B* const bwd(B *c){return prevRing(c);}
};

class AtoB_LinkedList2Iterator : public AtoB_Ring2Iterator {
public:
    AtoB_LinkedList2Iterator() : AtoB_Ring2Iterator(){}
    AtoB_LinkedList2Iterator(const A *p) : AtoB_Ring2Iterator(){ start(p); }
    void start(const A *p);
    B* fromHead(A *p);
    B* fromTail(A *p);
};
    
#endif // ZZ_AtoB_LINKED_LIST2_INCLUDED
