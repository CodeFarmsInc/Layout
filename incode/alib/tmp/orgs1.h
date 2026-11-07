
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class orgs_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_orgs_LINKED_LIST2_INCLUDED
#define ZZ_orgs_LINKED_LIST2_INCLUDED

class Generator;
class Organization;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class orgs_LinkedList2Parent {
public:
    Organization* tail;
    orgs_LinkedList2Parent(){ tail=NULL; }
};

class orgs_LinkedList2Child : public orgs_Ring2Element {
public:
    orgs_LinkedList2Child() : orgs_Ring2Element(){ }
};

// the following class is used when Parent==Child
class orgs_LinkedList2ParentLinkedList2Child : public orgs_Ring2Element {
public:
    Organization* tail;
    orgs_LinkedList2ParentLinkedList2Child() : orgs_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class orgs_LinkedList2 : orgs_Ring2 {

public:
    static Organization* const tail(Generator *p);
    static Organization* const head(Generator *p);
    static void addHead(Generator *p, Organization *c);
    static void addTail(Generator *p, Organization *c);
    static void append(Generator *p,Organization *c1, Organization *c2);
    static void insert(Organization *c1, Organization *c2);
    static void remove(Generator *p, Organization *c);
    static Organization* const next(Generator *p, Organization *c);
    static Organization* const prev(Generator *p, Organization *c);
    static Organization* const nextRing(Organization *c);
    static Organization* const prevRing(Organization *c);
    static void sort(ZZsortFun cmpFun, Generator *p);
    static void merge(Organization *s,Organization *t,Generator *p);
    static void setTail(Generator* p,Organization* c,int check);

    // historical DOL compatible interface
    static void del(Generator *p, Organization *c) { remove(p,c); }
    static void add(Generator *p, Organization *c) { addHead(p,c);}
    static void ins(Organization *c1, Organization *c2) { insert(c1,c2); }
    static Organization* child(Generator* p);
    static void set(Generator* p,Organization* c){ setTail(p,c,0);}
    static Organization* const fwd(Organization *c){return nextRing(c);}
    static Organization* const bwd(Organization *c){return prevRing(c);}
};

class orgs_LinkedList2Iterator : public orgs_Ring2Iterator {
public:
    orgs_LinkedList2Iterator() : orgs_Ring2Iterator(){}
    orgs_LinkedList2Iterator(const Generator *p) : orgs_Ring2Iterator(){ start(p); }
    void start(const Generator *p);
    Organization* fromHead(Generator *p);
    Organization* fromTail(Generator *p);
};
    
#endif // ZZ_orgs_LINKED_LIST2_INCLUDED
