
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class products_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_products_LINKED_LIST1_INCLUDED
#define ZZ_products_LINKED_LIST1_INCLUDED

class Company;
class Product;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class products_LinkedList1Parent {
public:
    Product* tail;
    products_LinkedList1Parent(){ tail=NULL; }
};

class products_LinkedList1Child : public products_Ring1Element {
public:
    products_LinkedList1Child() : products_Ring1Element(){ }
};

// the following class is used when Parent==Child
class products_LinkedList1ParentLinkedList1Child : public products_Ring1Element {
public:
    Product* tail;
    products_LinkedList1ParentLinkedList1Child() : products_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class products_LinkedList1 : products_Ring1 {

public:
    static Product *tail(Company *p);
    static Product *head(Company *p);
    static void addHead(Company *p, Product *c);
    static void addTail(Company *p, Product *c);
    static void append(Company *p,Product *c1, Product *c2);
    static void remove(Company *p, Product *c);
    static Product* const next(Company *p,Product *c);
    static Product* const fwd(Product *c);
    static void sort(ZZsortFun cmpFun, Company *p);
    static void merge(Product *s,Product *t,Company *p);
    static void setTail(Company* p,Product* c,int check);

    // historical DOL compatible interface
    static void del(Company *p, Product *c){ remove(p,c);}
    static void add(Company *p, Product *c){ addHead(p,c);}
    static Product* child(Company *p);
    static void set(Company* p,Product* c){ setTail(p,c,0);}
};

class products_LinkedList1Iterator : public products_Ring1Iterator {
public:
    products_LinkedList1Iterator() : products_Ring1Iterator(){}
    products_LinkedList1Iterator(const Company *p) : products_Ring1Iterator(){start(p);}
    virtual void start(const Company *p);
    virtual Product* fromHead(Company *p);
};
    
#endif // ZZ_products_LINKED_LIST1_INCLUDED
