
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class groups_Ring1
// ----------------------------------------------------------
#ifndef ZZ_groups_RING1_INCLUDED
#define ZZ_groups_RING1_INCLUDED

class Group;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class groups_Ring1Element {
public:
    Group *next;
    groups_Ring1Element(){ next=NULL; }
};

class groups_Ring1 {

public:
    // standard interface
    static Group* addHead(Group *tail, Group *c); // returns new tail
    static Group* addTail(Group *tail, Group *c); // returns new tail
    static Group* append(Group *tail,Group *c1, Group *c2); // returns new tail
    static Group* remove(Group *tail, Group *c);  // returns new tail, NULL when empty
    static Group* const next(Group *p, Group *c); // returns NULL when p is tail
    static Group* const nextRing(Group *c); // unprotected raw ring pointer
    static Group* sort(ZZsortFun cmpFun, Group *tail); // returns the new tail
    static void merge(Group *s,Group *t);

    // historical DOL compatible interface
    static Group* del(Group *tail, Group *c) { return remove(tail,c); }
    static Group* add(Group *tail, Group *c) { return addHead(tail,c); }
    static Group* const fwd(Group *c){ return nextRing(c);}
};

class groups_Ring1Iterator {
    Group *tail; // NULL when loop finished
    Group *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    groups_Ring1Iterator(){tail=nxt=NULL;}
    Group* fromHead(Group *p);
    Group* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Group *p);
    Group* const operator++();
    groups_Ring1Iterator(Group *p){start(p);}
};
    
#endif // ZZ_groups_RING1_INCLUDED
