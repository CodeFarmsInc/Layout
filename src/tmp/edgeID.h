#ifndef ZZ_edgeID_NAME_INCLUDED
#define ZZ_edgeID_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class edgeID_Name {
// ----------------------------------------------------------

class Edge;

// description of the cooperating classes
class edgeID_NameParent {
public:
    char* name;
    edgeID_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class edgeID_Name {

public:
    static void add(Edge *p, char *c);     // add link to
    static void addNew(Edge *p, char *c);  // allocate string, add link
    static char* get(Edge *p);
    static char* remove(Edge *p);
    static int compare(Edge *p1,Edge *p2);
    // ...
    // historical DOL interface
    static char* del(Edge *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Edge *p){return get(p);}
};
    
#endif // ZZ_edgeID_NAME_INCLUDED
