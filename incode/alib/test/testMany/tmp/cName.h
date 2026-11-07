#ifndef ZZ_cName_NAME_INCLUDED
#define ZZ_cName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class cName_Name {
// ----------------------------------------------------------

class Course;

// description of the cooperating classes
class cName_NameParent {
public:
    char* name;
    cName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class cName_Name {

public:
    static void add(Course *p, char *c);     // add link to
    static void addNew(Course *p, char *c);  // allocate string, add link
    static char* get(Course *p);
    static char* remove(Course *p);
    static int compare(Course *p1,Course *p2);
    // ...
    // historical DOL interface
    static char* del(Course *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Course *p){return get(p);}
};
    
#endif // ZZ_cName_NAME_INCLUDED
