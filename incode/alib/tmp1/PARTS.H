
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class parts_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_parts_LINKED_LIST_INCLUDED
#define ZZ_parts_LINKED_LIST_INCLUDED

class Organization;
class Participant;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class parts_LinkedListParent {
public:
    Participant* tail;
    parts_LinkedListParent(){ tail=NULL; }
};

class parts_LinkedListChild {
public:
    Participant* next;
    parts_LinkedListChild(){ next=NULL; }
};

// the following class is used when Parent==Child
class parts_LinkedListParentLinkedListChild {
public:
    Participant* tail;
    Participant* next;
    parts_LinkedListParentLinkedListChild(){ tail=NULL; next=NULL; }
};
// ----------------------------------------------------------

class parts_LinkedList {

public:
    static void addHead(Organization *p, Participant *c);
    static void addTail(Organization *p, Participant *c);
    static void append(Organization *p,Participant *c1, Participant *c2);
    static void remove(Organization *p, Participant *c);
    static Participant* const next(Organization *p, Participant *c);
    // ...
};

class parts_LinkedListIterator {
    Participant *tail; // temporary data
    Participant *nxt;
public:
    parts_LinkedListIterator(){tail=nxt=NULL;}
    parts_LinkedListIterator(const Organization *p){start(p);}
    virtual void start(const Organization *p);
    virtual Participant* const operator++();
};
    
#endif // ZZ_parts_LINKED_LIST_INCLUDED
