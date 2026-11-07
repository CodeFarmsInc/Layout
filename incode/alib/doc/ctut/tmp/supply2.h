
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class supply_Aggregate :
//                                   public supply_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_supply_AGGREGATE2_INCLUDED
#define ZZ_supply_AGGREGATE2_INCLUDED

class Supplier;
class PartType;

// description of the cooperating classes
class supply_Aggregate2Parent : public supply_LinkedList2Parent {
public:
    supply_Aggregate2Parent() : supply_LinkedList2Parent(){ }
};

class supply_Aggregate2Child : public supply_LinkedList2Child {
public:
    Supplier* parent;
    supply_Aggregate2Child() : supply_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class supply_Aggregate2ParentAggregate2Child 
       : public supply_LinkedList2ParentLinkedList2Child {
public:
    Supplier* parent;
    supply_Aggregate2ParentAggregate2Child()
       : supply_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class supply_Aggregate2 : public supply_LinkedList2 {

public:
    static void addHead(Supplier *p, PartType *c);
    static void addTail(Supplier *p, PartType *c);
    static void append(PartType *c1, PartType *c2); // has a different syntax
    static void remove(PartType *c);             // has a different syntax
    static Supplier* const parent(PartType *c);    // is new
    static PartType* const next(PartType *c){ // returns NULL when s is the tail
        return supply_LinkedList2::next(parent(c),c);
    }
    static PartType* const prev(PartType *c){ // returns NULL when s is the head
        return supply_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class supply_Aggregate2Iterator : public supply_LinkedList2Iterator {
};

#endif // ZZ_supply_AGGREGATE2_INCLUDED
