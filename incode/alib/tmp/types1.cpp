// --------------------------------------------------------
class Generator;
class OrgType;

OrgType* const types_LinkedList2::tail(Generator *p){return p->ZZds.ZZtypes.tail;}

OrgType* const types_LinkedList2::head(Generator *p){
    if(!(p->ZZds.ZZtypes.tail) || !(p->ZZds.ZZtypes.tail->ZZds.ZZtypes.next))return NULL;
    else return p->ZZds.ZZtypes.tail->ZZds.ZZtypes.next;
}

void types_LinkedList2::addHead(Generator *p, OrgType *c){
    p->ZZds.ZZtypes.tail=types_Ring2::addHead(p->ZZds.ZZtypes.tail,c);
}

void types_LinkedList2::addTail(Generator *p, OrgType *c){
    p->ZZds.ZZtypes.tail=types_Ring2::addTail(p->ZZds.ZZtypes.tail,c);
}

void types_LinkedList2::append(Generator *p,OrgType *c1, OrgType *c2){
    p->ZZds.ZZtypes.tail=types_Ring2::append(p->ZZds.ZZtypes.tail,c1,c2);
}

void types_LinkedList2::insert(OrgType *c1, OrgType *c2){types_Ring2::insert(c1,c2);}

void types_LinkedList2::sort(ZZsortFun cmpFun, Generator *p){
    p->ZZds.ZZtypes.tail=types_Ring2::sort(cmpFun,p->ZZds.ZZtypes.tail);
}

void types_LinkedList2::remove(Generator *p, OrgType *c){
    p->ZZds.ZZtypes.tail=types_Ring2::remove(p->ZZds.ZZtypes.tail,c);
}

OrgType* const types_LinkedList2::next(Generator *p,OrgType *c){ 
                               return types_Ring2::next(p->ZZds.ZZtypes.tail,c);}

OrgType* const types_LinkedList2::prev(Generator *p,OrgType *c){ 
                               return types_Ring2::prev(p->ZZds.ZZtypes.tail,c);}

OrgType* const types_LinkedList2::nextRing(OrgType *c){ return types_Ring2::nextRing(c);}

OrgType* const types_LinkedList2::prevRing(OrgType *c){ return types_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void types_LinkedList2::merge(OrgType *s,OrgType *t,Generator *p){
    OrgType *pp,*tail; int merge;
 
    tail=p->ZZds.ZZtypes.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZtypes.next; pp; pp=pp->ZZds.ZZtypes.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("types error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZtypes.next; pp; pp=pp->ZZds.ZZtypes.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("types error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    types_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZtypes.tail=NULL; else p->ZZds.ZZtypes.tail=t;
}

OrgType* types_LinkedList2::child(Generator *p){
    OrgType* t;
    t=p->ZZds.ZZtypes.tail; if(t)return t->ZZds.ZZtypes.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void types_LinkedList2::setTail(Generator* p,OrgType* c,int check){
    OrgType *pp,*tail;

    tail=p->ZZds.ZZtypes.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZtypes.next; pp; pp=pp->ZZds.ZZtypes.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("types warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZtypes.tail=c;
}

void types_LinkedList2Iterator::start(const Generator *p){
    types_Ring2Iterator::start(p->ZZds.ZZtypes.tail);
}

OrgType* types_LinkedList2Iterator::fromHead(Generator *p){
    return types_Ring2Iterator::fromHead(p->ZZds.ZZtypes.tail); 
}

OrgType* types_LinkedList2Iterator::fromTail(Generator *p){
    return types_Ring2Iterator::fromTail(p->ZZds.ZZtypes.tail); 
}
