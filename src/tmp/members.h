
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class members_Ring1
// ----------------------------------------------------------
#ifndef ZZ_members_RING1_INCLUDED
#define ZZ_members_RING1_INCLUDED

class Member;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class members_Ring1Element {
public:
    Member *next;
    members_Ring1Element(){ next=NULL; }
};

class members_Ring1 {

public:
    // standard interface
    static Member* addHead(Member *tail, Member *c); // returns new tail
    static Member* addTail(Member *tail, Member *c); // returns new tail
    static Member* append(Member *tail,Member *c1, Member *c2); // returns new tail
    static Member* remove(Member *tail, Member *c);  // returns new tail, NULL when empty
    static Member* const next(Member *p, Member *c); // returns NULL when p is tail
    static Member* const nextRing(Member *c); // unprotected raw ring pointer
    static Member* sort(ZZsortFun cmpFun, Member *tail); // returns the new tail
    static void merge(Member *s,Member *t);

    // historical DOL compatible interface
    static Member* del(Member *tail, Member *c) { return remove(tail,c); }
    static Member* add(Member *tail, Member *c) { return addHead(tail,c); }
    static Member* const fwd(Member *c){ return nextRing(c);}
};

class members_Ring1Iterator {
    Member *tail; // NULL when loop finished
    Member *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    members_Ring1Iterator(){tail=nxt=NULL;}
    Member* fromHead(Member *p);
    Member* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    void start(Member *p);
    Member* const operator++();
    members_Ring1Iterator(Member *p){start(p);}
};
    
#endif // ZZ_members_RING1_INCLUDED
