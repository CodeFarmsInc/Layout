
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class inPair2_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_inPair2_SINGLE_LINK_INCLUDED
#define ZZ_inPair2_SINGLE_LINK_INCLUDED

class Pair;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class inPair2_SingleLinkParent {
public:
    Node* linkTo;
    inPair2_SingleLinkParent(){ linkTo=NULL; }
};

class inPair2_SingleLinkChild {
};

// The following class is used when Parent==Child
class inPair2_SingleLinkParentSingleLinkChild {
public:
    Node* linkTo;
    inPair2_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class inPair2_SingleLink {

public:
    static void add(Pair *p,Node *c);
    static void remove(Pair *p);
    static Node* const target(Pair *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Pair *p){ remove(p); }
    static Node* const fwd(Pair *p){ return target(p); }
    static Node* const next(Pair *p){ return target(p); }
};
    
#endif // ZZ_inPair2_SINGLE_LINK_INCLUDED
