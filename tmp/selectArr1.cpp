
// ---------------------------------------------------------
Edge** selectArr_LinkArray::form(Layout *hp,unsigned int const cap,int const incr){
    return (Edge**)(selectArr_Array::form(hp,cap,incr));
}
// ---------------------------------------------------------
Edge* selectArr_LinkArray::get(Layout *hp,const unsigned int k){
    return (Edge*)(selectArr_Array::get(hp,k));
}
// ---------------------------------------------------------
void selectArr_LinkArray::set(Layout *hp,const unsigned int k,Edge *a){
    selectArr_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void selectArr_LinkArray::insert(Layout *hp,const int k,Edge *t){
    selectArr_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
Edge** selectArr_LinkArray::ind(Layout *hp,int i){
    return (Edge**)(selectArr_Array::ind(hp,i));
}
// ---------------------------------------------------------
void selectArr_LinkArray::addOrd(cmpType cmpF,Layout *hp,Edge *op){
    selectArr_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void selectArr_LinkArray::push(Layout *hp,Edge* e){
    selectArr_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
Edge* selectArr_LinkArray::pop(Layout *hp){
    return (Edge*)(*(selectArr_Array::pop(hp)));
}
// ---------------------------------------------------------
void selectArr_LinkArray::inHeap(cmpType cmpF,Layout *hp,Edge *e,bck callback){
    selectArr_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int selectArr_LinkArray::outHeap(cmpType cmpF,Layout *hp,Edge **e,bck callback){
    return selectArr_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
Edge** selectArr_LinkArray::head(Layout *hp){
    return (Edge**)(selectArr_Array::head(hp));
}
// ---------------------------------------------------------
void selectArr_LinkArray::delOrd(cmpType cmpF,Layout *hp,Edge *obj){
    selectArr_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int selectArr_LinkArray::getOrd(cmpType cmpF,Layout *hp,Edge *op,int *found){
    return selectArr_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void selectArr_LinkArray::sort(cmpType cmp,Layout *hp){ 
    selectArr_Array::sort(cmp,hp);
}
// ---------------------------------------------------------
void selectArr_LinkArray::sortSubset(cmpType cmp,Layout *hp,int i1,int i2){ 
    selectArr_Array::sortSubset(cmp,hp,i1,i2);
}
// ---------------------------------------------------------

void selectArr_LinkArray::setMaxCap(unsigned int maxCap){
    selectArr_Array::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int selectArr_LinkArray::formed(Layout *hp){
    return selectArr_Array::formed(hp);
}
// ---------------------------------------------------------
void selectArr_LinkArray::free(Layout *hp){
    selectArr_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int selectArr_LinkArray::capacity(Layout *hp){
    return selectArr_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int selectArr_LinkArray::size(Layout *hp){
    return selectArr_Array::size(hp);
}
// ---------------------------------------------------------
int selectArr_LinkArray::increment(Layout *hp){
    return selectArr_Array::increment(hp);
}
// ---------------------------------------------------------
void selectArr_LinkArray::remove(Layout *hp,const unsigned int k){
    selectArr_Array::remove(hp,k);
}
// ---------------------------------------------------------
int selectArr_LinkArray::reduce(Layout *hp){
    return selectArr_Array::reduce(hp);
}
// ---------------------------------------------------------
int selectArr_LinkArray::reduce(Layout *hp,const unsigned int newCap){
    return selectArr_Array::reduce(hp,newCap);
}
// ---------------------------------------------------------
int selectArr_LinkArray::grow(Layout *hp,const unsigned int newCap){
    return selectArr_Array::grow(hp,newCap);
}
// ---------------------------------------------------------
void selectArr_LinkArray::reset(Layout *hp,int newSz,int incr){
   selectArr_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void selectArr_LinkArray::addTail(Layout *hp,Edge *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------
void selectArr_LinkArray::init(Layout *hp){
    int i,cap,incr; Edge **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=head(hp);
    for(i=0; i<cap; i++) arr[i]=NULL;
    selectArr_Array::reset(hp,0,incr);
}
// ---------------------------------------------------------

