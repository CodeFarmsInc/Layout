#ifndef ZZ_fixedName_NAME_INCLUDED
#define ZZ_fixedName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class fixedName_Name {
// ----------------------------------------------------------

class FixedType;

// description of the cooperating classes
class fixedName_NameParent {
public:
    char* name;
    fixedName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class fixedName_Name {

public:
    static void add(FixedType *p, char *c);     // add link to
    static void addNew(FixedType *p, char *c);  // allocate string, add link
    static char* get(FixedType *p);
    static char* remove(FixedType *p);
    static int compare(FixedType *p1,FixedType *p2);
    // ...
    // historical DOL interface
    static char* del(FixedType *p){char* s=get(p); remove(p); return s;}
    static char* fwd(FixedType *p){return get(p);}
};
    
#endif // ZZ_fixedName_NAME_INCLUDED
