#ifndef ZZ_orgType_NAME_INCLUDED
#define ZZ_orgType_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class orgType_Name {
// ----------------------------------------------------------

class Parent;

// description of the cooperating classes
class orgType_NameParent {
public:
    char* name;
    orgType_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class orgType_Name {

public:
    static void add(Organization *p, char *c);
    static char* get(Organization *p);
    static void remove(Organization *p);
    static int compare(Organization *p1,Organization *p2);
    // ...
};
    
#endif // ZZ_orgType_NAME_INCLUDED
