// --------------------------------------------------------
class B;
class C;

C* BtoC_LinkedList1::tail(B *p){return p->ZZds.ZZBtoC.tail;}

C* BtoC_LinkedList1::head(B *p){
    if(!(p->ZZds.ZZBtoC.tail) || !(p->ZZds.ZZBtoC.tail->ZZds.ZZBtoC.next))return NULL;
    else return p->ZZds.ZZBtoC.tail->ZZds.ZZBtoC.next;
}

void BtoC_LinkedList1::addHead(B *p, C *c){
    p->ZZds.ZZBtoC.tail=BtoC_Ring1::addHead(p->ZZds.ZZBtoC.tail,c);
}

void BtoC_LinkedList1::addTail(B *p, C *c){
    p->ZZds.ZZBtoC.tail=BtoC_Ring1::addTail(p->ZZds.ZZBtoC.tail,c);
}

void BtoC_LinkedList1::append(B *p,C *c1, C *c2){
    p->ZZds.ZZBtoC.tail=BtoC_Ring1::append(p->ZZds.ZZBtoC.tail,c1,c2);
}

void BtoC_LinkedList1::remove(B *p, C *c){
    p->ZZds.ZZBtoC.tail=BtoC_Ring1::remove(p->ZZds.ZZBtoC.tail,c);
}

C* const BtoC_LinkedList1::next(B *p,C *c){
    return BtoC_Ring1::next(p->ZZds.ZZBtoC.tail,c);
}

C* const BtoC_LinkedList1::nextRing(C *c){ return BtoC_Ring1::nextRing(c);}

void BtoC_LinkedList1::sort(ZZsortFun cmpFun, B *p){
    p->ZZds.ZZBtoC.tail=BtoC_Ring1::sort(cmpFun,p->ZZds.ZZBtoC.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void BtoC_LinkedList1::merge(C *s,C *t,B *p){
    C *pp,*tail; int merge;
 
    tail=p->ZZds.ZZBtoC.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZBtoC.next; pp; pp=pp->ZZds.ZZBtoC.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("BtoC error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZBtoC.next; pp; pp=pp->ZZds.ZZBtoC.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("BtoC error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    BtoC_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZBtoC.tail=NULL; else p->ZZds.ZZBtoC.tail=t;
}

C* BtoC_LinkedList1::child(B *p){
    C* t;
    t=p->ZZds.ZZBtoC.tail; if(t)return t->ZZds.ZZBtoC.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void BtoC_LinkedList1::setTail(B* p,C* c,int check){
    C *pp,*tail;

    tail=p->ZZds.ZZBtoC.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZBtoC.next; pp; pp=pp->ZZds.ZZBtoC.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("BtoC warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZBtoC.tail=c;
}

void BtoC_LinkedList1Iterator::start(const B *p){
    BtoC_Ring1Iterator::start(p->ZZds.ZZBtoC.tail); 
}

C* BtoC_LinkedList1Iterator::fromHead(B *p){
    return BtoC_Ring1Iterator::fromHead(p->ZZds.ZZBtoC.tail); 
}
