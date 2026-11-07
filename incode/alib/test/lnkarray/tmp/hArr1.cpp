
// ---------------------------------------------------------
Employee** hArr_LinkArray::form(Header *hp,unsigned int const cap,int const incr){
    return (Employee**)(hArr_Array::form(hp,cap,incr));
}
// ---------------------------------------------------------
Employee* hArr_LinkArray::get(Header *hp,const unsigned int k){
    return (Employee*)(hArr_Array::get(hp,k));
}
// ---------------------------------------------------------
void hArr_LinkArray::set(Header *hp,const unsigned int k,Employee *a){
    hArr_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void hArr_LinkArray::insert(Header *hp,const int k,Employee *t){
    hArr_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
Employee** hArr_LinkArray::ind(Header *hp,int i){
    return (Employee**)(hArr_Array::ind(hp,i));
}
// ---------------------------------------------------------
void hArr_LinkArray::addOrd(cmpType cmpF,Header *hp,Employee *op){
    hArr_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void hArr_LinkArray::push(Header *hp,Employee* e){
    hArr_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
Employee* hArr_LinkArray::pop(Header *hp){
    return (Employee*)(*(hArr_Array::pop(hp)));
}
// ---------------------------------------------------------
void hArr_LinkArray::inHeap(cmpType cmpF,Header *hp,Employee *e,bck callback){
    hArr_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int hArr_LinkArray::outHeap(cmpType cmpF,Header *hp,Employee **e,bck callback){
    return hArr_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
Employee** hArr_LinkArray::head(Header *hp){
    return (Employee**)(hArr_Array::head(hp));
}
// ---------------------------------------------------------
void hArr_LinkArray::delOrd(cmpType cmpF,Header *hp,Employee *obj){
    hArr_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int hArr_LinkArray::getOrd(cmpType cmpF,Header *hp,Employee *op,int *found){
    return hArr_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void hArr_LinkArray::sort(cmpType cmp,Header *hp){ 
    hArr_Array::sort(cmp,hp);
}
// ---------------------------------------------------------
void hArr_LinkArray::sortSubset(cmpType cmp,Header *hp,int i1,int i2){ 
    hArr_Array::sortSubset(cmp,hp,i1,i2);
}
// ---------------------------------------------------------

void hArr_LinkArray::setMaxCap(unsigned int maxCap){
    hArr_Array::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int hArr_LinkArray::formed(Header *hp){
    return hArr_Array::formed(hp);
}
// ---------------------------------------------------------
void hArr_LinkArray::free(Header *hp){
    hArr_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int hArr_LinkArray::capacity(Header *hp){
    return hArr_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int hArr_LinkArray::size(Header *hp){
    return hArr_Array::size(hp);
}
// ---------------------------------------------------------
int hArr_LinkArray::increment(Header *hp){
    return hArr_Array::increment(hp);
}
// ---------------------------------------------------------
void hArr_LinkArray::remove(Header *hp,const unsigned int k){
    hArr_Array::remove(hp,k);
}
// ---------------------------------------------------------
int hArr_LinkArray::reduce(Header *hp){
    return hArr_Array::reduce(hp);
}
// ---------------------------------------------------------
int hArr_LinkArray::reduce(Header *hp,const unsigned int newCap){
    return hArr_Array::reduce(hp,newCap);
}
// ---------------------------------------------------------
int hArr_LinkArray::grow(Header *hp,const unsigned int newCap){
    return hArr_Array::grow(hp,newCap);
}
// ---------------------------------------------------------
void hArr_LinkArray::reset(Header *hp,int newSz,int incr){
   hArr_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void hArr_LinkArray::addTail(Header *hp,Employee *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------
void hArr_LinkArray::init(Header *hp){
    int i,cap,incr; Employee **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=head(hp);
    for(i=0; i<cap; i++) arr[i]=NULL;
    hArr_Array::reset(hp,0,incr);
}
// ---------------------------------------------------------

