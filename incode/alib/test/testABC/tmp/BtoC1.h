
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class BtoC_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_BtoC_LINKED_LIST1_INCLUDED
#define ZZ_BtoC_LINKED_LIST1_INCLUDED

class B;
class C;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class BtoC_LinkedList1Parent {
public:
    C* tail;
    BtoC_LinkedList1Parent(){ tail=NULL; }
};

class BtoC_LinkedList1Child : public BtoC_Ring1Element {
public:
    BtoC_LinkedList1Child() : BtoC_Ring1Element(){ }
};

// the following class is used when Parent==Child
class BtoC_LinkedList1ParentLinkedList1Child : public BtoC_Ring1Element {
public:
    C* tail;
    BtoC_LinkedList1ParentLinkedList1Child() : BtoC_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class BtoC_LinkedList1 : BtoC_Ring1 {

public:
    static C *tail(B *p);
    static C *head(B *p);
    static void addHead(B *p, C *c);
    static void addTail(B *p, C *c);
    static void append(B *p,C *c1, C *c2);
    static void remove(B *p, C *c);
    static C* const next(B *p,C *c);
    static C* const nextRing(C *c);
    static void sort(ZZsortFun cmpFun, B *p);
    static void merge(C *s,C *t,B *p);
    static void setTail(B* p,C* c,int check);

    // historical DOL compatible interface
    static void del(B *p, C *c){ remove(p,c);}
    static void add(B *p, C *c){ addHead(p,c);}
    static C* child(B *p);
    static void set(B* p,C* c){ setTail(p,c,0);}
    static C* const fwd(C *c){ return nextRing(c);}
};

class BtoC_LinkedList1Iterator : public BtoC_Ring1Iterator {
public:
    BtoC_LinkedList1Iterator() : BtoC_Ring1Iterator(){}
    BtoC_LinkedList1Iterator(const B *p) : BtoC_Ring1Iterator(){start(p);}
    void start(const B *p);
    C* fromHead(B *p);
};
    
#endif // ZZ_BtoC_LINKED_LIST1_INCLUDED
