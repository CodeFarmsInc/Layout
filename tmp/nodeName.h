#ifndef ZZ_nodeName_NAME_INCLUDED
#define ZZ_nodeName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class nodeName_Name {
// ----------------------------------------------------------

class Node;

// description of the cooperating classes
class nodeName_NameParent {
public:
    char* name;
    nodeName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class nodeName_Name {

public:
    static void add(Node *p, char *c);     // add link to
    static void addNew(Node *p, char *c);  // allocate string, add link
    static char* get(Node *p);
    static char* remove(Node *p);
    static int compare(Node *p1,Node *p2);
    // ...
    // historical DOL interface
    static char* del(Node *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Node *p){return get(p);}
};
    
#endif // ZZ_nodeName_NAME_INCLUDED
