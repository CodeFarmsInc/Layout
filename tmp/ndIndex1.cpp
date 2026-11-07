
// ---------------------------------------------------------
Node** ndIndex_LinkArray::form(Layout *hp,unsigned int const cap,int const incr){
    return (Node**)(ndIndex_Array::form(hp,cap,incr));
}
// ---------------------------------------------------------
Node* ndIndex_LinkArray::get(Layout *hp,const unsigned int k){
    return (Node*)(ndIndex_Array::get(hp,k));
}
// ---------------------------------------------------------
void ndIndex_LinkArray::set(Layout *hp,const unsigned int k,Node *a){
    ndIndex_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::insert(Layout *hp,const int k,Node *t){
    ndIndex_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
Node** ndIndex_LinkArray::ind(Layout *hp,int i){
    return (Node**)(ndIndex_Array::ind(hp,i));
}
// ---------------------------------------------------------
void ndIndex_LinkArray::addOrd(cmpType cmpF,Layout *hp,Node *op){
    ndIndex_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void ndIndex_LinkArray::push(Layout *hp,Node* e){
    ndIndex_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
Node* ndIndex_LinkArray::pop(Layout *hp){
    return (Node*)(*(ndIndex_Array::pop(hp)));
}
// ---------------------------------------------------------
void ndIndex_LinkArray::inHeap(cmpType cmpF,Layout *hp,Node *e,bck callback){
    ndIndex_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int ndIndex_LinkArray::outHeap(cmpType cmpF,Layout *hp,Node **e,bck callback){
    return ndIndex_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
Node** ndIndex_LinkArray::head(Layout *hp){
    return (Node**)(ndIndex_Array::head(hp));
}
// ---------------------------------------------------------
void ndIndex_LinkArray::delOrd(cmpType cmpF,Layout *hp,Node *obj){
    ndIndex_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int ndIndex_LinkArray::getOrd(cmpType cmpF,Layout *hp,Node *op,int *found){
    return ndIndex_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::sort(cmpType cmp,Layout *hp){ 
    ndIndex_Array::sort(cmp,hp);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::sortSubset(cmpType cmp,Layout *hp,int i1,int i2){ 
    ndIndex_Array::sortSubset(cmp,hp,i1,i2);
}
// ---------------------------------------------------------

void ndIndex_LinkArray::setMaxCap(unsigned int maxCap){
    ndIndex_Array::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int ndIndex_LinkArray::formed(Layout *hp){
    return ndIndex_Array::formed(hp);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::free(Layout *hp){
    ndIndex_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int ndIndex_LinkArray::capacity(Layout *hp){
    return ndIndex_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int ndIndex_LinkArray::size(Layout *hp){
    return ndIndex_Array::size(hp);
}
// ---------------------------------------------------------
int ndIndex_LinkArray::increment(Layout *hp){
    return ndIndex_Array::increment(hp);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::remove(Layout *hp,const unsigned int k){
    ndIndex_Array::remove(hp,k);
}
// ---------------------------------------------------------
int ndIndex_LinkArray::reduce(Layout *hp){
    return ndIndex_Array::reduce(hp);
}
// ---------------------------------------------------------
int ndIndex_LinkArray::reduce(Layout *hp,const unsigned int newCap){
    return ndIndex_Array::reduce(hp,newCap);
}
// ---------------------------------------------------------
int ndIndex_LinkArray::grow(Layout *hp,const unsigned int newCap){
    return ndIndex_Array::grow(hp,newCap);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::reset(Layout *hp,int newSz,int incr){
   ndIndex_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::addTail(Layout *hp,Node *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------
void ndIndex_LinkArray::init(Layout *hp){
    int i,cap,incr; Node **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=head(hp);
    for(i=0; i<cap; i++) arr[i]=NULL;
    ndIndex_Array::reset(hp,0,incr);
}
// ---------------------------------------------------------

