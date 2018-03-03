
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class names_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_names_LINKED_LIST1_INCLUDED
#define ZZ_names_LINKED_LIST1_INCLUDED

class Node;
class Name;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class names_LinkedList1Parent {
public:
    Name* tail;
    names_LinkedList1Parent(){ tail=NULL; }
};

class names_LinkedList1Child : public names_Ring1Element {
public:
    names_LinkedList1Child() : names_Ring1Element(){ }
};

// the following class is used when Parent==Child
class names_LinkedList1ParentLinkedList1Child : public names_Ring1Element {
public:
    Name* tail;
    names_LinkedList1ParentLinkedList1Child() : names_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class names_LinkedList1 : names_Ring1 {

public:
    static Name *tail(Node *p);
    static Name *head(Node *p);
    static void addHead(Node *p, Name *c);
    static void addTail(Node *p, Name *c);
    static void append(Node *p,Name *c1, Name *c2);
    static void remove(Node *p, Name *c);
    static Name* const next(Node *p,Name *c);
    static Name* const nextRing(Name *c);
    static void sort(ZZsortFun cmpFun, Node *p);
    static void merge(Name *s,Name *t,Node *p);
    static void setTail(Node* p,Name* c,int check);

    // historical DOL compatible interface
    static void del(Node *p, Name *c){ remove(p,c);}
    static void add(Node *p, Name *c){ addHead(p,c);}
    static Name* child(Node *p);
    static void set(Node* p,Name* c){ setTail(p,c,0);}
    static Name* const fwd(Name *c){ return nextRing(c);}
};

class names_LinkedList1Iterator : public names_Ring1Iterator {
public:
    names_LinkedList1Iterator() : names_Ring1Iterator(){}
    names_LinkedList1Iterator(const Node *p) : names_Ring1Iterator(){start(p);}
    void start(const Node *p);
    Name* fromHead(Node *p);
};
    
#endif // ZZ_names_LINKED_LIST1_INCLUDED
