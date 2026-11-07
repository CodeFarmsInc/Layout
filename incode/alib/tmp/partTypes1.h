
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class partTypes_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_partTypes_LINKED_LIST2_INCLUDED
#define ZZ_partTypes_LINKED_LIST2_INCLUDED

class OrgType;
class PartType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class partTypes_LinkedList2Parent {
public:
    PartType* tail;
    partTypes_LinkedList2Parent(){ tail=NULL; }
};

class partTypes_LinkedList2Child : public partTypes_Ring2Element {
public:
    partTypes_LinkedList2Child() : partTypes_Ring2Element(){ }
};

// the following class is used when Parent==Child
class partTypes_LinkedList2ParentLinkedList2Child : public partTypes_Ring2Element {
public:
    PartType* tail;
    partTypes_LinkedList2ParentLinkedList2Child() : partTypes_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class partTypes_LinkedList2 : partTypes_Ring2 {

public:
    static PartType* const tail(OrgType *p);
    static PartType* const head(OrgType *p);
    static void addHead(OrgType *p, PartType *c);
    static void addTail(OrgType *p, PartType *c);
    static void append(OrgType *p,PartType *c1, PartType *c2);
    static void insert(PartType *c1, PartType *c2);
    static void remove(OrgType *p, PartType *c);
    static PartType* const next(OrgType *p, PartType *c);
    static PartType* const prev(OrgType *p, PartType *c);
    static PartType* const nextRing(PartType *c);
    static PartType* const prevRing(PartType *c);
    static void sort(ZZsortFun cmpFun, OrgType *p);
    static void merge(PartType *s,PartType *t,OrgType *p);
    static void setTail(OrgType* p,PartType* c,int check);

    // historical DOL compatible interface
    static void del(OrgType *p, PartType *c) { remove(p,c); }
    static void add(OrgType *p, PartType *c) { addHead(p,c);}
    static void ins(PartType *c1, PartType *c2) { insert(c1,c2); }
    static PartType* child(OrgType* p);
    static void set(OrgType* p,PartType* c){ setTail(p,c,0);}
    static PartType* const fwd(PartType *c){return nextRing(c);}
    static PartType* const bwd(PartType *c){return prevRing(c);}
};

class partTypes_LinkedList2Iterator : public partTypes_Ring2Iterator {
public:
    partTypes_LinkedList2Iterator() : partTypes_Ring2Iterator(){}
    partTypes_LinkedList2Iterator(const OrgType *p) : partTypes_Ring2Iterator(){ start(p); }
    void start(const OrgType *p);
    PartType* fromHead(OrgType *p);
    PartType* fromTail(OrgType *p);
};
    
#endif // ZZ_partTypes_LINKED_LIST2_INCLUDED
