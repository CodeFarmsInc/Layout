// --------------------------------------------------------
class Layout;
class Net;

Net* const nets_LinkedList2::tail(Layout *p){return p->ZZds.ZZnets.tail;}

Net* const nets_LinkedList2::head(Layout *p){
    if(!(p->ZZds.ZZnets.tail) || !(p->ZZds.ZZnets.tail->ZZds.ZZnets.next))return NULL;
    else return p->ZZds.ZZnets.tail->ZZds.ZZnets.next;
}

void nets_LinkedList2::addHead(Layout *p, Net *c){
    p->ZZds.ZZnets.tail=nets_Ring2::addHead(p->ZZds.ZZnets.tail,c);
}

void nets_LinkedList2::addTail(Layout *p, Net *c){
    p->ZZds.ZZnets.tail=nets_Ring2::addTail(p->ZZds.ZZnets.tail,c);
}

void nets_LinkedList2::append(Layout *p,Net *c1, Net *c2){
    p->ZZds.ZZnets.tail=nets_Ring2::append(p->ZZds.ZZnets.tail,c1,c2);
}

void nets_LinkedList2::insert(Net *c1, Net *c2){nets_Ring2::insert(c1,c2);}

void nets_LinkedList2::sort(ZZsortFun cmpFun, Layout *p){
    p->ZZds.ZZnets.tail=nets_Ring2::sort(cmpFun,p->ZZds.ZZnets.tail);
}

void nets_LinkedList2::remove(Layout *p, Net *c){
    p->ZZds.ZZnets.tail=nets_Ring2::remove(p->ZZds.ZZnets.tail,c);
}

Net* const nets_LinkedList2::next(Layout *p,Net *c){ 
                               return nets_Ring2::next(p->ZZds.ZZnets.tail,c);}

Net* const nets_LinkedList2::prev(Layout *p,Net *c){ 
                               return nets_Ring2::prev(p->ZZds.ZZnets.tail,c);}

Net* const nets_LinkedList2::nextRing(Net *c){ return nets_Ring2::nextRing(c);}

Net* const nets_LinkedList2::prevRing(Net *c){ return nets_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void nets_LinkedList2::merge(Net *s,Net *t,Layout *p){
    Net *pp,*tail; int merge;
 
    tail=p->ZZds.ZZnets.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZnets.next; pp; pp=pp->ZZds.ZZnets.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("nets error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZnets.next; pp; pp=pp->ZZds.ZZnets.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("nets error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    nets_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZnets.tail=NULL; else p->ZZds.ZZnets.tail=t;
}

Net* nets_LinkedList2::child(Layout *p){
    Net* t;
    t=p->ZZds.ZZnets.tail; if(t)return t->ZZds.ZZnets.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void nets_LinkedList2::setTail(Layout* p,Net* c,int check){
    Net *pp,*tail;

    tail=p->ZZds.ZZnets.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZnets.next; pp; pp=pp->ZZds.ZZnets.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("nets warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZnets.tail=c;
}

void nets_LinkedList2Iterator::start(const Layout *p){
    nets_Ring2Iterator::start(p->ZZds.ZZnets.tail);
}

Net* nets_LinkedList2Iterator::fromHead(Layout *p){
    return nets_Ring2Iterator::fromHead(p->ZZds.ZZnets.tail); 
}

Net* nets_LinkedList2Iterator::fromTail(Layout *p){
    return nets_Ring2Iterator::fromTail(p->ZZds.ZZnets.tail); 
}
