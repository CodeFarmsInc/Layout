// --------------------------------------------------------
class OrgType;
class Iterator;

Iterator* iters_LinkedList1::tail(OrgType *p){return p->ZZds.ZZiters.tail;}

Iterator* iters_LinkedList1::head(OrgType *p){
    if(!(p->ZZds.ZZiters.tail) || !(p->ZZds.ZZiters.tail->ZZds.ZZiters.next))return NULL;
    else return p->ZZds.ZZiters.tail->ZZds.ZZiters.next;
}

void iters_LinkedList1::addHead(OrgType *p, Iterator *c){
    p->ZZds.ZZiters.tail=iters_Ring1::addHead(p->ZZds.ZZiters.tail,c);
}

void iters_LinkedList1::addTail(OrgType *p, Iterator *c){
    p->ZZds.ZZiters.tail=iters_Ring1::addTail(p->ZZds.ZZiters.tail,c);
}

void iters_LinkedList1::append(OrgType *p,Iterator *c1, Iterator *c2){
    p->ZZds.ZZiters.tail=iters_Ring1::append(p->ZZds.ZZiters.tail,c1,c2);
}

void iters_LinkedList1::remove(OrgType *p, Iterator *c){
    p->ZZds.ZZiters.tail=iters_Ring1::remove(p->ZZds.ZZiters.tail,c);
}

Iterator* const iters_LinkedList1::next(OrgType *p,Iterator *c){
    return iters_Ring1::next(p->ZZds.ZZiters.tail,c);
}

Iterator* const iters_LinkedList1::nextRing(Iterator *c){ return iters_Ring1::nextRing(c);}

void iters_LinkedList1::sort(ZZsortFun cmpFun, OrgType *p){
    p->ZZds.ZZiters.tail=iters_Ring1::sort(cmpFun,p->ZZds.ZZiters.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void iters_LinkedList1::merge(Iterator *s,Iterator *t,OrgType *p){
    Iterator *pp,*tail; int merge;
 
    tail=p->ZZds.ZZiters.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZiters.next; pp; pp=pp->ZZds.ZZiters.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("iters error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZiters.next; pp; pp=pp->ZZds.ZZiters.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("iters error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    iters_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZiters.tail=NULL; else p->ZZds.ZZiters.tail=t;
}

Iterator* iters_LinkedList1::child(OrgType *p){
    Iterator* t;
    t=p->ZZds.ZZiters.tail; if(t)return t->ZZds.ZZiters.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void iters_LinkedList1::setTail(OrgType* p,Iterator* c,int check){
    Iterator *pp,*tail;

    tail=p->ZZds.ZZiters.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZiters.next; pp; pp=pp->ZZds.ZZiters.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("iters warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZiters.tail=c;
}

void iters_LinkedList1Iterator::start(const OrgType *p){
    iters_Ring1Iterator::start(p->ZZds.ZZiters.tail); 
}

Iterator* iters_LinkedList1Iterator::fromHead(OrgType *p){
    return iters_Ring1Iterator::fromHead(p->ZZds.ZZiters.tail); 
}
