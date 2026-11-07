
// -------- data structure Bi1to1 ---------------
// which is the default for the bi-directional one-to-one association.
// This is just a wrapper class.
// ---------------------------------------------------
#ifndef ZZ_$$_BI1TO1_INCLUDED
#define ZZ_$$_BI1TO1_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Bi1to1Parent : public $$_DoubleLinkParent {
};

class $$_Bi1to1Child : public $$_DoubleLinkChild {
};

class $$_Bi1to1ParentBi1to1Child : public $$_DoubleLinkParentDoubleLinkChild {
};

class $$_Bi1to1 : public $$_DoubleLink {
};
    
#endif // ZZ_$$_BI1TO1_INCLUDED
