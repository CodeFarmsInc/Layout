
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class toBase_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_toBase_SINGLE_LINK_INCLUDED
#define ZZ_toBase_SINGLE_LINK_INCLUDED

class ClassLink;
class ApplClass;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class toBase_SingleLinkParent {
public:
    ApplClass* linkTo;
    toBase_SingleLinkParent(){ linkTo=NULL; }
};

class toBase_SingleLinkChild {
};

// The following class is used when Parent==Child
class toBase_SingleLinkParentSingleLinkChild {
public:
    ApplClass* linkTo;
    toBase_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class toBase_SingleLink {

public:
    static void add(ClassLink *p,ApplClass *c);
    static void remove(ClassLink *p);
    static ApplClass* const target(ClassLink *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(ClassLink *p){ remove(p); }
    static ApplClass* const fwd(ClassLink *p){ return target(p); }
    static ApplClass* const next(ClassLink *p){ return target(p); }
};
    
#endif // ZZ_toBase_SINGLE_LINK_INCLUDED
