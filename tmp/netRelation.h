
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class netRelation_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_netRelation_SINGLE_LINK_INCLUDED
#define ZZ_netRelation_SINGLE_LINK_INCLUDED

class Net;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class netRelation_SingleLinkParent {
public:
    Node* linkTo;
    netRelation_SingleLinkParent(){ linkTo=NULL; }
};

class netRelation_SingleLinkChild {
};

// The following class is used when Parent==Child
class netRelation_SingleLinkParentSingleLinkChild {
public:
    Node* linkTo;
    netRelation_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class netRelation_SingleLink {

public:
    static void add(Net *p,Node *c);
    static void remove(Net *p);
    static Node* const target(Net *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Net *p){ remove(p); }
    static Node* const fwd(Net *p){ return target(p); }
    static Node* const next(Net *p){ return target(p); }
};
    
#endif // ZZ_netRelation_SINGLE_LINK_INCLUDED
