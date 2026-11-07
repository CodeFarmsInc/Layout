
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class usedBy_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_usedBy_LINKED_LIST2_INCLUDED
#define ZZ_usedBy_LINKED_LIST2_INCLUDED

class ApplClass;
class Participant;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class usedBy_LinkedList2Parent {
public:
    Participant* tail;
    usedBy_LinkedList2Parent(){ tail=NULL; }
};

class usedBy_LinkedList2Child : public usedBy_Ring2Element {
public:
    usedBy_LinkedList2Child() : usedBy_Ring2Element(){ }
};

// the following class is used when Parent==Child
class usedBy_LinkedList2ParentLinkedList2Child : public usedBy_Ring2Element {
public:
    Participant* tail;
    usedBy_LinkedList2ParentLinkedList2Child() : usedBy_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class usedBy_LinkedList2 : usedBy_Ring2 {

public:
    static Participant* const tail(ApplClass *p);
    static Participant* const head(ApplClass *p);
    static void addHead(ApplClass *p, Participant *c);
    static void addTail(ApplClass *p, Participant *c);
    static void append(ApplClass *p,Participant *c1, Participant *c2);
    static void insert(Participant *c1, Participant *c2);
    static void remove(ApplClass *p, Participant *c);
    static Participant* const next(ApplClass *p, Participant *c);
    static Participant* const prev(ApplClass *p, Participant *c);
    static Participant* const nextRing(Participant *c);
    static Participant* const prevRing(Participant *c);
    static void sort(ZZsortFun cmpFun, ApplClass *p);
    static void merge(Participant *s,Participant *t,ApplClass *p);
    static void setTail(ApplClass* p,Participant* c,int check);

    // historical DOL compatible interface
    static void del(ApplClass *p, Participant *c) { remove(p,c); }
    static void add(ApplClass *p, Participant *c) { addHead(p,c);}
    static void ins(Participant *c1, Participant *c2) { insert(c1,c2); }
    static Participant* child(ApplClass* p);
    static void set(ApplClass* p,Participant* c){ setTail(p,c,0);}
    static Participant* const fwd(Participant *c){return nextRing(c);}
    static Participant* const bwd(Participant *c){return prevRing(c);}
};

class usedBy_LinkedList2Iterator : public usedBy_Ring2Iterator {
public:
    usedBy_LinkedList2Iterator() : usedBy_Ring2Iterator(){}
    usedBy_LinkedList2Iterator(const ApplClass *p) : usedBy_Ring2Iterator(){ start(p); }
    void start(const ApplClass *p);
    Participant* fromHead(ApplClass *p);
    Participant* fromTail(ApplClass *p);
};
    
#endif // ZZ_usedBy_LINKED_LIST2_INCLUDED
