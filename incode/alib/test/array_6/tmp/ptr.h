
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class ptr_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_ptr_SINGLE_LINK_INCLUDED
#define ZZ_ptr_SINGLE_LINK_INCLUDED

class PartPtr;
class Part;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class ptr_SingleLinkParent {
public:
    Part* linkTo;
    ptr_SingleLinkParent(){ linkTo=NULL; }
};

class ptr_SingleLinkChild {
};

// The following class is used when Parent==Child
class ptr_SingleLinkParentSingleLinkChild {
public:
    Part* linkTo;
    ptr_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class ptr_SingleLink {

public:
    static void add(PartPtr *p,Part *c);
    static void remove(PartPtr *p);
    static Part* const target(PartPtr *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(PartPtr *p){ remove(p); }
    static Part* const fwd(PartPtr *p){ return target(p); }
    static Part* const next(PartPtr *p){ return target(p); }
};
    
#endif // ZZ_ptr_SINGLE_LINK_INCLUDED
