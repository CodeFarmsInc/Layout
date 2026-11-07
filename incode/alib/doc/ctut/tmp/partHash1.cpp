#include <string.h>

// -------------------------------------------
// Form the array as if it just partHash_Array, then initialize it
// as NULL. This is necessary, since it is only (void*)[] which
// has no constructor.
// -------------------------------------------
void** partHash_Hash::form(Company *hp,int const sz){
    void** vv; int i;

    vv=partHash_Array::form(hp,sz,0); // 0 = fixed array
    if(!vv)return NULL;
    for(i=0; i<sz; i++,vv++){ *vv=NULL; }
    hp->ZZds.ZZpartHash.count=0;
    return vv;
}

// -------------------------------------------
// Disconnect all the elements from the hash table,
// then free the table itself.
// -------------------------------------------
void partHash_Hash::free(Company *hp){
    PartType *p; 
    partHash_Iterator it;

    // disconnect all elements in the table
    for(p=it.first(hp,-1); p; p=it.next()){
        p->ZZds.ZZpartHash.next=NULL;
    }
    partHash_Array::free(hp);
}

// -------------------------------------------
// Disconnect all elements from the table, and link them
// into one gigantic linked list.
// Re-allocate the array without copying the content.
// Re-load all the elements from the list into the new table.
// Returns: 0=everything OK, 1=error
// -------------------------------------------
int partHash_Hash::resize(Company *hp, int newSz){
    PartType *p,*head,*nxt;
    partHash_Iterator it;

    // link all elements into one list with 'head'
    for(p=it.first(hp,-1), head=NULL; p; p=it.next()){
        p->ZZds.ZZpartHash.next=head;
        head=p;
    }
    // 'head' is the beginning of the list now
 
    if(partHash_Array::sizeChange(hp,newSz,1))return 1; // 0 for exact size
    hp->ZZds.ZZpartHash.count=0; // start counting from 0 again

    // load the elements into the new table
    for(p=head, nxt=NULL; p; p=nxt){
        nxt=p->ZZds.ZZpartHash.next;
        p->ZZds.ZZpartHash.next=NULL;
        add(hp,p);
    }
    return 0;
}


// -------------------------------------------
// Search the table for an object which has the same key as 'obj'
// Return NULL when not finding it.
// -------------------------------------------
PartType* partHash_Hash::get(Company *hp, PartType *obj){
    int i; PartType *p,*s;

    i=hash(obj,hp->ZZds.ZZpartHash.sz);
    p=(PartType*)(hp->ZZds.ZZpartHash.array[i]);
    if(p){
        for(s=p->ZZds.ZZpartHash.next ; ; s=s->ZZds.ZZpartHash.next){
            if(!cmp(obj,s))break;
            if(s==p){s=NULL; break;}
        }
    }
    else s=NULL;
    return s;
}

// -------------------------------------------
// Use function hash() to convert object key to the bucket index,
// then add the object to the bucket list. Multiple objects with the same key
// are allowed in the table.
// Returns: 0=everything OK, 1=error
// -------------------------------------------
int partHash_Hash::add(Company *hp, PartType *obj){ // obj = object to load into the hash table
    int i; PartType *p;

    if(obj->ZZds.ZZpartHash.next){
        printf("partHash error: adding object which already is in a hash table\n");
        return 1;
    }
    i=hash(obj,hp->ZZds.ZZpartHash.sz);
    p=(PartType*)(hp->ZZds.ZZpartHash.array[i]);
    if(p){obj->ZZds.ZZpartHash.next=p->ZZds.ZZpartHash.next; p->ZZds.ZZpartHash.next=obj;}
    else {obj->ZZds.ZZpartHash.next=obj; hp->ZZds.ZZpartHash.array[i]=obj;}
    (hp->ZZds.ZZpartHash.count)++;
    return 0;
}

// -------------------------------------------
// Remove either obj or one object from the table which has the same key.
// Algorithm: Find the bucket and traverse the list.
// Returns the removed object, or NULL if not found.
// -------------------------------------------
PartType* partHash_Hash::remove(Company *hp, PartType *obj){
    int i; PartType *p,*s,*prev;

    i=hash(obj,hp->ZZds.ZZpartHash.sz);
    p=(PartType*)(hp->ZZds.ZZpartHash.array[i]);
    if(p){
        for(s=p->ZZds.ZZpartHash.next, prev=p; ; prev=s, s=s->ZZds.ZZpartHash.next){
            if(!cmp(obj,s))break;
            if(s==p){s=NULL; break;}
        }
    }
    else s=NULL;

    if(!s){
        if(!obj) printf("Error partHash: remove() called with obj=NULL\n");
        else if(obj->ZZds.ZZpartHash.next==NULL)
           printf("Warning partHash: remove() obj not in any hash table\n");
        else printf("Error partHash: remove() obj not in bucket=%d\n",i);
        return NULL;
    }

    // remove 's' from the list, 'prev' is the previous object in the list
    if(s==prev)   hp->ZZds.ZZpartHash.array[i]=NULL;
    else if(s==p) hp->ZZds.ZZpartHash.array[i]=s->ZZds.ZZpartHash.next;

    prev->ZZds.ZZpartHash.next=s->ZZds.ZZpartHash.next;
    s->ZZds.ZZpartHash.next=NULL;
    (hp->ZZds.ZZpartHash.count)--;
    return s;
}

// -------------------------------------------------------------
// Return the head of the list in bucket i, return NULL if empty.
// -------------------------------------------------------------
PartType* partHash_Hash::slot(Company *hp, int i){
    return (PartType*)(hp->ZZds.ZZpartHash.array[i]);
}

// -----------------------------------------------------------------
int partHash_Hash::size(Company *hp, int *popCount){ 
    *popCount=hp->ZZds.ZZpartHash.count;
    return partHash_Array::size(hp); 
}

// -------------------------------------------------------------
// Convert a string into a bucket index between 0 and (hashSz-1)
// Algorithm by Sedgewick
// -------------------------------------------------------------
int partHash_Hash::hashString(char *s,int hashSz){
    int i,hash,length;

    hash=0; 
    length=strlen(s);
    for(i=0; i<length; i++){
        hash=(117*hash + s[i])%hashSz;
    }
    return hash;
}

// ---------------------------------------------------------------------
// Convert an integer value into a bucket index between 0 and (hashSz-1)
// Algorithm: multiplication by the golden ratio (Standish, Knuth).
// WARNING: The negative value produces the same key as its absolute value.
// ---------------------------------------------------------------------
int partHash_Hash::hashInt(int val,int hashSz){
    static double d={0.6125423371};
    double di; int i;

    if(val<0)val= -val;
    di=d*val;
    i=(int)di;
    di=di-i;
    i=(int)(di*hashSz);
    return(i);
}

// -----------------------------------------------------------------
// Standard iterator interface:   for(p=it.first(i); p; p=it.next()){...}
// It can traverse one bucket(i>=0) or the entire table(i<0).
// -----------------------------------------------------------------
PartType* partHash_HashIterator::first(Company *hp,int i){
    PartType *p; int sz;

    holder=hp;
    sz=hp->ZZds.ZZpartHash.sz;

    if(i<0){all=1; bucket=0;}
    else {
        if(i>=sz){
            printf("partHash error calling first() bucket=%d max=%d\n",i,hp->ZZds.ZZpartHash.sz-1);
            return NULL;
        }
        bucket=i;
        all=0;
    }

    for(; bucket<sz; bucket++){
        tail=(PartType*)(hp->ZZds.ZZpartHash.array[bucket]); 
        if(!all || tail)break;
    }
    // tail is the first acceptable non-empty entry in the table
    if(!tail)return NULL;
    p=tail->ZZds.ZZpartHash.next;
    if(p==tail){
        if(!all)nxt=NULL;
        else {     // reset 'nxt' from this tail to the next non-empty bucket
            nxt=tail;
            (void)next(); // does not matter what it returs
        }
    }
    else nxt=p->ZZds.ZZpartHash.next;
    
    return p;
} 

PartType* const partHash_HashIterator::next(){
    PartType *p; int sz;

    if(!nxt)return NULL;
    sz=holder->ZZds.ZZpartHash.sz;
    p=nxt;
    if(nxt==tail){ // search for the next non-empty bucket
        if(!all)nxt=NULL; 
        else {
            for( tail=NULL, bucket++; bucket<sz; bucket++){
                tail=(PartType*)(holder->ZZds.ZZpartHash.array[bucket]); 
                if(tail)break;
            }
            if(!tail)nxt=NULL;
            else     nxt=tail->ZZds.ZZpartHash.next;
        }
    }
    else nxt=p->ZZds.ZZpartHash.next;

    return p;
}

// -----------------------------------------------------------------
// Historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
// It traverses only one bucket, use a loop with a call to slot() in
// order to traverse the entire table.
// -----------------------------------------------------------------
PartType* const partHash_HashIterator::operator++(){
    PartType *ret;

    if(tail){
        if(nxt){
            ret=nxt; 
            nxt=nxt->ZZds.ZZpartHash.next;
            if(ret==tail)tail=NULL;
        }
        else {
            ret=tail->ZZds.ZZpartHash.next;
            if(tail==ret)tail=NULL;
            else nxt=ret->ZZds.ZZpartHash.next;
        }
        return ret;
    }
    return NULL;
}
