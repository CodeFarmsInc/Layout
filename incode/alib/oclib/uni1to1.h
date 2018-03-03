
// -------- data structure Uni1to1 ---------------
// which is the default for the uni-directional one-to-one association.
// This is just a wrapper class.
// ---------------------------------------------------
#ifndef ZZ_$$_UNI1TO1_INCLUDED
#define ZZ_$$_UNI1TO1_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Uni1to1Parent : public $$_SingleLinkParent {
};

class $$_Uni1to1Child : public $$_SingleLinkChild {
};

class $$_Uni1to1ParentUni1to1Child : public $$_SingleLinkParentSingleLinkChild {
};

class $$_Uni1to1 : public $$_SingleLink {
};
    
#endif // ZZ_$$_UNI1TO1_INCLUDED
