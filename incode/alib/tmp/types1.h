
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class types_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_types_LINKED_LIST2_INCLUDED
#define ZZ_types_LINKED_LIST2_INCLUDED

class Generator;
class OrgType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class types_LinkedList2Parent {
public:
    OrgType* tail;
    types_LinkedList2Parent(){ tail=NULL; }
};

class types_LinkedList2Child : public types_Ring2Element {
public:
    types_LinkedList2Child() : types_Ring2Element(){ }
};

// the following class is used when Parent==Child
class types_LinkedList2ParentLinkedList2Child : public types_Ring2Element {
public:
    OrgType* tail;
    types_LinkedList2ParentLinkedList2Child() : types_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class types_LinkedList2 : types_Ring2 {

public:
    static OrgType* const tail(Generator *p);
    static OrgType* const head(Generator *p);
    static void addHead(Generator *p, OrgType *c);
    static void addTail(Generator *p, OrgType *c);
    static void append(Generator *p,OrgType *c1, OrgType *c2);
    static void insert(OrgType *c1, OrgType *c2);
    static void remove(Generator *p, OrgType *c);
    static OrgType* const next(Generator *p, OrgType *c);
    static OrgType* const prev(Generator *p, OrgType *c);
    static OrgType* const nextRing(OrgType *c);
    static OrgType* const prevRing(OrgType *c);
    static void sort(ZZsortFun cmpFun, Generator *p);
    static void merge(OrgType *s,OrgType *t,Generator *p);
    static void setTail(Generator* p,OrgType* c,int check);

    // historical DOL compatible interface
    static void del(Generator *p, OrgType *c) { remove(p,c); }
    static void add(Generator *p, OrgType *c) { addHead(p,c);}
    static void ins(OrgType *c1, OrgType *c2) { insert(c1,c2); }
    static OrgType* child(Generator* p);
    static void set(Generator* p,OrgType* c){ setTail(p,c,0);}
    static OrgType* const fwd(OrgType *c){return nextRing(c);}
    static OrgType* const bwd(OrgType *c){return prevRing(c);}
};

class types_LinkedList2Iterator : public types_Ring2Iterator {
public:
    types_LinkedList2Iterator() : types_Ring2Iterator(){}
    types_LinkedList2Iterator(const Generator *p) : types_Ring2Iterator(){ start(p); }
    void start(const Generator *p);
    OrgType* fromHead(Generator *p);
    OrgType* fromTail(Generator *p);
};
    
#endif // ZZ_types_LINKED_LIST2_INCLUDED
