
// -------- data structure SINGLE LINK ---------------
// EQUIVALENT OF:
// template <class Parent, class Child> class per1_SingleLink 
// ---------------------------------------------------
#ifndef ZZ_per1_SINGLE_LINK_INCLUDED
#define ZZ_per1_SINGLE_LINK_INCLUDED

class Couple;
class Person;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class per1_SingleLinkParent {
public:
    Person* linkTo;
    per1_SingleLinkParent(){ linkTo=NULL; }
};

class per1_SingleLinkChild {
};

// The following class is used when Parent==Child
class per1_SingleLinkParentSingleLinkChild {
public:
    Person* linkTo;
    per1_SingleLinkParentSingleLinkChild(){ linkTo=NULL; }
};
// ----------------------------------------------------------

class per1_SingleLink {

public:
    static void add(Couple *p,Person *c);
    static void remove(Couple *p);
    static Person* const target(Couple *p);

    // historical, DOL and earlier versions of IN_CODE interfaces
    static void del(Couple *p){ remove(p); }
    static Person* const fwd(Couple *p){ return target(p); }
    static Person* const next(Couple *p){ return target(p); }
};
    
#endif // ZZ_per1_SINGLE_LINK_INCLUDED
