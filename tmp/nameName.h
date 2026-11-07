#ifndef ZZ_nameName_NAME_INCLUDED
#define ZZ_nameName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class nameName_Name {
// ----------------------------------------------------------

class Name;

// description of the cooperating classes
class nameName_NameParent {
public:
    char* name;
    nameName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class nameName_Name {

public:
    static void add(Name *p, char *c);     // add link to
    static void addNew(Name *p, char *c);  // allocate string, add link
    static char* get(Name *p);
    static char* remove(Name *p);
    static int compare(Name *p1,Name *p2);
    // ...
    // historical DOL interface
    static char* del(Name *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Name *p){return get(p);}
};
    
#endif // ZZ_nameName_NAME_INCLUDED
