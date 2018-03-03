
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class AtoB_Aggregate :
//                                   public AtoB_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_AtoB_AGGREGATE2_INCLUDED
#define ZZ_AtoB_AGGREGATE2_INCLUDED

class A;
class B;

// description of the cooperating classes
class AtoB_Aggregate2Parent : public AtoB_LinkedList2Parent {
public:
    AtoB_Aggregate2Parent() : AtoB_LinkedList2Parent(){ }
};

class AtoB_Aggregate2Child : public AtoB_LinkedList2Child {
public:
    A* parent;
    AtoB_Aggregate2Child() : AtoB_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class AtoB_Aggregate2ParentAggregate2Child 
       : public AtoB_LinkedList2ParentLinkedList2Child {
public:
    A* parent;
    AtoB_Aggregate2ParentAggregate2Child()
       : AtoB_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class AtoB_Aggregate2 : public AtoB_LinkedList2 {

public:
    static void addHead(A *p, B *c);
    static void addTail(A *p, B *c);
    static void append(B *c1, B *c2); // has a different syntax
    static void insert(B *c1, B *c2); 
    static void remove(B *c);             // has a different syntax
    static A* const parent(B *c);    // is new
    static B* const next(B *c){ // returns NULL when s is the tail
        return AtoB_LinkedList2::next(parent(c),c);
    }
    static B* const prev(B *c){ // returns NULL when s is the head
        return AtoB_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class AtoB_Aggregate2Iterator : public AtoB_LinkedList2Iterator {
};

#endif // ZZ_AtoB_AGGREGATE2_INCLUDED
