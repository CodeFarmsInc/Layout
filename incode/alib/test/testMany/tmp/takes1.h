
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class takes_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_takes_LINKED_LIST2_INCLUDED
#define ZZ_takes_LINKED_LIST2_INCLUDED

class Student;
class Takes;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class takes_LinkedList2Parent {
public:
    Takes* tail;
    takes_LinkedList2Parent(){ tail=NULL; }
};

class takes_LinkedList2Child : public takes_Ring2Element {
public:
    takes_LinkedList2Child() : takes_Ring2Element(){ }
};

// the following class is used when Parent==Child
class takes_LinkedList2ParentLinkedList2Child : public takes_Ring2Element {
public:
    Takes* tail;
    takes_LinkedList2ParentLinkedList2Child() : takes_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class takes_LinkedList2 : takes_Ring2 {

public:
    static Takes* const tail(Student *p);
    static Takes* const head(Student *p);
    static void addHead(Student *p, Takes *c);
    static void addTail(Student *p, Takes *c);
    static void append(Student *p,Takes *c1, Takes *c2);
    static void insert(Takes *c1, Takes *c2);
    static void remove(Student *p, Takes *c);
    static Takes* const next(Student *p, Takes *c);
    static Takes* const prev(Student *p, Takes *c);
    static Takes* const nextRing(Takes *c);
    static Takes* const prevRing(Takes *c);
    static void sort(ZZsortFun cmpFun, Student *p);
    static void merge(Takes *s,Takes *t,Student *p);
    static void setTail(Student* p,Takes* c,int check);

    // historical DOL compatible interface
    static void del(Student *p, Takes *c) { remove(p,c); }
    static void add(Student *p, Takes *c) { addHead(p,c);}
    static void ins(Takes *c1, Takes *c2) { insert(c1,c2); }
    static Takes* child(Student* p);
    static void set(Student* p,Takes* c){ setTail(p,c,0);}
    static Takes* const fwd(Takes *c){return nextRing(c);}
    static Takes* const bwd(Takes *c){return prevRing(c);}
};

class takes_LinkedList2Iterator : public takes_Ring2Iterator {
public:
    takes_LinkedList2Iterator() : takes_Ring2Iterator(){}
    takes_LinkedList2Iterator(const Student *p) : takes_Ring2Iterator(){ start(p); }
    void start(const Student *p);
    Takes* fromHead(Student *p);
    Takes* fromTail(Student *p);
};
    
#endif // ZZ_takes_LINKED_LIST2_INCLUDED
