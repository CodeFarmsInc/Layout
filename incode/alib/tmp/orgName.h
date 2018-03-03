#ifndef ZZ_orgName_NAME_INCLUDED
#define ZZ_orgName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class orgName_Name {
// ----------------------------------------------------------

class Organization;

// description of the cooperating classes
class orgName_NameParent {
public:
    char* name;
    orgName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class orgName_Name {

public:
    static void add(Organization *p, char *c);     // add link to
    static void addNew(Organization *p, char *c);  // allocate string, add link
    static char* get(Organization *p);
    static char* remove(Organization *p);
    static int compare(Organization *p1,Organization *p2);
    // ...
    // historical DOL interface
    static char* del(Organization *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Organization *p){return get(p);}
};
    
#endif // ZZ_orgName_NAME_INCLUDED
