
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class inhFixed_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_inhFixed_SINGLE_LINK_INCLUDED
#define ZZ_inhFixed_SINGLE_LINK_INCLUDED

class FixedType;
class PartType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class inhFixed_SingleLinkParent {
public:
    PartType* linkTo;
    inhFixed_SingleLinkParent(){ linkTo=NULL; }
};

class inhFixed_SingleLinkChild {
};

// The following class is used when Parent==Child
class inhFixed_SingleLinkParentSingleLinkChild {
public:
    PartType* linkTo;
    inhFixed_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class inhFixed_SingleLink {

public:
    static void add(FixedType *p,PartType *c);
    static void remove(FixedType *p);
    static PartType* const target(FixedType *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(FixedType *p){ remove(p); }
    static PartType* const fwd(FixedType *p){ return target(p); }
    static PartType* const next(FixedType *p){ return target(p); }
};
    
#endif // ZZ_inhFixed_SINGLE_LINK_INCLUDED
