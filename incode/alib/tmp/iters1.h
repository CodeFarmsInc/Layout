
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class iters_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_iters_LINKED_LIST1_INCLUDED
#define ZZ_iters_LINKED_LIST1_INCLUDED

class OrgType;
class Iterator;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class iters_LinkedList1Parent {
public:
    Iterator* tail;
    iters_LinkedList1Parent(){ tail=NULL; }
};

class iters_LinkedList1Child : public iters_Ring1Element {
public:
    iters_LinkedList1Child() : iters_Ring1Element(){ }
};

// the following class is used when Parent==Child
class iters_LinkedList1ParentLinkedList1Child : public iters_Ring1Element {
public:
    Iterator* tail;
    iters_LinkedList1ParentLinkedList1Child() : iters_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class iters_LinkedList1 : iters_Ring1 {

public:
    static Iterator *tail(OrgType *p);
    static Iterator *head(OrgType *p);
    static void addHead(OrgType *p, Iterator *c);
    static void addTail(OrgType *p, Iterator *c);
    static void append(OrgType *p,Iterator *c1, Iterator *c2);
    static void remove(OrgType *p, Iterator *c);
    static Iterator* const next(OrgType *p,Iterator *c);
    static Iterator* const nextRing(Iterator *c);
    static void sort(ZZsortFun cmpFun, OrgType *p);
    static void merge(Iterator *s,Iterator *t,OrgType *p);
    static void setTail(OrgType* p,Iterator* c,int check);

    // historical DOL compatible interface
    static void del(OrgType *p, Iterator *c){ remove(p,c);}
    static void add(OrgType *p, Iterator *c){ addHead(p,c);}
    static Iterator* child(OrgType *p);
    static void set(OrgType* p,Iterator* c){ setTail(p,c,0);}
    static Iterator* const fwd(Iterator *c){ return nextRing(c);}
};

class iters_LinkedList1Iterator : public iters_Ring1Iterator {
public:
    iters_LinkedList1Iterator() : iters_Ring1Iterator(){}
    iters_LinkedList1Iterator(const OrgType *p) : iters_Ring1Iterator(){start(p);}
    void start(const OrgType *p);
    Iterator* fromHead(OrgType *p);
};
    
#endif // ZZ_iters_LINKED_LIST1_INCLUDED
