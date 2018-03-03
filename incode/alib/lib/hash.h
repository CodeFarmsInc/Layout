
// -------- data structure HASH TABLE ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class $$_Hash 
// ----------------------------------------------------------
#ifndef ZZ_$$_HASH1_INCLUDED
#define ZZ_$$_HASH1_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class $$_HashHolder : public $$_ArrayHolder {
public:
    int count; // population count
    $$_HashHolder() : $$_ArrayHolder(){count=0;}
};

class $$_HashElement {
public:
    $2* next; // ring of elements in the same bucket
    $$_HashElement(){next=NULL;}
};


class $$_Hash : public $$_Array {
public:
    static void** form($1 *hp,int const sz);
    static int formed($1 *hp){ return $$_Array::formed(hp); }
    static int size($1 *hp, int *popCount);
    static void free($1 *hp);
    static int resize($1 *hp, int newSz);
    static $2* get($1 *hp, $2 *obj); // obj = temp.object with the required key
    static int add($1 *hp, $2 *obj); // obj = object to load into the hash table
    static $2* remove($1 *hp, $2 *obj); 
            // obj = object with the key to be removed or the object itself

    // functions that must be provided by the application
    // --------------------------------------------------
    static int cmp($2 *p1,$2 *p2); // return 0 if the objects have the same key
    static int hash($2 *p,int hashSz); // converts key to the bucket number

    // convenient functions to use when coding hash()
    // --------------------------------------------------
    static int hashString(char *s,int hashSz);
    static int hashInt(int val,int hashSz);

    // historical DOL interface
    // --------------------------------------------------
    static $2* del($1 *hp, $2 *obj){return remove(hp,obj);}
    static $2* slot($1 *hp, int i);
    static int ZZhashString(char *s,int hashSz){return hashString(s,hashSz);}
    static int ZZhashInt(int val,int hashSz){return hashInt(val,hashSz);}
};


class $$_HashIterator {
    int all; // 1=all buckets, 0=just one given bucket
    int bucket;
    $2 *tail;
    $2 *nxt;
    $1 *holder;
public:
    $$_HashIterator(){all=0; bucket= -1; nxt=NULL; holder=NULL;}

    // standard iterator interface:   for(p=it.first(hp,i); p; p=it.next()){...}
    // -----------------------------------------------------------------
    $2* first($1 *hp,int i);  // traverse bucket i, for i<0 traverse all buckets
    $2* const next();

    // historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
    // -----------------------------------------------------------------
    void start($2 *p){tail=p; nxt=NULL; all=bucket=0; holder=NULL;}
    $2* const operator++();
    $$_HashIterator($2 *p){start(p);}
};

#endif // ZZ_$$_HASH1_INCLUDED
