
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class toEdge_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_toEdge_SINGLE_LINK_INCLUDED
#define ZZ_toEdge_SINGLE_LINK_INCLUDED

class EdgeRef;
class Edge;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class toEdge_SingleLinkParent {
public:
    Edge* linkTo;
    toEdge_SingleLinkParent(){ linkTo=NULL; }
};

class toEdge_SingleLinkChild {
};

// The following class is used when Parent==Child
class toEdge_SingleLinkParentSingleLinkChild {
public:
    Edge* linkTo;
    toEdge_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class toEdge_SingleLink {

public:
    static void add(EdgeRef *p,Edge *c);
    static void remove(EdgeRef *p);
    static Edge* const target(EdgeRef *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(EdgeRef *p){ remove(p); }
    static Edge* const fwd(EdgeRef *p){ return target(p); }
    static Edge* const next(EdgeRef *p){ return target(p); }
};
    
#endif // ZZ_toEdge_SINGLE_LINK_INCLUDED
