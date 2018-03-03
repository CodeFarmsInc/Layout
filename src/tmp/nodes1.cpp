// --------------------------------------------------------
class Layout;
class Node;

Node* nodes_LinkedList1::tail(Layout *p){return p->ZZds.ZZnodes.tail;}

Node* nodes_LinkedList1::head(Layout *p){
    if(!(p->ZZds.ZZnodes.tail) || !(p->ZZds.ZZnodes.tail->ZZds.ZZnodes.next))return NULL;
    else return p->ZZds.ZZnodes.tail->ZZds.ZZnodes.next;
}

void nodes_LinkedList1::addHead(Layout *p, Node *c){
    p->ZZds.ZZnodes.tail=nodes_Ring1::addHead(p->ZZds.ZZnodes.tail,c);
}

void nodes_LinkedList1::addTail(Layout *p, Node *c){
    p->ZZds.ZZnodes.tail=nodes_Ring1::addTail(p->ZZds.ZZnodes.tail,c);
}

void nodes_LinkedList1::append(Layout *p,Node *c1, Node *c2){
    p->ZZds.ZZnodes.tail=nodes_Ring1::append(p->ZZds.ZZnodes.tail,c1,c2);
}

void nodes_LinkedList1::remove(Layout *p, Node *c){
    p->ZZds.ZZnodes.tail=nodes_Ring1::remove(p->ZZds.ZZnodes.tail,c);
}

Node* const nodes_LinkedList1::next(Layout *p,Node *c){
    return nodes_Ring1::next(p->ZZds.ZZnodes.tail,c);
}

Node* const nodes_LinkedList1::nextRing(Node *c){ return nodes_Ring1::nextRing(c);}

void nodes_LinkedList1::sort(ZZsortFun cmpFun, Layout *p){
    p->ZZds.ZZnodes.tail=nodes_Ring1::sort(cmpFun,p->ZZds.ZZnodes.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void nodes_LinkedList1::merge(Node *s,Node *t,Layout *p){
    Node *pp,*tail; int merge;
 
    tail=p->ZZds.ZZnodes.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZnodes.next; pp; pp=pp->ZZds.ZZnodes.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("nodes error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZnodes.next; pp; pp=pp->ZZds.ZZnodes.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("nodes error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    nodes_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZnodes.tail=NULL; else p->ZZds.ZZnodes.tail=t;
}

Node* nodes_LinkedList1::child(Layout *p){
    Node* t;
    t=p->ZZds.ZZnodes.tail; if(t)return t->ZZds.ZZnodes.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void nodes_LinkedList1::setTail(Layout* p,Node* c,int check){
    Node *pp,*tail;

    tail=p->ZZds.ZZnodes.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZnodes.next; pp; pp=pp->ZZds.ZZnodes.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("nodes warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZnodes.tail=c;
}

void nodes_LinkedList1Iterator::start(const Layout *p){
    nodes_Ring1Iterator::start(p->ZZds.ZZnodes.tail); 
}

Node* nodes_LinkedList1Iterator::fromHead(Layout *p){
    return nodes_Ring1Iterator::fromHead(p->ZZds.ZZnodes.tail); 
}
