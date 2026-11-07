// ----------------------------------------------------------
//                    2XtoX<Relation,Entity1,Entity2>
//
// This is the most frequently used Many-To-Many relation between
// two entity types. For each recorded relation there is an Relation object.
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
#ifndef ZZ_byYear_2XTOX_INCLUDED
#define ZZ_byYear_2XTOX_INCLUDED

class Took;
class Student;
class Course;

// description of the cooperating classes
class byYear_2XtoXRelation : public byYear_1XtoXRelation {
public:
    Took *next2;
    Took *prev2;
    Course *parent2;
    byYear_2XtoXRelation() : byYear_1XtoXRelation(){ next2=prev2=NULL; parent2=NULL;}
};

class byYear_2XtoXEntity1 : public byYear_1XtoXEntity1 {
public:
    byYear_2XtoXEntity1() : byYear_1XtoXEntity1(){ }
};

class byYear_2XtoXEntity2 {
public:
    Took *tail2;
    byYear_2XtoXEntity2(){tail2=NULL;}
};


// ----------------------------------------------------------

class byYear_2XtoX : public byYear_1XtoX {

public:
    static void add(Took *r, Student *e1,Course *e2); // equivalent of addTail()
    static void remove(Took *r);

    static Student* const entity1(Took *r){return byYear_1XtoX::entity1(r);}
    static Took* const next1(Took *r)  {return byYear_1XtoX::next1(r);}
    static Took* const prev1(Took *r)  {return byYear_1XtoX::prev1(r);}

    static Course* const entity2(Took *r);
    static Took* const next2(Took *r);   // returns NULL when s is the tail
    static Took* const prev2(Took *r);   // returns NULL when s is the head
};

class byYear_2XtoXIterator : public byYear_1XtoXIterator {
    // standard interface:          for(r=it.from1(e1); r; r=it.next1()){...}
    // standard interface:          for(r=it.from2(e2); r; r=it.next2()){...}
    Took *tail2;
    Took *nxt2;
public:
    Took* from1(Student *e) {return byYear_1XtoXIterator::from1(e);}
    Took* const next1(){return byYear_1XtoXIterator::next1();}

    Took* from2(Course *e);
    Took* const next2();
};

#endif // ZZ_byYear_2XTOX_INCLUDED
