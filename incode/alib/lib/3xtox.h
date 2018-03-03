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
#ifndef ZZ_$$_3XTOX_INCLUDED
#define ZZ_$$_3XTOX_INCLUDED

class $1;
class $2;
class $3;
class $4;

// description of the cooperating classes
class $$_3XtoXRelation : public $$_2XtoXRelation {
public:
    $1 *next3;
    $1 *prev3;
    $4 *parent3;
    $$_3XtoXRelation() : $$_2XtoXRelation(){ next3=prev3=NULL; parent3=NULL;}
};

class $$_3XtoXEntity1 : public $$_2XtoXEntity1 {
public:
    $$_3XtoXEntity1() : $$_2XtoXEntity1(){ }
};

class $$_3XtoXEntity2 : public $$_2XtoXEntity2 {
public:
    $$_3XtoXEntity2() : $$_2XtoXEntity2(){ }
};

class $$_3XtoXEntity3 {
public:
    $1 *tail3;
    $$_3XtoXEntity3(){tail3=NULL;}
};


// ----------------------------------------------------------

class $$_3XtoX : public $$_2XtoX {

public:
    static void add($1 *r, $2 *e1,$3 *e2,$4 *e3); // equivalent of addTail()
    static void remove($1 *r);
    static $2* const entity1($1 *r){ return $$_1XtoX::entity1(r); }
    static $3* const entity2($1 *r){ return $$_2XtoX::entity2(r); }
    static $4* const entity3($1 *r);
    static $1* const next1($1 *r){ return $$_1XtoX::next1(r); }
    static $1* const prev1($1 *r){ return $$_1XtoX::prev1(r); }
    static $1* const next2($1 *r){ return $$_2XtoX::next2(r); }
    static $1* const prev2($1 *r){ return $$_2XtoX::prev2(r); }
    static $1* const next3($1 *r);   // returns NULL when s is the tail
    static $1* const prev3($1 *r);   // returns NULL when s is the head
};

class $$_3XtoXIterator : public $$_2XtoXIterator {
    // standard interface:          for(r=it.from1(e1); r; r=it.next1()){...}
    // standard interface:          for(r=it.from2(e2); r; r=it.next2()){...}
    // standard interface:          for(r=it.from3(e3); r; r=it.next3()){...}
    $1 *tail3;
    $1 *nxt3;
public:
    $1* from1($2 *e){ return $$_1XtoXIterator::from1(e);}
    $1* const next1(){ return $$_1XtoXIterator::next1();}
    $1* from2($3 *e){ return $$_2XtoXIterator::from2(e);}
    $1* const next2(){ return $$_2XtoXIterator::next2();}
    $1* from3($4 *e);
    $1* const next3();
};

#endif // ZZ_$$_3XTOX_INCLUDED
