
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class groups_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_groups_LINKED_LIST1_INCLUDED
#define ZZ_groups_LINKED_LIST1_INCLUDED

class Layout;
class Group;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class groups_LinkedList1Parent {
public:
    Group* tail;
    groups_LinkedList1Parent(){ tail=NULL; }
};

class groups_LinkedList1Child : public groups_Ring1Element {
public:
    groups_LinkedList1Child() : groups_Ring1Element(){ }
};

// the following class is used when Parent==Child
class groups_LinkedList1ParentLinkedList1Child : public groups_Ring1Element {
public:
    Group* tail;
    groups_LinkedList1ParentLinkedList1Child() : groups_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class groups_LinkedList1 : groups_Ring1 {

public:
    static Group *tail(Layout *p);
    static Group *head(Layout *p);
    static void addHead(Layout *p, Group *c);
    static void addTail(Layout *p, Group *c);
    static void append(Layout *p,Group *c1, Group *c2);
    static void remove(Layout *p, Group *c);
    static Group* const next(Layout *p,Group *c);
    static Group* const nextRing(Group *c);
    static void sort(ZZsortFun cmpFun, Layout *p);
    static void merge(Group *s,Group *t,Layout *p);
    static void setTail(Layout* p,Group* c,int check);

    // historical DOL compatible interface
    static void del(Layout *p, Group *c){ remove(p,c);}
    static void add(Layout *p, Group *c){ addHead(p,c);}
    static Group* child(Layout *p);
    static void set(Layout* p,Group* c){ setTail(p,c,0);}
    static Group* const fwd(Group *c){ return nextRing(c);}
};

class groups_LinkedList1Iterator : public groups_Ring1Iterator {
public:
    groups_LinkedList1Iterator() : groups_Ring1Iterator(){}
    groups_LinkedList1Iterator(const Layout *p) : groups_Ring1Iterator(){start(p);}
    void start(const Layout *p);
    Group* fromHead(Layout *p);
};
    
#endif // ZZ_groups_LINKED_LIST1_INCLUDED
