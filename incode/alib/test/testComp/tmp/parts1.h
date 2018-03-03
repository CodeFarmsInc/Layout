
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class parts_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_parts_LINKED_LIST1_INCLUDED
#define ZZ_parts_LINKED_LIST1_INCLUDED

class Picture;
class Graphics;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class parts_LinkedList1Parent {
public:
    Graphics* tail;
    parts_LinkedList1Parent(){ tail=NULL; }
};

class parts_LinkedList1Child : public parts_Ring1Element {
public:
    parts_LinkedList1Child() : parts_Ring1Element(){ }
};

// the following class is used when Parent==Child
class parts_LinkedList1ParentLinkedList1Child : public parts_Ring1Element {
public:
    Graphics* tail;
    parts_LinkedList1ParentLinkedList1Child() : parts_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class parts_LinkedList1 : parts_Ring1 {

public:
    static Graphics *tail(Picture *p);
    static Graphics *head(Picture *p);
    static void addHead(Picture *p, Graphics *c);
    static void addTail(Picture *p, Graphics *c);
    static void append(Picture *p,Graphics *c1, Graphics *c2);
    static void remove(Picture *p, Graphics *c);
    static Graphics* const next(Picture *p,Graphics *c);
    static Graphics* const nextRing(Graphics *c);
    static void sort(ZZsortFun cmpFun, Picture *p);
    static void merge(Graphics *s,Graphics *t,Picture *p);
    static void setTail(Picture* p,Graphics* c,int check);

    // historical DOL compatible interface
    static void del(Picture *p, Graphics *c){ remove(p,c);}
    static void add(Picture *p, Graphics *c){ addHead(p,c);}
    static Graphics* child(Picture *p);
    static void set(Picture* p,Graphics* c){ setTail(p,c,0);}
    static Graphics* const fwd(Graphics *c){ return nextRing(c);}
};

class parts_LinkedList1Iterator : public parts_Ring1Iterator {
public:
    parts_LinkedList1Iterator() : parts_Ring1Iterator(){}
    parts_LinkedList1Iterator(const Picture *p) : parts_Ring1Iterator(){start(p);}
    void start(const Picture *p);
    Graphics* fromHead(Picture *p);
};
    
#endif // ZZ_parts_LINKED_LIST1_INCLUDED
