#ifndef ZZ_iterName_NAME_INCLUDED
#define ZZ_iterName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class iterName_Name {
// ----------------------------------------------------------

class Iterator;

// description of the cooperating classes
class iterName_NameParent {
public:
    char* name;
    iterName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class iterName_Name {

public:
    static void add(Iterator *p, char *c);     // add link to
    static void addNew(Iterator *p, char *c);  // allocate string, add link
    static char* get(Iterator *p);
    static char* remove(Iterator *p);
    static int compare(Iterator *p1,Iterator *p2);
    // ...
    // historical DOL interface
    static char* del(Iterator *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Iterator *p){return get(p);}
};
    
#endif // ZZ_iterName_NAME_INCLUDED
