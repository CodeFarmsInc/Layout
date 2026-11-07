
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class eRing_Ring1
// ----------------------------------------------------------
#ifndef ZZ_eRing_RING1_INCLUDED
#define ZZ_eRing_RING1_INCLUDED

class Employee;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class eRing_Ring1Element {
public:
    Employee *next;
    eRing_Ring1Element(){ next=NULL; }
};

class eRing_Ring1 {

public:
    // standard interface
    static Employee* addHead(Employee *tail, Employee *c); // returns new tail
    static Employee* addTail(Employee *tail, Employee *c); // returns new tail
    static Employee* append(Employee *tail,Employee *c1, Employee *c2); // returns new tail
    static Employee* remove(Employee *tail, Employee *c);  // returns new tail, NULL when empty
    static Employee* const next(Employee *p, Employee *c); // returns NULL when p is tail
    static Employee* const nextRing(Employee *c); // unprotected raw ring pointer
    static Employee* sort(ZZsortFun cmpFun, Employee *tail); // returns the new tail
    static void merge(Employee *s,Employee *t);

    // historical DOL compatible interface
    static Employee* del(Employee *tail, Employee *c) { return remove(tail,c); }
    static Employee* add(Employee *tail, Employee *c) { return addHead(tail,c); }
    static Employee* const fwd(Employee *c){ return nextRing(c);}
};

class eRing_Ring1Iterator {
    Employee *tail; // NULL when loop finished
    Employee *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    eRing_Ring1Iterator(){tail=nxt=NULL;}
    Employee* fromHead(Employee *p);
    Employee* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Employee *p);
    Employee* const operator++();
    eRing_Ring1Iterator(Employee *p){start(p);}
};
    
#endif // ZZ_eRing_RING1_INCLUDED
