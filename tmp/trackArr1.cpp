
// ---------------------------------------------------------
Track** trackArr_LinkArray::form(Layout *hp,unsigned int const cap,int const incr){
    return (Track**)(trackArr_Array::form(hp,cap,incr));
}
// ---------------------------------------------------------
Track* trackArr_LinkArray::get(Layout *hp,const unsigned int k){
    return (Track*)(trackArr_Array::get(hp,k));
}
// ---------------------------------------------------------
void trackArr_LinkArray::set(Layout *hp,const unsigned int k,Track *a){
    trackArr_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void trackArr_LinkArray::insert(Layout *hp,const int k,Track *t){
    trackArr_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
Track** trackArr_LinkArray::ind(Layout *hp,int i){
    return (Track**)(trackArr_Array::ind(hp,i));
}
// ---------------------------------------------------------
void trackArr_LinkArray::addOrd(cmpType cmpF,Layout *hp,Track *op){
    trackArr_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void trackArr_LinkArray::push(Layout *hp,Track* e){
    trackArr_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
Track* trackArr_LinkArray::pop(Layout *hp){
    return (Track*)(*(trackArr_Array::pop(hp)));
}
// ---------------------------------------------------------
void trackArr_LinkArray::inHeap(cmpType cmpF,Layout *hp,Track *e,bck callback){
    trackArr_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int trackArr_LinkArray::outHeap(cmpType cmpF,Layout *hp,Track **e,bck callback){
    return trackArr_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
Track** trackArr_LinkArray::head(Layout *hp){
    return (Track**)(trackArr_Array::head(hp));
}
// ---------------------------------------------------------
void trackArr_LinkArray::delOrd(cmpType cmpF,Layout *hp,Track *obj){
    trackArr_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int trackArr_LinkArray::getOrd(cmpType cmpF,Layout *hp,Track *op,int *found){
    return trackArr_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void trackArr_LinkArray::sort(cmpType cmp,Layout *hp){ 
    trackArr_Array::sort(cmp,hp);
}
// ---------------------------------------------------------
void trackArr_LinkArray::sortSubset(cmpType cmp,Layout *hp,int i1,int i2){ 
    trackArr_Array::sortSubset(cmp,hp,i1,i2);
}
// ---------------------------------------------------------

void trackArr_LinkArray::setMaxCap(unsigned int maxCap){
    trackArr_Array::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int trackArr_LinkArray::formed(Layout *hp){
    return trackArr_Array::formed(hp);
}
// ---------------------------------------------------------
void trackArr_LinkArray::free(Layout *hp){
    trackArr_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int trackArr_LinkArray::capacity(Layout *hp){
    return trackArr_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int trackArr_LinkArray::size(Layout *hp){
    return trackArr_Array::size(hp);
}
// ---------------------------------------------------------
int trackArr_LinkArray::increment(Layout *hp){
    return trackArr_Array::increment(hp);
}
// ---------------------------------------------------------
void trackArr_LinkArray::remove(Layout *hp,const unsigned int k){
    trackArr_Array::remove(hp,k);
}
// ---------------------------------------------------------
int trackArr_LinkArray::reduce(Layout *hp){
    return trackArr_Array::reduce(hp);
}
// ---------------------------------------------------------
int trackArr_LinkArray::reduce(Layout *hp,const unsigned int newCap){
    return trackArr_Array::reduce(hp,newCap);
}
// ---------------------------------------------------------
int trackArr_LinkArray::grow(Layout *hp,const unsigned int newCap){
    return trackArr_Array::grow(hp,newCap);
}
// ---------------------------------------------------------
void trackArr_LinkArray::reset(Layout *hp,int newSz,int incr){
   trackArr_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void trackArr_LinkArray::addTail(Layout *hp,Track *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------
void trackArr_LinkArray::init(Layout *hp){
    int i,cap,incr; Track **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=head(hp);
    for(i=0; i<cap; i++) arr[i]=NULL;
    trackArr_Array::reset(hp,0,incr);
}
// ---------------------------------------------------------

