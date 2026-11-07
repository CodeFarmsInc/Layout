
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class inherits_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_inherits_SINGLE_LINK_INCLUDED
#define ZZ_inherits_SINGLE_LINK_INCLUDED

class Organization;
class Organization;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class inherits_SingleLinkParent {
public:
    Organization* linkTo;
    inherits_SingleLinkParent(){ linkTo=NULL; }
};

class inherits_SingleLinkChild {
};

// The following class is used when Parent==Child
class inherits_SingleLinkParentSingleLinkChild {
public:
    Organization* linkTo;
    inherits_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class inherits_SingleLink {

public:
    static void add(Organization *p,Organization *c);
    static void remove(Organization *p);
    static Organization* const next(Organization *p);
    // ...
};
    
#endif // ZZ_inherits_SINGLE_LINK_INCLUDED
