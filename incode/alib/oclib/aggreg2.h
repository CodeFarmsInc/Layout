
// ----------------- data structure Aggregate ---------------
// ----------------------------------------------------------
// EQUIVALENT OF:
//     template <class Parent, class Child> class $$_Aggregate :
//                                   public $$_LinkedList<Parent,Child>
// INHERITS FROM: LinkedList
// ----------------------------------------------------------
#ifndef ZZ_$$_AGGREGATE2_INCLUDED
#define ZZ_$$_AGGREGATE2_INCLUDED

@class $1;
@class $2;

#define $$_Aggregate2Parent \
    $$_LinkedList2Parent

#define $$_Aggregate2Child \
    $$_LinkedList2Child; \
    $1* $$_parent

// the following class is used when Parent==Child
#define $$_Aggregate2ParentAggregate2Child  \
    $$_LinkedList2ParentLinkedList2Child; \
    $1* $$_parent
// ..............................................
#define $$_Aggregate2Parent_ptrList \
    $$_LinkedList2Parent_ptrList

#define $$_Aggregate2Child_ptrList \
    $$_LinkedList2Child_ptrList; \
    $0.parent=ONE

// the following class is used when Parent==Child
#define $$_Aggregate2ParentAggregate2Child_ptrList  \
    $$_LinkedList2ParentLinkedList2Child_ptrList; \
    $0.parent=ONE

// ----------------------------------------------------------

@interface $$_Aggregate2 : $$_LinkedList2 
+ (void) addHead: ($1*) p add: ($2*) c;
+ (void) addTail: ($1*) p add: ($2*) c;
+ (void) append: ($2*) c1 elem: ($2*) c; // has a different syntax
+ (void) insert: ($2*) c1 before: ($2*) c; 
+ (void) remove: ($2*) c;             // has a different syntax
+ ($1*) parent: ($2*) c;    // is new
+ ($2*) next: ($2*) c; // returns NULL when s is the tail
+ ($2*) prev: ($2*) c; // returns NULL when s is the head
    // ...
@end

@interface $$_Aggregate2Iterator : $$_LinkedList2Iterator 
- (id) init;
@end

#endif // ZZ_$$_AGGREGATE2_INCLUDED
