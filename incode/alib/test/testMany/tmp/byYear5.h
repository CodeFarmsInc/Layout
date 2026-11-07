// ----------------------------------------------------------
//            3XtoX<Relation,Entity1,Entity2,Entity3>
//
// This is a good example how Many-to-Many can be expanded to any
// number of parameters.
// ----------------------------------------------------------
// By repeating this code with minor modifications, it is easy
// to derive higher order many-to-many relations:
//    from 2XtoX to derive 2XtoX (this code)
//    from 2XtoX to derive 3XtoX
//    from 3XtoX to derive 4XtoX
//    ... and so on ...
//                                    Jiri Soukup, July 14, 2005
// ----------------------------------------------------------

// ----------------------------------------------------------
#ifndef ZZ_byYear_3XTOX_INCLUDED
#define ZZ_byYear_3XTOX_INCLUDED

class Took;
class Student;
class Course;
class Year;

// description of the cooperating classes
class byYear_3XtoXRelation : public byYear_2XtoXRelation {
public:
    Took *next3;
    Took *prev3;
    Year *parent3;
    byYear_3XtoXRelation() : byYear_2XtoXRelation(){ next3=prev3=NULL; parent3=NULL;}
};

class byYear_3XtoXEntity1 : public byYear_2XtoXEntity1 {
public:
    byYear_3XtoXEntity1() : byYear_2XtoXEntity1(){ }
};

class byYear_3XtoXEntity2 : public byYear_2XtoXEntity2 {
public:
    byYear_3XtoXEntity2() : byYear_2XtoXEntity2(){ }
};

class byYear_3XtoXEntity3 {
public:
    Took *tail3;
    byYear_3XtoXEntity3(){tail3=NULL;}
};


// ----------------------------------------------------------

class byYear_3XtoX : public byYear_2XtoX {

public:
    static void add(Took *r, Student *e1,Course *e2,Year *e3); // equivalent of addTail()
    static void remove(Took *r);
    static Student* const entity1(Took *r){ return byYear_1XtoX::entity1(r); }
    static Course* const entity2(Took *r){ return byYear_2XtoX::entity2(r); }
    static Year* const entity3(Took *r);
    static Took* const next1(Took *r){ return byYear_1XtoX::next1(r); }
    static Took* const prev1(Took *r){ return byYear_1XtoX::prev1(r); }
    static Took* const next2(Took *r){ return byYear_2XtoX::next2(r); }
    static Took* const prev2(Took *r){ return byYear_2XtoX::prev2(r); }
    static Took* const next3(Took *r);   // returns NULL when s is the tail
    static Took* const prev3(Took *r);   // returns NULL when s is the head
};

class byYear_3XtoXIterator : public byYear_2XtoXIterator {
    // standard interface:          for(r=it.from1(e1); r; r=it.next1()){...}
    // standard interface:          for(r=it.from2(e2); r; r=it.next2()){...}
    // standard interface:          for(r=it.from3(e3); r; r=it.next3()){...}
    Took *tail3;
    Took *nxt3;
public:
    Took* from1(Student *e){ return byYear_1XtoXIterator::from1(e);}
    Took* const next1(){ return byYear_1XtoXIterator::next1();}
    Took* from2(Course *e){ return byYear_2XtoXIterator::from2(e);}
    Took* const next2(){ return byYear_2XtoXIterator::next2();}
    Took* from3(Year *e);
    Took* const next3();
};

#endif // ZZ_byYear_3XTOX_INCLUDED
