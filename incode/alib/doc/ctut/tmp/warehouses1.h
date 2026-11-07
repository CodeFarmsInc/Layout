
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class warehouses_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_warehouses_LINKED_LIST1_INCLUDED
#define ZZ_warehouses_LINKED_LIST1_INCLUDED

class Company;
class Warehouse;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class warehouses_LinkedList1Parent {
public:
    Warehouse* tail;
    warehouses_LinkedList1Parent(){ tail=NULL; }
};

class warehouses_LinkedList1Child : public warehouses_Ring1Element {
public:
    warehouses_LinkedList1Child() : warehouses_Ring1Element(){ }
};

// the following class is used when Parent==Child
class warehouses_LinkedList1ParentLinkedList1Child : public warehouses_Ring1Element {
public:
    Warehouse* tail;
    warehouses_LinkedList1ParentLinkedList1Child() : warehouses_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class warehouses_LinkedList1 : warehouses_Ring1 {

public:
    static Warehouse *tail(Company *p);
    static Warehouse *head(Company *p);
    static void addHead(Company *p, Warehouse *c);
    static void addTail(Company *p, Warehouse *c);
    static void append(Company *p,Warehouse *c1, Warehouse *c2);
    static void remove(Company *p, Warehouse *c);
    static Warehouse* const next(Company *p,Warehouse *c);
    static Warehouse* const fwd(Warehouse *c);
    static void sort(ZZsortFun cmpFun, Company *p);
    static void merge(Warehouse *s,Warehouse *t,Company *p);
    static void setTail(Company* p,Warehouse* c,int check);

    // historical DOL compatible interface
    static void del(Company *p, Warehouse *c){ remove(p,c);}
    static void add(Company *p, Warehouse *c){ addHead(p,c);}
    static Warehouse* child(Company *p);
    static void set(Company* p,Warehouse* c){ setTail(p,c,0);}
};

class warehouses_LinkedList1Iterator : public warehouses_Ring1Iterator {
public:
    warehouses_LinkedList1Iterator() : warehouses_Ring1Iterator(){}
    warehouses_LinkedList1Iterator(const Company *p) : warehouses_Ring1Iterator(){start(p);}
    virtual void start(const Company *p);
    virtual Warehouse* fromHead(Company *p);
};
    
#endif // ZZ_warehouses_LINKED_LIST1_INCLUDED
