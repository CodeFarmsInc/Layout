
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class byNet_Aggregate :
//                                   public byNet_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_byNet_AGGREGATE2_INCLUDED
#define ZZ_byNet_AGGREGATE2_INCLUDED

class Net;
class Edge;

// description of the cooperating classes
class byNet_Aggregate2Parent : public byNet_LinkedList2Parent {
public:
    byNet_Aggregate2Parent() : byNet_LinkedList2Parent(){ }
};

class byNet_Aggregate2Child : public byNet_LinkedList2Child {
public:
    Net* parent;
    byNet_Aggregate2Child() : byNet_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class byNet_Aggregate2ParentAggregate2Child 
       : public byNet_LinkedList2ParentLinkedList2Child {
public:
    Net* parent;
    byNet_Aggregate2ParentAggregate2Child()
       : byNet_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class byNet_Aggregate2 : public byNet_LinkedList2 {

public:
    static void addHead(Net *p, Edge *c);
    static void addTail(Net *p, Edge *c);
    static void append(Edge *c1, Edge *c2); // has a different syntax
    static void insert(Edge *c1, Edge *c2); 
    static void remove(Edge *c);             // has a different syntax
    static Net* const parent(Edge *c);    // is new
    static Edge* const next(Edge *c){ // returns NULL when s is the tail
        return byNet_LinkedList2::next(parent(c),c);
    }
    static Edge* const prev(Edge *c){ // returns NULL when s is the head
        return byNet_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class byNet_Aggregate2Iterator : public byNet_LinkedList2Iterator {
};

#endif // ZZ_byNet_AGGREGATE2_INCLUDED
