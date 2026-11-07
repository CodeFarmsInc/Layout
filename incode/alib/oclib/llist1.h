
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class $$_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_$$_LINKED_LIST1_INCLUDED
#define ZZ_$$_LINKED_LIST1_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_LinkedList1Parent {
public:
    $2* tail;
    $$_LinkedList1Parent(){ tail=NULL; }
};

class $$_LinkedList1Child : public $$_Ring1Element {
public:
    $$_LinkedList1Child() : $$_Ring1Element(){ }
};

// the following class is used when Parent==Child
class $$_LinkedList1ParentLinkedList1Child : public $$_Ring1Element {
public:
    $2* tail;
    $$_LinkedList1ParentLinkedList1Child() : $$_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class $$_LinkedList1 : $$_Ring1 {

public:
    static $2 *tail($1 *p);
    static $2 *head($1 *p);
    static void addHead($1 *p, $2 *c);
    static void addTail($1 *p, $2 *c);
    static void append($1 *p,$2 *c1, $2 *c2);
    static void remove($1 *p, $2 *c);
    static $2* const next($1 *p,$2 *c);
    static $2* const nextRing($2 *c);
    static void sort(ZZsortFun cmpFun, $1 *p);
    static void merge($2 *s,$2 *t,$1 *p);
    static void setTail($1* p,$2* c,int check);

    // historical DOL compatible interface
    static void del($1 *p, $2 *c){ remove(p,c);}
    static void add($1 *p, $2 *c){ addHead(p,c);}
    static $2* child($1 *p);
    static void set($1* p,$2* c){ setTail(p,c,0);}
    static $2* const fwd($2 *c){ return nextRing(c);}
};

class $$_LinkedList1Iterator : public $$_Ring1Iterator {
public:
    $$_LinkedList1Iterator() : $$_Ring1Iterator(){}
    $$_LinkedList1Iterator(const $1 *p) : $$_Ring1Iterator(){start(p);}
    void start(const $1 *p);
    $2* fromHead($1 *p);
};
    
#endif // ZZ_$$_LINKED_LIST1_INCLUDED
