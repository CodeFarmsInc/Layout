// --------------------------------------------------------
class ApplClass;
class Participant;

Participant* const usedBy_LinkedList2::tail(ApplClass *p){return p->ZZds.ZZusedBy.tail;}

Participant* const usedBy_LinkedList2::head(ApplClass *p){
    if(!(p->ZZds.ZZusedBy.tail) || !(p->ZZds.ZZusedBy.tail->ZZds.ZZusedBy.next))return NULL;
    else return p->ZZds.ZZusedBy.tail->ZZds.ZZusedBy.next;
}

void usedBy_LinkedList2::addHead(ApplClass *p, Participant *c){
    p->ZZds.ZZusedBy.tail=usedBy_Ring2::addHead(p->ZZds.ZZusedBy.tail,c);
}

void usedBy_LinkedList2::addTail(ApplClass *p, Participant *c){
    p->ZZds.ZZusedBy.tail=usedBy_Ring2::addTail(p->ZZds.ZZusedBy.tail,c);
}

void usedBy_LinkedList2::append(ApplClass *p,Participant *c1, Participant *c2){
    p->ZZds.ZZusedBy.tail=usedBy_Ring2::append(p->ZZds.ZZusedBy.tail,c1,c2);
}

void usedBy_LinkedList2::insert(Participant *c1, Participant *c2){usedBy_Ring2::insert(c1,c2);}

void usedBy_LinkedList2::sort(ZZsortFun cmpFun, ApplClass *p){
    p->ZZds.ZZusedBy.tail=usedBy_Ring2::sort(cmpFun,p->ZZds.ZZusedBy.tail);
}

void usedBy_LinkedList2::remove(ApplClass *p, Participant *c){
    p->ZZds.ZZusedBy.tail=usedBy_Ring2::remove(p->ZZds.ZZusedBy.tail,c);
}

Participant* const usedBy_LinkedList2::next(ApplClass *p,Participant *c){ 
                               return usedBy_Ring2::next(p->ZZds.ZZusedBy.tail,c);}

Participant* const usedBy_LinkedList2::prev(ApplClass *p,Participant *c){ 
                               return usedBy_Ring2::prev(p->ZZds.ZZusedBy.tail,c);}

Participant* const usedBy_LinkedList2::nextRing(Participant *c){ return usedBy_Ring2::nextRing(c);}

Participant* const usedBy_LinkedList2::prevRing(Participant *c){ return usedBy_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void usedBy_LinkedList2::merge(Participant *s,Participant *t,ApplClass *p){
    Participant *pp,*tail; int merge;
 
    tail=p->ZZds.ZZusedBy.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZusedBy.next; pp; pp=pp->ZZds.ZZusedBy.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("usedBy error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZusedBy.next; pp; pp=pp->ZZds.ZZusedBy.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("usedBy error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    usedBy_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZusedBy.tail=NULL; else p->ZZds.ZZusedBy.tail=t;
}

Participant* usedBy_LinkedList2::child(ApplClass *p){
    Participant* t;
    t=p->ZZds.ZZusedBy.tail; if(t)return t->ZZds.ZZusedBy.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void usedBy_LinkedList2::setTail(ApplClass* p,Participant* c,int check){
    Participant *pp,*tail;

    tail=p->ZZds.ZZusedBy.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZusedBy.next; pp; pp=pp->ZZds.ZZusedBy.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("usedBy warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZusedBy.tail=c;
}

void usedBy_LinkedList2Iterator::start(const ApplClass *p){
    usedBy_Ring2Iterator::start(p->ZZds.ZZusedBy.tail);
}

Participant* usedBy_LinkedList2Iterator::fromHead(ApplClass *p){
    return usedBy_Ring2Iterator::fromHead(p->ZZds.ZZusedBy.tail); 
}

Participant* usedBy_LinkedList2Iterator::fromTail(ApplClass *p){
    return usedBy_Ring2Iterator::fromTail(p->ZZds.ZZusedBy.tail); 
}
