
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class eTrace_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_eTrace_SINGLE_LINK_INCLUDED
#define ZZ_eTrace_SINGLE_LINK_INCLUDED

class Edge;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class eTrace_SingleLinkParent {
public:
    Node* linkTo;
    eTrace_SingleLinkParent(){ linkTo=NULL; }
};

class eTrace_SingleLinkChild {
};

// The following class is used when Parent==Child
class eTrace_SingleLinkParentSingleLinkChild {
public:
    Node* linkTo;
    eTrace_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class eTrace_SingleLink {

public:
    static void add(Edge *p,Node *c);
    static void remove(Edge *p);
    static Node* const target(Edge *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Edge *p){ remove(p); }
    static Node* const fwd(Edge *p){ return target(p); }
    static Node* const next(Edge *p){ return target(p); }
};
    
#endif // ZZ_eTrace_SINGLE_LINK_INCLUDED
