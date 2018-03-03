// --------------------------------------------------------
class Layout;
class Edge;

Edge* edges_LinkedList1::tail(Layout *p){return p->ZZds.ZZedges.tail;}

Edge* edges_LinkedList1::head(Layout *p){
    if(!(p->ZZds.ZZedges.tail) || !(p->ZZds.ZZedges.tail->ZZds.ZZedges.next))return NULL;
    else return p->ZZds.ZZedges.tail->ZZds.ZZedges.next;
}

void edges_LinkedList1::addHead(Layout *p, Edge *c){
    p->ZZds.ZZedges.tail=edges_Ring1::addHead(p->ZZds.ZZedges.tail,c);
}

void edges_LinkedList1::addTail(Layout *p, Edge *c){
    p->ZZds.ZZedges.tail=edges_Ring1::addTail(p->ZZds.ZZedges.tail,c);
}

void edges_LinkedList1::append(Layout *p,Edge *c1, Edge *c2){
    p->ZZds.ZZedges.tail=edges_Ring1::append(p->ZZds.ZZedges.tail,c1,c2);
}

void edges_LinkedList1::remove(Layout *p, Edge *c){
    p->ZZds.ZZedges.tail=edges_Ring1::remove(p->ZZds.ZZedges.tail,c);
}

Edge* const edges_LinkedList1::next(Layout *p,Edge *c){
    return edges_Ring1::next(p->ZZds.ZZedges.tail,c);
}

Edge* const edges_LinkedList1::nextRing(Edge *c){ return edges_Ring1::nextRing(c);}

void edges_LinkedList1::sort(ZZsortFun cmpFun, Layout *p){
    p->ZZds.ZZedges.tail=edges_Ring1::sort(cmpFun,p->ZZds.ZZedges.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void edges_LinkedList1::merge(Edge *s,Edge *t,Layout *p){
    Edge *pp,*tail; int merge;
 
    tail=p->ZZds.ZZedges.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZedges.next; pp; pp=pp->ZZds.ZZedges.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("edges error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZedges.next; pp; pp=pp->ZZds.ZZedges.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("edges error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    edges_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZedges.tail=NULL; else p->ZZds.ZZedges.tail=t;
}

Edge* edges_LinkedList1::child(Layout *p){
    Edge* t;
    t=p->ZZds.ZZedges.tail; if(t)return t->ZZds.ZZedges.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void edges_LinkedList1::setTail(Layout* p,Edge* c,int check){
    Edge *pp,*tail;

    tail=p->ZZds.ZZedges.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZedges.next; pp; pp=pp->ZZds.ZZedges.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("edges warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZedges.tail=c;
}

void edges_LinkedList1Iterator::start(const Layout *p){
    edges_Ring1Iterator::start(p->ZZds.ZZedges.tail); 
}

Edge* edges_LinkedList1Iterator::fromHead(Layout *p){
    return edges_Ring1Iterator::fromHead(p->ZZds.ZZedges.tail); 
}
