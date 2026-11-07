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
#ifndef ZZ_takes_2XTOX_INCLUDED
#define ZZ_takes_2XTOX_INCLUDED

class Takes;
class Student;
class Course;

// description of the cooperating classes
class takes_2XtoXRelation : public takes_1XtoXRelation {
public:
    Takes *next2;
    Takes *prev2;
    Course *parent2;
    takes_2XtoXRelation() : takes_1XtoXRelation(){ next2=prev2=NULL; parent2=NULL;}
};

class takes_2XtoXEntity1 : public takes_1XtoXEntity1 {
public:
    takes_2XtoXEntity1() : takes_1XtoXEntity1(){ }
};

class takes_2XtoXEntity2 {
public:
    Takes *tail2;
    takes_2XtoXEntity2(){tail2=NULL;}
};


// ----------------------------------------------------------

class takes_2XtoX : public takes_1XtoX {

public:
    static void add(Takes *r, Student *e1,Course *e2); // equivalent of addTail()
    static void remove(Takes *r);

    static Student* const entity1(Takes *r){return takes_1XtoX::entity1(r);}
    static Takes* const next1(Takes *r)  {return takes_1XtoX::next1(r);}
    static Takes* const prev1(Takes *r)  {return takes_1XtoX::prev1(r);}

    static Course* const entity2(Takes *r);
    static Takes* const next2(Takes *r);   // returns NULL when s is the tail
    static Takes* const prev2(Takes *r);   // returns NULL when s is the head
};

class takes_2XtoXIterator : public takes_1XtoXIterator {
    // standard interface:          for(r=it.from1(e1); r; r=it.next1()){...}
    // standard interface:          for(r=it.from2(e2); r; r=it.next2()){...}
    Takes *tail2;
    Takes *nxt2;
public:
    Takes* from1(Student *e) {return takes_1XtoXIterator::from1(e);}
    Takes* const next1(){return takes_1XtoXIterator::next1();}

    Takes* from2(Course *e);
    Takes* const next2();
};

#endif // ZZ_takes_2XTOX_INCLUDED
