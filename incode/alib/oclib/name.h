#ifndef ZZ_$$_NAME_INCLUDED
#define ZZ_$$_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class $$_Name {
// ----------------------------------------------------------

@class $1;

// description of the cooperating classes
#define $$_NameParent \
    char* $$_name

#define $$_NameParent_ptrList \
    $0.name=ONE \

// ----------------------------------------------------------

@interface $$_Name 
+ (void) add: ($1*) p cString: (char*) c;     // add link to
+ (void) addNew: ($1*) p cString: (char*) c;  // allocate string, add link
+ (char*) get: ($1*) p;
+ (char*) remove: ($1*) p;
+ (int) compare: ($1*) p1 second: ($1*) p2;
    // ...
@end
    
#endif // ZZ_$$_NAME_INCLUDED
