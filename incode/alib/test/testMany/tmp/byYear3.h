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
#ifndef ZZ_byYear_1XTOX_INCLUDED
#define ZZ_byYear_1XTOX_INCLUDED

class Took;
class Student;

// description of the cooperating classes
class byYear_1XtoXRelation : public byYear_Aggregate2Child {
public:
    byYear_1XtoXRelation() : byYear_Aggregate2Child(){ }
};

class byYear_1XtoXEntity1 : public byYear_Aggregate2Parent {
public:
    byYear_1XtoXEntity1() : byYear_Aggregate2Parent(){ }
};

// ----------------------------------------------------------

class byYear_1XtoX : private byYear_Aggregate2 {

public:
    static void add(Took *r, Student *e){ byYear_Aggregate2::addTail(e,r);}
    static void remove(Took *r){ byYear_Aggregate2::remove(r); }
    static Student* const entity1(Took *r){ return byYear_Aggregate2::parent(r); }
    static Took* const next1(Took *r){ // returns NULL when s is the tail
        return byYear_Aggregate2::next(r);
    }
    static Took* const prev1(Took *r){ // returns NULL when s is the head
        return byYear_Aggregate2::prev(r);
    }
};

class byYear_1XtoXIterator : private byYear_Aggregate2Iterator {
    // standard interface:          for(r=it.from1(e); r; r=it.next1()){...}
public:
    Took* from1(Student *e){return byYear_Aggregate2Iterator::fromHead(e);}
    Took* const next1(){return byYear_Aggregate2Iterator::next();}
};

#endif // ZZ_byYear_1XTOX_INCLUDED
