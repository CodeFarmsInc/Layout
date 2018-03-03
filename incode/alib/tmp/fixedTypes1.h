
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class fixedTypes_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_fixedTypes_LINKED_LIST1_INCLUDED
#define ZZ_fixedTypes_LINKED_LIST1_INCLUDED

class OrgType;
class FixedType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class fixedTypes_LinkedList1Parent {
public:
    FixedType* tail;
    fixedTypes_LinkedList1Parent(){ tail=NULL; }
};

class fixedTypes_LinkedList1Child : public fixedTypes_Ring1Element {
public:
    fixedTypes_LinkedList1Child() : fixedTypes_Ring1Element(){ }
};

// the following class is used when Parent==Child
class fixedTypes_LinkedList1ParentLinkedList1Child : public fixedTypes_Ring1Element {
public:
    FixedType* tail;
    fixedTypes_LinkedList1ParentLinkedList1Child() : fixedTypes_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class fixedTypes_LinkedList1 : fixedTypes_Ring1 {

public:
    static FixedType *tail(OrgType *p);
    static FixedType *head(OrgType *p);
    static void addHead(OrgType *p, FixedType *c);
    static void addTail(OrgType *p, FixedType *c);
    static void append(OrgType *p,FixedType *c1, FixedType *c2);
    static void remove(OrgType *p, FixedType *c);
    static FixedType* const next(OrgType *p,FixedType *c);
    static FixedType* const nextRing(FixedType *c);
    static void sort(ZZsortFun cmpFun, OrgType *p);
    static void merge(FixedType *s,FixedType *t,OrgType *p);
    static void setTail(OrgType* p,FixedType* c,int check);

    // historical DOL compatible interface
    static void del(OrgType *p, FixedType *c){ remove(p,c);}
    static void add(OrgType *p, FixedType *c){ addHead(p,c);}
    static FixedType* child(OrgType *p);
    static void set(OrgType* p,FixedType* c){ setTail(p,c,0);}
    static FixedType* const fwd(FixedType *c){ return nextRing(c);}
};

class fixedTypes_LinkedList1Iterator : public fixedTypes_Ring1Iterator {
public:
    fixedTypes_LinkedList1Iterator() : fixedTypes_Ring1Iterator(){}
    fixedTypes_LinkedList1Iterator(const OrgType *p) : fixedTypes_Ring1Iterator(){start(p);}
    void start(const OrgType *p);
    FixedType* fromHead(OrgType *p);
};
    
#endif // ZZ_fixedTypes_LINKED_LIST1_INCLUDED
