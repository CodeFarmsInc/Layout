
// ---------------------------------------------------------
Employee** eArr_LinkArray::form(Department *hp,unsigned int const cap,int const incr){
    return (Employee**)(eArr_Array::form(hp,cap,incr));
}
// ---------------------------------------------------------
Employee* eArr_LinkArray::get(Department *hp,const unsigned int k){
    return (Employee*)(eArr_Array::get(hp,k));
}
// ---------------------------------------------------------
void eArr_LinkArray::set(Department *hp,const unsigned int k,Employee *a){
    eArr_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void eArr_LinkArray::insert(Department *hp,const int k,Employee *t){
    eArr_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
Employee** eArr_LinkArray::ind(Department *hp,int i){
    return (Employee**)(eArr_Array::ind(hp,i));
}
// ---------------------------------------------------------
void eArr_LinkArray::addOrd(cmpType cmpF,Department *hp,Employee *op){
    eArr_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void eArr_LinkArray::push(Department *hp,Employee* e){
    eArr_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
Employee* eArr_LinkArray::pop(Department *hp){
    return (Employee*)(*(eArr_Array::pop(hp)));
}
// ---------------------------------------------------------
void eArr_LinkArray::inHeap(cmpType cmpF,Department *hp,Employee *e,bck callback){
    eArr_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int eArr_LinkArray::outHeap(cmpType cmpF,Department *hp,Employee **e,bck callback){
    return eArr_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
Employee** eArr_LinkArray::head(Department *hp){
    return (Employee**)(eArr_Array::head(hp));
}
// ---------------------------------------------------------
void eArr_LinkArray::delOrd(cmpType cmpF,Department *hp,Employee *obj){
    eArr_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int eArr_LinkArray::getOrd(cmpType cmpF,Department *hp,Employee *op,int *found){
    return eArr_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void eArr_LinkArray::sort(cmpType cmp,Department *hp){ 
    eArr_Array::sort(cmp,hp);
}
// ---------------------------------------------------------
void eArr_LinkArray::sortSubset(cmpType cmp,Department *hp,int i1,int i2){ 
    eArr_Array::sortSubset(cmp,hp,i1,i2);
}
// ---------------------------------------------------------

void eArr_LinkArray::setMaxCap(unsigned int maxCap){
    eArr_Array::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int eArr_LinkArray::formed(Department *hp){
    return eArr_Array::formed(hp);
}
// ---------------------------------------------------------
void eArr_LinkArray::free(Department *hp){
    eArr_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int eArr_LinkArray::capacity(Department *hp){
    return eArr_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int eArr_LinkArray::size(Department *hp){
    return eArr_Array::size(hp);
}
// ---------------------------------------------------------
int eArr_LinkArray::increment(Department *hp){
    return eArr_Array::increment(hp);
}
// ---------------------------------------------------------
void eArr_LinkArray::remove(Department *hp,const unsigned int k){
    eArr_Array::remove(hp,k);
}
// ---------------------------------------------------------
int eArr_LinkArray::reduce(Department *hp){
    return eArr_Array::reduce(hp);
}
// ---------------------------------------------------------
int eArr_LinkArray::reduce(Department *hp,const unsigned int newCap){
    return eArr_Array::reduce(hp,newCap);
}
// ---------------------------------------------------------
int eArr_LinkArray::grow(Department *hp,const unsigned int newCap){
    return eArr_Array::grow(hp,newCap);
}
// ---------------------------------------------------------
void eArr_LinkArray::reset(Department *hp,int newSz,int incr){
   eArr_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void eArr_LinkArray::addTail(Department *hp,Employee *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------
void eArr_LinkArray::init(Department *hp){
    int i,cap,incr; Employee **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=head(hp);
    for(i=0; i<cap; i++) arr[i]=NULL;
    eArr_Array::reset(hp,0,incr);
}
// ---------------------------------------------------------

