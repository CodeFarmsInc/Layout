
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class rStart_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_rStart_SINGLE_LINK_INCLUDED
#define ZZ_rStart_SINGLE_LINK_INCLUDED

class Header;
class Employee;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class rStart_SingleLinkParent {
public:
    Employee* linkTo;
    rStart_SingleLinkParent(){ linkTo=NULL; }
};

class rStart_SingleLinkChild {
};

// The following class is used when Parent==Child
class rStart_SingleLinkParentSingleLinkChild {
public:
    Employee* linkTo;
    rStart_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class rStart_SingleLink {

public:
    static void add(Header *p,Employee *c);
    static void remove(Header *p);
    static Employee* const target(Header *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Header *p){ remove(p); }
    static Employee* const fwd(Header *p){ return target(p); }
    static Employee* const next(Header *p){ return target(p); }
};
    
#endif // ZZ_rStart_SINGLE_LINK_INCLUDED
