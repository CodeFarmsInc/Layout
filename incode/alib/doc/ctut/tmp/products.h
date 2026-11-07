
// -------- data structure SINGLY LINKED RING ---------------
// EQUIVALENT OF:
// template <class Node> class products_Ring1
// ----------------------------------------------------------
#ifndef ZZ_products_RING1_INCLUDED
#define ZZ_products_RING1_INCLUDED

class Product;
typedef int (*ZZsortFun)(const void *, const void *);

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class products_Ring1Element {
public:
    Product *next;
    products_Ring1Element(){ next=NULL; }
};

class products_Ring1 {

public:
    // standard interface
    static Product* addHead(Product *tail, Product *c); // returns new tail
    static Product* addTail(Product *tail, Product *c); // returns new tail
    static Product* append(Product *tail,Product *c1, Product *c2); // returns new tail
    static Product* remove(Product *tail, Product *c);  // returns new tail, NULL when empty
    static Product* const next(Product *p, Product *c); // returns NULL when p is tail
    static Product* const fwd(Product *c); // unprotected raw ring pointer
    static Product* sort(ZZsortFun cmpFun, Product *tail); // returns the new tail
    static void merge(Product *s,Product *t);

    // historical DOL compatible interface
    static Product* del(Product *tail, Product *c) { return remove(tail,c); }
    static Product* add(Product *tail, Product *c) { return addHead(tail,c); }
};

class products_Ring1Iterator {
    Product *tail; // NULL when loop finished
    Product *nxt;  // NULL when starting a new loop
public:
    // standard interface:          for(p=it.fromHead(x); p; p=it.next()){...}
    products_Ring1Iterator(){tail=nxt=NULL;}
    virtual Product* fromHead(Product *p);
    virtual Product* const next();

    // historical DOL interface:    it.start(x); for(p= ++it; p; p= ++it){...}
    virtual void start(Product *p);
    virtual Product* const operator++();
    products_Ring1Iterator(Product *p){start(p);}
};
    
#endif // ZZ_products_RING1_INCLUDED
