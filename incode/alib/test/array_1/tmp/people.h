
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class people_Ring1
// ----------------------------------------------------------
#ifndef ZZ_people_RING1_INCLUDED
#define ZZ_people_RING1_INCLUDED

class Person;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class people_Ring1Element {
public:
    Person *next;
    people_Ring1Element(){ next=NULL; }
};

class people_Ring1 {

public:
    // standard interface
    static Person* addHead(Person *tail, Person *c); // returns new tail
    static Person* addTail(Person *tail, Person *c); // returns new tail
    static Person* append(Person *tail,Person *c1, Person *c2); // returns new tail
    static Person* remove(Person *tail, Person *c);  // returns new tail, NULL when empty
    static Person* const next(Person *p, Person *c); // returns NULL when p is tail
    static Person* const nextRing(Person *c); // unprotected raw ring pointer
    static Person* sort(ZZsortFun cmpFun, Person *tail); // returns the new tail
    static void merge(Person *s,Person *t);

    // historical DOL compatible interface
    static Person* del(Person *tail, Person *c) { return remove(tail,c); }
    static Person* add(Person *tail, Person *c) { return addHead(tail,c); }
    static Person* const fwd(Person *c){ return nextRing(c);}
};

class people_Ring1Iterator {
    Person *tail; // NULL when loop finished
    Person *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    people_Ring1Iterator(){tail=nxt=NULL;}
    Person* fromHead(Person *p);
    Person* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Person *p);
    Person* const operator++();
    people_Ring1Iterator(Person *p){start(p);}
};
    
#endif // ZZ_people_RING1_INCLUDED
