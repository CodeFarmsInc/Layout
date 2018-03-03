// --------------------------------------------------------
class Net;
class Edge;

Edge* const byNet_LinkedList2::tail(Net *p){return p->ZZds.ZZbyNet.tail;}

Edge* const byNet_LinkedList2::head(Net *p){
    if(!(p->ZZds.ZZbyNet.tail) || !(p->ZZds.ZZbyNet.tail->ZZds.ZZbyNet.next))return NULL;
    else return p->ZZds.ZZbyNet.tail->ZZds.ZZbyNet.next;
}

void byNet_LinkedList2::addHead(Net *p, Edge *c){
    p->ZZds.ZZbyNet.tail=byNet_Ring2::addHead(p->ZZds.ZZbyNet.tail,c);
}

void byNet_LinkedList2::addTail(Net *p, Edge *c){
    p->ZZds.ZZbyNet.tail=byNet_Ring2::addTail(p->ZZds.ZZbyNet.tail,c);
}

void byNet_LinkedList2::append(Net *p,Edge *c1, Edge *c2){
    p->ZZds.ZZbyNet.tail=byNet_Ring2::append(p->ZZds.ZZbyNet.tail,c1,c2);
}

void byNet_LinkedList2::insert(Edge *c1, Edge *c2){byNet_Ring2::insert(c1,c2);}

void byNet_LinkedList2::sort(ZZsortFun cmpFun, Net *p){
    p->ZZds.ZZbyNet.tail=byNet_Ring2::sort(cmpFun,p->ZZds.ZZbyNet.tail);
}

void byNet_LinkedList2::remove(Net *p, Edge *c){
    p->ZZds.ZZbyNet.tail=byNet_Ring2::remove(p->ZZds.ZZbyNet.tail,c);
}

Edge* const byNet_LinkedList2::next(Net *p,Edge *c){ 
                               return byNet_Ring2::next(p->ZZds.ZZbyNet.tail,c);}

Edge* const byNet_LinkedList2::prev(Net *p,Edge *c){ 
                               return byNet_Ring2::prev(p->ZZds.ZZbyNet.tail,c);}

Edge* const byNet_LinkedList2::nextRing(Edge *c){ return byNet_Ring2::nextRing(c);}

Edge* const byNet_LinkedList2::prevRing(Edge *c){ return byNet_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void byNet_LinkedList2::merge(Edge *s,Edge *t,Net *p){
    Edge *pp,*tail; int merge;
 
    tail=p->ZZds.ZZbyNet.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZbyNet.next; pp; pp=pp->ZZds.ZZbyNet.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("byNet error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZbyNet.next; pp; pp=pp->ZZds.ZZbyNet.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("byNet error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    byNet_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZbyNet.tail=NULL; else p->ZZds.ZZbyNet.tail=t;
}

Edge* byNet_LinkedList2::child(Net *p){
    Edge* t;
    t=p->ZZds.ZZbyNet.tail; if(t)return t->ZZds.ZZbyNet.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void byNet_LinkedList2::setTail(Net* p,Edge* c,int check){
    Edge *pp,*tail;

    tail=p->ZZds.ZZbyNet.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZbyNet.next; pp; pp=pp->ZZds.ZZbyNet.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("byNet warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZbyNet.tail=c;
}

void byNet_LinkedList2Iterator::start(const Net *p){
    byNet_Ring2Iterator::start(p->ZZds.ZZbyNet.tail);
}

Edge* byNet_LinkedList2Iterator::fromHead(Net *p){
    return byNet_Ring2Iterator::fromHead(p->ZZds.ZZbyNet.tail); 
}

Edge* byNet_LinkedList2Iterator::fromTail(Net *p){
    return byNet_Ring2Iterator::fromTail(p->ZZds.ZZbyNet.tail); 
}
