
// ---------------------------------------------------------
$2** $$_LinkArray::form($1 *hp,unsigned int const cap,int const incr){
    return ($2**)($$_Array::form(hp,cap,incr));
}
// ---------------------------------------------------------
$2* $$_LinkArray::get($1 *hp,const unsigned int k){
    return ($2*)($$_Array::get(hp,k));
}
// ---------------------------------------------------------
void $$_LinkArray::set($1 *hp,const unsigned int k,$2 *a){
    $$_Array::set(hp,k,(void*)a);
}
// ---------------------------------------------------------
void $$_LinkArray::insert($1 *hp,const int k,$2 *t){
    $$_Array::insert(hp,k,(void**)(&t));
} 
// ---------------------------------------------------------
$2** $$_LinkArray::ind($1 *hp,int i){
    return ($2**)($$_Array::ind(hp,i));
}
// ---------------------------------------------------------
void $$_LinkArray::addOrd(cmpType cmpF,$1 *hp,$2 *op){
    $$_Array::addOrd(cmpF,hp,(void**)(&op));
}
// ---------------------------------------------------------
void $$_LinkArray::push($1 *hp,$2* e){
    $$_Array::push(hp,(void**)(&e));
}
// ---------------------------------------------------------
$2* $$_LinkArray::pop($1 *hp){
    return ($2*)(*($$_Array::pop(hp)));
}
// ---------------------------------------------------------
void $$_LinkArray::inHeap(cmpType cmpF,$1 *hp,$2 *e,bck callback){
    $$_Array::inHeap(cmpF,hp,(void**)(&e),callback);
}
// ---------------------------------------------------------
int $$_LinkArray::outHeap(cmpType cmpF,$1 *hp,$2 **e,bck callback){
    return $$_Array::outHeap(cmpF,hp,(void**)e,callback);
}
// ---------------------------------------------------------
$2** $$_LinkArray::head($1 *hp){
    return ($2**)($$_Array::head(hp));
}
// ---------------------------------------------------------
void $$_LinkArray::delOrd(cmpType cmpF,$1 *hp,$2 *obj){
    $$_Array::delOrd(cmpF,hp,(void**)(&obj));
}
// ---------------------------------------------------------
int $$_LinkArray::getOrd(cmpType cmpF,$1 *hp,$2 *op,int *found){
    return $$_Array::getOrd(cmpF,hp,(void**)(&op),found);
}
// ---------------------------------------------------------
void $$_LinkArray::sort(cmpType cmp,$1 *hp){ 
    $$_Array::sort(cmp,hp);
}
// ---------------------------------------------------------
void $$_LinkArray::sortSubset(cmpType cmp,$1 *hp,int i1,int i2){ 
    $$_Array::sortSubset(cmp,hp,i1,i2);
}
// ---------------------------------------------------------

void $$_LinkArray::setMaxCap(unsigned int maxCap){
    $$_Array::setMaxCap(maxCap);
}
// ---------------------------------------------------------
int $$_LinkArray::formed($1 *hp){
    return $$_Array::formed(hp);
}
// ---------------------------------------------------------
void $$_LinkArray::free($1 *hp){
    $$_Array::free(hp);
}
// ---------------------------------------------------------
unsigned int $$_LinkArray::capacity($1 *hp){
    return $$_Array::capacity(hp);
}
// ---------------------------------------------------------
unsigned int $$_LinkArray::size($1 *hp){
    return $$_Array::size(hp);
}
// ---------------------------------------------------------
int $$_LinkArray::increment($1 *hp){
    return $$_Array::increment(hp);
}
// ---------------------------------------------------------
void $$_LinkArray::remove($1 *hp,const unsigned int k){
    $$_Array::remove(hp,k);
}
// ---------------------------------------------------------
int $$_LinkArray::reduce($1 *hp){
    return $$_Array::reduce(hp);
}
// ---------------------------------------------------------
int $$_LinkArray::reduce($1 *hp,const unsigned int newCap){
    return $$_Array::reduce(hp,newCap);
}
// ---------------------------------------------------------
int $$_LinkArray::grow($1 *hp,const unsigned int newCap){
    return $$_Array::grow(hp,newCap);
}
// ---------------------------------------------------------
void $$_LinkArray::reset($1 *hp,int newSz,int incr){
   $$_Array::reset(hp,newSz,incr);
}
// ---------------------------------------------------------
void $$_LinkArray::addTail($1 *hp,$2 *a){
    set(hp,size(hp),a);
}
// ---------------------------------------------------------
void $$_LinkArray::init($1 *hp){
    int i,cap,incr; $2 **arr;

    cap=capacity(hp);
    incr=increment(hp);
    arr=head(hp);
    for(i=0; i<cap; i++) arr[i]=NULL;
    $$_Array::reset(hp,0,incr);
}
// ---------------------------------------------------------

