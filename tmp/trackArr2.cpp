
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::setMaxCap(unsigned int maxCap){
    trackArr_LinkArray::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int trackArr_IndexedLinkArray::form(Layout *hp,unsigned int const cap,int const incr){
    if(trackArr_LinkArray::form(hp,cap,incr))return 1; else return 0;
}
// ---------------------------------------------------------
int trackArr_IndexedLinkArray::formed(Layout *hp){
    return trackArr_LinkArray::formed(hp);
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::free(Layout *hp){
    int i,sz; Track *e;

    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZtrackArr.index= -1; // mark as unused
    }
    trackArr_LinkArray::free(hp);
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::init(Layout *hp){
    int i,cap,incr,sz; Track **arr;

    cap=capacity(hp);
    incr=increment(hp);
    sz=size(hp);
    arr=trackArr_LinkArray::head(hp);

    for(i=0; i<cap; i++){
	if(i<sz){
            if(arr[i]==NULL)continue;
            arr[i]->ZZds.ZZtrackArr.index= -1;
	}
        arr[i]=NULL;
    }
    reset(hp,0,incr);
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::init(Track *e){
    if(e)e->ZZds.ZZtrackArr.index= -1;
}
// ---------------------------------------------------------
unsigned int trackArr_IndexedLinkArray::capacity(Layout *hp){
    return trackArr_LinkArray::capacity(hp);
}
// ---------------------------------------------------------
int trackArr_IndexedLinkArray::increment(Layout *hp){
    return trackArr_LinkArray::increment(hp);
}
// ---------------------------------------------------------
Track* trackArr_IndexedLinkArray::get(Layout *hp,const unsigned int k){
    return trackArr_LinkArray::get(hp,k);
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::set(Layout *hp,const unsigned int k,Track *a){
    Track *p; 

    if(a->ZZds.ZZtrackArr.index != -1){
        printf("error in trackArr::set(), object already used index=%d\n",
                                            a->ZZds.ZZtrackArr.index);
        return;
    }
    trackArr_LinkArray::set(hp,k,a);
    a->ZZds.ZZtrackArr.index=k;
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::remove(Layout *hp,const unsigned int k){
    Track *e; int sz;
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZtrackArr.index= -1; // mark as unused
    }
    trackArr_LinkArray::remove(hp,k);
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZtrackArr.index=k;
    }
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::insert(Layout *hp,const int k,Track *t){
    int i,sz; Track *e;

    if(t->ZZds.ZZtrackArr.index != -1){
        printf("error in trackArr::set(), object already used index=%d\n",
                                            t->ZZds.ZZtrackArr.index);
        return;
    }
    trackArr_LinkArray::insert(hp,k,t);
    sz=size(hp);
    for(i=k; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZtrackArr.index=i;
    }
} 
// ---------------------------------------------------------
int trackArr_IndexedLinkArray::reduce(Layout *hp){
    return trackArr_LinkArray::reduce(hp);
}
// ---------------------------------------------------------
int trackArr_IndexedLinkArray::reduce(Layout *hp,const unsigned int newCap){
    int i,sz; Track *e;
    sz=size(hp);
    for(i=newCap; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZtrackArr.index= -1;
    }
    return trackArr_LinkArray::reduce(hp,newCap);
}
// ---------------------------------------------------------
int trackArr_IndexedLinkArray::grow(Layout *hp,const unsigned int newCap){
    return trackArr_LinkArray::grow(hp,newCap);
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::sort(cmpType cmp,Layout *hp){
    int i,sz; Track *e;
    trackArr_LinkArray::sort(cmp,hp);
    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZtrackArr.index=i;
    }
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::sortSubset(cmpType cmp,Layout *hp,int i1,int i2){
    int i,sz; Track *e;
    trackArr_LinkArray::sortSubset(cmp,hp,i1,i2);
    sz=size(hp);
    for(i=i1; i<=i2; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZtrackArr.index=i;
    }
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::reset(Layout *hp,int newSz,int incr){
    trackArr_LinkArray::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void trackArr_IndexedLinkArray::addTail(Layout *hp,Track *a){

    if(a->ZZds.ZZtrackArr.index != -1){
        printf("error in trackArr::addTail(), object already used index=%d\n",
                                            a->ZZds.ZZtrackArr.index);
        return;
    }
    a->ZZds.ZZtrackArr.index=size(hp);
    trackArr_LinkArray::addTail(hp,a);
}
// ---------------------------------------------------------
int trackArr_IndexedLinkArray::getIndex(Track *e){
    return e->ZZds.ZZtrackArr.index; 
}
// ---------------------------------------------------------
unsigned int trackArr_IndexedLinkArray::size(Layout *hp){
     return trackArr_LinkArray::size(hp);
}
// ---------------------------------------------------------
