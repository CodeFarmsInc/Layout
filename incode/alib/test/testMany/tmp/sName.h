#ifndef ZZ_sName_NAME_INCLUDED
#define ZZ_sName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class sName_Name {
// ----------------------------------------------------------

class Student;

// description of the cooperating classes
class sName_NameParent {
public:
    char* name;
    sName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class sName_Name {

public:
    static void add(Student *p, char *c);     // add link to
    static void addNew(Student *p, char *c);  // allocate string, add link
    static char* get(Student *p);
    static char* remove(Student *p);
    static int compare(Student *p1,Student *p2);
    // ...
    // historical DOL interface
    static char* del(Student *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Student *p){return get(p);}
};
    
#endif // ZZ_sName_NAME_INCLUDED
