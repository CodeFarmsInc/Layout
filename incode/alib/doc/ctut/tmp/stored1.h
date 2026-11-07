
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class stored_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_stored_LINKED_LIST2_INCLUDED
#define ZZ_stored_LINKED_LIST2_INCLUDED

class Warehouse;
class PartType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class stored_LinkedList2Parent {
public:
    PartType* tail;
    stored_LinkedList2Parent(){ tail=NULL; }
};

class stored_LinkedList2Child : public stored_Ring2Element {
public:
    stored_LinkedList2Child() : stored_Ring2Element(){ }
};

// the following class is used when Parent==Child
class stored_LinkedList2ParentLinkedList2Child : public stored_Ring2Element {
public:
    PartType* tail;
    stored_LinkedList2ParentLinkedList2Child() : stored_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class stored_LinkedList2 : stored_Ring2 {

public:
    static PartType* const tail(Warehouse *p);
    static PartType* const head(Warehouse *p);
    static void addHead(Warehouse *p, PartType *c);
    static void addTail(Warehouse *p, PartType *c);
    static void append(Warehouse *p,PartType *c1, PartType *c2);
    static void insert(PartType *c1, PartType *c2);
    static void remove(Warehouse *p, PartType *c);
    static PartType* const next(Warehouse *p, PartType *c);
    static PartType* const prev(Warehouse *p, PartType *c);
    static PartType* const fwd(PartType *c);
    static PartType* const bwd(PartType *c);
    static void sort(ZZsortFun cmpFun, Warehouse *p);
    static void merge(PartType *s,PartType *t,Warehouse *p);
    static void setTail(Warehouse* p,PartType* c,int check);

    // historical DOL compatible interface
    static void del(Warehouse *p, PartType *c) { remove(p,c); }
    static void add(Warehouse *p, PartType *c) { addHead(p,c);}
    static void ins(PartType *c1, PartType *c2) { insert(c1,c2); }
    static PartType* child(Warehouse* p);
    static void set(Warehouse* p,PartType* c){ setTail(p,c,0);}
};

class stored_LinkedList2Iterator : public stored_Ring2Iterator {
public:
    stored_LinkedList2Iterator() : stored_Ring2Iterator(){}
    stored_LinkedList2Iterator(const Warehouse *p) : stored_Ring2Iterator(){ start(p); }
    virtual void start(const Warehouse *p);
    virtual PartType* fromHead(Warehouse *p);
    virtual PartType* fromTail(Warehouse *p);
};
    
#endif // ZZ_stored_LINKED_LIST2_INCLUDED
