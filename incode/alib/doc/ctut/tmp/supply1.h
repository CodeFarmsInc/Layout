
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class supply_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_supply_LINKED_LIST2_INCLUDED
#define ZZ_supply_LINKED_LIST2_INCLUDED

class Supplier;
class PartType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class supply_LinkedList2Parent {
public:
    PartType* tail;
    supply_LinkedList2Parent(){ tail=NULL; }
};

class supply_LinkedList2Child : public supply_Ring2Element {
public:
    supply_LinkedList2Child() : supply_Ring2Element(){ }
};

// the following class is used when Parent==Child
class supply_LinkedList2ParentLinkedList2Child : public supply_Ring2Element {
public:
    PartType* tail;
    supply_LinkedList2ParentLinkedList2Child() : supply_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class supply_LinkedList2 : supply_Ring2 {

public:
    static PartType* const tail(Supplier *p);
    static PartType* const head(Supplier *p);
    static void addHead(Supplier *p, PartType *c);
    static void addTail(Supplier *p, PartType *c);
    static void append(Supplier *p,PartType *c1, PartType *c2);
    static void insert(PartType *c1, PartType *c2);
    static void remove(Supplier *p, PartType *c);
    static PartType* const next(Supplier *p, PartType *c);
    static PartType* const prev(Supplier *p, PartType *c);
    static PartType* const fwd(PartType *c);
    static PartType* const bwd(PartType *c);
    static void sort(ZZsortFun cmpFun, Supplier *p);
    static void merge(PartType *s,PartType *t,Supplier *p);
    static void setTail(Supplier* p,PartType* c,int check);

    // historical DOL compatible interface
    static void del(Supplier *p, PartType *c) { remove(p,c); }
    static void add(Supplier *p, PartType *c) { addHead(p,c);}
    static void ins(PartType *c1, PartType *c2) { insert(c1,c2); }
    static PartType* child(Supplier* p);
    static void set(Supplier* p,PartType* c){ setTail(p,c,0);}
};

class supply_LinkedList2Iterator : public supply_Ring2Iterator {
public:
    supply_LinkedList2Iterator() : supply_Ring2Iterator(){}
    supply_LinkedList2Iterator(const Supplier *p) : supply_Ring2Iterator(){ start(p); }
    virtual void start(const Supplier *p);
    virtual PartType* fromHead(Supplier *p);
    virtual PartType* fromTail(Supplier *p);
};
    
#endif // ZZ_supply_LINKED_LIST2_INCLUDED
