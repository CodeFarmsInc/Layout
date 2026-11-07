#ifndef ZZ_partAppl_NAME_INCLUDED
#define ZZ_partAppl_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class partAppl_Name {
// ----------------------------------------------------------

class Parent;

// description of the cooperating classes
class partAppl_NameParent {
public:
    char* name;
    partAppl_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class partAppl_Name {

public:
    static void add(Participant *p, char *c);
    static char* get(Participant *p);
    static void remove(Participant *p);
    static int compare(Participant *p1,Participant *p2);
    // ...
};
    
#endif // ZZ_partAppl_NAME_INCLUDED
