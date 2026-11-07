
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class sources_Aggregate :
//                                   public sources_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_sources_AGGREGATE2_INCLUDED
#define ZZ_sources_AGGREGATE2_INCLUDED

class Node;
class Edge;

// description of the cooperating classes
class sources_Aggregate2Parent : public sources_LinkedList2Parent {
public:
    sources_Aggregate2Parent() : sources_LinkedList2Parent(){ }
};

class sources_Aggregate2Child : public sources_LinkedList2Child {
public:
    Node* parent;
    sources_Aggregate2Child() : sources_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class sources_Aggregate2ParentAggregate2Child 
       : public sources_LinkedList2ParentLinkedList2Child {
public:
    Node* parent;
    sources_Aggregate2ParentAggregate2Child()
       : sources_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class sources_Aggregate2 : public sources_LinkedList2 {

public:
    static void addHead(Node *p, Edge *c);
    static void addTail(Node *p, Edge *c);
    static void append(Edge *c1, Edge *c2); // has a different syntax
    static void insert(Edge *c1, Edge *c2); 
    static void remove(Edge *c);             // has a different syntax
    static Node* const parent(Edge *c);    // is new
    static Edge* const next(Edge *c){ // returns NULL when s is the tail
        return sources_LinkedList2::next(parent(c),c);
    }
    static Edge* const prev(Edge *c){ // returns NULL when s is the head
        return sources_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class sources_Aggregate2Iterator : public sources_LinkedList2Iterator {
};

#endif // ZZ_sources_AGGREGATE2_INCLUDED
