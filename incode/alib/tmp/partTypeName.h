#ifndef ZZ_partTypeName_NAME_INCLUDED
#define ZZ_partTypeName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class partTypeName_Name {
// ----------------------------------------------------------

class PartType;

// description of the cooperating classes
class partTypeName_NameParent {
public:
    char* name;
    partTypeName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class partTypeName_Name {

public:
    static void add(PartType *p, char *c);     // add link to
    static void addNew(PartType *p, char *c);  // allocate string, add link
    static char* get(PartType *p);
    static char* remove(PartType *p);
    static int compare(PartType *p1,PartType *p2);
    // ...
    // historical DOL interface
    static char* del(PartType *p){char* s=get(p); remove(p); return s;}
    static char* fwd(PartType *p){return get(p);}
};
    
#endif // ZZ_partTypeName_NAME_INCLUDED
