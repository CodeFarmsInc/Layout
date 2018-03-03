// --------------------------------------------------------
class Node;
class Member;

Member* members_LinkedList1::tail(Node *p){return p->ZZds.ZZmembers.tail;}

Member* members_LinkedList1::head(Node *p){
    if(!(p->ZZds.ZZmembers.tail) || !(p->ZZds.ZZmembers.tail->ZZds.ZZmembers.next))return NULL;
    else return p->ZZds.ZZmembers.tail->ZZds.ZZmembers.next;
}

void members_LinkedList1::addHead(Node *p, Member *c){
    p->ZZds.ZZmembers.tail=members_Ring1::addHead(p->ZZds.ZZmembers.tail,c);
}

void members_LinkedList1::addTail(Node *p, Member *c){
    p->ZZds.ZZmembers.tail=members_Ring1::addTail(p->ZZds.ZZmembers.tail,c);
}

void members_LinkedList1::append(Node *p,Member *c1, Member *c2){
    p->ZZds.ZZmembers.tail=members_Ring1::append(p->ZZds.ZZmembers.tail,c1,c2);
}

void members_LinkedList1::remove(Node *p, Member *c){
    p->ZZds.ZZmembers.tail=members_Ring1::remove(p->ZZds.ZZmembers.tail,c);
}

Member* const members_LinkedList1::next(Node *p,Member *c){
    return members_Ring1::next(p->ZZds.ZZmembers.tail,c);
}

Member* const members_LinkedList1::nextRing(Member *c){ return members_Ring1::nextRing(c);}

void members_LinkedList1::sort(ZZsortFun cmpFun, Node *p){
    p->ZZds.ZZmembers.tail=members_Ring1::sort(cmpFun,p->ZZds.ZZmembers.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void members_LinkedList1::merge(Member *s,Member *t,Node *p){
    Member *pp,*tail; int merge;
 
    tail=p->ZZds.ZZmembers.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZmembers.next; pp; pp=pp->ZZds.ZZmembers.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("members error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZmembers.next; pp; pp=pp->ZZds.ZZmembers.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("members error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    members_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZmembers.tail=NULL; else p->ZZds.ZZmembers.tail=t;
}

Member* members_LinkedList1::child(Node *p){
    Member* t;
    t=p->ZZds.ZZmembers.tail; if(t)return t->ZZds.ZZmembers.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void members_LinkedList1::setTail(Node* p,Member* c,int check){
    Member *pp,*tail;

    tail=p->ZZds.ZZmembers.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZmembers.next; pp; pp=pp->ZZds.ZZmembers.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("members warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZmembers.tail=c;
}

void members_LinkedList1Iterator::start(const Node *p){
    members_Ring1Iterator::start(p->ZZds.ZZmembers.tail); 
}

Member* members_LinkedList1Iterator::fromHead(Node *p){
    return members_Ring1Iterator::fromHead(p->ZZds.ZZmembers.tail); 
}
