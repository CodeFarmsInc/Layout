
// -------- data structure BAG = collection based on array of pointers --------
// EQUIVALENT OF:
// template <class Holder,class Element> class assemble_Bag 
// ----------------------------------------------------------
#ifndef ZZ_assemble_BAG_INCLUDED
#define ZZ_assemble_BAG_INCLUDED


class assemble_BagHolder : public assemble_ArrayHolder {
friend class assemble_Bag;
    int objCount;
public:
    assemble_BagHolder() : assemble_ArrayHolder() {objCount=0;}
};


class assemble_Bag : private assemble_Array {
friend class assemble_BagIterator;
private:
    static PartType* get(Assembly *hp,int i);
public:
    static void form(Assembly *hp,int initCap,int incr);
    static int count(Assembly *hp);
    static void free(Assembly *hp);
    static void add(Assembly *hp, PartType *obj);
    static void remove(Assembly *hp, PartType *obj); // removes all ref. to obj, see Note 1
};


class assemble_BagIterator {
     Assembly *holder;
     int index;
public:
    assemble_BagIterator(){holder=NULL; index=0;}

    // standard iterator interface:   for(p=it.first(hp); p; p=it.next()){...}
    // -----------------------------------------------------------------
    PartType* first(Assembly *hp);
    PartType* const next();
};

// NOTE: add() can be called during an iteration loop without disturbing
//       the expected behaviour (the new items are added at the end).
//       remove() should not be called from within the loop -- the result
//       is unpredictable, some items may be missed. The problem here
//       is that more than one references to the same object may be removed,
//       which re-shuffles the internal array.


#endif // ZZ_assemble_BAG_INCLUDED
