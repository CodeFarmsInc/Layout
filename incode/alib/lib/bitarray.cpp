int $$_BitArray::getBit($1 *hp,int i){
    if(i>hp->$0.maxIndex)hp->$0.maxIndex=i;
    return $$_Array::getBit(hp,i);
}
// -------------------------------------------
int $$_BitArray::setBit($1 *hp,int i,int val){
    if(i>hp->$0.maxIndex)hp->$0.maxIndex=i;
    return $$_Array::setBit(hp,i,val);
}
// -------------------------------------------
unsigned int $$_BitArray::size($1 *hp){
    return hp->$0.maxIndex + 1;
}
// -------------------------------------------
unsigned int $$_BitArray::capacity($1 *hp){
    return 8 * $$_Array::capacity(hp);
}
// -------------------------------------------
int $$_BitArray::increment($1 *hp){
    int i=$$_Array::increment(hp); if(i>0)i=8*i; 
    return i;
}
// -------------------------------------------    
char* $$_BitArray::form($1 *hp,unsigned int const cap,int const incr){
    int i=incr;
    if(i>0)i=(i+7)/8; 
    hp->$0.maxIndex= -1;
    return $$_Array::form(hp,(cap-1)/8+1,i);
}

