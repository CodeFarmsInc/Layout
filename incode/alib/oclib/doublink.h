
// -------- data structure DOUBLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class $$_DoubleLink 
// ---------------------------------------------------
#ifndef ZZ_$$_DOUBLE_LINK_INCLUDED
#define ZZ_$$_DOUBLE_LINK_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_DoubleLinkParent : public $$_SingleLinkParent {
public:
    $$_DoubleLinkParent() : $$_SingleLinkParent(){};
};

class $$_DoubleLinkChild : $$_SingleLinkChild {
public:
    $1* linkFrom;
    $$_DoubleLinkChild(){linkFrom=NULL;}
};

// The following class is used when Parent==Child
class $$_DoubleLinkParentDoubleLinkChild :
                             $$_SingleLinkParentSingleLinkChild {
public:
    $1* linkFrom;
    $$_DoubleLinkParentDoubleLinkChild() :
             $$_SingleLinkParentSingleLinkChild(){ linkFrom=NULL; }
};
// ----------------------------------------------------------

class $$_DoubleLink {

public:
    static void add($1 *p,$2 *c);
    static void remove($1 *p);
    static $2* const target($1 *p);
    static $1* const source($2 *p);

    // historical DOL and other interfaces
    static void del($1 *p){ remove(p); }
    static $2* const fwd($1 *p){ return target(p); }
    static $2* const next($1 *p){ return target(p); }
    static $1* const bwd($2 *p){ return source(p); }
};
    
#endif // ZZ_$$_DOUBLE_LINK_INCLUDED
