
// ---------------------------------------------------------
void eArr_IndexedLinkArray::setMaxCap(unsigned int maxCap){
    eArr_LinkArray::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int eArr_IndexedLinkArray::form(Department *hp,unsigned int const cap,int const incr){
    if(eArr_LinkArray::form(hp,cap,incr))return 1; else return 0;
}
// ---------------------------------------------------------
int eArr_IndexedLinkArray::formed(Department *hp){
    return eArr_LinkArray::formed(hp);
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::free(Department *hp){
    int i,sz; Employee *e;

    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZeArr.index= -1; // mark as unused
    }
    eArr_LinkArray::free(hp);
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::init(Department *hp){
    int i,cap,incr; Employee **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=eArr_LinkArray::head(hp);
    for(i=0; i<cap; i++){
        if(arr[i]==NULL)continue;
        arr[i]->ZZds.ZZeArr.index= -1;
        arr[i]=NULL;
    }
    reset(hp,0,incr);
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::init(Employee *e){
    if(e)e->ZZds.ZZeArr.index= -1;
}
// ---------------------------------------------------------
unsigned int eArr_IndexedLinkArray::capacity(Department *hp){
    return eArr_LinkArray::capacity(hp);
}
// ---------------------------------------------------------
int eArr_IndexedLinkArray::increment(Department *hp){
    return eArr_LinkArray::increment(hp);
}
// ---------------------------------------------------------
Employee* eArr_IndexedLinkArray::get(Department *hp,const unsigned int k){
    return eArr_LinkArray::get(hp,k);
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::set(Department *hp,const unsigned int k,Employee *a){
    Employee *p; 

    if(a->ZZds.ZZeArr.index != -1){
        printf("error in eArr::set(), object already used index=%d\n",
                                            a->ZZds.ZZeArr.index);
        return;
    }
    eArr_LinkArray::set(hp,k,a);
    a->ZZds.ZZeArr.index=k;
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::remove(Department *hp,const unsigned int k){
    Employee *e; int sz;
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZeArr.index= -1; // mark as unused
    }
    eArr_LinkArray::remove(hp,k);
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZeArr.index=k;
    }
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::insert(Department *hp,const int k,Employee *t){
    int i,sz; Employee *e;

    if(t->ZZds.ZZeArr.index != -1){
        printf("error in eArr::set(), object already used index=%d\n",
                                            t->ZZds.ZZeArr.index);
        return;
    }
    eArr_LinkArray::insert(hp,k,t);
    sz=size(hp);
    for(i=k; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZeArr.index=i;
    }
} 
// ---------------------------------------------------------
int eArr_IndexedLinkArray::reduce(Department *hp){
    return eArr_LinkArray::reduce(hp);
}
// ---------------------------------------------------------
int eArr_IndexedLinkArray::reduce(Department *hp,const unsigned int newCap){
    int i,sz; Employee *e;
    sz=size(hp);
    for(i=newCap; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZeArr.index= -1;
    }
    return eArr_LinkArray::reduce(hp,newCap);
}
// ---------------------------------------------------------
int eArr_IndexedLinkArray::grow(Department *hp,const unsigned int newCap){
    return eArr_LinkArray::grow(hp,newCap);
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::sort(cmpType cmp,Department *hp){
    int i,sz; Employee *e;
    eArr_LinkArray::sort(cmp,hp);
    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZeArr.index=i;
    }
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::sortSubset(cmpType cmp,Department *hp,int i1,int i2){
    int i,sz; Employee *e;
    eArr_LinkArray::sortSubset(cmp,hp,i1,i2);
    sz=size(hp);
    for(i=i1; i<=i2; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZeArr.index=i;
    }
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::reset(Department *hp,int newSz,int incr){
    eArr_LinkArray::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void eArr_IndexedLinkArray::addTail(Department *hp,Employee *a){

    if(a->ZZds.ZZeArr.index != -1){
        printf("error in eArr::addTail(), object already used index=%d\n",
                                            a->ZZds.ZZeArr.index);
        return;
    }
    a->ZZds.ZZeArr.index=size(hp);
    eArr_LinkArray::addTail(hp,a);
}
// ---------------------------------------------------------
int eArr_IndexedLinkArray::getIndex(Employee *e){
    return e->ZZds.ZZeArr.index; 
}
// ---------------------------------------------------------
unsigned int eArr_IndexedLinkArray::size(Department *hp){
     return eArr_LinkArray::size(hp);
}
// ---------------------------------------------------------
