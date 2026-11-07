
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class hPtr_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_hPtr_SINGLE_LINK_INCLUDED
#define ZZ_hPtr_SINGLE_LINK_INCLUDED

class PtrEmpl;
class Employee;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class hPtr_SingleLinkParent {
public:
    Employee* linkTo;
    hPtr_SingleLinkParent(){ linkTo=NULL; }
};

class hPtr_SingleLinkChild {
};

// The following class is used when Parent==Child
class hPtr_SingleLinkParentSingleLinkChild {
public:
    Employee* linkTo;
    hPtr_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class hPtr_SingleLink {

public:
    static void add(PtrEmpl *p,Employee *c);
    static void remove(PtrEmpl *p);
    static Employee* const target(PtrEmpl *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(PtrEmpl *p){ remove(p); }
    static Employee* const fwd(PtrEmpl *p){ return target(p); }
    static Employee* const next(PtrEmpl *p){ return target(p); }
};
    
#endif // ZZ_hPtr_SINGLE_LINK_INCLUDED
