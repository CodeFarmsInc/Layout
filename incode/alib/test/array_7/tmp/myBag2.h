
// -------- data structure Uni1toX ---------------
// which is the default for the uni-directional one-to-many association.
// This is just a wrapper class.
// ---------------------------------------------------
#ifndef ZZ_myBag_UNI1TOX_INCLUDED
#define ZZ_myBag_UNI1TOX_INCLUDED

class Root;
class Part;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class myBag_Uni1toXParent : public myBag_BagHolder { };

class myBag_Uni1toX : public myBag_Bag { };

class myBag_Uni1toXIterator : public myBag_BagIterator { };
    
#endif // ZZ_myBag_UNI1TOX_INCLUDED
