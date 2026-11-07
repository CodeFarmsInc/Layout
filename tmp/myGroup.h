
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class myGroup_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_myGroup_SINGLE_LINK_INCLUDED
#define ZZ_myGroup_SINGLE_LINK_INCLUDED

class Node;
class Group;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class myGroup_SingleLinkParent {
public:
    Group* linkTo;
    myGroup_SingleLinkParent(){ linkTo=NULL; }
};

class myGroup_SingleLinkChild {
};

// The following class is used when Parent==Child
class myGroup_SingleLinkParentSingleLinkChild {
public:
    Group* linkTo;
    myGroup_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class myGroup_SingleLink {

public:
    static void add(Node *p,Group *c);
    static void remove(Node *p);
    static Group* const target(Node *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Node *p){ remove(p); }
    static Group* const fwd(Node *p){ return target(p); }
    static Group* const next(Node *p){ return target(p); }
};
    
#endif // ZZ_myGroup_SINGLE_LINK_INCLUDED
