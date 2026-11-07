// --------------------------------------------------------
class Node;
class Name;

Name* names_LinkedList1::tail(Node *p){return p->ZZds.ZZnames.tail;}

Name* names_LinkedList1::head(Node *p){
    if(!(p->ZZds.ZZnames.tail) || !(p->ZZds.ZZnames.tail->ZZds.ZZnames.next))return NULL;
    else return p->ZZds.ZZnames.tail->ZZds.ZZnames.next;
}

void names_LinkedList1::addHead(Node *p, Name *c){
    p->ZZds.ZZnames.tail=names_Ring1::addHead(p->ZZds.ZZnames.tail,c);
}

void names_LinkedList1::addTail(Node *p, Name *c){
    p->ZZds.ZZnames.tail=names_Ring1::addTail(p->ZZds.ZZnames.tail,c);
}

void names_LinkedList1::append(Node *p,Name *c1, Name *c2){
    p->ZZds.ZZnames.tail=names_Ring1::append(p->ZZds.ZZnames.tail,c1,c2);
}

void names_LinkedList1::remove(Node *p, Name *c){
    p->ZZds.ZZnames.tail=names_Ring1::remove(p->ZZds.ZZnames.tail,c);
}

Name* const names_LinkedList1::next(Node *p,Name *c){
    return names_Ring1::next(p->ZZds.ZZnames.tail,c);
}

Name* const names_LinkedList1::nextRing(Name *c){ return names_Ring1::nextRing(c);}

void names_LinkedList1::sort(ZZsortFun cmpFun, Node *p){
    p->ZZds.ZZnames.tail=names_Ring1::sort(cmpFun,p->ZZds.ZZnames.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void names_LinkedList1::merge(Name *s,Name *t,Node *p){
    Name *pp,*tail; int merge;
 
    tail=p->ZZds.ZZnames.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZnames.next; pp; pp=pp->ZZds.ZZnames.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("names error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZnames.next; pp; pp=pp->ZZds.ZZnames.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("names error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    names_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZnames.tail=NULL; else p->ZZds.ZZnames.tail=t;
}

Name* names_LinkedList1::child(Node *p){
    Name* t;
    t=p->ZZds.ZZnames.tail; if(t)return t->ZZds.ZZnames.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void names_LinkedList1::setTail(Node* p,Name* c,int check){
    Name *pp,*tail;

    tail=p->ZZds.ZZnames.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZnames.next; pp; pp=pp->ZZds.ZZnames.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("names warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZnames.tail=c;
}

void names_LinkedList1Iterator::start(const Node *p){
    names_Ring1Iterator::start(p->ZZds.ZZnames.tail); 
}

Name* names_LinkedList1Iterator::fromHead(Node *p){
    return names_Ring1Iterator::fromHead(p->ZZds.ZZnames.tail); 
}
