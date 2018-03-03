
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class parts_Aggregate :
//                                   public parts_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_parts_AGGREGATE_INCLUDED
#define ZZ_parts_AGGREGATE_INCLUDED

class Organization;
class Participant;

// description of the cooperating classes
class parts_AggregateParent : public parts_LinkedListParent {
};

class parts_AggregateChild : public parts_LinkedListChild {
public:
    Organization* parent;
    parts_AggregateChild(){ parent=NULL; }
};

// the following class is used when Parent==Child
class parts_AggregateParentAggregateChild : public parts_LinkedListParent {
public:
    Organization* parent;
    parts_AggregateParentAggregateChild(){ parent=NULL; }
};

// ----------------------------------------------------------

class parts_Aggregate : public parts_LinkedList {

public:
    static void addHead(Organization *p, Participant *c);
    static void addTail(Organization *p, Participant *c);
    static void append(Participant *c1, Participant *c2); // has a different syntax
    static void remove(Participant *c);             // has a different syntax
    static Organization* const parent(Participant *c);    // is new
    // ...
};

class parts_AggregateIterator : public parts_LinkedListIterator {
};

#endif // ZZ_parts_AGGREGATE_INCLUDED
