
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class inhMatch_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_inhMatch_SINGLE_LINK_INCLUDED
#define ZZ_inhMatch_SINGLE_LINK_INCLUDED

class PartType;
class PartType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class inhMatch_SingleLinkParent {
public:
    PartType* linkTo;
    inhMatch_SingleLinkParent(){ linkTo=NULL; }
};

class inhMatch_SingleLinkChild {
};

// The following class is used when Parent==Child
class inhMatch_SingleLinkParentSingleLinkChild {
public:
    PartType* linkTo;
    inhMatch_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class inhMatch_SingleLink {

public:
    static void add(PartType *p,PartType *c);
    static void remove(PartType *p);
    static PartType* const target(PartType *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(PartType *p){ remove(p); }
    static PartType* const fwd(PartType *p){ return target(p); }
    static PartType* const next(PartType *p){ return target(p); }
};
    
#endif // ZZ_inhMatch_SINGLE_LINK_INCLUDED
