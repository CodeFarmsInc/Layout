
// -------- data structure DOUBLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent,class Child> class $$_LinkedList
// ----------------------------------------------------------
#ifndef ZZ_$$_LINKED_LIST2_INCLUDED
#define ZZ_$$_LINKED_LIST2_INCLUDED

class $1;
class $2;

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_LinkedList2Parent {
public:
    $2* tail;
    $$_LinkedList2Parent(){ tail=NULL; }
};

class $$_LinkedList2Child : public $$_Ring2Element {
public:
    $$_LinkedList2Child() : $$_Ring2Element(){ }
};

// the following class is used when Parent==Child
class $$_LinkedList2ParentLinkedList2Child : public $$_Ring2Element {
public:
    $2* tail;
    $$_LinkedList2ParentLinkedList2Child() : $$_Ring2Element(){ tail=NULL; }
};
// ----------------------------------------------------------

class $$_LinkedList2 : $$_Ring2 {

public:
    static $2* const tail($1 *p);
    static $2* const head($1 *p);
    static void addHead($1 *p, $2 *c);
    static void addTail($1 *p, $2 *c);
    static void append($1 *p,$2 *c1, $2 *c2);
    static void insert($2 *c1, $2 *c2);
    static void remove($1 *p, $2 *c);
    static $2* const next($1 *p, $2 *c);
    static $2* const prev($1 *p, $2 *c);
    static $2* const nextRing($2 *c);
    static $2* const prevRing($2 *c);
    static void sort(ZZsortFun cmpFun, $1 *p);
    static void merge($2 *s,$2 *t,$1 *p);
    static void setTail($1* p,$2* c,int check);

    // historical DOL compatible interface
    static void del($1 *p, $2 *c) { remove(p,c); }
    static void add($1 *p, $2 *c) { addHead(p,c);}
    static void ins($2 *c1, $2 *c2) { insert(c1,c2); }
    static $2* child($1* p);
    static void set($1* p,$2* c){ setTail(p,c,0);}
    static $2* const fwd($2 *c){return nextRing(c);}
    static $2* const bwd($2 *c){return prevRing(c);}
};

class $$_LinkedList2Iterator : public $$_Ring2Iterator {
public:
    $$_LinkedList2Iterator() : $$_Ring2Iterator(){}
    $$_LinkedList2Iterator(const $1 *p) : $$_Ring2Iterator(){ start(p); }
    void start(const $1 *p);
    $2* fromHead($1 *p);
    $2* fromTail($1 *p);
};
    
#endif // ZZ_$$_LINKED_LIST2_INCLUDED
