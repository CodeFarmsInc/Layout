
// -------- data structure HASH TABLE ---------------
// EQUIVALENT OF:
// template <class Holder,class Element> class classes_Hash 
// ----------------------------------------------------------
#ifndef ZZ_classes_HASH1_INCLUDED
#define ZZ_classes_HASH1_INCLUDED

// ----------------------------------------------------------
// description of the cooperating classes
// ----------------------------------------------------------
class classes_HashHolder : public classes_ArrayHolder {
public:
    int count; // population count
    classes_HashHolder() : classes_ArrayHolder(){count=0;}
};

class classes_HashElement {
public:
    ApplClass* next; // ring of elements in the same bucket
    classes_HashElement(){next=NULL;}
};


class classes_Hash : public classes_Array {
public:
    static void** form(Generator *hp,int const sz);
    static int formed(Generator *hp){ return classes_Array::formed(hp); }
    static int size(Generator *hp, int *popCount);
    static void free(Generator *hp);
    static int resize(Generator *hp, int newSz);
    static ApplClass* get(Generator *hp, ApplClass *obj); // obj = temp.object with the required key
    static int add(Generator *hp, ApplClass *obj); // obj = object to load into the hash table
    static ApplClass* remove(Generator *hp, ApplClass *obj); 
            // obj = object with the key to be removed or the object itself

    // functions that must be provided by the application
    // --------------------------------------------------
    static int cmp(ApplClass *p1,ApplClass *p2); // return 0 if the objects have the same key
    static int hash(ApplClass *p,int hashSz); // converts key to the bucket number

    // convenient functions to use when coding hash()
    // --------------------------------------------------
    static int hashString(char *s,int hashSz);
    static int hashInt(int val,int hashSz);

    // historical DOL interface
    // --------------------------------------------------
    static ApplClass* del(Generator *hp, ApplClass *obj){return remove(hp,obj);}
    static ApplClass* slot(Generator *hp, int i);
    static int ZZhashString(char *s,int hashSz){return hashString(s,hashSz);}
    static int ZZhashInt(int val,int hashSz){return hashInt(val,hashSz);}
};


class classes_HashIterator {
    int all; // 1=all buckets, 0=just one given bucket
    int bucket;
    ApplClass *tail;
    ApplClass *nxt;
    Generator *holder;
public:
    classes_HashIterator(){all=0; bucket= -1; nxt=NULL; holder=NULL;}

    // standard iterator interface:   for(p=it.first(hp,i); p; p=it.next()){...}
    // -----------------------------------------------------------------
    ApplClass* first(Generator *hp,int i);  // traverse bucket i, for i<0 traverse all buckets
    ApplClass* const next();

    // historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
    // -----------------------------------------------------------------
    void start(ApplClass *p){tail=p; nxt=NULL; all=bucket=0; holder=NULL;}
    ApplClass* const operator++();
    classes_HashIterator(ApplClass *p){start(p);}
};

#endif // ZZ_classes_HASH1_INCLUDED
