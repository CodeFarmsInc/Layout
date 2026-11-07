#ifndef ZZ_eName_NAME_INCLUDED
#define ZZ_eName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class eName_Name {
// ----------------------------------------------------------

class Employee;

// description of the cooperating classes
class eName_NameParent {
public:
    char* name;
    eName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class eName_Name {

public:
    static void add(Employee *p, char *c);     // add link to
    static void addNew(Employee *p, char *c);  // allocate string, add link
    static char* get(Employee *p);
    static char* remove(Employee *p);
    static int compare(Employee *p1,Employee *p2);
    // ...
    // historical DOL interface
    static char* del(Employee *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Employee *p){return get(p);}
};
    
#endif // ZZ_eName_NAME_INCLUDED
