
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class inPair1_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_inPair1_SINGLE_LINK_INCLUDED
#define ZZ_inPair1_SINGLE_LINK_INCLUDED

class Pair;
class Node;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class inPair1_SingleLinkParent {
public:
    Node* linkTo;
    inPair1_SingleLinkParent(){ linkTo=NULL; }
};

class inPair1_SingleLinkChild {
};

// The following class is used when Parent==Child
class inPair1_SingleLinkParentSingleLinkChild {
public:
    Node* linkTo;
    inPair1_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class inPair1_SingleLink {

public:
    static void add(Pair *p,Node *c);
    static void remove(Pair *p);
    static Node* const target(Pair *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Pair *p){ remove(p); }
    static Node* const fwd(Pair *p){ return target(p); }
    static Node* const next(Pair *p){ return target(p); }
};
    
#endif // ZZ_inPair1_SINGLE_LINK_INCLUDED
