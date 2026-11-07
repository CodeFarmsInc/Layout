
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class members_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_members_LINKED_LIST1_INCLUDED
#define ZZ_members_LINKED_LIST1_INCLUDED

class Node;
class Member;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class members_LinkedList1Parent {
public:
    Member* tail;
    members_LinkedList1Parent(){ tail=NULL; }
};

class members_LinkedList1Child : public members_Ring1Element {
public:
    members_LinkedList1Child() : members_Ring1Element(){ }
};

// the following class is used when Parent==Child
class members_LinkedList1ParentLinkedList1Child : public members_Ring1Element {
public:
    Member* tail;
    members_LinkedList1ParentLinkedList1Child() : members_Ring1Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class members_LinkedList1 : members_Ring1 {

public:
    static Member *tail(Node *p);
    static Member *head(Node *p);
    static void addHead(Node *p, Member *c);
    static void addTail(Node *p, Member *c);
    static void append(Node *p,Member *c1, Member *c2);
    static void remove(Node *p, Member *c);
    static Member* const next(Node *p,Member *c);
    static Member* const nextRing(Member *c);
    static void sort(ZZsortFun cmpFun, Node *p);
    static void merge(Member *s,Member *t,Node *p);
    static void setTail(Node* p,Member* c,int check);

    // historical DOL compatible interface
    static void del(Node *p, Member *c){ remove(p,c);}
    static void add(Node *p, Member *c){ addHead(p,c);}
    static Member* child(Node *p);
    static void set(Node* p,Member* c){ setTail(p,c,0);}
    static Member* const fwd(Member *c){ return nextRing(c);}
};

class members_LinkedList1Iterator : public members_Ring1Iterator {
public:
    members_LinkedList1Iterator() : members_Ring1Iterator(){}
    members_LinkedList1Iterator(const Node *p) : members_Ring1Iterator(){start(p);}
    void start(const Node *p);
    Member* fromHead(Node *p);
};
    
#endif // ZZ_members_LINKED_LIST1_INCLUDED
