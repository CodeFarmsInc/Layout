#include <string.h>

// -------------------------------------------
// Form the array as if it just byName_Array, then initialize it
// as NULL. This is necessary, since it is only (void*)[] which
// has no constructor.
// -------------------------------------------
void** byName_Hash::form(Company *hp,int const sz){
    void** vv; int i;

    vv=byName_Array::form(hp,sz,0); // 0 = fixed array
    if(!vv)return NULL;
    for(i=0; i<sz; i++,vv++){ *vv=NULL; }
    hp->ZZds.ZZbyName.count=0;
    return vv;
}

// -------------------------------------------
// Disconnect all the elements from the hash table,
// then free the table itself.
// -------------------------------------------
void byName_Hash::free(Company *hp){
    Employee *p; 
    byName_Iterator it;

    // disconnect all elements in the table
    for(p=it.first(hp,-1); p; p=it.next()){
        p->ZZds.ZZbyName.next=NULL;
    }
    byName_Array::free(hp);
}

// -------------------------------------------
// Disconnect all elements from the table, and link them
// into one gigantic linked list.
// Re-allocate the array without copying the content.
// Re-load all the elements from the list into the new table.
// Returns: 0=everything OK, 1=error
// -------------------------------------------
int byName_Hash::resize(Company *hp, int newSz){
    Employee *p,*head,*nxt;
    byName_Iterator it;

    // link all elements into one list with 'head'
    for(p=it.first(hp,-1), head=NULL; p; p=it.next()){
        p->ZZds.ZZbyName.next=head;
        head=p;
    }
    // 'head' is the beginning of the list now
 
    if(byName_Array::sizeChange(hp,newSz,1))return 1; // 0 for exact size
    hp->ZZds.ZZbyName.count=0; // start counting from 0 again

    // load the elements into the new table
    for(p=head, nxt=NULL; p; p=nxt){
        nxt=p->ZZds.ZZbyName.next;
        p->ZZds.ZZbyName.next=NULL;
        add(hp,p);
    }
    return 0;
}


// -------------------------------------------
// Search the table for an object which has the same key as 'obj'
// Return NULL when not finding it.
// -------------------------------------------
Employee* byName_Hash::get(Company *hp, Employee *obj){
    int i; Employee *p,*s;

    i=hash(obj,hp->ZZds.ZZbyName.sz);
    p=(Employee*)(hp->ZZds.ZZbyName.array[i]);
    if(p){
        for(s=p->ZZds.ZZbyName.next ; ; s=s->ZZds.ZZbyName.next){
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
int byName_Hash::add(Company *hp, Employee *obj){ // obj = object to load into the hash table
    int i; Employee *p;

    if(obj->ZZds.ZZbyName.next){
        printf("byName error: adding object which already is in a hash table\n");
        return 1;
    }
    i=hash(obj,hp->ZZds.ZZbyName.sz);
    p=(Employee*)(hp->ZZds.ZZbyName.array[i]);
    if(p){obj->ZZds.ZZbyName.next=p->ZZds.ZZbyName.next; p->ZZds.ZZbyName.next=obj;}
    else {obj->ZZds.ZZbyName.next=obj; hp->ZZds.ZZbyName.array[i]=obj;}
    (hp->ZZds.ZZbyName.count)++;
    return 0;
}

// -------------------------------------------
// Remove either obj or one object from the table which has the same key.
// Algorithm: Find the bucket and traverse the list.
// Returns the removed object, or NULL if not found.
// -------------------------------------------
Employee* byName_Hash::remove(Company *hp, Employee *obj){
    int i; Employee *p,*s,*prev;

    i=hash(obj,hp->ZZds.ZZbyName.sz);
    p=(Employee*)(hp->ZZds.ZZbyName.array[i]);
    if(p){
        for(s=p->ZZds.ZZbyName.next, prev=p; ; prev=s, s=s->ZZds.ZZbyName.next){
            if(!cmp(obj,s))break;
            if(s==p){s=NULL; break;}
        }
    }
    else s=NULL;

    if(!s){
        if(!obj) printf("Error byName: remove() called with obj=NULL\n");
        else if(obj->ZZds.ZZbyName.next==NULL)
           printf("Warning byName: remove() obj not in any hash table\n");
        else printf("Error byName: remove() obj not in bucket=%d\n",i);
        return NULL;
    }

    // remove 's' from the list, 'prev' is the previous object in the list
    if(s==prev)   hp->ZZds.ZZbyName.array[i]=NULL;
    else if(s==p) hp->ZZds.ZZbyName.array[i]=s->ZZds.ZZbyName.next;

    prev->ZZds.ZZbyName.next=s->ZZds.ZZbyName.next;
    s->ZZds.ZZbyName.next=NULL;
    (hp->ZZds.ZZbyName.count)--;
    return s;
}

// -------------------------------------------------------------
// Return the head of the list in bucket i, return NULL if empty.
// -------------------------------------------------------------
Employee* byName_Hash::slot(Company *hp, int i){
    return (Employee*)(hp->ZZds.ZZbyName.array[i]);
}

// -----------------------------------------------------------------
int byName_Hash::size(Company *hp, int *popCount){ 
    *popCount=hp->ZZds.ZZbyName.count;
    return byName_Array::size(hp); 
}

// -------------------------------------------------------------
// Convert a string into a bucket index between 0 and (hashSz-1)
// Algorithm by Sedgewick
// -------------------------------------------------------------
int byName_Hash::hashString(char *s,int hashSz){
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
int byName_Hash::hashInt(int val,int hashSz){
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
Employee* byName_HashIterator::first(Company *hp,int i){
    Employee *p; int sz;

    holder=hp;
    sz=hp->ZZds.ZZbyName.sz;

    if(i<0){all=1; bucket=0;}
    else {
        if(i>=sz){
            printf("byName error calling first() bucket=%d max=%d\n",i,hp->ZZds.ZZbyName.sz-1);
            return NULL;
        }
        bucket=i;
        all=0;
    }

    for(; bucket<sz; bucket++){
        tail=(Employee*)(hp->ZZds.ZZbyName.array[bucket]); 
        if(!all || tail)break;
    }
    // tail is the first acceptable non-empty entry in the table
    if(!tail)return NULL;
    p=tail->ZZds.ZZbyName.next;
    if(p==tail){
        if(!all)nxt=NULL;
        else {     // reset 'nxt' from this tail to the next non-empty bucket
            nxt=tail;
            (void)next(); // does not matter what it returs
        }
    }
    else nxt=p->ZZds.ZZbyName.next;
    
    return p;
} 

Employee* const byName_HashIterator::next(){
    Employee *p; int sz;

    if(!nxt)return NULL;
    sz=holder->ZZds.ZZbyName.sz;
    p=nxt;
    if(nxt==tail){ // search for the next non-empty bucket
        if(!all)nxt=NULL; 
        else {
            for( tail=NULL, bucket++; bucket<sz; bucket++){
                tail=(Employee*)(holder->ZZds.ZZbyName.array[bucket]); 
                if(tail)break;
            }
            if(!tail)nxt=NULL;
            else     nxt=tail->ZZds.ZZbyName.next;
        }
    }
    else nxt=p->ZZds.ZZbyName.next;

    return p;
}

// -----------------------------------------------------------------
// Historical DOL iterator:  it.start(x); for(p= ++it; p; p= ++it){...}
// It traverses only one bucket, use a loop with a call to slot() in
// order to traverse the entire table.
// -----------------------------------------------------------------
Employee* const byName_HashIterator::operator++(){
    Employee *ret;

    if(tail){
        if(nxt){
            ret=nxt; 
            nxt=nxt->ZZds.ZZbyName.next;
            if(ret==tail)tail=NULL;
        }
        else {
            ret=tail->ZZds.ZZbyName.next;
            if(tail==ret)tail=NULL;
            else nxt=ret->ZZds.ZZbyName.next;
        }
        return ret;
    }
    return NULL;
}
