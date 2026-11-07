#ifndef ZZ_$$_NAME_INCLUDED
#define ZZ_$$_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class $$_Name {
// ----------------------------------------------------------

class $1;

// description of the cooperating classes
class $$_NameParent {
public:
    char* name;
    $$_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class $$_Name {

public:
    static void add($1 *p, char *c);     // add link to
    static void addNew($1 *p, char *c);  // allocate string, add link
    static char* get($1 *p);
    static char* remove($1 *p);
    static int compare($1 *p1,$1 *p2);
    // ...
    // historical DOL interface
    static char* del($1 *p){char* s=get(p); remove(p); return s;}
    static char* fwd($1 *p){return get(p);}
};
    
#endif // ZZ_$$_NAME_INCLUDED
