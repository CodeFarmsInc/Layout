
// -------- data structure BAG = collection based on array of pointers --------
// EQUIVALENT OF:
// template <class Holder,class Element> class myBag_Bag 
// ----------------------------------------------------------
#ifndef ZZ_myBag_BAG_INCLUDED
#define ZZ_myBag_BAG_INCLUDED


class myBag_BagHolder : public myBag_ArrayHolder {
friend class myBag_Bag;
    int objCount;
public:
    myBag_BagHolder() : myBag_ArrayHolder() {objCount=0;}
};


class myBag_Bag : private myBag_Array {
friend class myBag_BagIterator;
private:
    static Part* get(Root *hp,int i);
public:
    static void form(Root *hp,int initCap,int incr);
    static int count(Root *hp);
    static void free(Root *hp);
    static void add(Root *hp, Part *obj);
    static void remove(Root *hp, Part *obj); // removes all ref. to obj, see Note 1
};


class myBag_BagIterator {
     Root *holder;
     int index;
public:
    myBag_BagIterator(){holder=NULL; index=0;}

    // standard iterator interface:   for(p=it.first(hp); p; p=it.next()){...}
    // -----------------------------------------------------------------
    Part* first(Root *hp);
    Part* const next();
};

// NOTE: add() can be called during an iteration loop without disturbing
//       the expected behaviour (the new items are added at the end).
//       remove() should not be called from within the loop -- the result
//       is unpredictable, some items may be missed. The problem here
//       is that more than one references to the same object may be removed,
//       which re-shuffles the internal array.


#endif // ZZ_myBag_BAG_INCLUDED
