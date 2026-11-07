
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class takes_Aggregate :
//                                   public takes_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_takes_AGGREGATE2_INCLUDED
#define ZZ_takes_AGGREGATE2_INCLUDED

class Student;
class Takes;

// description of the cooperating classes
class takes_Aggregate2Parent : public takes_LinkedList2Parent {
public:
    takes_Aggregate2Parent() : takes_LinkedList2Parent(){ }
};

class takes_Aggregate2Child : public takes_LinkedList2Child {
public:
    Student* parent;
    takes_Aggregate2Child() : takes_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class takes_Aggregate2ParentAggregate2Child 
       : public takes_LinkedList2ParentLinkedList2Child {
public:
    Student* parent;
    takes_Aggregate2ParentAggregate2Child()
       : takes_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class takes_Aggregate2 : public takes_LinkedList2 {

public:
    static void addHead(Student *p, Takes *c);
    static void addTail(Student *p, Takes *c);
    static void append(Takes *c1, Takes *c2); // has a different syntax
    static void insert(Takes *c1, Takes *c2); 
    static void remove(Takes *c);             // has a different syntax
    static Student* const parent(Takes *c);    // is new
    static Takes* const next(Takes *c){ // returns NULL when s is the tail
        return takes_LinkedList2::next(parent(c),c);
    }
    static Takes* const prev(Takes *c){ // returns NULL when s is the head
        return takes_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class takes_Aggregate2Iterator : public takes_LinkedList2Iterator {
};

#endif // ZZ_takes_AGGREGATE2_INCLUDED
