
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::setMaxSize(unsigned int maxSize){
    floatingNodeArr_LinkArray::setMaxSize(maxSize);
}
// ---------------------------------------------------------
int floatingNodeArr_IndexedLinkArray::form(Layout *hp,unsigned int const sz,int const incr){
    if(floatingNodeArr_LinkArray::form(hp,sz,incr))return 1; else return 0;
}
// ---------------------------------------------------------
int floatingNodeArr_IndexedLinkArray::formed(Layout *hp){
    return floatingNodeArr_LinkArray::formed(hp);
}
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::free(Layout *hp){
    int i,sz; Node *e;

    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZfloatingNodeArr.index= -1; // mark as unused
    }
    floatingNodeArr_LinkArray::free(hp);
}
// ---------------------------------------------------------
unsigned int floatingNodeArr_IndexedLinkArray::capacity(Layout *hp){
    return floatingNodeArr_LinkArray::capacity(hp);
}
// ---------------------------------------------------------
int floatingNodeArr_IndexedLinkArray::increment(Layout *hp){
    return floatingNodeArr_LinkArray::increment(hp);
}
// ---------------------------------------------------------
Node* floatingNodeArr_IndexedLinkArray::get(Layout *hp,const unsigned int k){
    return floatingNodeArr_LinkArray::get(hp,k);
}
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::set(Layout *hp,const unsigned int k,Node *a){
    Node *p; 

    if(a->ZZds.ZZfloatingNodeArr.index != -1){
        printf("error in floatingNodeArr::set(), object already used index=%d\n",
                                            a->ZZds.ZZfloatingNodeArr.index);
        return;
    }
    floatingNodeArr_LinkArray::set(hp,k,a);
    a->ZZds.ZZfloatingNodeArr.index=k;
}
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::remove(Layout *hp,const unsigned int k){
    Node *e; int sz;
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZfloatingNodeArr.index= -1; // mark as unused
    }
    floatingNodeArr_LinkArray::remove(hp,k);
    sz=size(hp);
    if(k<sz){
        e=get(hp,k);
        if(e)e->ZZds.ZZfloatingNodeArr.index=k;
    }
}
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::insert(Layout *hp,const int k,Node *t){
    int i,sz; Node *e;

    if(t->ZZds.ZZfloatingNodeArr.index != -1){
        printf("error in floatingNodeArr::set(), object already used index=%d\n",
                                            t->ZZds.ZZfloatingNodeArr.index);
        return;
    }
    floatingNodeArr_LinkArray::insert(hp,k,t);
    sz=size(hp);
    for(i=k; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZfloatingNodeArr.index=i;
    }
} 
// ---------------------------------------------------------
int floatingNodeArr_IndexedLinkArray::reduce(Layout *hp){
    return floatingNodeArr_LinkArray::reduce(hp);
}
// ---------------------------------------------------------
int floatingNodeArr_IndexedLinkArray::reduce(Layout *hp,const unsigned int newSz){
    int i,sz; Node *e;
    sz=size(hp);
    for(i=newSz; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZfloatingNodeArr.index= -1;
    }
    return floatingNodeArr_LinkArray::reduce(hp,newSz);
}
// ---------------------------------------------------------
int floatingNodeArr_IndexedLinkArray::grow(Layout *hp,const unsigned int newSz){
    return floatingNodeArr_LinkArray::grow(hp,newSz);
}
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::sort(Layout *hp,cmpType cmp){
    int i,sz; Node *e;
    floatingNodeArr_LinkArray::sort(hp,cmp);
    sz=size(hp);
    for(i=0; i<sz; i++){
        e=get(hp,i);
        if(e)e->ZZds.ZZfloatingNodeArr.index=i;
    }
}
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::reset(Layout *hp,int newSz,int incr){
    floatingNodeArr_LinkArray::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void floatingNodeArr_IndexedLinkArray::addTail(Layout *hp,Node *a){

    if(a->ZZds.ZZfloatingNodeArr.index != -1){
        printf("error in floatingNodeArr::addTail(), object already used index=%d\n",
                                            a->ZZds.ZZfloatingNodeArr.index);
        return;
    }
    a->ZZds.ZZfloatingNodeArr.index=size(hp);
    floatingNodeArr_LinkArray::addTail(hp,a);
}
// ---------------------------------------------------------
int floatingNodeArr_IndexedLinkArray::getIndex(Node *e){ return e->ZZds.ZZfloatingNodeArr.index; }
// ---------------------------------------------------------
unsigned int floatingNodeArr_IndexedLinkArray::size(Layout *hp){
     return floatingNodeArr_LinkArray::size(hp);
}
// ---------------------------------------------------------
