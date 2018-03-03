
// ---------------------------------------------------------
void $$_IndexedLinkArray::setMaxCap(unsigned int maxCap){
    $$_LinkArray::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int $$_IndexedLinkArray::form($1 *hp,unsigned int const cap,int const incr){
    if($$_LinkArray::form(hp,cap,incr))return 1; else return 0;
}
// ---------------------------------------------------------
int $$_IndexedLinkArray::formed($1 *hp){
    return $$_LinkArray::formed(hp);
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::free($1 *hp){
    int i,sz; $2 *e;

    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->$0.index= -1; // mark as unused
    }
    $$_LinkArray::free(hp);
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::init($1 *hp){
    int i,cap,incr,sz; $2 **arr;

    cap=capacity(hp);
    incr=increment(hp);
    sz=size(hp);
    arr=$$_LinkArray::head(hp);

    for(i=0; i<cap; i++){
	if(i<sz){
            if(arr[i]==NULL)continue;
            arr[i]->$0.index= -1;
	}
        arr[i]=NULL;
    }
    reset(hp,0,incr);
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::init($2 *e){
    if(e)e->$0.index= -1;
}
// ---------------------------------------------------------
unsigned int $$_IndexedLinkArray::capacity($1 *hp){
    return $$_LinkArray::capacity(hp);
}
// ---------------------------------------------------------
int $$_IndexedLinkArray::increment($1 *hp){
    return $$_LinkArray::increment(hp);
}
// ---------------------------------------------------------
$2* $$_IndexedLinkArray::get($1 *hp,const unsigned int k){
    return $$_LinkArray::get(hp,k);
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::set($1 *hp,const unsigned int k,$2 *a){
    $2 *p; 

    if(a->$0.index != -1){
        printf("error in $$::set(), object already used index=%d\n",
                                            a->$0.index);
        return;
    }
    $$_LinkArray::set(hp,k,a);
    a->$0.index=k;
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::remove($1 *hp,const unsigned int k){
    $2 *e; int sz;
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->$0.index= -1; // mark as unused
    }
    $$_LinkArray::remove(hp,k);
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->$0.index=k;
    }
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::insert($1 *hp,const int k,$2 *t){
    int i,sz; $2 *e;

    if(t->$0.index != -1){
        printf("error in $$::set(), object already used index=%d\n",
                                            t->$0.index);
        return;
    }
    $$_LinkArray::insert(hp,k,t);
    sz=size(hp);
    for(i=k; i<sz; i++){
        e=get(hp,i);
        if(e)e->$0.index=i;
    }
} 
// ---------------------------------------------------------
int $$_IndexedLinkArray::reduce($1 *hp){
    return $$_LinkArray::reduce(hp);
}
// ---------------------------------------------------------
int $$_IndexedLinkArray::reduce($1 *hp,const unsigned int newCap){
    int i,sz; $2 *e;
    sz=size(hp);
    for(i=newCap; i<sz; i++){
        e=get(hp,i);
        if(e)e->$0.index= -1;
    }
    return $$_LinkArray::reduce(hp,newCap);
}
// ---------------------------------------------------------
int $$_IndexedLinkArray::grow($1 *hp,const unsigned int newCap){
    return $$_LinkArray::grow(hp,newCap);
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::sort(cmpType cmp,$1 *hp){
    int i,sz; $2 *e;
    $$_LinkArray::sort(cmp,hp);
    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->$0.index=i;
    }
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::sortSubset(cmpType cmp,$1 *hp,int i1,int i2){
    int i,sz; $2 *e;
    $$_LinkArray::sortSubset(cmp,hp,i1,i2);
    sz=size(hp);
    for(i=i1; i<=i2; i++){
        e=get(hp,i);
        if(e)e->$0.index=i;
    }
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::reset($1 *hp,int newSz,int incr){
    $$_LinkArray::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void $$_IndexedLinkArray::addTail($1 *hp,$2 *a){

    if(a->$0.index != -1){
        printf("error in $$::addTail(), object already used index=%d\n",
                                            a->$0.index);
        return;
    }
    a->$a.index=size(hp);
    $$_LinkArray::addTail(hp,a);
}
// ---------------------------------------------------------
int $$_IndexedLinkArray::getIndex($2 *e){
    return e->$0.index; 
}
// ---------------------------------------------------------
unsigned int $$_IndexedLinkArray::size($1 *hp){
     return $$_LinkArray::size(hp);
}
// ---------------------------------------------------------
