// --------------------------------------------------------
class Layout;
class Group;

Group* groups_LinkedList1::tail(Layout *p){return p->ZZds.ZZgroups.tail;}

Group* groups_LinkedList1::head(Layout *p){
    if(!(p->ZZds.ZZgroups.tail) || !(p->ZZds.ZZgroups.tail->ZZds.ZZgroups.next))return NULL;
    else return p->ZZds.ZZgroups.tail->ZZds.ZZgroups.next;
}

void groups_LinkedList1::addHead(Layout *p, Group *c){
    p->ZZds.ZZgroups.tail=groups_Ring1::addHead(p->ZZds.ZZgroups.tail,c);
}

void groups_LinkedList1::addTail(Layout *p, Group *c){
    p->ZZds.ZZgroups.tail=groups_Ring1::addTail(p->ZZds.ZZgroups.tail,c);
}

void groups_LinkedList1::append(Layout *p,Group *c1, Group *c2){
    p->ZZds.ZZgroups.tail=groups_Ring1::append(p->ZZds.ZZgroups.tail,c1,c2);
}

void groups_LinkedList1::remove(Layout *p, Group *c){
    p->ZZds.ZZgroups.tail=groups_Ring1::remove(p->ZZds.ZZgroups.tail,c);
}

Group* const groups_LinkedList1::next(Layout *p,Group *c){
    return groups_Ring1::next(p->ZZds.ZZgroups.tail,c);
}

Group* const groups_LinkedList1::nextRing(Group *c){ return groups_Ring1::nextRing(c);}

void groups_LinkedList1::sort(ZZsortFun cmpFun, Layout *p){
    p->ZZds.ZZgroups.tail=groups_Ring1::sort(cmpFun,p->ZZds.ZZgroups.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void groups_LinkedList1::merge(Group *s,Group *t,Layout *p){
    Group *pp,*tail; int merge;
 
    tail=p->ZZds.ZZgroups.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZgroups.next; pp; pp=pp->ZZds.ZZgroups.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("groups error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZgroups.next; pp; pp=pp->ZZds.ZZgroups.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("groups error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    groups_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZgroups.tail=NULL; else p->ZZds.ZZgroups.tail=t;
}

Group* groups_LinkedList1::child(Layout *p){
    Group* t;
    t=p->ZZds.ZZgroups.tail; if(t)return t->ZZds.ZZgroups.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void groups_LinkedList1::setTail(Layout* p,Group* c,int check){
    Group *pp,*tail;

    tail=p->ZZds.ZZgroups.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZgroups.next; pp; pp=pp->ZZds.ZZgroups.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("groups warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZgroups.tail=c;
}

void groups_LinkedList1Iterator::start(const Layout *p){
    groups_Ring1Iterator::start(p->ZZds.ZZgroups.tail); 
}

Group* groups_LinkedList1Iterator::fromHead(Layout *p){
    return groups_Ring1Iterator::fromHead(p->ZZds.ZZgroups.tail); 
}
