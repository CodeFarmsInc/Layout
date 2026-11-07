
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::setMaxCap(unsigned int maxCap){
    ndIndex_LinkArray::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int ndIndex_IndexedLinkArray::form(Layout *hp,unsigned int const cap,int const incr){
    if(ndIndex_LinkArray::form(hp,cap,incr))return 1; else return 0;
}
// ---------------------------------------------------------
int ndIndex_IndexedLinkArray::formed(Layout *hp){
    return ndIndex_LinkArray::formed(hp);
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::free(Layout *hp){
    int i,sz; Node *e;

    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZndIndex.index= -1; // mark as unused
    }
    ndIndex_LinkArray::free(hp);
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::init(Layout *hp){
    int i,cap,incr,sz; Node **arr;

    cap=capacity(hp);
    incr=increment(hp);
    sz=size(hp);
    arr=ndIndex_LinkArray::head(hp);

    for(i=0; i<cap; i++){
	if(i<sz){
            if(arr[i]==NULL)continue;
            arr[i]->ZZds.ZZndIndex.index= -1;
	}
        arr[i]=NULL;
    }
    reset(hp,0,incr);
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::init(Node *e){
    if(e)e->ZZds.ZZndIndex.index= -1;
}
// ---------------------------------------------------------
unsigned int ndIndex_IndexedLinkArray::capacity(Layout *hp){
    return ndIndex_LinkArray::capacity(hp);
}
// ---------------------------------------------------------
int ndIndex_IndexedLinkArray::increment(Layout *hp){
    return ndIndex_LinkArray::increment(hp);
}
// ---------------------------------------------------------
Node* ndIndex_IndexedLinkArray::get(Layout *hp,const unsigned int k){
    return ndIndex_LinkArray::get(hp,k);
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::set(Layout *hp,const unsigned int k,Node *a){
    Node *p; 

    if(a->ZZds.ZZndIndex.index != -1){
        printf("error in ndIndex::set(), object already used index=%d\n",
                                            a->ZZds.ZZndIndex.index);
        return;
    }
    ndIndex_LinkArray::set(hp,k,a);
    a->ZZds.ZZndIndex.index=k;
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::remove(Layout *hp,const unsigned int k){
    Node *e; int sz;
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZndIndex.index= -1; // mark as unused
    }
    ndIndex_LinkArray::remove(hp,k);
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZndIndex.index=k;
    }
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::insert(Layout *hp,const int k,Node *t){
    int i,sz; Node *e;

    if(t->ZZds.ZZndIndex.index != -1){
        printf("error in ndIndex::set(), object already used index=%d\n",
                                            t->ZZds.ZZndIndex.index);
        return;
    }
    ndIndex_LinkArray::insert(hp,k,t);
    sz=size(hp);
    for(i=k; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZndIndex.index=i;
    }
} 
// ---------------------------------------------------------
int ndIndex_IndexedLinkArray::reduce(Layout *hp){
    return ndIndex_LinkArray::reduce(hp);
}
// ---------------------------------------------------------
int ndIndex_IndexedLinkArray::reduce(Layout *hp,const unsigned int newCap){
    int i,sz; Node *e;
    sz=size(hp);
    for(i=newCap; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZndIndex.index= -1;
    }
    return ndIndex_LinkArray::reduce(hp,newCap);
}
// ---------------------------------------------------------
int ndIndex_IndexedLinkArray::grow(Layout *hp,const unsigned int newCap){
    return ndIndex_LinkArray::grow(hp,newCap);
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::sort(cmpType cmp,Layout *hp){
    int i,sz; Node *e;
    ndIndex_LinkArray::sort(cmp,hp);
    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZndIndex.index=i;
    }
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::sortSubset(cmpType cmp,Layout *hp,int i1,int i2){
    int i,sz; Node *e;
    ndIndex_LinkArray::sortSubset(cmp,hp,i1,i2);
    sz=size(hp);
    for(i=i1; i<=i2; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZndIndex.index=i;
    }
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::reset(Layout *hp,int newSz,int incr){
    ndIndex_LinkArray::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void ndIndex_IndexedLinkArray::addTail(Layout *hp,Node *a){

    if(a->ZZds.ZZndIndex.index != -1){
        printf("error in ndIndex::addTail(), object already used index=%d\n",
                                            a->ZZds.ZZndIndex.index);
        return;
    }
    a->ZZds.ZZndIndex.index=size(hp);
    ndIndex_LinkArray::addTail(hp,a);
}
// ---------------------------------------------------------
int ndIndex_IndexedLinkArray::getIndex(Node *e){
    return e->ZZds.ZZndIndex.index; 
}
// ---------------------------------------------------------
unsigned int ndIndex_IndexedLinkArray::size(Layout *hp){
     return ndIndex_LinkArray::size(hp);
}
// ---------------------------------------------------------
