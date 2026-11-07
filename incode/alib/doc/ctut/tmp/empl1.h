
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class empl_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_empl_LINKED_LIST1_INCLUDED
#define ZZ_empl_LINKED_LIST1_INCLUDED

class Department;
class Employee;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class empl_LinkedList1Parent {
public:
    Employee* tail;
    empl_LinkedList1Parent(){ tail=NULL; }
};

class empl_LinkedList1Child : public empl_Ring1Element {
public:
    empl_LinkedList1Child() : empl_Ring1Element(){ }
};

// the following class is used when Parent==Child
class empl_LinkedList1ParentLinkedList1Child : public empl_Ring1Element {
public:
    Employee* tail;
    empl_LinkedList1ParentLinkedList1Child() : empl_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class empl_LinkedList1 : empl_Ring1 {

public:
    static Employee *tail(Department *p);
    static Employee *head(Department *p);
    static void addHead(Department *p, Employee *c);
    static void addTail(Department *p, Employee *c);
    static void append(Department *p,Employee *c1, Employee *c2);
    static void remove(Department *p, Employee *c);
    static Employee* const next(Department *p,Employee *c);
    static Employee* const fwd(Employee *c);
    static void sort(ZZsortFun cmpFun, Department *p);
    static void merge(Employee *s,Employee *t,Department *p);
    static void setTail(Department* p,Employee* c,int check);

    // historical DOL compatible interface
    static void del(Department *p, Employee *c){ remove(p,c);}
    static void add(Department *p, Employee *c){ addHead(p,c);}
    static Employee* child(Department *p);
    static void set(Department* p,Employee* c){ setTail(p,c,0);}
};

class empl_LinkedList1Iterator : public empl_Ring1Iterator {
public:
    empl_LinkedList1Iterator() : empl_Ring1Iterator(){}
    empl_LinkedList1Iterator(const Department *p) : empl_Ring1Iterator(){start(p);}
    virtual void start(const Department *p);
    virtual Employee* fromHead(Department *p);
};
    
#endif // ZZ_empl_LINKED_LIST1_INCLUDED
