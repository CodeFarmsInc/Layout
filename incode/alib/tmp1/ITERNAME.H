#ifndef ZZ_iterName_NAME_INCLUDED
#define ZZ_iterName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class iterName_Name {
// ----------------------------------------------------------

class Parent;

// description of the cooperating classes
class iterName_NameParent {
public:
    char* name;
    iterName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class iterName_Name {

public:
    static void add(Iterator *p, char *c);
    static char* get(Iterator *p);
    static void remove(Iterator *p);
    static int compare(Iterator *p1,Iterator *p2);
    // ...
};
    
#endif // ZZ_iterName_NAME_INCLUDED
