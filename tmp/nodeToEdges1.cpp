// --------------------------------------------------------
class Node;
class EdgeRef;

EdgeRef* nodeToEdges_LinkedList1::tail(Node *p){return p->ZZds.ZZnodeToEdges.tail;}

EdgeRef* nodeToEdges_LinkedList1::head(Node *p){
    if(!(p->ZZds.ZZnodeToEdges.tail) || !(p->ZZds.ZZnodeToEdges.tail->ZZds.ZZnodeToEdges.next))return NULL;
    else return p->ZZds.ZZnodeToEdges.tail->ZZds.ZZnodeToEdges.next;
}

void nodeToEdges_LinkedList1::addHead(Node *p, EdgeRef *c){
    p->ZZds.ZZnodeToEdges.tail=nodeToEdges_Ring1::addHead(p->ZZds.ZZnodeToEdges.tail,c);
}

void nodeToEdges_LinkedList1::addTail(Node *p, EdgeRef *c){
    p->ZZds.ZZnodeToEdges.tail=nodeToEdges_Ring1::addTail(p->ZZds.ZZnodeToEdges.tail,c);
}

void nodeToEdges_LinkedList1::append(Node *p,EdgeRef *c1, EdgeRef *c2){
    p->ZZds.ZZnodeToEdges.tail=nodeToEdges_Ring1::append(p->ZZds.ZZnodeToEdges.tail,c1,c2);
}

void nodeToEdges_LinkedList1::remove(Node *p, EdgeRef *c){
    p->ZZds.ZZnodeToEdges.tail=nodeToEdges_Ring1::remove(p->ZZds.ZZnodeToEdges.tail,c);
}

EdgeRef* const nodeToEdges_LinkedList1::next(Node *p,EdgeRef *c){
    return nodeToEdges_Ring1::next(p->ZZds.ZZnodeToEdges.tail,c);
}

EdgeRef* const nodeToEdges_LinkedList1::nextRing(EdgeRef *c){ return nodeToEdges_Ring1::nextRing(c);}

void nodeToEdges_LinkedList1::sort(ZZsortFun cmpFun, Node *p){
    p->ZZds.ZZnodeToEdges.tail=nodeToEdges_Ring1::sort(cmpFun,p->ZZds.ZZnodeToEdges.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void nodeToEdges_LinkedList1::merge(EdgeRef *s,EdgeRef *t,Node *p){
    EdgeRef *pp,*tail; int merge;
 
    tail=p->ZZds.ZZnodeToEdges.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZnodeToEdges.next; pp; pp=pp->ZZds.ZZnodeToEdges.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("nodeToEdges error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZnodeToEdges.next; pp; pp=pp->ZZds.ZZnodeToEdges.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("nodeToEdges error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    nodeToEdges_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZnodeToEdges.tail=NULL; else p->ZZds.ZZnodeToEdges.tail=t;
}

EdgeRef* nodeToEdges_LinkedList1::child(Node *p){
    EdgeRef* t;
    t=p->ZZds.ZZnodeToEdges.tail; if(t)return t->ZZds.ZZnodeToEdges.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void nodeToEdges_LinkedList1::setTail(Node* p,EdgeRef* c,int check){
    EdgeRef *pp,*tail;

    tail=p->ZZds.ZZnodeToEdges.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZnodeToEdges.next; pp; pp=pp->ZZds.ZZnodeToEdges.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("nodeToEdges warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZnodeToEdges.tail=c;
}

void nodeToEdges_LinkedList1Iterator::start(const Node *p){
    nodeToEdges_Ring1Iterator::start(p->ZZds.ZZnodeToEdges.tail); 
}

EdgeRef* nodeToEdges_LinkedList1Iterator::fromHead(Node *p){
    return nodeToEdges_Ring1Iterator::fromHead(p->ZZds.ZZnodeToEdges.tail); 
}
