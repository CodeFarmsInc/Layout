#ifndef ZZ_memberName_NAME_INCLUDED
#define ZZ_memberName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class memberName_Name {
// ----------------------------------------------------------

class Member;

// description of the cooperating classes
class memberName_NameParent {
public:
    char* name;
    memberName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class memberName_Name {

public:
    static void add(Member *p, char *c);     // add link to
    static void addNew(Member *p, char *c);  // allocate string, add link
    static char* get(Member *p);
    static char* remove(Member *p);
    static int compare(Member *p1,Member *p2);
    // ...
    // historical DOL interface
    static char* del(Member *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Member *p){return get(p);}
};
    
#endif // ZZ_memberName_NAME_INCLUDED
