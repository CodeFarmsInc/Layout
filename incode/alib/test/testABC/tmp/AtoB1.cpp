// --------------------------------------------------------
class A;
class B;

B* const AtoB_LinkedList2::tail(A *p){return p->ZZds.ZZAtoB.tail;}

B* const AtoB_LinkedList2::head(A *p){
    if(!(p->ZZds.ZZAtoB.tail) || !(p->ZZds.ZZAtoB.tail->ZZds.ZZAtoB.next))return NULL;
    else return p->ZZds.ZZAtoB.tail->ZZds.ZZAtoB.next;
}

void AtoB_LinkedList2::addHead(A *p, B *c){
    p->ZZds.ZZAtoB.tail=AtoB_Ring2::addHead(p->ZZds.ZZAtoB.tail,c);
}

void AtoB_LinkedList2::addTail(A *p, B *c){
    p->ZZds.ZZAtoB.tail=AtoB_Ring2::addTail(p->ZZds.ZZAtoB.tail,c);
}

void AtoB_LinkedList2::append(A *p,B *c1, B *c2){
    p->ZZds.ZZAtoB.tail=AtoB_Ring2::append(p->ZZds.ZZAtoB.tail,c1,c2);
}

void AtoB_LinkedList2::insert(B *c1, B *c2){AtoB_Ring2::insert(c1,c2);}

void AtoB_LinkedList2::sort(ZZsortFun cmpFun, A *p){
    p->ZZds.ZZAtoB.tail=AtoB_Ring2::sort(cmpFun,p->ZZds.ZZAtoB.tail);
}

void AtoB_LinkedList2::remove(A *p, B *c){
    p->ZZds.ZZAtoB.tail=AtoB_Ring2::remove(p->ZZds.ZZAtoB.tail,c);
}

B* const AtoB_LinkedList2::next(A *p,B *c){ 
                               return AtoB_Ring2::next(p->ZZds.ZZAtoB.tail,c);}

B* const AtoB_LinkedList2::prev(A *p,B *c){ 
                               return AtoB_Ring2::prev(p->ZZds.ZZAtoB.tail,c);}

B* const AtoB_LinkedList2::nextRing(B *c){ return AtoB_Ring2::nextRing(c);}

B* const AtoB_LinkedList2::prevRing(B *c){ return AtoB_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void AtoB_LinkedList2::merge(B *s,B *t,A *p){
    B *pp,*tail; int merge;
 
    tail=p->ZZds.ZZAtoB.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZAtoB.next; pp; pp=pp->ZZds.ZZAtoB.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("AtoB error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZAtoB.next; pp; pp=pp->ZZds.ZZAtoB.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("AtoB error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    AtoB_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZAtoB.tail=NULL; else p->ZZds.ZZAtoB.tail=t;
}

B* AtoB_LinkedList2::child(A *p){
    B* t;
    t=p->ZZds.ZZAtoB.tail; if(t)return t->ZZds.ZZAtoB.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void AtoB_LinkedList2::setTail(A* p,B* c,int check){
    B *pp,*tail;

    tail=p->ZZds.ZZAtoB.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZAtoB.next; pp; pp=pp->ZZds.ZZAtoB.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("AtoB warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZAtoB.tail=c;
}

void AtoB_LinkedList2Iterator::start(const A *p){
    AtoB_Ring2Iterator::start(p->ZZds.ZZAtoB.tail);
}

B* AtoB_LinkedList2Iterator::fromHead(A *p){
    return AtoB_Ring2Iterator::fromHead(p->ZZds.ZZAtoB.tail); 
}

B* AtoB_LinkedList2Iterator::fromTail(A *p){
    return AtoB_Ring2Iterator::fromTail(p->ZZds.ZZAtoB.tail); 
}
