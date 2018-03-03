
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class eList_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_eList_LINKED_LIST1_INCLUDED
#define ZZ_eList_LINKED_LIST1_INCLUDED

class Department;
class Employee;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class eList_LinkedList1Parent {
public:
    Employee* tail;
    eList_LinkedList1Parent(){ tail=NULL; }
};

class eList_LinkedList1Child : public eList_Ring1Element {
public:
    eList_LinkedList1Child() : eList_Ring1Element(){ }
};

// the following class is used when Parent==Child
class eList_LinkedList1ParentLinkedList1Child : public eList_Ring1Element {
public:
    Employee* tail;
    eList_LinkedList1ParentLinkedList1Child() : eList_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class eList_LinkedList1 : eList_Ring1 {

public:
    static Employee *tail(Department *p);
    static Employee *head(Department *p);
    static void addHead(Department *p, Employee *c);
    static void addTail(Department *p, Employee *c);
    static void append(Department *p,Employee *c1, Employee *c2);
    static void remove(Department *p, Employee *c);
    static Employee* const next(Department *p,Employee *c);
    static Employee* const nextRing(Employee *c);
    static void sort(ZZsortFun cmpFun, Department *p);
    static void merge(Employee *s,Employee *t,Department *p);
    static void setTail(Department* p,Employee* c,int check);

    // historical DOL compatible interface
    static void del(Department *p, Employee *c){ remove(p,c);}
    static void add(Department *p, Employee *c){ addHead(p,c);}
    static Employee* child(Department *p);
    static void set(Department* p,Employee* c){ setTail(p,c,0);}
    static Employee* const fwd(Employee *c){ return nextRing(c);}
};

class eList_LinkedList1Iterator : public eList_Ring1Iterator {
public:
    eList_LinkedList1Iterator() : eList_Ring1Iterator(){}
    eList_LinkedList1Iterator(const Department *p) : eList_Ring1Iterator(){start(p);}
    void start(const Department *p);
    Employee* fromHead(Department *p);
};
    
#endif // ZZ_eList_LINKED_LIST1_INCLUDED
