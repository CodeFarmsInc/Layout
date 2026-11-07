#ifndef ZZ_partName_NAME_INCLUDED
#define ZZ_partName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class partName_Name {
// ----------------------------------------------------------

class Participant;

// description of the cooperating classes
class partName_NameParent {
public:
    char* name;
    partName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class partName_Name {

public:
    static void add(Participant *p, char *c);     // add link to
    static void addNew(Participant *p, char *c);  // allocate string, add link
    static char* get(Participant *p);
    static char* remove(Participant *p);
    static int compare(Participant *p1,Participant *p2);
    // ...
    // historical DOL interface
    static char* del(Participant *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Participant *p){return get(p);}
};
    
#endif // ZZ_partName_NAME_INCLUDED
