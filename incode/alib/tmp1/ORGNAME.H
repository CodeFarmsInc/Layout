#ifndef ZZ_orgName_NAME_INCLUDED
#define ZZ_orgName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class orgName_Name {
// ----------------------------------------------------------

class Parent;

// description of the cooperating classes
class orgName_NameParent {
public:
    char* name;
    orgName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class orgName_Name {

public:
    static void add(Organization *p, char *c);
    static char* get(Organization *p);
    static void remove(Organization *p);
    static int compare(Organization *p1,Organization *p2);
    // ...
};
    
#endif // ZZ_orgName_NAME_INCLUDED
