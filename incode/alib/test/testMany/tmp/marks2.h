
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class marks_Aggregate :
//                                   public marks_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_marks_AGGREGATE2_INCLUDED
#define ZZ_marks_AGGREGATE2_INCLUDED

class Student;
class Mark;

// description of the cooperating classes
class marks_Aggregate2Parent : public marks_LinkedList2Parent {
public:
    marks_Aggregate2Parent() : marks_LinkedList2Parent(){ }
};

class marks_Aggregate2Child : public marks_LinkedList2Child {
public:
    Student* parent;
    marks_Aggregate2Child() : marks_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class marks_Aggregate2ParentAggregate2Child 
       : public marks_LinkedList2ParentLinkedList2Child {
public:
    Student* parent;
    marks_Aggregate2ParentAggregate2Child()
       : marks_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class marks_Aggregate2 : public marks_LinkedList2 {

public:
    static void addHead(Student *p, Mark *c);
    static void addTail(Student *p, Mark *c);
    static void append(Mark *c1, Mark *c2); // has a different syntax
    static void insert(Mark *c1, Mark *c2); 
    static void remove(Mark *c);             // has a different syntax
    static Student* const parent(Mark *c);    // is new
    static Mark* const next(Mark *c){ // returns NULL when s is the tail
        return marks_LinkedList2::next(parent(c),c);
    }
    static Mark* const prev(Mark *c){ // returns NULL when s is the head
        return marks_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class marks_Aggregate2Iterator : public marks_LinkedList2Iterator {
};

#endif // ZZ_marks_AGGREGATE2_INCLUDED
