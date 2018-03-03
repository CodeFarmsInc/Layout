
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class iters_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_iters_LINKED_LIST_INCLUDED
#define ZZ_iters_LINKED_LIST_INCLUDED

class Organization;
class Iterator;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class iters_LinkedListParent {
public:
    Iterator* tail;
    iters_LinkedListParent(){ tail=NULL; }
};

class iters_LinkedListChild {
public:
    Iterator* next;
    iters_LinkedListChild(){ next=NULL; }
};

// the following class is used when Parent==Child
class iters_LinkedListParentLinkedListChild {
public:
    Iterator* tail;
    Iterator* next;
    iters_LinkedListParentLinkedListChild(){ tail=NULL; next=NULL; }
};
// ----------------------------------------------------------

class iters_LinkedList {

public:
    static void addHead(Organization *p, Iterator *c);
    static void addTail(Organization *p, Iterator *c);
    static void append(Organization *p,Iterator *c1, Iterator *c2);
    static void remove(Organization *p, Iterator *c);
    static Iterator* const next(Organization *p, Iterator *c);
    // ...
};

class iters_LinkedListIterator {
    Iterator *tail; // temporary data
    Iterator *nxt;
public:
    iters_LinkedListIterator(){tail=nxt=NULL;}
    iters_LinkedListIterator(const Organization *p){start(p);}
    virtual void start(const Organization *p);
    virtual Iterator* const operator++();
};
    
#endif // ZZ_iters_LINKED_LIST_INCLUDED
