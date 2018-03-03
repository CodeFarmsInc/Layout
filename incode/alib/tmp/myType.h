
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class myType_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_myType_SINGLE_LINK_INCLUDED
#define ZZ_myType_SINGLE_LINK_INCLUDED

class Organization;
class OrgType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class myType_SingleLinkParent {
public:
    OrgType* linkTo;
    myType_SingleLinkParent(){ linkTo=NULL; }
};

class myType_SingleLinkChild {
};

// The following class is used when Parent==Child
class myType_SingleLinkParentSingleLinkChild {
public:
    OrgType* linkTo;
    myType_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class myType_SingleLink {

public:
    static void add(Organization *p,OrgType *c);
    static void remove(Organization *p);
    static OrgType* const target(Organization *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Organization *p){ remove(p); }
    static OrgType* const fwd(Organization *p){ return target(p); }
    static OrgType* const next(Organization *p){ return target(p); }
};
    
#endif // ZZ_myType_SINGLE_LINK_INCLUDED
