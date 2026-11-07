
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class root_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_root_SINGLE_LINK_INCLUDED
#define ZZ_root_SINGLE_LINK_INCLUDED

class Layout;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class root_SingleLinkParent {
public:
    Node* linkTo;
    root_SingleLinkParent(){ linkTo=NULL; }
};

class root_SingleLinkChild {
};

// The following class is used when Parent==Child
class root_SingleLinkParentSingleLinkChild {
public:
    Node* linkTo;
    root_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class root_SingleLink {

public:
    static void add(Layout *p,Node *c);
    static void remove(Layout *p);
    static Node* const target(Layout *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Layout *p){ remove(p); }
    static Node* const fwd(Layout *p){ return target(p); }
    static Node* const next(Layout *p){ return target(p); }
};
    
#endif // ZZ_root_SINGLE_LINK_INCLUDED
