// --------------------------------------------------------
class Track;
class Edge;

Edge* const byTrack_LinkedList2::tail(Track *p){return p->ZZds.ZZbyTrack.tail;}

Edge* const byTrack_LinkedList2::head(Track *p){
    if(!(p->ZZds.ZZbyTrack.tail) || !(p->ZZds.ZZbyTrack.tail->ZZds.ZZbyTrack.next))return NULL;
    else return p->ZZds.ZZbyTrack.tail->ZZds.ZZbyTrack.next;
}

void byTrack_LinkedList2::addHead(Track *p, Edge *c){
    p->ZZds.ZZbyTrack.tail=byTrack_Ring2::addHead(p->ZZds.ZZbyTrack.tail,c);
}

void byTrack_LinkedList2::addTail(Track *p, Edge *c){
    p->ZZds.ZZbyTrack.tail=byTrack_Ring2::addTail(p->ZZds.ZZbyTrack.tail,c);
}

void byTrack_LinkedList2::append(Track *p,Edge *c1, Edge *c2){
    p->ZZds.ZZbyTrack.tail=byTrack_Ring2::append(p->ZZds.ZZbyTrack.tail,c1,c2);
}

void byTrack_LinkedList2::insert(Edge *c1, Edge *c2){byTrack_Ring2::insert(c1,c2);}

void byTrack_LinkedList2::sort(ZZsortFun cmpFun, Track *p){
    p->ZZds.ZZbyTrack.tail=byTrack_Ring2::sort(cmpFun,p->ZZds.ZZbyTrack.tail);
}

void byTrack_LinkedList2::remove(Track *p, Edge *c){
    p->ZZds.ZZbyTrack.tail=byTrack_Ring2::remove(p->ZZds.ZZbyTrack.tail,c);
}

Edge* const byTrack_LinkedList2::next(Track *p,Edge *c){ 
                               return byTrack_Ring2::next(p->ZZds.ZZbyTrack.tail,c);}

Edge* const byTrack_LinkedList2::prev(Track *p,Edge *c){ 
                               return byTrack_Ring2::prev(p->ZZds.ZZbyTrack.tail,c);}

Edge* const byTrack_LinkedList2::nextRing(Edge *c){ return byTrack_Ring2::nextRing(c);}

Edge* const byTrack_LinkedList2::prevRing(Edge *c){ return byTrack_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void byTrack_LinkedList2::merge(Edge *s,Edge *t,Track *p){
    Edge *pp,*tail; int merge;
 
    tail=p->ZZds.ZZbyTrack.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZbyTrack.next; pp; pp=pp->ZZds.ZZbyTrack.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("byTrack error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZbyTrack.next; pp; pp=pp->ZZds.ZZbyTrack.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("byTrack error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    byTrack_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZbyTrack.tail=NULL; else p->ZZds.ZZbyTrack.tail=t;
}

Edge* byTrack_LinkedList2::child(Track *p){
    Edge* t;
    t=p->ZZds.ZZbyTrack.tail; if(t)return t->ZZds.ZZbyTrack.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void byTrack_LinkedList2::setTail(Track* p,Edge* c,int check){
    Edge *pp,*tail;

    tail=p->ZZds.ZZbyTrack.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZbyTrack.next; pp; pp=pp->ZZds.ZZbyTrack.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("byTrack warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZbyTrack.tail=c;
}

void byTrack_LinkedList2Iterator::start(const Track *p){
    byTrack_Ring2Iterator::start(p->ZZds.ZZbyTrack.tail);
}

Edge* byTrack_LinkedList2Iterator::fromHead(Track *p){
    return byTrack_Ring2Iterator::fromHead(p->ZZds.ZZbyTrack.tail); 
}

Edge* byTrack_LinkedList2Iterator::fromTail(Track *p){
    return byTrack_Ring2Iterator::fromTail(p->ZZds.ZZbyTrack.tail); 
}
