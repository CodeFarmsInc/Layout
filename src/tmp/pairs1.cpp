// --------------------------------------------------------
class Layout;
class Pair;

Pair* pairs_LinkedList1::tail(Layout *p){return p->ZZds.ZZpairs.tail;}

Pair* pairs_LinkedList1::head(Layout *p){
    if(!(p->ZZds.ZZpairs.tail) || !(p->ZZds.ZZpairs.tail->ZZds.ZZpairs.next))return NULL;
    else return p->ZZds.ZZpairs.tail->ZZds.ZZpairs.next;
}

void pairs_LinkedList1::addHead(Layout *p, Pair *c){
    p->ZZds.ZZpairs.tail=pairs_Ring1::addHead(p->ZZds.ZZpairs.tail,c);
}

void pairs_LinkedList1::addTail(Layout *p, Pair *c){
    p->ZZds.ZZpairs.tail=pairs_Ring1::addTail(p->ZZds.ZZpairs.tail,c);
}

void pairs_LinkedList1::append(Layout *p,Pair *c1, Pair *c2){
    p->ZZds.ZZpairs.tail=pairs_Ring1::append(p->ZZds.ZZpairs.tail,c1,c2);
}

void pairs_LinkedList1::remove(Layout *p, Pair *c){
    p->ZZds.ZZpairs.tail=pairs_Ring1::remove(p->ZZds.ZZpairs.tail,c);
}

Pair* const pairs_LinkedList1::next(Layout *p,Pair *c){
    return pairs_Ring1::next(p->ZZds.ZZpairs.tail,c);
}

Pair* const pairs_LinkedList1::nextRing(Pair *c){ return pairs_Ring1::nextRing(c);}

void pairs_LinkedList1::sort(ZZsortFun cmpFun, Layout *p){
    p->ZZds.ZZpairs.tail=pairs_Ring1::sort(cmpFun,p->ZZds.ZZpairs.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void pairs_LinkedList1::merge(Pair *s,Pair *t,Layout *p){
    Pair *pp,*tail; int merge;
 
    tail=p->ZZds.ZZpairs.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZpairs.next; pp; pp=pp->ZZds.ZZpairs.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("pairs error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZpairs.next; pp; pp=pp->ZZds.ZZpairs.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("pairs error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    pairs_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZpairs.tail=NULL; else p->ZZds.ZZpairs.tail=t;
}

Pair* pairs_LinkedList1::child(Layout *p){
    Pair* t;
    t=p->ZZds.ZZpairs.tail; if(t)return t->ZZds.ZZpairs.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void pairs_LinkedList1::setTail(Layout* p,Pair* c,int check){
    Pair *pp,*tail;

    tail=p->ZZds.ZZpairs.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZpairs.next; pp; pp=pp->ZZds.ZZpairs.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("pairs warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZpairs.tail=c;
}

void pairs_LinkedList1Iterator::start(const Layout *p){
    pairs_Ring1Iterator::start(p->ZZds.ZZpairs.tail); 
}

Pair* pairs_LinkedList1Iterator::fromHead(Layout *p){
    return pairs_Ring1Iterator::fromHead(p->ZZds.ZZpairs.tail); 
}
