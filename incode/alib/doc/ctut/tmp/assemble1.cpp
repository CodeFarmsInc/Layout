
// ---------------------------------------------------------
PartType* assemble_Bag::get(Assembly *hp,int i){
    if(i<0)return NULL;
    if(hp->ZZds.ZZassemble.objCount<=i)return NULL;
    return (PartType*)(*(assemble_Array::ind(hp,i)));
}

// ---------------------------------------------------------
void assemble_Bag::form(Assembly *hp,int initCap,int incr){
    if(!(assemble_Array::formed(hp))){
        assemble_Array::form(hp,initCap,incr);
        hp->ZZds.ZZassemble.objCount=0;
    }
}

// ---------------------------------------------------------
int assemble_Bag::count(Assembly *hp){ return hp->ZZds.ZZassemble.objCount;}

// ---------------------------------------------------------
// Discard and de-allocate the array attached to hp
// ---------------------------------------------------------
void assemble_Bag::free(Assembly *hp){ 
    if(assemble_Array::formed(hp)) assemble_Array::free(hp);
    hp->ZZds.ZZassemble.objCount=0;
}

// ---------------------------------------------------------
// New reference is always added at the end. If the array
// has not been formed yet, do it with the default of 8 entries
// and possible increment 3x any time a larger array is needed.
// ---------------------------------------------------------
void assemble_Bag::add(Assembly *hp, PartType *obj){
    if(!(assemble_Array::formed(hp))) assemble_Array::form(hp,8,-3);
    assemble_Array::set(hp,hp->ZZds.ZZassemble.objCount,obj);
    (hp->ZZds.ZZassemble.objCount)++;
}

// ---------------------------------------------------------
// Remove all references to obj from the bag.
// ---------------------------------------------------------
void assemble_Bag::remove(Assembly *hp, PartType *obj){ 
    int i,k,sz; PartType *e;
    sz=hp->ZZds.ZZassemble.objCount;
    for(i=k=0; i<sz; i++){
        e=get(hp,i);
        if(e!=obj){
            set(hp,k,e);
            k++;
        }
    }
    hp->ZZds.ZZassemble.objCount=k;
}


// ---------------------------------------------------------
PartType* assemble_BagIterator::first(Assembly *hp){
    holder=hp;
    if(assemble_Bag::count(hp)>0){index=1; return (PartType*)(assemble_Bag::get(hp,0));}
    else                  {hp=NULL; return NULL;}
}


// ---------------------------------------------------------
// Using the current objCount allows to 
// ---------------------------------------------------------
PartType* const assemble_BagIterator::next(){
    if(!holder)return NULL;
    if(assemble_Bag::count(holder)<=index){holder=NULL; return NULL;}
    index++;
    return (PartType*)(assemble_Bag::get(holder,index-1));
}
