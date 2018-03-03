// ----------------------------------------------------------
//                    1XtoX<Relation,Entity>
// ----------------------------------------------------------
// This data organization is not intended for direct use. It is the root
// organization of ManyToMany for 2,3 or more participating classes.
// Note that 1XtoX is derived from Aggregate2<>, but the 
// parameters are reversed.
//                                    Jiri Soukup, July 14, 2005
// ----------------------------------------------------------

// ----------------------------------------------------------
#ifndef ZZ_takes_1XTOX_INCLUDED
#define ZZ_takes_1XTOX_INCLUDED

class Takes;
class Student;

// description of the cooperating classes
class takes_1XtoXRelation : public takes_Aggregate2Child {
public:
    takes_1XtoXRelation() : takes_Aggregate2Child(){ }
};

class takes_1XtoXEntity1 : public takes_Aggregate2Parent {
public:
    takes_1XtoXEntity1() : takes_Aggregate2Parent(){ }
};

// ----------------------------------------------------------

class takes_1XtoX : private takes_Aggregate2 {

public:
    static void add(Takes *r, Student *e){ takes_Aggregate2::addTail(e,r);}
    static void remove(Takes *r){ takes_Aggregate2::remove(r); }
    static Student* const entity1(Takes *r){ return takes_Aggregate2::parent(r); }
    static Takes* const next1(Takes *r){ // returns NULL when s is the tail
        return takes_Aggregate2::next(r);
    }
    static Takes* const prev1(Takes *r){ // returns NULL when s is the head
        return takes_Aggregate2::prev(r);
    }
};

class takes_1XtoXIterator : private takes_Aggregate2Iterator {
    // standard interface:          for(r=it.from1(e); r; r=it.next1()){...}
public:
    Takes* from1(Student *e){return takes_Aggregate2Iterator::fromHead(e);}
    Takes* const next1(){return takes_Aggregate2Iterator::next();}
};

#endif // ZZ_takes_1XTOX_INCLUDED
