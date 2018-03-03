
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class nets_Aggregate :
//                                   public nets_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_nets_AGGREGATE2_INCLUDED
#define ZZ_nets_AGGREGATE2_INCLUDED

class Layout;
class Net;

// description of the cooperating classes
class nets_Aggregate2Parent : public nets_LinkedList2Parent {
public:
    nets_Aggregate2Parent() : nets_LinkedList2Parent(){ }
};

class nets_Aggregate2Child : public nets_LinkedList2Child {
public:
    Layout* parent;
    nets_Aggregate2Child() : nets_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class nets_Aggregate2ParentAggregate2Child 
       : public nets_LinkedList2ParentLinkedList2Child {
public:
    Layout* parent;
    nets_Aggregate2ParentAggregate2Child()
       : nets_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class nets_Aggregate2 : public nets_LinkedList2 {

public:
    static void addHead(Layout *p, Net *c);
    static void addTail(Layout *p, Net *c);
    static void append(Net *c1, Net *c2); // has a different syntax
    static void insert(Net *c1, Net *c2); 
    static void remove(Net *c);             // has a different syntax
    static Layout* const parent(Net *c);    // is new
    static Net* const next(Net *c){ // returns NULL when s is the tail
        return nets_LinkedList2::next(parent(c),c);
    }
    static Net* const prev(Net *c){ // returns NULL when s is the head
        return nets_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class nets_Aggregate2Iterator : public nets_LinkedList2Iterator {
};

#endif // ZZ_nets_AGGREGATE2_INCLUDED
