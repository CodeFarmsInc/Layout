
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class $$_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_$$_LINKED_LIST2_INCLUDED
#define ZZ_$$_LINKED_LIST2_INCLUDED

@class $1;
@class $2;

// ----------------------------------------------------------
// description of the cooperating classes (here structures)
// ----------------------------------------------------------
#define $$_LinkedList2Parent \
    $2* $$_tail

#define $$_LinkedList2Child \
    $$_Ring2Element; 

// the following class is used when Parent==Child
#define $$_LinkedList2ParentLinkedList2Child \
    $1* $$_next; \
    $1* $$_prev; \
    $1* $$_tail
// .........................................
#define $$_LinkedList2Parent_ptrList \
    $0.tail=ONE;

#define $$_LinkedList2Child_ptrList \
    $$_Ring2Element_ptrList; 

// the following class is used when Parent==Child
#define $$_LinkedList2ParentLinkedList2Child_ptrList \
    $0.next=ONE; \
    $0.prev=ONE; \
    $0.tail=ONE

// ----------------------------------------------------------
@interface $$_LinkedList2 : $$_Ring2 
+ ($2*) tail: ($1*) p;
+ ($2*) head: ($1*) p;
+ (void) addHead: ($1*) p add: ($2*) c;
+ (void) addTail: ($1*) p add: ($2*) c;
+ (void) append: ($1*) p after: ($2*) c1 add: ($2*) c2;
+ (void) insert: ($2*) c1 before: ($2*) c2;
+ (void) remove: ($1*) p elem: ($2*) c;
+ ($2*) next: ($1*) p elem: ($2*) c;
+ ($2*) prev: ($1*) p elem: ($2*) c;
+ ($2*) nextRing: ($2*) c;
+ ($2*) prevRing: ($2*) c;
+ (void) sort: (ZZsortFun) cmpFun parent: ($1*) p;
+ (void) merge: ($2*) s second: ($2*) t newParent: ($1*) p;
+ (void) setTail: ($1*) p second:($2*) c checkRequest: (int) check;
@end

@interface $$_LinkedList2Iterator : $$_Ring2Iterator 
- (id) init;
- ($2*) fromHead: ($1*) p;
- ($2*) fromTail: ($1*) p;
- ($2*) next;
@end
    
#endif // ZZ_$$_LINKED_LIST2_INCLUDED
