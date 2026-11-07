
// ---------------------------------------------------------
Node** newLayerArr_LinkArray::form(Layout *hp,unsigned int const cap,int const incr){
    return (Node**)(newLayerArr_Array::form(hp,cap,incr));
}
// ---------------------------------------------------------
Node* newLayerArr_LinkArray::get(Layout *hp,const unsigned int k){
    return (Node*)(newLayerArr_Array::get(hp,k));
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::set(Layout *hp,const unsigned int k,Node *a){
    newLayerArr_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::insert(Layout *hp,const int k,Node *t){
    newLayerArr_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
Node** newLayerArr_LinkArray::ind(Layout *hp,int i){
    return (Node**)(newLayerArr_Array::ind(hp,i));
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::addOrd(cmpType cmpF,Layout *hp,Node *op){
    newLayerArr_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::push(Layout *hp,Node* e){
    newLayerArr_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
Node* newLayerArr_LinkArray::pop(Layout *hp){
    return (Node*)(*(newLayerArr_Array::pop(hp)));
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::inHeap(cmpType cmpF,Layout *hp,Node *e,bck callback){
    newLayerArr_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int newLayerArr_LinkArray::outHeap(cmpType cmpF,Layout *hp,Node **e,bck callback){
    return newLayerArr_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
Node** newLayerArr_LinkArray::head(Layout *hp){
    return (Node**)(newLayerArr_Array::head(hp));
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::delOrd(cmpType cmpF,Layout *hp,Node *obj){
    newLayerArr_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int newLayerArr_LinkArray::getOrd(cmpType cmpF,Layout *hp,Node *op,int *found){
    return newLayerArr_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::sort(cmpType cmp,Layout *hp){ 
    newLayerArr_Array::sort(cmp,hp);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::sortSubset(cmpType cmp,Layout *hp,int i1,int i2){ 
    newLayerArr_Array::sortSubset(cmp,hp,i1,i2);
}
// ---------------------------------------------------------

void newLayerArr_LinkArray::setMaxCap(unsigned int maxCap){
    newLayerArr_Array::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int newLayerArr_LinkArray::formed(Layout *hp){
    return newLayerArr_Array::formed(hp);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::free(Layout *hp){
    newLayerArr_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int newLayerArr_LinkArray::capacity(Layout *hp){
    return newLayerArr_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int newLayerArr_LinkArray::size(Layout *hp){
    return newLayerArr_Array::size(hp);
}
// ---------------------------------------------------------
int newLayerArr_LinkArray::increment(Layout *hp){
    return newLayerArr_Array::increment(hp);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::remove(Layout *hp,const unsigned int k){
    newLayerArr_Array::remove(hp,k);
}
// ---------------------------------------------------------
int newLayerArr_LinkArray::reduce(Layout *hp){
    return newLayerArr_Array::reduce(hp);
}
// ---------------------------------------------------------
int newLayerArr_LinkArray::reduce(Layout *hp,const unsigned int newCap){
    return newLayerArr_Array::reduce(hp,newCap);
}
// ---------------------------------------------------------
int newLayerArr_LinkArray::grow(Layout *hp,const unsigned int newCap){
    return newLayerArr_Array::grow(hp,newCap);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::reset(Layout *hp,int newSz,int incr){
   newLayerArr_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::addTail(Layout *hp,Node *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------
void newLayerArr_LinkArray::init(Layout *hp){
    int i,cap,incr; Node **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=head(hp);
    for(i=0; i<cap; i++) arr[i]=NULL;
    newLayerArr_Array::reset(hp,0,incr);
}
// ---------------------------------------------------------

