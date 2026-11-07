
// ---------------------------------------------------------
Node** floatingNodeArr_LinkArray::form(Layout *hp,unsigned int const sz,int const incr){
    return (Node**)(floatingNodeArr_Array::form(hp,sz,incr));
}
// ---------------------------------------------------------
Node* floatingNodeArr_LinkArray::get(Layout *hp,const unsigned int k){
    return (Node*)(floatingNodeArr_Array::get(hp,k));
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::set(Layout *hp,const unsigned int k,Node *a){
    floatingNodeArr_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::insert(Layout *hp,const int k,Node *t){
    floatingNodeArr_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
Node** floatingNodeArr_LinkArray::ind(Layout *hp,int i){
    return (Node**)(floatingNodeArr_Array::ind(hp,i));
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::addOrd(cmpType cmpF,Layout *hp,Node *op){
    floatingNodeArr_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::push(Layout *hp,Node* e){
    floatingNodeArr_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
Node* floatingNodeArr_LinkArray::pop(Layout *hp){
    return (Node*)(*(floatingNodeArr_Array::pop(hp)));
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::inHeap(cmpType cmpF,Layout *hp,Node *e,bck callback){
    floatingNodeArr_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int floatingNodeArr_LinkArray::outHeap(cmpType cmpF,Layout *hp,Node **e,bck callback){
    return floatingNodeArr_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
Node** floatingNodeArr_LinkArray::head(Layout *hp){
    return (Node**)(floatingNodeArr_Array::head(hp));
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::delOrd(cmpType cmpF,Layout *hp,Node *obj){
    floatingNodeArr_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int floatingNodeArr_LinkArray::getOrd(cmpType cmpF,Layout *hp,Node *op,int *found){
    return floatingNodeArr_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::sort(Layout *hp,cmpType cmp){ 
    floatingNodeArr_Array::sort(hp,cmp);
}
// ---------------------------------------------------------

void floatingNodeArr_LinkArray::setMaxSize(unsigned int maxSize){
    floatingNodeArr_Array::setMaxSize(maxSize);
}
// ---------------------------------------------------------
int floatingNodeArr_LinkArray::formed(Layout *hp){
    return floatingNodeArr_Array::formed(hp);
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::free(Layout *hp){
    floatingNodeArr_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int floatingNodeArr_LinkArray::capacity(Layout *hp){
    return floatingNodeArr_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int floatingNodeArr_LinkArray::size(Layout *hp){
    return floatingNodeArr_Array::size(hp);
}
// ---------------------------------------------------------
int floatingNodeArr_LinkArray::increment(Layout *hp){
    return floatingNodeArr_Array::increment(hp);
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::remove(Layout *hp,const unsigned int k){
    floatingNodeArr_Array::remove(hp,k);
}
// ---------------------------------------------------------
int floatingNodeArr_LinkArray::reduce(Layout *hp){
    return floatingNodeArr_Array::reduce(hp);
}
// ---------------------------------------------------------
int floatingNodeArr_LinkArray::reduce(Layout *hp,const unsigned int newSz){
    return floatingNodeArr_Array::reduce(hp,newSz);
}
// ---------------------------------------------------------
int floatingNodeArr_LinkArray::grow(Layout *hp,const unsigned int newSz){
    return floatingNodeArr_Array::grow(hp,newSz);
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::reset(Layout *hp,int newSz,int incr){
   floatingNodeArr_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void floatingNodeArr_LinkArray::addTail(Layout *hp,Node *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------

