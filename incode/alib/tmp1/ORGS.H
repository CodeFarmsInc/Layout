
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class orgs_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_orgs_LINKED_LIST_INCLUDED
#define ZZ_orgs_LINKED_LIST_INCLUDED

class Generator;
class Organization;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class orgs_LinkedListParent {
public:
    Organization* tail;
    orgs_LinkedListParent(){ tail=NULL; }
};

class orgs_LinkedListChild {
public:
    Organization* next;
    orgs_LinkedListChild(){ next=NULL; }
};

// the following class is used when Parent==Child
class orgs_LinkedListParentLinkedListChild {
public:
    Organization* tail;
    Organization* next;
    orgs_LinkedListParentLinkedListChild(){ tail=NULL; next=NULL; }
};
// ----------------------------------------------------------

class orgs_LinkedList {

public:
    static void addHead(Generator *p, Organization *c);
    static void addTail(Generator *p, Organization *c);
    static void append(Generator *p,Organization *c1, Organization *c2);
    static void remove(Generator *p, Organization *c);
    static Organization* const next(Generator *p, Organization *c);
    // ...
};

class orgs_LinkedListIterator {
    Organization *tail; // temporary data
    Organization *nxt;
public:
    orgs_LinkedListIterator(){tail=nxt=NULL;}
    orgs_LinkedListIterator(const Generator *p){start(p);}
    virtual void start(const Generator *p);
    virtual Organization* const operator++();
};
    
#endif // ZZ_orgs_LINKED_LIST_INCLUDED
