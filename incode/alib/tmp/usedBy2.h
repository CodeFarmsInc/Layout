
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class usedBy_Aggregate :
//                                   public usedBy_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_usedBy_AGGREGATE2_INCLUDED
#define ZZ_usedBy_AGGREGATE2_INCLUDED

class ApplClass;
class Participant;

// description of the cooperating classes
class usedBy_Aggregate2Parent : public usedBy_LinkedList2Parent {
public:
    usedBy_Aggregate2Parent() : usedBy_LinkedList2Parent(){ }
};

class usedBy_Aggregate2Child : public usedBy_LinkedList2Child {
public:
    ApplClass* parent;
    usedBy_Aggregate2Child() : usedBy_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class usedBy_Aggregate2ParentAggregate2Child 
       : public usedBy_LinkedList2ParentLinkedList2Child {
public:
    ApplClass* parent;
    usedBy_Aggregate2ParentAggregate2Child()
       : usedBy_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class usedBy_Aggregate2 : public usedBy_LinkedList2 {

public:
    static void addHead(ApplClass *p, Participant *c);
    static void addTail(ApplClass *p, Participant *c);
    static void append(Participant *c1, Participant *c2); // has a different syntax
    static void insert(Participant *c1, Participant *c2); 
    static void remove(Participant *c);             // has a different syntax
    static ApplClass* const parent(Participant *c);    // is new
    static Participant* const next(Participant *c){ // returns NULL when s is the tail
        return usedBy_LinkedList2::next(parent(c),c);
    }
    static Participant* const prev(Participant *c){ // returns NULL when s is the head
        return usedBy_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class usedBy_Aggregate2Iterator : public usedBy_LinkedList2Iterator {
};

#endif // ZZ_usedBy_AGGREGATE2_INCLUDED
