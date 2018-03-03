int bitArr_BitArray::getBit(Root *hp,int i){
    if(i>hp->ZZds.ZZbitArr.maxIndex)hp->ZZds.ZZbitArr.maxIndex=i;
    return bitArr_Array::getBit(hp,i);
}
// -------------------------------------------
int bitArr_BitArray::setBit(Root *hp,int i,int val){
    if(i>hp->ZZds.ZZbitArr.maxIndex)hp->ZZds.ZZbitArr.maxIndex=i;
    return bitArr_Array::setBit(hp,i,val);
}
// -------------------------------------------
unsigned int bitArr_BitArray::size(Root *hp){
    return hp->ZZds.ZZbitArr.maxIndex + 1;
}
// -------------------------------------------
unsigned int bitArr_BitArray::capacity(Root *hp){
    return 8 * bitArr_Array::capacity(hp);
}
// -------------------------------------------
int bitArr_BitArray::increment(Root *hp){
    int i=bitArr_Array::increment(hp); if(i>0)i=8*i; 
    return i;
}
// -------------------------------------------    
char* bitArr_BitArray::form(Root *hp,unsigned int const cap,int const incr){
    int i=incr;
    if(i>0)i=(i+7)/8; 
    hp->ZZds.ZZbitArr.maxIndex= -1;
    return bitArr_Array::form(hp,(cap-1)/8+1,i);
}

