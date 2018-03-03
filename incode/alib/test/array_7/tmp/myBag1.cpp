
// ---------------------------------------------------------
Part* myBag_Bag::get(Root *hp,int i){
    if(i<0)return NULL;
    if(hp->ZZds.ZZmyBag.objCount<=i)return NULL;
    return (Part*)(*(myBag_Array::ind(hp,i)));
}

// ---------------------------------------------------------
void myBag_Bag::form(Root *hp,int initCap,int incr){
    if(!(myBag_Array::formed(hp))){
        myBag_Array::form(hp,initCap,incr);
        hp->ZZds.ZZmyBag.objCount=0;
    }
}

// ---------------------------------------------------------
int myBag_Bag::count(Root *hp){ return hp->ZZds.ZZmyBag.objCount;}

// ---------------------------------------------------------
// Discard and de-allocate the array attached to hp
// ---------------------------------------------------------
void myBag_Bag::free(Root *hp){ 
    if(myBag_Array::formed(hp)) myBag_Array::free(hp);
    hp->ZZds.ZZmyBag.objCount=0;
}

// ---------------------------------------------------------
// New reference is always added at the end. If the array
// has not been formed yet, do it with the default of 8 entries
// and possible increment 3x any time a larger array is needed.
// ---------------------------------------------------------
void myBag_Bag::add(Root *hp, Part *obj){
    if(!(myBag_Array::formed(hp))) myBag_Array::form(hp,8,-3);
    myBag_Array::set(hp,hp->ZZds.ZZmyBag.objCount,obj);
    (hp->ZZds.ZZmyBag.objCount)++;
}

// ---------------------------------------------------------
// Remove all references to obj from the bag.
// ---------------------------------------------------------
void myBag_Bag::remove(Root *hp, Part *obj){ 
    int i,k,sz; Part *e;
    sz=hp->ZZds.ZZmyBag.objCount;
    for(i=k=0; i<sz; i++){
        e=get(hp,i);
        if(e!=obj){
            set(hp,k,e);
            k++;
        }
    }
    hp->ZZds.ZZmyBag.objCount=k;
}


// ---------------------------------------------------------
Part* myBag_BagIterator::first(Root *hp){
    holder=hp;
    if(myBag_Bag::count(hp)>0){index=1; return (Part*)(myBag_Bag::get(hp,0));}
    else                  {hp=NULL; return NULL;}
}


// ---------------------------------------------------------
// Using the current objCount allows to 
// ---------------------------------------------------------
Part* const myBag_BagIterator::next(){
    if(!holder)return NULL;
    if(myBag_Bag::count(holder)<=index){holder=NULL; return NULL;}
    index++;
    return (Part*)(myBag_Bag::get(holder,index-1));
}
