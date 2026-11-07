// --------------------------------------------------------
class OrgType;
class PartType;

PartType* const partTypes_LinkedList2::tail(OrgType *p){return p->ZZds.ZZpartTypes.tail;}

PartType* const partTypes_LinkedList2::head(OrgType *p){
    if(!(p->ZZds.ZZpartTypes.tail) || !(p->ZZds.ZZpartTypes.tail->ZZds.ZZpartTypes.next))return NULL;
    else return p->ZZds.ZZpartTypes.tail->ZZds.ZZpartTypes.next;
}

void partTypes_LinkedList2::addHead(OrgType *p, PartType *c){
    p->ZZds.ZZpartTypes.tail=partTypes_Ring2::addHead(p->ZZds.ZZpartTypes.tail,c);
}

void partTypes_LinkedList2::addTail(OrgType *p, PartType *c){
    p->ZZds.ZZpartTypes.tail=partTypes_Ring2::addTail(p->ZZds.ZZpartTypes.tail,c);
}

void partTypes_LinkedList2::append(OrgType *p,PartType *c1, PartType *c2){
    p->ZZds.ZZpartTypes.tail=partTypes_Ring2::append(p->ZZds.ZZpartTypes.tail,c1,c2);
}

void partTypes_LinkedList2::insert(PartType *c1, PartType *c2){partTypes_Ring2::insert(c1,c2);}

void partTypes_LinkedList2::sort(ZZsortFun cmpFun, OrgType *p){
    p->ZZds.ZZpartTypes.tail=partTypes_Ring2::sort(cmpFun,p->ZZds.ZZpartTypes.tail);
}

void partTypes_LinkedList2::remove(OrgType *p, PartType *c){
    p->ZZds.ZZpartTypes.tail=partTypes_Ring2::remove(p->ZZds.ZZpartTypes.tail,c);
}

PartType* const partTypes_LinkedList2::next(OrgType *p,PartType *c){ 
                               return partTypes_Ring2::next(p->ZZds.ZZpartTypes.tail,c);}

PartType* const partTypes_LinkedList2::prev(OrgType *p,PartType *c){ 
                               return partTypes_Ring2::prev(p->ZZds.ZZpartTypes.tail,c);}

PartType* const partTypes_LinkedList2::nextRing(PartType *c){ return partTypes_Ring2::nextRing(c);}

PartType* const partTypes_LinkedList2::prevRing(PartType *c){ return partTypes_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void partTypes_LinkedList2::merge(PartType *s,PartType *t,OrgType *p){
    PartType *pp,*tail; int merge;
 
    tail=p->ZZds.ZZpartTypes.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZpartTypes.next; pp; pp=pp->ZZds.ZZpartTypes.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("partTypes error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZpartTypes.next; pp; pp=pp->ZZds.ZZpartTypes.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("partTypes error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    partTypes_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZpartTypes.tail=NULL; else p->ZZds.ZZpartTypes.tail=t;
}

PartType* partTypes_LinkedList2::child(OrgType *p){
    PartType* t;
    t=p->ZZds.ZZpartTypes.tail; if(t)return t->ZZds.ZZpartTypes.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void partTypes_LinkedList2::setTail(OrgType* p,PartType* c,int check){
    PartType *pp,*tail;

    tail=p->ZZds.ZZpartTypes.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZpartTypes.next; pp; pp=pp->ZZds.ZZpartTypes.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("partTypes warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZpartTypes.tail=c;
}

void partTypes_LinkedList2Iterator::start(const OrgType *p){
    partTypes_Ring2Iterator::start(p->ZZds.ZZpartTypes.tail);
}

PartType* partTypes_LinkedList2Iterator::fromHead(OrgType *p){
    return partTypes_Ring2Iterator::fromHead(p->ZZds.ZZpartTypes.tail); 
}

PartType* partTypes_LinkedList2Iterator::fromTail(OrgType *p){
    return partTypes_Ring2Iterator::fromTail(p->ZZds.ZZpartTypes.tail); 
}
