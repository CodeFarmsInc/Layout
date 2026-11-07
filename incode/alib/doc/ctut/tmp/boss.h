
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class boss_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_boss_SINGLE_LINK_INCLUDED
#define ZZ_boss_SINGLE_LINK_INCLUDED

class Department;
class Manager;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class boss_SingleLinkParent {
public:
    Manager* linkTo;
    boss_SingleLinkParent(){ linkTo=NULL; }
};

class boss_SingleLinkChild {
};

// The following class is used when Parent==Child
class boss_SingleLinkParentSingleLinkChild {
public:
    Manager* linkTo;
    boss_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class boss_SingleLink {

public:
    static void add(Department *p,Manager *c);
    static void remove(Department *p);
    static Manager* const target(Department *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Department *p){ remove(p); }
    static Manager* const fwd(Department *p){ return target(p); }
    static Manager* const next(Department *p){ return target(p); }
};
    
#endif // ZZ_boss_SINGLE_LINK_INCLUDED
