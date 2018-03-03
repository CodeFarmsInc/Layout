
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class byYear_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_byYear_LINKED_LIST2_INCLUDED
#define ZZ_byYear_LINKED_LIST2_INCLUDED

class Student;
class Took;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class byYear_LinkedList2Parent {
public:
    Took* tail;
    byYear_LinkedList2Parent(){ tail=NULL; }
};

class byYear_LinkedList2Child : public byYear_Ring2Element {
public:
    byYear_LinkedList2Child() : byYear_Ring2Element(){ }
};

// the following class is used when Parent==Child
class byYear_LinkedList2ParentLinkedList2Child : public byYear_Ring2Element {
public:
    Took* tail;
    byYear_LinkedList2ParentLinkedList2Child() : byYear_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class byYear_LinkedList2 : byYear_Ring2 {

public:
    static Took* const tail(Student *p);
    static Took* const head(Student *p);
    static void addHead(Student *p, Took *c);
    static void addTail(Student *p, Took *c);
    static void append(Student *p,Took *c1, Took *c2);
    static void insert(Took *c1, Took *c2);
    static void remove(Student *p, Took *c);
    static Took* const next(Student *p, Took *c);
    static Took* const prev(Student *p, Took *c);
    static Took* const nextRing(Took *c);
    static Took* const prevRing(Took *c);
    static void sort(ZZsortFun cmpFun, Student *p);
    static void merge(Took *s,Took *t,Student *p);
    static void setTail(Student* p,Took* c,int check);

    // historical DOL compatible interface
    static void del(Student *p, Took *c) { remove(p,c); }
    static void add(Student *p, Took *c) { addHead(p,c);}
    static void ins(Took *c1, Took *c2) { insert(c1,c2); }
    static Took* child(Student* p);
    static void set(Student* p,Took* c){ setTail(p,c,0);}
    static Took* const fwd(Took *c){return nextRing(c);}
    static Took* const bwd(Took *c){return prevRing(c);}
};

class byYear_LinkedList2Iterator : public byYear_Ring2Iterator {
public:
    byYear_LinkedList2Iterator() : byYear_Ring2Iterator(){}
    byYear_LinkedList2Iterator(const Student *p) : byYear_Ring2Iterator(){ start(p); }
    void start(const Student *p);
    Took* fromHead(Student *p);
    Took* fromTail(Student *p);
};
    
#endif // ZZ_byYear_LINKED_LIST2_INCLUDED
