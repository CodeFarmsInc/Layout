
// -------- data structure Bi1toX ---------------
// which is the default for the bi-directional one-to-many association.
// This is just a wrapper class.
// ---------------------------------------------------
#ifndef ZZ_$$_BI1TOX_INCLUDED
#define ZZ_$$_BI1TOX_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_Bi1toXParent : public $$_Aggregate2Parent {
};

class $$_Bi1toXChild : public $$_Aggregate2Child {
};

class $$_Bi1toXParentBi1toXChild : public $$_Aggregate2ParentAggregate2Child {
};

class $$_Bi1toX : public $$_Aggregate2 {
};

class $$_Bi1toXIterator : public $$_Aggregate2Iterator {
};
    
#endif // ZZ_$$_BI1TOX_INCLUDED
