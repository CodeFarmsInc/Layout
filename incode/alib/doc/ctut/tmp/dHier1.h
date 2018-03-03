
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class dHier_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_dHier_LINKED_LIST1_INCLUDED
#define ZZ_dHier_LINKED_LIST1_INCLUDED

class Department;
class Department;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class dHier_LinkedList1Parent {
public:
    Department* tail;
    dHier_LinkedList1Parent(){ tail=NULL; }
};

class dHier_LinkedList1Child : public dHier_Ring1Element {
public:
    dHier_LinkedList1Child() : dHier_Ring1Element(){ }
};

// the following class is used when Parent==Child
class dHier_LinkedList1ParentLinkedList1Child : public dHier_Ring1Element {
public:
    Department* tail;
    dHier_LinkedList1ParentLinkedList1Child() : dHier_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class dHier_LinkedList1 : dHier_Ring1 {

public:
    static Department *tail(Department *p);
    static Department *head(Department *p);
    static void addHead(Department *p, Department *c);
    static void addTail(Department *p, Department *c);
    static void append(Department *p,Department *c1, Department *c2);
    static void remove(Department *p, Department *c);
    static Department* const next(Department *p,Department *c);
    static Department* const fwd(Department *c);
    static void sort(ZZsortFun cmpFun, Department *p);
    static void merge(Department *s,Department *t,Department *p);
    static void setTail(Department* p,Department* c,int check);

    // historical DOL compatible interface
    static void del(Department *p, Department *c){ remove(p,c);}
    static void add(Department *p, Department *c){ addHead(p,c);}
    static Department* child(Department *p);
    static void set(Department* p,Department* c){ setTail(p,c,0);}
};

class dHier_LinkedList1Iterator : public dHier_Ring1Iterator {
public:
    dHier_LinkedList1Iterator() : dHier_Ring1Iterator(){}
    dHier_LinkedList1Iterator(const Department *p) : dHier_Ring1Iterator(){start(p);}
    virtual void start(const Department *p);
    virtual Department* fromHead(Department *p);
};
    
#endif // ZZ_dHier_LINKED_LIST1_INCLUDED
