#ifndef ZZ_prodName_NAME_INCLUDED
#define ZZ_prodName_NAME_INCLUDED
// -------- data structure SINGLY LINKED LIST ---------------
// EQUIVALENT OF:
// template <class Parent> class prodName_Name {
// ----------------------------------------------------------

class Product;

// description of the cooperating classes
class prodName_NameParent {
public:
    char* name;
    prodName_NameParent(){ name=NULL; }
};

// ----------------------------------------------------------

class prodName_Name {

public:
    static void add(Product *p, char *c);
    static char* get(Product *p);
    static char* remove(Product *p);
    static int compare(Product *p1,Product *p2);
    // ...
    // historical DOL interface
    static char* del(Product *p){char* s=get(p); remove(p); return s;}
    static char* fwd(Product *p){return get(p);}
};
    
#endif // ZZ_prodName_NAME_INCLUDED
