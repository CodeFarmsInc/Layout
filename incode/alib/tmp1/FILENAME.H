#ifndef ZZ_fileName_NAME_INCLUDED
#define ZZ_fileName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class fileName_Name {
// ----------------------------------------------------------

class Parent;

// description of the cooperating classes
class fileName_NameParent {
public:
    char* name;
    fileName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class fileName_Name {

public:
    static void add(Organization *p, char *c);
    static char* get(Organization *p);
    static void remove(Organization *p);
    static int compare(Organization *p1,Organization *p2);
    // ...
};
    
#endif // ZZ_fileName_NAME_INCLUDED
