// --------------------------------------------------------
class ApplClass;
class ClassLink;

ClassLink* dependsOn_LinkedList1::tail(ApplClass *p){return p->ZZds.ZZdependsOn.tail;}

ClassLink* dependsOn_LinkedList1::head(ApplClass *p){
    if(!(p->ZZds.ZZdependsOn.tail) || !(p->ZZds.ZZdependsOn.tail->ZZds.ZZdependsOn.next))return NULL;
    else return p->ZZds.ZZdependsOn.tail->ZZds.ZZdependsOn.next;
}

void dependsOn_LinkedList1::addHead(ApplClass *p, ClassLink *c){
    p->ZZds.ZZdependsOn.tail=dependsOn_Ring1::addHead(p->ZZds.ZZdependsOn.tail,c);
}

void dependsOn_LinkedList1::addTail(ApplClass *p, ClassLink *c){
    p->ZZds.ZZdependsOn.tail=dependsOn_Ring1::addTail(p->ZZds.ZZdependsOn.tail,c);
}

void dependsOn_LinkedList1::append(ApplClass *p,ClassLink *c1, ClassLink *c2){
    p->ZZds.ZZdependsOn.tail=dependsOn_Ring1::append(p->ZZds.ZZdependsOn.tail,c1,c2);
}

void dependsOn_LinkedList1::remove(ApplClass *p, ClassLink *c){
    p->ZZds.ZZdependsOn.tail=dependsOn_Ring1::remove(p->ZZds.ZZdependsOn.tail,c);
}

ClassLink* const dependsOn_LinkedList1::next(ApplClass *p,ClassLink *c){
    return dependsOn_Ring1::next(p->ZZds.ZZdependsOn.tail,c);
}

ClassLink* const dependsOn_LinkedList1::nextRing(ClassLink *c){ return dependsOn_Ring1::nextRing(c);}

void dependsOn_LinkedList1::sort(ZZsortFun cmpFun, ApplClass *p){
    p->ZZds.ZZdependsOn.tail=dependsOn_Ring1::sort(cmpFun,p->ZZds.ZZdependsOn.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void dependsOn_LinkedList1::merge(ClassLink *s,ClassLink *t,ApplClass *p){
    ClassLink *pp,*tail; int merge;
 
    tail=p->ZZds.ZZdependsOn.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZdependsOn.next; pp; pp=pp->ZZds.ZZdependsOn.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("dependsOn error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZdependsOn.next; pp; pp=pp->ZZds.ZZdependsOn.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("dependsOn error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    dependsOn_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZdependsOn.tail=NULL; else p->ZZds.ZZdependsOn.tail=t;
}

ClassLink* dependsOn_LinkedList1::child(ApplClass *p){
    ClassLink* t;
    t=p->ZZds.ZZdependsOn.tail; if(t)return t->ZZds.ZZdependsOn.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void dependsOn_LinkedList1::setTail(ApplClass* p,ClassLink* c,int check){
    ClassLink *pp,*tail;

    tail=p->ZZds.ZZdependsOn.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZdependsOn.next; pp; pp=pp->ZZds.ZZdependsOn.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("dependsOn warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZdependsOn.tail=c;
}

void dependsOn_LinkedList1Iterator::start(const ApplClass *p){
    dependsOn_Ring1Iterator::start(p->ZZds.ZZdependsOn.tail); 
}

ClassLink* dependsOn_LinkedList1Iterator::fromHead(ApplClass *p){
    return dependsOn_Ring1Iterator::fromHead(p->ZZds.ZZdependsOn.tail); 
}
