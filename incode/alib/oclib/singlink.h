
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class $$_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_$$_SINGLE_LINK_INCLUDED
#define ZZ_$$_SINGLE_LINK_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_SingleLinkParent {
public:
    $2* linkTo;
    $$_SingleLinkParent(){ linkTo=NULL; }
};

class $$_SingleLinkChild {
};

// The following class is used when Parent==Child
class $$_SingleLinkParentSingleLinkChild {
public:
    $2* linkTo;
    $$_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class $$_SingleLink {

public:
    static void add($1 *p,$2 *c);
    static void remove($1 *p);
    static $2* const target($1 *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del($1 *p){ remove(p); }
    static $2* const fwd($1 *p){ return target(p); }
    static $2* const next($1 *p){ return target(p); }
};
    
#endif // ZZ_$$_SINGLE_LINK_INCLUDED
