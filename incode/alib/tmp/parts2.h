
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class parts_Aggregate :
//                                   public parts_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_parts_AGGREGATE2_INCLUDED
#define ZZ_parts_AGGREGATE2_INCLUDED

class Organization;
class Participant;

// description of the cooperating classes
class parts_Aggregate2Parent : public parts_LinkedList2Parent {
public:
    parts_Aggregate2Parent() : parts_LinkedList2Parent(){ }
};

class parts_Aggregate2Child : public parts_LinkedList2Child {
public:
    Organization* parent;
    parts_Aggregate2Child() : parts_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class parts_Aggregate2ParentAggregate2Child 
       : public parts_LinkedList2ParentLinkedList2Child {
public:
    Organization* parent;
    parts_Aggregate2ParentAggregate2Child()
       : parts_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class parts_Aggregate2 : public parts_LinkedList2 {

public:
    static void addHead(Organization *p, Participant *c);
    static void addTail(Organization *p, Participant *c);
    static void append(Participant *c1, Participant *c2); // has a different syntax
    static void insert(Participant *c1, Participant *c2); 
    static void remove(Participant *c);             // has a different syntax
    static Organization* const parent(Participant *c);    // is new
    static Participant* const next(Participant *c){ // returns NULL when s is the tail
        return parts_LinkedList2::next(parent(c),c);
    }
    static Participant* const prev(Participant *c){ // returns NULL when s is the head
        return parts_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class parts_Aggregate2Iterator : public parts_LinkedList2Iterator {
};

#endif // ZZ_parts_AGGREGATE2_INCLUDED
