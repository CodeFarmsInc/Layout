
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class marks_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_marks_LINKED_LIST2_INCLUDED
#define ZZ_marks_LINKED_LIST2_INCLUDED

class Student;
class Mark;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class marks_LinkedList2Parent {
public:
    Mark* tail;
    marks_LinkedList2Parent(){ tail=NULL; }
};

class marks_LinkedList2Child : public marks_Ring2Element {
public:
    marks_LinkedList2Child() : marks_Ring2Element(){ }
};

// the following class is used when Parent==Child
class marks_LinkedList2ParentLinkedList2Child : public marks_Ring2Element {
public:
    Mark* tail;
    marks_LinkedList2ParentLinkedList2Child() : marks_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class marks_LinkedList2 : marks_Ring2 {

public:
    static Mark* const tail(Student *p);
    static Mark* const head(Student *p);
    static void addHead(Student *p, Mark *c);
    static void addTail(Student *p, Mark *c);
    static void append(Student *p,Mark *c1, Mark *c2);
    static void insert(Mark *c1, Mark *c2);
    static void remove(Student *p, Mark *c);
    static Mark* const next(Student *p, Mark *c);
    static Mark* const prev(Student *p, Mark *c);
    static Mark* const nextRing(Mark *c);
    static Mark* const prevRing(Mark *c);
    static void sort(ZZsortFun cmpFun, Student *p);
    static void merge(Mark *s,Mark *t,Student *p);
    static void setTail(Student* p,Mark* c,int check);

    // historical DOL compatible interface
    static void del(Student *p, Mark *c) { remove(p,c); }
    static void add(Student *p, Mark *c) { addHead(p,c);}
    static void ins(Mark *c1, Mark *c2) { insert(c1,c2); }
    static Mark* child(Student* p);
    static void set(Student* p,Mark* c){ setTail(p,c,0);}
    static Mark* const fwd(Mark *c){return nextRing(c);}
    static Mark* const bwd(Mark *c){return prevRing(c);}
};

class marks_LinkedList2Iterator : public marks_Ring2Iterator {
public:
    marks_LinkedList2Iterator() : marks_Ring2Iterator(){}
    marks_LinkedList2Iterator(const Student *p) : marks_Ring2Iterator(){ start(p); }
    void start(const Student *p);
    Mark* fromHead(Student *p);
    Mark* fromTail(Student *p);
};
    
#endif // ZZ_marks_LINKED_LIST2_INCLUDED
