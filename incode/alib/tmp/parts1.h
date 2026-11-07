
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class parts_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_parts_LINKED_LIST2_INCLUDED
#define ZZ_parts_LINKED_LIST2_INCLUDED

class Organization;
class Participant;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class parts_LinkedList2Parent {
public:
    Participant* tail;
    parts_LinkedList2Parent(){ tail=NULL; }
};

class parts_LinkedList2Child : public parts_Ring2Element {
public:
    parts_LinkedList2Child() : parts_Ring2Element(){ }
};

// the following class is used when Parent==Child
class parts_LinkedList2ParentLinkedList2Child : public parts_Ring2Element {
public:
    Participant* tail;
    parts_LinkedList2ParentLinkedList2Child() : parts_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class parts_LinkedList2 : parts_Ring2 {

public:
    static Participant* const tail(Organization *p);
    static Participant* const head(Organization *p);
    static void addHead(Organization *p, Participant *c);
    static void addTail(Organization *p, Participant *c);
    static void append(Organization *p,Participant *c1, Participant *c2);
    static void insert(Participant *c1, Participant *c2);
    static void remove(Organization *p, Participant *c);
    static Participant* const next(Organization *p, Participant *c);
    static Participant* const prev(Organization *p, Participant *c);
    static Participant* const nextRing(Participant *c);
    static Participant* const prevRing(Participant *c);
    static void sort(ZZsortFun cmpFun, Organization *p);
    static void merge(Participant *s,Participant *t,Organization *p);
    static void setTail(Organization* p,Participant* c,int check);

    // historical DOL compatible interface
    static void del(Organization *p, Participant *c) { remove(p,c); }
    static void add(Organization *p, Participant *c) { addHead(p,c);}
    static void ins(Participant *c1, Participant *c2) { insert(c1,c2); }
    static Participant* child(Organization* p);
    static void set(Organization* p,Participant* c){ setTail(p,c,0);}
    static Participant* const fwd(Participant *c){return nextRing(c);}
    static Participant* const bwd(Participant *c){return prevRing(c);}
};

class parts_LinkedList2Iterator : public parts_Ring2Iterator {
public:
    parts_LinkedList2Iterator() : parts_Ring2Iterator(){}
    parts_LinkedList2Iterator(const Organization *p) : parts_Ring2Iterator(){ start(p); }
    void start(const Organization *p);
    Participant* fromHead(Organization *p);
    Participant* fromTail(Organization *p);
};
    
#endif // ZZ_parts_LINKED_LIST2_INCLUDED
