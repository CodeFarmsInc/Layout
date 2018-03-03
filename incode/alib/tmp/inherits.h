
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class inherits_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_inherits_SINGLE_LINK_INCLUDED
#define ZZ_inherits_SINGLE_LINK_INCLUDED

class OrgType;
class OrgType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class inherits_SingleLinkParent {
public:
    OrgType* linkTo;
    inherits_SingleLinkParent(){ linkTo=NULL; }
};

class inherits_SingleLinkChild {
};

// The following class is used when Parent==Child
class inherits_SingleLinkParentSingleLinkChild {
public:
    OrgType* linkTo;
    inherits_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class inherits_SingleLink {

public:
    static void add(OrgType *p,OrgType *c);
    static void remove(OrgType *p);
    static OrgType* const target(OrgType *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(OrgType *p){ remove(p); }
    static OrgType* const fwd(OrgType *p){ return target(p); }
    static OrgType* const next(OrgType *p){ return target(p); }
};
    
#endif // ZZ_inherits_SINGLE_LINK_INCLUDED
