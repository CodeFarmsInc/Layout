// --------------------------------------------------------
class Node;
class Edge;

Edge* const targets_LinkedList2::tail(Node *p){return p->ZZds.ZZtargets.tail;}

Edge* const targets_LinkedList2::head(Node *p){
    if(!(p->ZZds.ZZtargets.tail) || !(p->ZZds.ZZtargets.tail->ZZds.ZZtargets.next))return NULL;
    else return p->ZZds.ZZtargets.tail->ZZds.ZZtargets.next;
}

void targets_LinkedList2::addHead(Node *p, Edge *c){
    p->ZZds.ZZtargets.tail=targets_Ring2::addHead(p->ZZds.ZZtargets.tail,c);
}

void targets_LinkedList2::addTail(Node *p, Edge *c){
    p->ZZds.ZZtargets.tail=targets_Ring2::addTail(p->ZZds.ZZtargets.tail,c);
}

void targets_LinkedList2::append(Node *p,Edge *c1, Edge *c2){
    p->ZZds.ZZtargets.tail=targets_Ring2::append(p->ZZds.ZZtargets.tail,c1,c2);
}

void targets_LinkedList2::insert(Edge *c1, Edge *c2){targets_Ring2::insert(c1,c2);}

void targets_LinkedList2::sort(ZZsortFun cmpFun, Node *p){
    p->ZZds.ZZtargets.tail=targets_Ring2::sort(cmpFun,p->ZZds.ZZtargets.tail);
}

void targets_LinkedList2::remove(Node *p, Edge *c){
    p->ZZds.ZZtargets.tail=targets_Ring2::remove(p->ZZds.ZZtargets.tail,c);
}

Edge* const targets_LinkedList2::next(Node *p,Edge *c){ 
                               return targets_Ring2::next(p->ZZds.ZZtargets.tail,c);}

Edge* const targets_LinkedList2::prev(Node *p,Edge *c){ 
                               return targets_Ring2::prev(p->ZZds.ZZtargets.tail,c);}

Edge* const targets_LinkedList2::nextRing(Edge *c){ return targets_Ring2::nextRing(c);}

Edge* const targets_LinkedList2::prevRing(Edge *c){ return targets_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void targets_LinkedList2::merge(Edge *s,Edge *t,Node *p){
    Edge *pp,*tail; int merge;
 
    tail=p->ZZds.ZZtargets.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZtargets.next; pp; pp=pp->ZZds.ZZtargets.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("targets error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZtargets.next; pp; pp=pp->ZZds.ZZtargets.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("targets error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    targets_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZtargets.tail=NULL; else p->ZZds.ZZtargets.tail=t;
}

Edge* targets_LinkedList2::child(Node *p){
    Edge* t;
    t=p->ZZds.ZZtargets.tail; if(t)return t->ZZds.ZZtargets.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void targets_LinkedList2::setTail(Node* p,Edge* c,int check){
    Edge *pp,*tail;

    tail=p->ZZds.ZZtargets.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZtargets.next; pp; pp=pp->ZZds.ZZtargets.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("targets warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZtargets.tail=c;
}

void targets_LinkedList2Iterator::start(const Node *p){
    targets_Ring2Iterator::start(p->ZZds.ZZtargets.tail);
}

Edge* targets_LinkedList2Iterator::fromHead(Node *p){
    return targets_Ring2Iterator::fromHead(p->ZZds.ZZtargets.tail); 
}

Edge* targets_LinkedList2Iterator::fromTail(Node *p){
    return targets_Ring2Iterator::fromTail(p->ZZds.ZZtargets.tail); 
}
