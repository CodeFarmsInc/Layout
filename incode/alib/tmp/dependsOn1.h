
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class dependsOn_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_dependsOn_LINKED_LIST1_INCLUDED
#define ZZ_dependsOn_LINKED_LIST1_INCLUDED

class ApplClass;
class ClassLink;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class dependsOn_LinkedList1Parent {
public:
    ClassLink* tail;
    dependsOn_LinkedList1Parent(){ tail=NULL; }
};

class dependsOn_LinkedList1Child : public dependsOn_Ring1Element {
public:
    dependsOn_LinkedList1Child() : dependsOn_Ring1Element(){ }
};

// the following class is used when Parent==Child
class dependsOn_LinkedList1ParentLinkedList1Child : public dependsOn_Ring1Element {
public:
    ClassLink* tail;
    dependsOn_LinkedList1ParentLinkedList1Child() : dependsOn_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class dependsOn_LinkedList1 : dependsOn_Ring1 {

public:
    static ClassLink *tail(ApplClass *p);
    static ClassLink *head(ApplClass *p);
    static void addHead(ApplClass *p, ClassLink *c);
    static void addTail(ApplClass *p, ClassLink *c);
    static void append(ApplClass *p,ClassLink *c1, ClassLink *c2);
    static void remove(ApplClass *p, ClassLink *c);
    static ClassLink* const next(ApplClass *p,ClassLink *c);
    static ClassLink* const nextRing(ClassLink *c);
    static void sort(ZZsortFun cmpFun, ApplClass *p);
    static void merge(ClassLink *s,ClassLink *t,ApplClass *p);
    static void setTail(ApplClass* p,ClassLink* c,int check);

    // historical DOL compatible interface
    static void del(ApplClass *p, ClassLink *c){ remove(p,c);}
    static void add(ApplClass *p, ClassLink *c){ addHead(p,c);}
    static ClassLink* child(ApplClass *p);
    static void set(ApplClass* p,ClassLink* c){ setTail(p,c,0);}
    static ClassLink* const fwd(ClassLink *c){ return nextRing(c);}
};

class dependsOn_LinkedList1Iterator : public dependsOn_Ring1Iterator {
public:
    dependsOn_LinkedList1Iterator() : dependsOn_Ring1Iterator(){}
    dependsOn_LinkedList1Iterator(const ApplClass *p) : dependsOn_Ring1Iterator(){start(p);}
    void start(const ApplClass *p);
    ClassLink* fromHead(ApplClass *p);
};
    
#endif // ZZ_dependsOn_LINKED_LIST1_INCLUDED
