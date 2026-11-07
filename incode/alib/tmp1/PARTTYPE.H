#ifndef ZZ_partType_NAME_INCLUDED
#define ZZ_partType_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class partType_Name {
// ----------------------------------------------------------

class Parent;

// description of the cooperating classes
class partType_NameParent {
public:
    char* name;
    partType_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class partType_Name {

public:
    static void add(Participant *p, char *c);
    static char* get(Participant *p);
    static void remove(Participant *p);
    static int compare(Participant *p1,Participant *p2);
    // ...
};
    
#endif // ZZ_partType_NAME_INCLUDED
