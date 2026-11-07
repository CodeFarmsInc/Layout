
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class byYear_Aggregate :
//                                   public byYear_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_byYear_AGGREGATE2_INCLUDED
#define ZZ_byYear_AGGREGATE2_INCLUDED

class Student;
class Took;

// description of the cooperating classes
class byYear_Aggregate2Parent : public byYear_LinkedList2Parent {
public:
    byYear_Aggregate2Parent() : byYear_LinkedList2Parent(){ }
};

class byYear_Aggregate2Child : public byYear_LinkedList2Child {
public:
    Student* parent;
    byYear_Aggregate2Child() : byYear_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class byYear_Aggregate2ParentAggregate2Child 
       : public byYear_LinkedList2ParentLinkedList2Child {
public:
    Student* parent;
    byYear_Aggregate2ParentAggregate2Child()
       : byYear_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class byYear_Aggregate2 : public byYear_LinkedList2 {

public:
    static void addHead(Student *p, Took *c);
    static void addTail(Student *p, Took *c);
    static void append(Took *c1, Took *c2); // has a different syntax
    static void insert(Took *c1, Took *c2); 
    static void remove(Took *c);             // has a different syntax
    static Student* const parent(Took *c);    // is new
    static Took* const next(Took *c){ // returns NULL when s is the tail
        return byYear_LinkedList2::next(parent(c),c);
    }
    static Took* const prev(Took *c){ // returns NULL when s is the head
        return byYear_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class byYear_Aggregate2Iterator : public byYear_LinkedList2Iterator {
};

#endif // ZZ_byYear_AGGREGATE2_INCLUDED
