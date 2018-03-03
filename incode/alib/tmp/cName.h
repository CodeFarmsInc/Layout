#ifndef ZZ_cName_NAME_INCLUDED
#define ZZ_cName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class cName_Name {
// ----------------------------------------------------------

class ApplClass;

// description of the cooperating classes
class cName_NameParent {
public:
    char* name;
    cName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class cName_Name {

public:
    static void add(ApplClass *p, char *c);     // add link to
    static void addNew(ApplClass *p, char *c);  // allocate string, add link
    static char* get(ApplClass *p);
    static char* remove(ApplClass *p);
    static int compare(ApplClass *p1,ApplClass *p2);
    // ...
    // historical DOL interface
    static char* del(ApplClass *p){char* s=get(p); remove(p); return s;}
    static char* fwd(ApplClass *p){return get(p);}
};
    
#endif // ZZ_cName_NAME_INCLUDED
