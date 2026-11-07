
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class firstTo_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_firstTo_SINGLE_LINK_INCLUDED
#define ZZ_firstTo_SINGLE_LINK_INCLUDED

class Node;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class firstTo_SingleLinkParent {
public:
    Node* linkTo;
    firstTo_SingleLinkParent(){ linkTo=NULL; }
};

class firstTo_SingleLinkChild {
};

// The following class is used when Parent==Child
class firstTo_SingleLinkParentSingleLinkChild {
public:
    Node* linkTo;
    firstTo_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class firstTo_SingleLink {

public:
    static void add(Node *p,Node *c);
    static void remove(Node *p);
    static Node* const target(Node *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Node *p){ remove(p); }
    static Node* const fwd(Node *p){ return target(p); }
    static Node* const next(Node *p){ return target(p); }
};
    
#endif // ZZ_firstTo_SINGLE_LINK_INCLUDED
