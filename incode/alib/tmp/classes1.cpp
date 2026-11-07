#include <string.h>

// -------------------------------------------
// Form the array as if it just classes_Array, then initialize it
// as NULL. This is necessary, since it is only (void*)[] which
// has no constructor.
// -------------------------------------------
void** classes_Hash::form(Generator *hp,int const sz){
    void** vv; int i;

    vv=classes_Array::form(hp,sz,0); // 0 = fixed array
    if(!vv)return NULL;
    for(i=0; i<sz; i++,vv++){ *vv=NULL; }
    hp->ZZds.ZZclasses.count=0;
    return vv;
}

// -------------------------------------------
// Disconnect all the elements from the hash table,
// then free the table itself.
// -------------------------------------------
void classes_Hash::free(Generator *hp){
    ApplClass *p; 
    classes_Iterator it;

    // disconnect all elements in the table
    for(p=it.first(hp,-1); p; p=it.next()){
        p->ZZds.ZZclasses.next=NULL;
    }
    classes_Array::free(hp);
}

// -------------------------------------------
// Disconnect all elements from the table, and link them
// into one gigantic linked list.
// Re-allocate the array without copying the content.
// Re-load all the elements from the list into the new table.
// Returns: 0=everything OK, 1=error
// -------------------------------------------
int classes_Hash::resize(Generator *hp, int newSz){
    ApplClass *p,*head,*nxt;
    classes_Iterator it;

    // link all elements into one list with 'head'
    for(p=it.first(hp,-1), head=NULL; p; p=it.next()){
        p->ZZds.ZZclasses.next=head;
        head=p;
    }
    // 'head' is the beginning of the list now
 
    if(classes_Array::sizeChange(hp,newSz,1))return 1; // 0 for exact size
    hp->ZZds.ZZclasses.count=0; // start counting from 0 again

    // load the elements into the new table
    for(p=head, nxt=NULL; p; p=nxt){
        nxt=p->ZZds.ZZclasses.next;
        p->ZZds.ZZclasses.next=NULL;
        add(hp,p);
    }
    return 0;
}


// -------------------------------------------
// Search the table for an object which has the same key as 'obj'
// Return NULL when not finding it.
// -------------------------------------------
ApplClass* classes_Hash::get(Generator *hp, ApplClass *obj){
    int i; ApplClass *p,*s;

    i=hash(obj,hp->ZZds.ZZclasses.sz);
    p=(ApplClass*)(hp->ZZds.ZZclasses.array[i]);
    if(p){
        for(s=p->ZZds.ZZclasses.next ; ; s=s->ZZds.ZZclasses.next){
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
int classes_Hash::add(Generator *hp, ApplClass *obj){ // obj = object to load into the hash table
    int i; ApplClass *p;

    if(obj->ZZds.ZZclasses.next){
        printf("classes error: adding object which already is in a hash table\n");
        return 1;
    }
    i=hash(obj,hp->ZZds.ZZclasses.sz);
    p=(ApplClass*)(hp->ZZds.ZZclasses.array[i]);
    if(p){obj->ZZds.ZZclasses.next=p->ZZds.ZZclasses.next; p->ZZds.ZZclasses.next=obj;}
    else {obj->ZZds.ZZclasses.next=obj; hp->ZZds.ZZclasses.array[i]=obj;}
    (hp->ZZds.ZZclasses.count)++;
    return 0;
}

// -------------------------------------------
// Remove either obj or one object from the table which has the same key.
// Algorithm: Find the bucket and traverse the list.
// Returns the removed object, or NULL if not found.
// -------------------------------------------
ApplClass* classes_Hash::remove(Generator *hp, ApplClass *obj){
    int i; ApplClass *p,*s,*prev;

    i=hash(obj,hp->ZZds.ZZclasses.sz);
    p=(ApplClass*)(hp->ZZds.ZZclasses.array[i]);
    if(p){
        for(s=p->ZZds.ZZclasses.next, prev=p; ; prev=s, s=s->ZZds.ZZclasses.next){
            if(!cmp(obj,s))break;
            if(s==p){s=NULL; break;}
        }
    }
    else s=NULL;

    if(!s){
        if(!obj) printf("Error classes: remove() called with obj=NULL\n");
        else if(obj->ZZds.ZZclasses.next==NULL)
           printf("Warning classes: remove() obj not in any hash table\n");
        else printf("Error classes: remove() obj not in bucket=%d\n",i);
        return NULL;
    }

    // remove 's' from the list, 'prev' is the previous object in the list
    if(s==prev)   hp->ZZds.ZZclasses.array[i]=NULL;
    else if(s==p) hp->ZZds.ZZclasses.array[i]=s->ZZds.ZZclasses.next;

    prev->ZZds.ZZclasses.next=s->ZZds.ZZclasses.next;
    s->ZZds.ZZclasses.next=NULL;
    (hp->ZZds.ZZclasses.count)--;
    return s;
}

// -------------------------------------------------------------
// Return the head of the list in bucket i, return NULL if empty.
// -------------------------------------------------------------
ApplClass* classes_Hash::slot(Generator *hp, int i){
    return (ApplClass*)(hp->ZZds.ZZclasses.array[i]);
}

// -----------------------------------------------------------------
int classes_Hash::size(Generator *hp, int *popCount){ 
    *popCount=hp->ZZds.ZZclasses.count;
    return classes_Array::size(hp); 
}

// -------------------------------------------------------------
// Convert a string into a bucket index between 0 and (hashSz-1)
// Algorithm by Sedgewick
// -------------------------------------------------------------
int classes_Hash::hashString(char *s,int hashSz){
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
int classes_Hash::hashInt(int val,int hashSz){
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
ApplClass* classes_HashIterator::first(Generator *hp,int i){
    ApplClass *p; int sz;

    holder=hp;
    sz=hp->ZZds.ZZclasses.sz;

    if(i<0){all=1; bucket=0;}
    else {
        if(i>=sz){
            printf("classes error calling first() bucket=%d max=%d\n",i,hp->ZZds.ZZclasses.sz-1);
            return NULL;
        }
        bucket=i;
        all=0;
    }

    for(; bucket<sz; bucket++){
        tail=(ApplClass*)(hp->ZZds.ZZclasses.array[bucket]); 
        if(!all || tail)break;
    }
    // tail is the first acceptable non-empty entry in the table
    if(!tail)return NULL;
    p=tail->ZZds.ZZclasses.next;
    if(p==tail){
        if(!all)nxt=NULL;
        else {     // reset 'nxt' from this tail to the next non-empty bucket
            nxt=tail;
            (void)next(); // does not matter what it returs
        }
    }
    else nxt=p->ZZds.ZZclasses.next;
    
    return p;
} 

ApplClass* const classes_HashIterator::next(){
    ApplClass *p; int sz;

    if(!nxt)return NULL;
    sz=holder->ZZds.ZZclasses.sz;
    p=nxt;
    if(nxt==tail){ // search for the next non-empty bucket
        if(!all)nxt=NULL; 
        else {
            for( tail=NULL, bucket++; bucket<sz; bucket++){
                tail=(ApplClass*)(holder->ZZds.ZZclasses.array[bucket]); 
                if(tail)break;
            }
            if(!tail)nxt=NULL;
            else     nxt=tail->ZZds.ZZclasses.next;
        }
    }
    else nxt=p->ZZds.ZZclasses.next;

    return p;
}

// -----------------------------------------------------------------
// Historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
// It traverses only one bucket, use a loop with a call to slot() in
// order to traverse the entire table.
// -----------------------------------------------------------------
ApplClass* const classes_HashIterator::operator++(){
    ApplClass *ret;

    if(tail){
        if(nxt){
            ret=nxt; 
            nxt=nxt->ZZds.ZZclasses.next;
            if(ret==tail)tail=NULL;
        }
        else {
            ret=tail->ZZds.ZZclasses.next;
            if(tail==ret)tail=NULL;
            else nxt=ret->ZZds.ZZclasses.next;
        }
        return ret;
    }
    return NULL;
}
