
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class suppliers_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_suppliers_LINKED_LIST1_INCLUDED
#define ZZ_suppliers_LINKED_LIST1_INCLUDED

class Company;
class Supplier;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class suppliers_LinkedList1Parent {
public:
    Supplier* tail;
    suppliers_LinkedList1Parent(){ tail=NULL; }
};

class suppliers_LinkedList1Child : public suppliers_Ring1Element {
public:
    suppliers_LinkedList1Child() : suppliers_Ring1Element(){ }
};

// the following class is used when Parent==Child
class suppliers_LinkedList1ParentLinkedList1Child : public suppliers_Ring1Element {
public:
    Supplier* tail;
    suppliers_LinkedList1ParentLinkedList1Child() : suppliers_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class suppliers_LinkedList1 : suppliers_Ring1 {

public:
    static Supplier *tail(Company *p);
    static Supplier *head(Company *p);
    static void addHead(Company *p, Supplier *c);
    static void addTail(Company *p, Supplier *c);
    static void append(Company *p,Supplier *c1, Supplier *c2);
    static void remove(Company *p, Supplier *c);
    static Supplier* const next(Company *p,Supplier *c);
    static Supplier* const fwd(Supplier *c);
    static void sort(ZZsortFun cmpFun, Company *p);
    static void merge(Supplier *s,Supplier *t,Company *p);
    static void setTail(Company* p,Supplier* c,int check);

    // historical DOL compatible interface
    static void del(Company *p, Supplier *c){ remove(p,c);}
    static void add(Company *p, Supplier *c){ addHead(p,c);}
    static Supplier* child(Company *p);
    static void set(Company* p,Supplier* c){ setTail(p,c,0);}
};

class suppliers_LinkedList1Iterator : public suppliers_Ring1Iterator {
public:
    suppliers_LinkedList1Iterator() : suppliers_Ring1Iterator(){}
    suppliers_LinkedList1Iterator(const Company *p) : suppliers_Ring1Iterator(){start(p);}
    virtual void start(const Company *p);
    virtual Supplier* fromHead(Company *p);
};
    
#endif // ZZ_suppliers_LINKED_LIST1_INCLUDED
