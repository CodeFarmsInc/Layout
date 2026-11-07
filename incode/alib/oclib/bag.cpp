
// ---------------------------------------------------------
$2* $$_Bag::get($1 *hp,int i){
    if(i<0)return NULL;
    if(hp->$0.objCount<=i)return NULL;
    return ($2*)(*($$_Array::ind(hp,i)));
}

// ---------------------------------------------------------
void $$_Bag::form($1 *hp,int initCap,int incr){
    if(!($$_Array::formed(hp))){
        $$_Array::form(hp,initCap,incr);
        hp->$0.objCount=0;
    }
}

// ---------------------------------------------------------
int $$_Bag::count($1 *hp){ return hp->$0.objCount;}

// ---------------------------------------------------------
// Discard and de-allocate the array attached to hp
// ---------------------------------------------------------
void $$_Bag::free($1 *hp){ 
    if($$_Array::formed(hp)) $$_Array::free(hp);
    hp->$0.objCount=0;
}

// ---------------------------------------------------------
// New reference is always added at the end. If the array
// has not been formed yet, do it with the default of 8 entries
// and possible increment 3x any time a larger array is needed.
// ---------------------------------------------------------
void $$_Bag::add($1 *hp, $2 *obj){
    if(!($$_Array::formed(hp))) $$_Array::form(hp,8,-3);
    $$_Array::set(hp,hp->$0.objCount,obj);
    (hp->$0.objCount)++;
}

// ---------------------------------------------------------
// Remove all references to obj from the bag.
// ---------------------------------------------------------
void $$_Bag::remove($1 *hp, $2 *obj){ 
    int i,k,sz; $2 *e;
    sz=hp->$0.objCount;
    for(i=k=0; i<sz; i++){
        e=get(hp,i);
        if(e!=obj){
            set(hp,k,e);
            k++;
        }
    }
    hp->$0.objCount=k;
}


// ---------------------------------------------------------
$2* $$_BagIterator::first($1 *hp){
    holder=hp;
    if($$_Bag::count(hp)>0){index=1; return ($2*)($$_Bag::get(hp,0));}
    else                  {hp=NULL; return NULL;}
}


// ---------------------------------------------------------
// Using the current objCount allows to 
// ---------------------------------------------------------
$2* const $$_BagIterator::next(){
    if(!holder)return NULL;
    if($$_Bag::count(holder)<=index){holder=NULL; return NULL;}
    index++;
    return ($2*)($$_Bag::get(holder,index-1));
}
