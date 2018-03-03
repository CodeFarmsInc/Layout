// --------------------------------------------------------
class Edge;
class NodeRef;

NodeRef* edgeToNodes_LinkedList1::tail(Edge *p){return p->ZZds.ZZedgeToNodes.tail;}

NodeRef* edgeToNodes_LinkedList1::head(Edge *p){
    if(!(p->ZZds.ZZedgeToNodes.tail) || !(p->ZZds.ZZedgeToNodes.tail->ZZds.ZZedgeToNodes.next))return NULL;
    else return p->ZZds.ZZedgeToNodes.tail->ZZds.ZZedgeToNodes.next;
}

void edgeToNodes_LinkedList1::addHead(Edge *p, NodeRef *c){
    p->ZZds.ZZedgeToNodes.tail=edgeToNodes_Ring1::addHead(p->ZZds.ZZedgeToNodes.tail,c);
}

void edgeToNodes_LinkedList1::addTail(Edge *p, NodeRef *c){
    p->ZZds.ZZedgeToNodes.tail=edgeToNodes_Ring1::addTail(p->ZZds.ZZedgeToNodes.tail,c);
}

void edgeToNodes_LinkedList1::append(Edge *p,NodeRef *c1, NodeRef *c2){
    p->ZZds.ZZedgeToNodes.tail=edgeToNodes_Ring1::append(p->ZZds.ZZedgeToNodes.tail,c1,c2);
}

void edgeToNodes_LinkedList1::remove(Edge *p, NodeRef *c){
    p->ZZds.ZZedgeToNodes.tail=edgeToNodes_Ring1::remove(p->ZZds.ZZedgeToNodes.tail,c);
}

NodeRef* const edgeToNodes_LinkedList1::next(Edge *p,NodeRef *c){
    return edgeToNodes_Ring1::next(p->ZZds.ZZedgeToNodes.tail,c);
}

NodeRef* const edgeToNodes_LinkedList1::nextRing(NodeRef *c){ return edgeToNodes_Ring1::nextRing(c);}

void edgeToNodes_LinkedList1::sort(ZZsortFun cmpFun, Edge *p){
    p->ZZds.ZZedgeToNodes.tail=edgeToNodes_Ring1::sort(cmpFun,p->ZZds.ZZedgeToNodes.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void edgeToNodes_LinkedList1::merge(NodeRef *s,NodeRef *t,Edge *p){
    NodeRef *pp,*tail; int merge;
 
    tail=p->ZZds.ZZedgeToNodes.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZedgeToNodes.next; pp; pp=pp->ZZds.ZZedgeToNodes.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("edgeToNodes error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZedgeToNodes.next; pp; pp=pp->ZZds.ZZedgeToNodes.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("edgeToNodes error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    edgeToNodes_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZedgeToNodes.tail=NULL; else p->ZZds.ZZedgeToNodes.tail=t;
}

NodeRef* edgeToNodes_LinkedList1::child(Edge *p){
    NodeRef* t;
    t=p->ZZds.ZZedgeToNodes.tail; if(t)return t->ZZds.ZZedgeToNodes.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void edgeToNodes_LinkedList1::setTail(Edge* p,NodeRef* c,int check){
    NodeRef *pp,*tail;

    tail=p->ZZds.ZZedgeToNodes.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZedgeToNodes.next; pp; pp=pp->ZZds.ZZedgeToNodes.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("edgeToNodes warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZedgeToNodes.tail=c;
}

void edgeToNodes_LinkedList1Iterator::start(const Edge *p){
    edgeToNodes_Ring1Iterator::start(p->ZZds.ZZedgeToNodes.tail); 
}

NodeRef* edgeToNodes_LinkedList1Iterator::fromHead(Edge *p){
    return edgeToNodes_Ring1Iterator::fromHead(p->ZZds.ZZedgeToNodes.tail); 
}
