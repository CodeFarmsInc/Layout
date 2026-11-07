
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class trace_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_trace_SINGLE_LINK_INCLUDED
#define ZZ_trace_SINGLE_LINK_INCLUDED

class Node;
class Edge;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class trace_SingleLinkParent {
public:
    Edge* linkTo;
    trace_SingleLinkParent(){ linkTo=NULL; }
};

class trace_SingleLinkChild {
};

// The following class is used when Parent==Child
class trace_SingleLinkParentSingleLinkChild {
public:
    Edge* linkTo;
    trace_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class trace_SingleLink {

public:
    static void add(Node *p,Edge *c);
    static void remove(Node *p);
    static Edge* const target(Node *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Node *p){ remove(p); }
    static Edge* const fwd(Node *p){ return target(p); }
    static Edge* const next(Node *p){ return target(p); }
};
    
#endif // ZZ_trace_SINGLE_LINK_INCLUDED
