
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class byTrack_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_byTrack_LINKED_LIST2_INCLUDED
#define ZZ_byTrack_LINKED_LIST2_INCLUDED

class Track;
class Edge;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class byTrack_LinkedList2Parent {
public:
    Edge* tail;
    byTrack_LinkedList2Parent(){ tail=NULL; }
};

class byTrack_LinkedList2Child : public byTrack_Ring2Element {
public:
    byTrack_LinkedList2Child() : byTrack_Ring2Element(){ }
};

// the following class is used when Parent==Child
class byTrack_LinkedList2ParentLinkedList2Child : public byTrack_Ring2Element {
public:
    Edge* tail;
    byTrack_LinkedList2ParentLinkedList2Child() : byTrack_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class byTrack_LinkedList2 : byTrack_Ring2 {

public:
    static Edge* const tail(Track *p);
    static Edge* const head(Track *p);
    static void addHead(Track *p, Edge *c);
    static void addTail(Track *p, Edge *c);
    static void append(Track *p,Edge *c1, Edge *c2);
    static void insert(Edge *c1, Edge *c2);
    static void remove(Track *p, Edge *c);
    static Edge* const next(Track *p, Edge *c);
    static Edge* const prev(Track *p, Edge *c);
    static Edge* const nextRing(Edge *c);
    static Edge* const prevRing(Edge *c);
    static void sort(ZZsortFun cmpFun, Track *p);
    static void merge(Edge *s,Edge *t,Track *p);
    static void setTail(Track* p,Edge* c,int check);

    // historical DOL compatible interface
    static void del(Track *p, Edge *c) { remove(p,c); }
    static void add(Track *p, Edge *c) { addHead(p,c);}
    static void ins(Edge *c1, Edge *c2) { insert(c1,c2); }
    static Edge* child(Track* p);
    static void set(Track* p,Edge* c){ setTail(p,c,0);}
    static Edge* const fwd(Edge *c){return nextRing(c);}
    static Edge* const bwd(Edge *c){return prevRing(c);}
};

class byTrack_LinkedList2Iterator : public byTrack_Ring2Iterator {
public:
    byTrack_LinkedList2Iterator() : byTrack_Ring2Iterator(){}
    byTrack_LinkedList2Iterator(const Track *p) : byTrack_Ring2Iterator(){ start(p); }
    void start(const Track *p);
    Edge* fromHead(Track *p);
    Edge* fromTail(Track *p);
};
    
#endif // ZZ_byTrack_LINKED_LIST2_INCLUDED
