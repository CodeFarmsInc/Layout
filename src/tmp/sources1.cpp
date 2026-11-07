// --------------------------------------------------------
class Node;
class Edge;

Edge* const sources_LinkedList2::tail(Node *p){return p->ZZds.ZZsources.tail;}

Edge* const sources_LinkedList2::head(Node *p){
    if(!(p->ZZds.ZZsources.tail) || !(p->ZZds.ZZsources.tail->ZZds.ZZsources.next))return NULL;
    else return p->ZZds.ZZsources.tail->ZZds.ZZsources.next;
}

void sources_LinkedList2::addHead(Node *p, Edge *c){
    p->ZZds.ZZsources.tail=sources_Ring2::addHead(p->ZZds.ZZsources.tail,c);
}

void sources_LinkedList2::addTail(Node *p, Edge *c){
    p->ZZds.ZZsources.tail=sources_Ring2::addTail(p->ZZds.ZZsources.tail,c);
}

void sources_LinkedList2::append(Node *p,Edge *c1, Edge *c2){
    p->ZZds.ZZsources.tail=sources_Ring2::append(p->ZZds.ZZsources.tail,c1,c2);
}

void sources_LinkedList2::insert(Edge *c1, Edge *c2){sources_Ring2::insert(c1,c2);}

void sources_LinkedList2::sort(ZZsortFun cmpFun, Node *p){
    p->ZZds.ZZsources.tail=sources_Ring2::sort(cmpFun,p->ZZds.ZZsources.tail);
}

void sources_LinkedList2::remove(Node *p, Edge *c){
    p->ZZds.ZZsources.tail=sources_Ring2::remove(p->ZZds.ZZsources.tail,c);
}

Edge* const sources_LinkedList2::next(Node *p,Edge *c){ 
                               return sources_Ring2::next(p->ZZds.ZZsources.tail,c);}

Edge* const sources_LinkedList2::prev(Node *p,Edge *c){ 
                               return sources_Ring2::prev(p->ZZds.ZZsources.tail,c);}

Edge* const sources_LinkedList2::nextRing(Edge *c){ return sources_Ring2::nextRing(c);}

Edge* const sources_LinkedList2::prevRing(Edge *c){ return sources_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void sources_LinkedList2::merge(Edge *s,Edge *t,Node *p){
    Edge *pp,*tail; int merge;
 
    tail=p->ZZds.ZZsources.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZsources.next; pp; pp=pp->ZZds.ZZsources.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("sources error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZsources.next; pp; pp=pp->ZZds.ZZsources.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("sources error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    sources_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZsources.tail=NULL; else p->ZZds.ZZsources.tail=t;
}

Edge* sources_LinkedList2::child(Node *p){
    Edge* t;
    t=p->ZZds.ZZsources.tail; if(t)return t->ZZds.ZZsources.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void sources_LinkedList2::setTail(Node* p,Edge* c,int check){
    Edge *pp,*tail;

    tail=p->ZZds.ZZsources.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZsources.next; pp; pp=pp->ZZds.ZZsources.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("sources warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZsources.tail=c;
}

void sources_LinkedList2Iterator::start(const Node *p){
    sources_Ring2Iterator::start(p->ZZds.ZZsources.tail);
}

Edge* sources_LinkedList2Iterator::fromHead(Node *p){
    return sources_Ring2Iterator::fromHead(p->ZZds.ZZsources.tail); 
}

Edge* sources_LinkedList2Iterator::fromTail(Node *p){
    return sources_Ring2Iterator::fromTail(p->ZZds.ZZsources.tail); 
}
