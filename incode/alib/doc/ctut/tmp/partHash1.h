
// -------- data structure HASH TABLE ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class partHash_Hash 
// ----------------------------------------------------------
#ifndef ZZ_partHash_HASH1_INCLUDED
#define ZZ_partHash_HASH1_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class partHash_HashHolder : public partHash_ArrayHolder {
public:
    int count; // population count
    partHash_HashHolder() : partHash_ArrayHolder(){count=0;}
};

class partHash_HashElement {
public:
    PartType* next; // ring of elements in the same bucket
    partHash_HashElement(){next=NULL;}
};


class partHash_Hash : public partHash_Array {
public:
    static void** form(Company *hp,int const sz);
    static int formed(Company *hp){ return partHash_Array::formed(hp); }
    static int size(Company *hp, int *popCount);
    static void free(Company *hp);
    static int resize(Company *hp, int newSz);
    static PartType* get(Company *hp, PartType *obj); // obj = temp.object with the required key
    static int add(Company *hp, PartType *obj); // obj = object to load into the hash table
    static PartType* remove(Company *hp, PartType *obj); 
            // obj = object with the key to be removed or the object itself

    // functions that must be provided by the application
    // --------------------------------------------------
    static int cmp(PartType *p1,PartType *p2); // return 0 if the objects have the same key
    static int hash(PartType *p,int hashSz); // converts key to the bucket number

    // convenient functions to use when coding hash()
    // --------------------------------------------------
    static int hashString(char *s,int hashSz);
    static int hashInt(int val,int hashSz);

    // historical DOL interface
    // --------------------------------------------------
    static PartType* del(Company *hp, PartType *obj){return remove(hp,obj);}
    static PartType* slot(Company *hp, int i);
    static int ZZhashString(char *s,int hashSz){return hashString(s,hashSz);}
    static int ZZhashInt(int val,int hashSz){return hashInt(val,hashSz);}
};


class partHash_HashIterator {
    int all; // 1=all buckets, 0=just one given bucket
    int bucket;
    PartType *tail;
    PartType *nxt;
    Company *holder;
public:
    partHash_HashIterator(){all=0; bucket= -1; nxt=NULL; holder=NULL;}

    // standard iterator interface:   for(p=it.first(hp,i); p; p=it.next()){...}
    // -----------------------------------------------------------------
    PartType* first(Company *hp,int i);  // traverse bucket i, for i<0 traverse all buckets
    PartType* const next();

    // historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
    // -----------------------------------------------------------------
    void start(PartType *p){tail=p; nxt=NULL; all=bucket=0; holder=NULL;}
    PartType* const operator++();
    partHash_HashIterator(PartType *p){start(p);}
};

#endif // ZZ_partHash_HASH1_INCLUDED
