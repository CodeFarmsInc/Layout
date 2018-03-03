// --------------------------------------------------------
class Department;
class Department;

Department* dHier_LinkedList1::tail(Department *p){return p->ZZds.ZZdHier.tail;}

Department* dHier_LinkedList1::head(Department *p){
    if(!(p->ZZds.ZZdHier.tail) || !(p->ZZds.ZZdHier.tail->ZZds.ZZdHier.next))return NULL;
    else return p->ZZds.ZZdHier.tail->ZZds.ZZdHier.next;
}

void dHier_LinkedList1::addHead(Department *p, Department *c){
    p->ZZds.ZZdHier.tail=dHier_Ring1::addHead(p->ZZds.ZZdHier.tail,c);
}

void dHier_LinkedList1::addTail(Department *p, Department *c){
    p->ZZds.ZZdHier.tail=dHier_Ring1::addTail(p->ZZds.ZZdHier.tail,c);
}

void dHier_LinkedList1::append(Department *p,Department *c1, Department *c2){
    p->ZZds.ZZdHier.tail=dHier_Ring1::append(p->ZZds.ZZdHier.tail,c1,c2);
}

void dHier_LinkedList1::remove(Department *p, Department *c){
    p->ZZds.ZZdHier.tail=dHier_Ring1::remove(p->ZZds.ZZdHier.tail,c);
}

Department* const dHier_LinkedList1::next(Department *p,Department *c){
    return dHier_Ring1::next(p->ZZds.ZZdHier.tail,c);
}

Department* const dHier_LinkedList1::fwd(Department *c){ return dHier_Ring1::fwd(c);}

void dHier_LinkedList1::sort(ZZsortFun cmpFun, Department *p){
    p->ZZds.ZZdHier.tail=dHier_Ring1::sort(cmpFun,p->ZZds.ZZdHier.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void dHier_LinkedList1::merge(Department *s,Department *t,Department *p){
    Department *pp,*tail; int merge;
 
    tail=p->ZZds.ZZdHier.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZdHier.next; pp; pp=pp->ZZds.ZZdHier.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("dHier error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZdHier.next; pp; pp=pp->ZZds.ZZdHier.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("dHier error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    dHier_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZdHier.tail=NULL; else p->ZZds.ZZdHier.tail=t;
}

Department* dHier_LinkedList1::child(Department *p){
    Department* t;
    t=p->ZZds.ZZdHier.tail; if(t)return t->ZZds.ZZdHier.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void dHier_LinkedList1::setTail(Department* p,Department* c,int check){
    Department *pp,*tail;

    tail=p->ZZds.ZZdHier.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZdHier.next; pp; pp=pp->ZZds.ZZdHier.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("dHier warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZdHier.tail=c;
}

void dHier_LinkedList1Iterator::start(const Department *p){
    dHier_Ring1Iterator::start(p->ZZds.ZZdHier.tail); 
}

Department* dHier_LinkedList1Iterator::fromHead(Department *p){
    return dHier_Ring1Iterator::fromHead(p->ZZds.ZZdHier.tail); 
}
