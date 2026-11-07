
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class partTypes_Aggregate :
//                                   public partTypes_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_partTypes_AGGREGATE2_INCLUDED
#define ZZ_partTypes_AGGREGATE2_INCLUDED

class OrgType;
class PartType;

// description of the cooperating classes
class partTypes_Aggregate2Parent : public partTypes_LinkedList2Parent {
public:
    partTypes_Aggregate2Parent() : partTypes_LinkedList2Parent(){ }
};

class partTypes_Aggregate2Child : public partTypes_LinkedList2Child {
public:
    OrgType* parent;
    partTypes_Aggregate2Child() : partTypes_LinkedList2Child(){ parent=NULL; }
};

// the following class is used when Parent==Child
class partTypes_Aggregate2ParentAggregate2Child 
       : public partTypes_LinkedList2ParentLinkedList2Child {
public:
    OrgType* parent;
    partTypes_Aggregate2ParentAggregate2Child()
       : partTypes_LinkedList2ParentLinkedList2Child(){ parent=NULL; }
};

// ----------------------------------------------------------

class partTypes_Aggregate2 : public partTypes_LinkedList2 {

public:
    static void addHead(OrgType *p, PartType *c);
    static void addTail(OrgType *p, PartType *c);
    static void append(PartType *c1, PartType *c2); // has a different syntax
    static void insert(PartType *c1, PartType *c2); 
    static void remove(PartType *c);             // has a different syntax
    static OrgType* const parent(PartType *c);    // is new
    static PartType* const next(PartType *c){ // returns NULL when s is the tail
        return partTypes_LinkedList2::next(parent(c),c);
    }
    static PartType* const prev(PartType *c){ // returns NULL when s is the head
        return partTypes_LinkedList2::prev(parent(c),c);
    }
    // ...
};

class partTypes_Aggregate2Iterator : public partTypes_LinkedList2Iterator {
};

#endif // ZZ_partTypes_AGGREGATE2_INCLUDED
