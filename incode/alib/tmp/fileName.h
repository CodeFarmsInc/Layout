#ifndef ZZ_fileName_NAME_INCLUDED
#define ZZ_fileName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class fileName_Name {
// ----------------------------------------------------------

class OrgType;

// description of the cooperating classes
class fileName_NameParent {
public:
    char* name;
    fileName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class fileName_Name {

public:
    static void add(OrgType *p, char *c);     // add link to
    static void addNew(OrgType *p, char *c);  // allocate string, add link
    static char* get(OrgType *p);
    static char* remove(OrgType *p);
    static int compare(OrgType *p1,OrgType *p2);
    // ...
    // historical DOL interface
    static char* del(OrgType *p){char* s=get(p); remove(p); return s;}
    static char* fwd(OrgType *p){return get(p);}
};
    
#endif // ZZ_fileName_NAME_INCLUDED
