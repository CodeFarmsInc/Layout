#ifndef ZZ_diagramTitle_NAME_INCLUDED
#define ZZ_diagramTitle_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class diagramTitle_Name {
// ----------------------------------------------------------

class Layout;

// description of the cooperating classes
class diagramTitle_NameParent {
public:
    char* name;
    diagramTitle_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class diagramTitle_Name {

public:
    static void add(Layout *p, char *c);     // add link to
    static void addNew(Layout *p, char *c);  // allocate string, add link
    static char* get(Layout *p);
    static char* remove(Layout *p);
    static int compare(Layout *p1,Layout *p2);
    // ...
    // historical DOL interface
    static char* del(Layout *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Layout *p){return get(p);}
};
    
#endif // ZZ_diagramTitle_NAME_INCLUDED
