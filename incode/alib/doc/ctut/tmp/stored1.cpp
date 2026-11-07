// --------------------------------------------------------
class Warehouse;
class PartType;

PartType* const stored_LinkedList2::tail(Warehouse *p){return p->ZZds.ZZstored.tail;}

PartType* const stored_LinkedList2::head(Warehouse *p){
    if(!(p->ZZds.ZZstored.tail) || !(p->ZZds.ZZstored.tail->ZZds.ZZstored.next))return NULL;
    else return p->ZZds.ZZstored.tail->ZZds.ZZstored.next;
}

void stored_LinkedList2::addHead(Warehouse *p, PartType *c){
    p->ZZds.ZZstored.tail=stored_Ring2::addHead(p->ZZds.ZZstored.tail,c);
}

void stored_LinkedList2::addTail(Warehouse *p, PartType *c){
    p->ZZds.ZZstored.tail=stored_Ring2::addTail(p->ZZds.ZZstored.tail,c);
}

void stored_LinkedList2::append(Warehouse *p,PartType *c1, PartType *c2){
    p->ZZds.ZZstored.tail=stored_Ring2::append(p->ZZds.ZZstored.tail,c1,c2);
}

void stored_LinkedList2::insert(PartType *c1, PartType *c2){stored_Ring2::insert(c1,c2);}

void stored_LinkedList2::sort(ZZsortFun cmpFun, Warehouse *p){
    p->ZZds.ZZstored.tail=stored_Ring2::sort(cmpFun,p->ZZds.ZZstored.tail);
}

void stored_LinkedList2::remove(Warehouse *p, PartType *c){
    p->ZZds.ZZstored.tail=stored_Ring2::remove(p->ZZds.ZZstored.tail,c);
}

PartType* const stored_LinkedList2::next(Warehouse *p,PartType *c){ 
                               return stored_Ring2::next(p->ZZds.ZZstored.tail,c);}

PartType* const stored_LinkedList2::prev(Warehouse *p,PartType *c){ 
                               return stored_Ring2::prev(p->ZZds.ZZstored.tail,c);}

PartType* const stored_LinkedList2::fwd(PartType *c){ return stored_Ring2::fwd(c);}

PartType* const stored_LinkedList2::bwd(PartType *c){ return stored_Ring2::bwd(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void stored_LinkedList2::merge(PartType *s,PartType *t,Warehouse *p){
    PartType *pp,*tail; int merge;
 
    tail=p->ZZds.ZZstored.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZstored.next; pp; pp=pp->ZZds.ZZstored.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("stored error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZstored.next; pp; pp=pp->ZZds.ZZstored.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("stored error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    stored_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZstored.tail=NULL; else p->ZZds.ZZstored.tail=t;
}

PartType* stored_LinkedList2::child(Warehouse *p){
    PartType* t;
    t=p->ZZds.ZZstored.tail; if(t)return t->ZZds.ZZstored.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void stored_LinkedList2::setTail(Warehouse* p,PartType* c,int check){
    PartType *pp,*tail;

    tail=p->ZZds.ZZstored.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZstored.next; pp; pp=pp->ZZds.ZZstored.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("stored warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZstored.tail=c;
}

void stored_LinkedList2Iterator::start(const Warehouse *p){
    stored_Ring2Iterator::start(p->ZZds.ZZstored.tail);
}

PartType* stored_LinkedList2Iterator::fromHead(Warehouse *p){
    return stored_Ring2Iterator::fromHead(p->ZZds.ZZstored.tail); 
}

PartType* stored_LinkedList2Iterator::fromTail(Warehouse *p){
    return stored_Ring2Iterator::fromTail(p->ZZds.ZZstored.tail); 
}
