// --------------------------------------------------------
class Generator;
class Organization;

Organization* const orgs_LinkedList2::tail(Generator *p){return p->ZZds.ZZorgs.tail;}

Organization* const orgs_LinkedList2::head(Generator *p){
    if(!(p->ZZds.ZZorgs.tail) || !(p->ZZds.ZZorgs.tail->ZZds.ZZorgs.next))return NULL;
    else return p->ZZds.ZZorgs.tail->ZZds.ZZorgs.next;
}

void orgs_LinkedList2::addHead(Generator *p, Organization *c){
    p->ZZds.ZZorgs.tail=orgs_Ring2::addHead(p->ZZds.ZZorgs.tail,c);
}

void orgs_LinkedList2::addTail(Generator *p, Organization *c){
    p->ZZds.ZZorgs.tail=orgs_Ring2::addTail(p->ZZds.ZZorgs.tail,c);
}

void orgs_LinkedList2::append(Generator *p,Organization *c1, Organization *c2){
    p->ZZds.ZZorgs.tail=orgs_Ring2::append(p->ZZds.ZZorgs.tail,c1,c2);
}

void orgs_LinkedList2::insert(Organization *c1, Organization *c2){orgs_Ring2::insert(c1,c2);}

void orgs_LinkedList2::sort(ZZsortFun cmpFun, Generator *p){
    p->ZZds.ZZorgs.tail=orgs_Ring2::sort(cmpFun,p->ZZds.ZZorgs.tail);
}

void orgs_LinkedList2::remove(Generator *p, Organization *c){
    p->ZZds.ZZorgs.tail=orgs_Ring2::remove(p->ZZds.ZZorgs.tail,c);
}

Organization* const orgs_LinkedList2::next(Generator *p,Organization *c){ 
                               return orgs_Ring2::next(p->ZZds.ZZorgs.tail,c);}

Organization* const orgs_LinkedList2::prev(Generator *p,Organization *c){ 
                               return orgs_Ring2::prev(p->ZZds.ZZorgs.tail,c);}

Organization* const orgs_LinkedList2::nextRing(Organization *c){ return orgs_Ring2::nextRing(c);}

Organization* const orgs_LinkedList2::prevRing(Organization *c){ return orgs_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void orgs_LinkedList2::merge(Organization *s,Organization *t,Generator *p){
    Organization *pp,*tail; int merge;
 
    tail=p->ZZds.ZZorgs.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZorgs.next; pp; pp=pp->ZZds.ZZorgs.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("orgs error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZorgs.next; pp; pp=pp->ZZds.ZZorgs.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("orgs error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    orgs_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZorgs.tail=NULL; else p->ZZds.ZZorgs.tail=t;
}

Organization* orgs_LinkedList2::child(Generator *p){
    Organization* t;
    t=p->ZZds.ZZorgs.tail; if(t)return t->ZZds.ZZorgs.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void orgs_LinkedList2::setTail(Generator* p,Organization* c,int check){
    Organization *pp,*tail;

    tail=p->ZZds.ZZorgs.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZorgs.next; pp; pp=pp->ZZds.ZZorgs.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("orgs warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZorgs.tail=c;
}

void orgs_LinkedList2Iterator::start(const Generator *p){
    orgs_Ring2Iterator::start(p->ZZds.ZZorgs.tail);
}

Organization* orgs_LinkedList2Iterator::fromHead(Generator *p){
    return orgs_Ring2Iterator::fromHead(p->ZZds.ZZorgs.tail); 
}

Organization* orgs_LinkedList2Iterator::fromTail(Generator *p){
    return orgs_Ring2Iterator::fromTail(p->ZZds.ZZorgs.tail); 
}
