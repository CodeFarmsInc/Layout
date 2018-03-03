// --------------------------------------------------------
class Organization;
class Participant;

Participant* const parts_LinkedList2::tail(Organization *p){return p->ZZds.ZZparts.tail;}

Participant* const parts_LinkedList2::head(Organization *p){
    if(!(p->ZZds.ZZparts.tail) || !(p->ZZds.ZZparts.tail->ZZds.ZZparts.next))return NULL;
    else return p->ZZds.ZZparts.tail->ZZds.ZZparts.next;
}

void parts_LinkedList2::addHead(Organization *p, Participant *c){
    p->ZZds.ZZparts.tail=parts_Ring2::addHead(p->ZZds.ZZparts.tail,c);
}

void parts_LinkedList2::addTail(Organization *p, Participant *c){
    p->ZZds.ZZparts.tail=parts_Ring2::addTail(p->ZZds.ZZparts.tail,c);
}

void parts_LinkedList2::append(Organization *p,Participant *c1, Participant *c2){
    p->ZZds.ZZparts.tail=parts_Ring2::append(p->ZZds.ZZparts.tail,c1,c2);
}

void parts_LinkedList2::insert(Participant *c1, Participant *c2){parts_Ring2::insert(c1,c2);}

void parts_LinkedList2::sort(ZZsortFun cmpFun, Organization *p){
    p->ZZds.ZZparts.tail=parts_Ring2::sort(cmpFun,p->ZZds.ZZparts.tail);
}

void parts_LinkedList2::remove(Organization *p, Participant *c){
    p->ZZds.ZZparts.tail=parts_Ring2::remove(p->ZZds.ZZparts.tail,c);
}

Participant* const parts_LinkedList2::next(Organization *p,Participant *c){ 
                               return parts_Ring2::next(p->ZZds.ZZparts.tail,c);}

Participant* const parts_LinkedList2::prev(Organization *p,Participant *c){ 
                               return parts_Ring2::prev(p->ZZds.ZZparts.tail,c);}

Participant* const parts_LinkedList2::nextRing(Participant *c){ return parts_Ring2::nextRing(c);}

Participant* const parts_LinkedList2::prevRing(Participant *c){ return parts_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void parts_LinkedList2::merge(Participant *s,Participant *t,Organization *p){
    Participant *pp,*tail; int merge;
 
    tail=p->ZZds.ZZparts.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZparts.next; pp; pp=pp->ZZds.ZZparts.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("parts error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZparts.next; pp; pp=pp->ZZds.ZZparts.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("parts error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    parts_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZparts.tail=NULL; else p->ZZds.ZZparts.tail=t;
}

Participant* parts_LinkedList2::child(Organization *p){
    Participant* t;
    t=p->ZZds.ZZparts.tail; if(t)return t->ZZds.ZZparts.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void parts_LinkedList2::setTail(Organization* p,Participant* c,int check){
    Participant *pp,*tail;

    tail=p->ZZds.ZZparts.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZparts.next; pp; pp=pp->ZZds.ZZparts.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("parts warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZparts.tail=c;
}

void parts_LinkedList2Iterator::start(const Organization *p){
    parts_Ring2Iterator::start(p->ZZds.ZZparts.tail);
}

Participant* parts_LinkedList2Iterator::fromHead(Organization *p){
    return parts_Ring2Iterator::fromHead(p->ZZds.ZZparts.tail); 
}

Participant* parts_LinkedList2Iterator::fromTail(Organization *p){
    return parts_Ring2Iterator::fromTail(p->ZZds.ZZparts.tail); 
}
