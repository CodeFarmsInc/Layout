
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class toNode_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_toNode_SINGLE_LINK_INCLUDED
#define ZZ_toNode_SINGLE_LINK_INCLUDED

class NodeRef;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class toNode_SingleLinkParent {
public:
    Node* linkTo;
    toNode_SingleLinkParent(){ linkTo=NULL; }
};

class toNode_SingleLinkChild {
};

// The following class is used when Parent==Child
class toNode_SingleLinkParentSingleLinkChild {
public:
    Node* linkTo;
    toNode_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class toNode_SingleLink {

public:
    static void add(NodeRef *p,Node *c);
    static void remove(NodeRef *p);
    static Node* const target(NodeRef *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(NodeRef *p){ remove(p); }
    static Node* const fwd(NodeRef *p){ return target(p); }
    static Node* const next(NodeRef *p){ return target(p); }
};
    
#endif // ZZ_toNode_SINGLE_LINK_INCLUDED
