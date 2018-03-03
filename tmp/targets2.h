
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class targets_Aggregate :
//                                   public targets_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_targets_AGGREGATE2_INCLUDED
#define ZZ_targets_AGGREGATE2_INCLUDED

class Node;
class Edge;

// description of the cooperating classes
class targets_Aggregate2Parent : public targets_LinkedList2Parent {
public:
    targets_Aggregate2Parent() : targets_LinkedList2Parent(){ }
};

class targets_Aggregate2Child : public targets_LinkedList2Child {
public:
    Node* parent;
    targets_Aggregate2Child() : targets_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class targets_Aggregate2ParentAggregate2Child 
       : public targets_LinkedList2ParentLinkedList2Child {
public:
    Node* parent;
    targets_Aggregate2ParentAggregate2Child()
       : targets_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class targets_Aggregate2 : public targets_LinkedList2 {

public:
    static void addHead(Node *p, Edge *c);
    static void addTail(Node *p, Edge *c);
    static void append(Edge *c1, Edge *c2); // has a different syntax
    static void insert(Edge *c1, Edge *c2); 
    static void remove(Edge *c);             // has a different syntax
    static Node* const parent(Edge *c);    // is new
    static Edge* const next(Edge *c){ // returns NULL when s is the tail
        return targets_LinkedList2::next(parent(c),c);
    }
    static Edge* const prev(Edge *c){ // returns NULL when s is the head
        return targets_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class targets_Aggregate2Iterator : public targets_LinkedList2Iterator {
};

#endif // ZZ_targets_AGGREGATE2_INCLUDED
