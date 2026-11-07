
// -------- data structure BAG = collection based on array of pointers --------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_Bag 
// ----------------------------------------------------------
#ifndef ZZ_$$_BAG_INCLUDED
#define ZZ_$$_BAG_INCLUDED


class $$_BagHolder : public $$_ArrayHolder {
friend class $$_Bag;
    int objCount;
public:
    $$_BagHolder() : $$_ArrayHolder() {objCount=0;}
};


class $$_Bag : private $$_Array {
friend class $$_BagIterator;
private:
    static $2* get($1 *hp,int i);
public:
    static void form($1 *hp,int initCap,int incr);
    static int count($1 *hp);
    static void free($1 *hp);
    static void add($1 *hp, $2 *obj);
    static void remove($1 *hp, $2 *obj); // removes all ref. to obj, see Note 1
};


class $$_BagIterator {
     $1 *holder;
     int index;
public:
    $$_BagIterator(){holder=NULL; index=0;}

    // standard iterator interface:   for(p=it.first(hp); p; p=it.next()){...}
    // -----------------------------------------------------------------
    $2* first($1 *hp);
    $2* const next();
};

// NOTE: add() can be called during an iteration loop without disturbing
//       the expected behaviour (the new items are added at the end).
//       remove() should not be called from within the loop -- the result
//       is unpredictable, some items may be missed. The problem here
//       is that more than one references to the same object may be removed,
//       which re-shuffles the internal array.


#endif // ZZ_$$_BAG_INCLUDED
