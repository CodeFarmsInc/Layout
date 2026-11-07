// --------------------------------------------------------
class Supplier;
class PartType;

PartType* const supply_LinkedList2::tail(Supplier *p){return p->ZZds.ZZsupply.tail;}

PartType* const supply_LinkedList2::head(Supplier *p){
    if(!(p->ZZds.ZZsupply.tail) || !(p->ZZds.ZZsupply.tail->ZZds.ZZsupply.next))return NULL;
    else return p->ZZds.ZZsupply.tail->ZZds.ZZsupply.next;
}

void supply_LinkedList2::addHead(Supplier *p, PartType *c){
    p->ZZds.ZZsupply.tail=supply_Ring2::addHead(p->ZZds.ZZsupply.tail,c);
}

void supply_LinkedList2::addTail(Supplier *p, PartType *c){
    p->ZZds.ZZsupply.tail=supply_Ring2::addTail(p->ZZds.ZZsupply.tail,c);
}

void supply_LinkedList2::append(Supplier *p,PartType *c1, PartType *c2){
    p->ZZds.ZZsupply.tail=supply_Ring2::append(p->ZZds.ZZsupply.tail,c1,c2);
}

void supply_LinkedList2::insert(PartType *c1, PartType *c2){supply_Ring2::insert(c1,c2);}

void supply_LinkedList2::sort(ZZsortFun cmpFun, Supplier *p){
    p->ZZds.ZZsupply.tail=supply_Ring2::sort(cmpFun,p->ZZds.ZZsupply.tail);
}

void supply_LinkedList2::remove(Supplier *p, PartType *c){
    p->ZZds.ZZsupply.tail=supply_Ring2::remove(p->ZZds.ZZsupply.tail,c);
}

PartType* const supply_LinkedList2::next(Supplier *p,PartType *c){ 
                               return supply_Ring2::next(p->ZZds.ZZsupply.tail,c);}

PartType* const supply_LinkedList2::prev(Supplier *p,PartType *c){ 
                               return supply_Ring2::prev(p->ZZds.ZZsupply.tail,c);}

PartType* const supply_LinkedList2::fwd(PartType *c){ return supply_Ring2::fwd(c);}

PartType* const supply_LinkedList2::bwd(PartType *c){ return supply_Ring2::bwd(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void supply_LinkedList2::merge(PartType *s,PartType *t,Supplier *p){
    PartType *pp,*tail; int merge;
 
    tail=p->ZZds.ZZsupply.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZsupply.next; pp; pp=pp->ZZds.ZZsupply.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("supply error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZsupply.next; pp; pp=pp->ZZds.ZZsupply.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("supply error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    supply_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZsupply.tail=NULL; else p->ZZds.ZZsupply.tail=t;
}

PartType* supply_LinkedList2::child(Supplier *p){
    PartType* t;
    t=p->ZZds.ZZsupply.tail; if(t)return t->ZZds.ZZsupply.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void supply_LinkedList2::setTail(Supplier* p,PartType* c,int check){
    PartType *pp,*tail;

    tail=p->ZZds.ZZsupply.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZsupply.next; pp; pp=pp->ZZds.ZZsupply.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("supply warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZsupply.tail=c;
}

void supply_LinkedList2Iterator::start(const Supplier *p){
    supply_Ring2Iterator::start(p->ZZds.ZZsupply.tail);
}

PartType* supply_LinkedList2Iterator::fromHead(Supplier *p){
    return supply_Ring2Iterator::fromHead(p->ZZds.ZZsupply.tail); 
}

PartType* supply_LinkedList2Iterator::fromTail(Supplier *p){
    return supply_Ring2Iterator::fromTail(p->ZZds.ZZsupply.tail); 
}
