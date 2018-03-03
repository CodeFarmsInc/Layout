
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class byTrack_Aggregate :
//                                   public byTrack_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_byTrack_AGGREGATE2_INCLUDED
#define ZZ_byTrack_AGGREGATE2_INCLUDED

class Track;
class Edge;

// description of the cooperating classes
class byTrack_Aggregate2Parent : public byTrack_LinkedList2Parent {
public:
    byTrack_Aggregate2Parent() : byTrack_LinkedList2Parent(){ }
};

class byTrack_Aggregate2Child : public byTrack_LinkedList2Child {
public:
    Track* parent;
    byTrack_Aggregate2Child() : byTrack_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class byTrack_Aggregate2ParentAggregate2Child 
       : public byTrack_LinkedList2ParentLinkedList2Child {
public:
    Track* parent;
    byTrack_Aggregate2ParentAggregate2Child()
       : byTrack_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class byTrack_Aggregate2 : public byTrack_LinkedList2 {

public:
    static void addHead(Track *p, Edge *c);
    static void addTail(Track *p, Edge *c);
    static void append(Edge *c1, Edge *c2); // has a different syntax
    static void insert(Edge *c1, Edge *c2); 
    static void remove(Edge *c);             // has a different syntax
    static Track* const parent(Edge *c);    // is new
    static Edge* const next(Edge *c){ // returns NULL when s is the tail
        return byTrack_LinkedList2::next(parent(c),c);
    }
    static Edge* const prev(Edge *c){ // returns NULL when s is the head
        return byTrack_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class byTrack_Aggregate2Iterator : public byTrack_LinkedList2Iterator {
};

#endif // ZZ_byTrack_AGGREGATE2_INCLUDED
