
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class myPartType_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_myPartType_SINGLE_LINK_INCLUDED
#define ZZ_myPartType_SINGLE_LINK_INCLUDED

class Participant;
class PartType;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class myPartType_SingleLinkParent {
public:
    PartType* linkTo;
    myPartType_SingleLinkParent(){ linkTo=NULL; }
};

class myPartType_SingleLinkChild {
};

// The following class is used when Parent==Child
class myPartType_SingleLinkParentSingleLinkChild {
public:
    PartType* linkTo;
    myPartType_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class myPartType_SingleLink {

public:
    static void add(Participant *p,PartType *c);
    static void remove(Participant *p);
    static PartType* const target(Participant *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Participant *p){ remove(p); }
    static PartType* const fwd(Participant *p){ return target(p); }
    static PartType* const next(Participant *p){ return target(p); }
};
    
#endif // ZZ_myPartType_SINGLE_LINK_INCLUDED
