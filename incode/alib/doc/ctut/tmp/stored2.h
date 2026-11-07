
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class stored_Aggregate :
//                                   public stored_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_stored_AGGREGATE2_INCLUDED
#define ZZ_stored_AGGREGATE2_INCLUDED

class Warehouse;
class PartType;

// description of the cooperating classes
class stored_Aggregate2Parent : public stored_LinkedList2Parent {
public:
    stored_Aggregate2Parent() : stored_LinkedList2Parent(){ }
};

class stored_Aggregate2Child : public stored_LinkedList2Child {
public:
    Warehouse* parent;
    stored_Aggregate2Child() : stored_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class stored_Aggregate2ParentAggregate2Child 
       : public stored_LinkedList2ParentLinkedList2Child {
public:
    Warehouse* parent;
    stored_Aggregate2ParentAggregate2Child()
       : stored_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class stored_Aggregate2 : public stored_LinkedList2 {

public:
    static void addHead(Warehouse *p, PartType *c);
    static void addTail(Warehouse *p, PartType *c);
    static void append(PartType *c1, PartType *c2); // has a different syntax
    static void remove(PartType *c);             // has a different syntax
    static Warehouse* const parent(PartType *c);    // is new
    static PartType* const next(PartType *c){ // returns NULL when s is the tail
        return stored_LinkedList2::next(parent(c),c);
    }
    static PartType* const prev(PartType *c){ // returns NULL when s is the head
        return stored_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class stored_Aggregate2Iterator : public stored_LinkedList2Iterator {
};

#endif // ZZ_stored_AGGREGATE2_INCLUDED
