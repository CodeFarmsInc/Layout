#include <string.h>

// -------------------------------------------
// Form the array as if it just $$_Array, then initialize it
// as NULL. This is necessary, since it is only (void*)[] which
// has no constructor.
// -------------------------------------------
void** $$_Hash::form($1 *hp,int const sz){
    void** vv; int i;

    vv=$$_Array::form(hp,sz,0); // 0 = fixed array
    if(!vv)return NULL;
    for(i=0; i<sz; i++,vv++){ *vv=NULL; }
    hp->$0.count=0;
    return vv;
}

// -------------------------------------------
// Disconnect all the elements from the hash table,
// then free the table itself.
// -------------------------------------------
void $$_Hash::free($1 *hp){
    $2 *p; 
    $$_Iterator it;

    // disconnect all elements in the table
    for(p=it.first(hp,-1); p; p=it.next()){
        p->$0.next=NULL;
    }
    $$_Array::free(hp);
}

// -------------------------------------------
// Disconnect all elements from the table, and link them
// into one gigantic linked list.
// Re-allocate the array without copying the content.
// Re-load all the elements from the list into the new table.
// Returns: 0=everything OK, 1=error
// -------------------------------------------
int $$_Hash::resize($1 *hp, int newSz){
    $2 *p,*head,*nxt;
    $$_Iterator it;

    // link all elements into one list with 'head'
    for(p=it.first(hp,-1), head=NULL; p; p=it.next()){
        p->$0.next=head;
        head=p;
    }
    // 'head' is the beginning of the list now
 
    if($$_Array::sizeChange(hp,newSz,1))return 1; // 0 for exact size
    hp->$0.count=0; // start counting from 0 again

    // load the elements into the new table
    for(p=head, nxt=NULL; p; p=nxt){
        nxt=p->$0.next;
        p->$0.next=NULL;
        add(hp,p);
    }
    return 0;
}


// -------------------------------------------
// Search the table for an object which has the same key as 'obj'
// Return NULL when not finding it.
// -------------------------------------------
$2* $$_Hash::get($1 *hp, $2 *obj){
    int i; $2 *p,*s;

    i=hash(obj,hp->$0.sz);
    p=($2*)(hp->$0.array[i]);
    if(p){
        for(s=p->$0.next ; ; s=s->$0.next){
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
int $$_Hash::add($1 *hp, $2 *obj){ // obj = object to load into the hash table
    int i; $2 *p;

    if(obj->$0.next){
        printf("$$ error: adding object which already is in a hash table\n");
        return 1;
    }
    i=hash(obj,hp->$0.sz);
    p=($2*)(hp->$0.array[i]);
    if(p){obj->$0.next=p->$0.next; p->$0.next=obj;}
    else {obj->$0.next=obj; hp->$0.array[i]=obj;}
    (hp->$0.count)++;
    return 0;
}

// -------------------------------------------
// Remove either obj or one object from the table which has the same key.
// Algorithm: Find the bucket and traverse the list.
// Returns the removed object, or NULL if not found.
// -------------------------------------------
$2* $$_Hash::remove($1 *hp, $2 *obj){
    int i; $2 *p,*s,*prev;

    i=hash(obj,hp->$0.sz);
    p=($2*)(hp->$0.array[i]);
    if(p){
        for(s=p->$0.next, prev=p; ; prev=s, s=s->$0.next){
            if(!cmp(obj,s))break;
            if(s==p){s=NULL; break;}
        }
    }
    else s=NULL;

    if(!s){
        if(!obj) printf("Error $$: remove() called with obj=NULL\n");
        else if(obj->$0.next==NULL)
           printf("Warning $$: remove() obj not in any hash table\n");
        else printf("Error $$: remove() obj not in bucket=%d\n",i);
        return NULL;
    }

    // remove 's' from the list, 'prev' is the previous object in the list
    if(s==prev)   hp->$0.array[i]=NULL;
    else if(s==p) hp->$0.array[i]=s->$0.next;

    prev->$0.next=s->$0.next;
    s->$0.next=NULL;
    (hp->$0.count)--;
    return s;
}

// -------------------------------------------------------------
// Return the head of the list in bucket i, return NULL if empty.
// -------------------------------------------------------------
$2* $$_Hash::slot($1 *hp, int i){
    return ($2*)(hp->$0.array[i]);
}

// -----------------------------------------------------------------
int $$_Hash::size($1 *hp, int *popCount){ 
    *popCount=hp->$0.count;
    return $$_Array::size(hp); 
}

// -------------------------------------------------------------
// Convert a string into a bucket index between 0 and (hashSz-1)
// Algorithm by Sedgewick
// -------------------------------------------------------------
int $$_Hash::hashString(char *s,int hashSz){
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
int $$_Hash::hashInt(int val,int hashSz){
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
$2* $$_HashIterator::first($1 *hp,int i){
    $2 *p; int sz;

    holder=hp;
    sz=hp->$0.sz;

    if(i<0){all=1; bucket=0;}
    else {
        if(i>=sz){
            printf("$$ error calling first() bucket=%d max=%d\n",i,hp->$0.sz-1);
            return NULL;
        }
        bucket=i;
        all=0;
    }

    for(; bucket<sz; bucket++){
        tail=($2*)(hp->$0.array[bucket]); 
        if(!all || tail)break;
    }
    // tail is the first acceptable non-empty entry in the table
    if(!tail)return NULL;
    p=tail->$0.next;
    if(p==tail){
        if(!all)nxt=NULL;
        else {     // reset 'nxt' from this tail to the next non-empty bucket
            nxt=tail;
            (void)next(); // does not matter what it returs
        }
    }
    else nxt=p->$0.next;
    
    return p;
} 

$2* const $$_HashIterator::next(){
    $2 *p; int sz;

    if(!nxt)return NULL;
    sz=holder->$0.sz;
    p=nxt;
    if(nxt==tail){ // search for the next non-empty bucket
        if(!all)nxt=NULL; 
        else {
            for( tail=NULL, bucket++; bucket<sz; bucket++){
                tail=($2*)(holder->$0.array[bucket]); 
                if(tail)break;
            }
            if(!tail)nxt=NULL;
            else     nxt=tail->$0.next;
        }
    }
    else nxt=p->$0.next;

    return p;
}

// -----------------------------------------------------------------
// Historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
// It traverses only one bucket, use a loop with a call to slot() in
// order to traverse the entire table.
// -----------------------------------------------------------------
$2* const $$_HashIterator::operator++(){
    $2 *ret;

    if(tail){
        if(nxt){
            ret=nxt; 
            nxt=nxt->$0.next;
            if(ret==tail)tail=NULL;
        }
        else {
            ret=tail->$0.next;
            if(tail==ret)tail=NULL;
            else nxt=ret->$0.next;
        }
        return ret;
    }
    return NULL;
}
