#ifndef ZZ_name_NAME_INCLUDED
#define ZZ_name_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class name_Name {
// ----------------------------------------------------------

class Person;

// description of the cooperating classes
class name_NameParent {
public:
    char* name;
    name_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class name_Name {

public:
    static void add(Person *p, char *c);     // add link to
    static void addNew(Person *p, char *c);  // allocate string, add link
    static char* get(Person *p);
    static char* remove(Person *p);
    static int compare(Person *p1,Person *p2);
    // ...
    // historical DOL interface
    static char* del(Person *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Person *p){return get(p);}
};
    
#endif // ZZ_name_NAME_INCLUDED
