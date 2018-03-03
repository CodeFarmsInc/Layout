// --------------------------------------------------------
class OrgType;
class FixedType;

FixedType* fixedTypes_LinkedList1::tail(OrgType *p){return p->ZZds.ZZfixedTypes.tail;}

FixedType* fixedTypes_LinkedList1::head(OrgType *p){
    if(!(p->ZZds.ZZfixedTypes.tail) || !(p->ZZds.ZZfixedTypes.tail->ZZds.ZZfixedTypes.next))return NULL;
    else return p->ZZds.ZZfixedTypes.tail->ZZds.ZZfixedTypes.next;
}

void fixedTypes_LinkedList1::addHead(OrgType *p, FixedType *c){
    p->ZZds.ZZfixedTypes.tail=fixedTypes_Ring1::addHead(p->ZZds.ZZfixedTypes.tail,c);
}

void fixedTypes_LinkedList1::addTail(OrgType *p, FixedType *c){
    p->ZZds.ZZfixedTypes.tail=fixedTypes_Ring1::addTail(p->ZZds.ZZfixedTypes.tail,c);
}

void fixedTypes_LinkedList1::append(OrgType *p,FixedType *c1, FixedType *c2){
    p->ZZds.ZZfixedTypes.tail=fixedTypes_Ring1::append(p->ZZds.ZZfixedTypes.tail,c1,c2);
}

void fixedTypes_LinkedList1::remove(OrgType *p, FixedType *c){
    p->ZZds.ZZfixedTypes.tail=fixedTypes_Ring1::remove(p->ZZds.ZZfixedTypes.tail,c);
}

FixedType* const fixedTypes_LinkedList1::next(OrgType *p,FixedType *c){
    return fixedTypes_Ring1::next(p->ZZds.ZZfixedTypes.tail,c);
}

FixedType* const fixedTypes_LinkedList1::nextRing(FixedType *c){ return fixedTypes_Ring1::nextRing(c);}

void fixedTypes_LinkedList1::sort(ZZsortFun cmpFun, OrgType *p){
    p->ZZds.ZZfixedTypes.tail=fixedTypes_Ring1::sort(cmpFun,p->ZZds.ZZfixedTypes.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void fixedTypes_LinkedList1::merge(FixedType *s,FixedType *t,OrgType *p){
    FixedType *pp,*tail; int merge;
 
    tail=p->ZZds.ZZfixedTypes.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZfixedTypes.next; pp; pp=pp->ZZds.ZZfixedTypes.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("fixedTypes error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZfixedTypes.next; pp; pp=pp->ZZds.ZZfixedTypes.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("fixedTypes error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    fixedTypes_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZfixedTypes.tail=NULL; else p->ZZds.ZZfixedTypes.tail=t;
}

FixedType* fixedTypes_LinkedList1::child(OrgType *p){
    FixedType* t;
    t=p->ZZds.ZZfixedTypes.tail; if(t)return t->ZZds.ZZfixedTypes.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void fixedTypes_LinkedList1::setTail(OrgType* p,FixedType* c,int check){
    FixedType *pp,*tail;

    tail=p->ZZds.ZZfixedTypes.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZfixedTypes.next; pp; pp=pp->ZZds.ZZfixedTypes.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("fixedTypes warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZfixedTypes.tail=c;
}

void fixedTypes_LinkedList1Iterator::start(const OrgType *p){
    fixedTypes_Ring1Iterator::start(p->ZZds.ZZfixedTypes.tail); 
}

FixedType* fixedTypes_LinkedList1Iterator::fromHead(OrgType *p){
    return fixedTypes_Ring1Iterator::fromHead(p->ZZds.ZZfixedTypes.tail); 
}
