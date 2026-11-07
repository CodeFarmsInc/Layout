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
#ifndef ZZ_marks_1XTOX_INCLUDED
#define ZZ_marks_1XTOX_INCLUDED

class Mark;
class Student;

// description of the cooperating classes
class marks_1XtoXRelation : public marks_Aggregate2Child {
public:
    marks_1XtoXRelation() : marks_Aggregate2Child(){ }
};

class marks_1XtoXEntity1 : public marks_Aggregate2Parent {
public:
    marks_1XtoXEntity1() : marks_Aggregate2Parent(){ }
};

// ----------------------------------------------------------

class marks_1XtoX : private marks_Aggregate2 {

public:
    static void add(Mark *r, Student *e){ marks_Aggregate2::addTail(e,r);}
    static void remove(Mark *r){ marks_Aggregate2::remove(r); }
    static Student* const entity1(Mark *r){ return marks_Aggregate2::parent(r); }
    static Mark* const next1(Mark *r){ // returns NULL when s is the tail
        return marks_Aggregate2::next(r);
    }
    static Mark* const prev1(Mark *r){ // returns NULL when s is the head
        return marks_Aggregate2::prev(r);
    }
};

class marks_1XtoXIterator : private marks_Aggregate2Iterator {
    // standard interface:          for(r=it.from1(e); r; r=it.next1()){...}
public:
    Mark* from1(Student *e){return marks_Aggregate2Iterator::fromHead(e);}
    Mark* const next1(){return marks_Aggregate2Iterator::next();}
};

#endif // ZZ_marks_1XTOX_INCLUDED
