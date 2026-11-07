
// -------- data structure HASH TABLE ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class byName_Hash 
// ----------------------------------------------------------
#ifndef ZZ_byName_HASH1_INCLUDED
#define ZZ_byName_HASH1_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class byName_HashHolder : public byName_ArrayHolder {
public:
    int count; // population count
    byName_HashHolder() : byName_ArrayHolder(){count=0;}
};

class byName_HashElement {
public:
    Employee* next; // ring of elements in the same bucket
    byName_HashElement(){next=NULL;}
};


class byName_Hash : public byName_Array {
public:
    static void** form(Company *hp,int const sz);
    static int formed(Company *hp){ return byName_Array::formed(hp); }
    static int size(Company *hp, int *popCount);
    static void free(Company *hp);
    static int resize(Company *hp, int newSz);
    static Employee* get(Company *hp, Employee *obj); // obj = temp.object with the required key
    static int add(Company *hp, Employee *obj); // obj = object to load into the hash table
    static Employee* remove(Company *hp, Employee *obj); 
            // obj = object with the key to be removed or the object itself

    // functions that must be provided by the application
    // --------------------------------------------------
    static int cmp(Employee *p1,Employee *p2); // return 0 if the objects have the same key
    static int hash(Employee *p,int hashSz); // converts key to the bucket number

    // convenient functions to use when coding hash()
    // --------------------------------------------------
    static int hashString(char *s,int hashSz);
    static int hashInt(int val,int hashSz);

    // historical DOL interface
    // --------------------------------------------------
    static Employee* del(Company *hp, Employee *obj){return remove(hp,obj);}
    static Employee* slot(Company *hp, int i);
    static int ZZhashString(char *s,int hashSz){return hashString(s,hashSz);}
    static int ZZhashInt(int val,int hashSz){return hashInt(val,hashSz);}
};


class byName_HashIterator {
    int all; // 1=all buckets, 0=just one given bucket
    int bucket;
    Employee *tail;
    Employee *nxt;
    Company *holder;
public:
    byName_HashIterator(){all=0; bucket= -1; nxt=NULL; holder=NULL;}

    // standard iterator interface:   for(p=it.first(hp,i); p; p=it.next()){...}
    // -----------------------------------------------------------------
    Employee* first(Company *hp,int i);  // traverse bucket i, for i<0 traverse all buckets
    Employee* const next();

    // historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
    // -----------------------------------------------------------------
    void start(Employee *p){tail=p; nxt=NULL; all=bucket=0; holder=NULL;}
    Employee* const operator++();
    byName_HashIterator(Employee *p){start(p);}
};

#endif // ZZ_byName_HASH1_INCLUDED
