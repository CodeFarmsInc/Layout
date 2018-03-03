// --------------------------------------------------------
class $1;
class $2;

$2* $$_LinkedList1::tail($1 *p){return p->$0.tail;}

$2* $$_LinkedList1::head($1 *p){
    if(!(p->$0.tail) || !(p->$0.tail->$0.next))return NULL;
    else return p->$0.tail->$0.next;
}

void $$_LinkedList1::addHead($1 *p, $2 *c){
    p->$0.tail=$$_Ring1::addHead(p->$0.tail,c);
}

void $$_LinkedList1::addTail($1 *p, $2 *c){
    p->$0.tail=$$_Ring1::addTail(p->$0.tail,c);
}

void $$_LinkedList1::append($1 *p,$2 *c1, $2 *c2){
    p->$0.tail=$$_Ring1::append(p->$0.tail,c1,c2);
}

void $$_LinkedList1::remove($1 *p, $2 *c){
    p->$0.tail=$$_Ring1::remove(p->$0.tail,c);
}

$2* const $$_LinkedList1::next($1 *p,$2 *c){
    return $$_Ring1::next(p->$0.tail,c);
}

$2* const $$_LinkedList1::nextRing($2 *c){ return $$_Ring1::nextRing(c);}

void $$_LinkedList1::sort(ZZsortFun cmpFun, $1 *p){
    p->$0.tail=$$_Ring1::sort(cmpFun,p->$0.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void $$_LinkedList1::merge($2 *s,$2 *t,$1 *p){
    $2 *pp,*tail; int merge;
 
    tail=p->$0.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->$0.next; pp; pp=pp->$0.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("$$ error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->$0.next; pp; pp=pp->$0.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("$$ error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    $$_Ring1::merge(s,t); 
    if(merge)p->$0.tail=NULL; else p->$0.tail=t;
}

$2* $$_LinkedList1::child($1 *p){
    $2* t;
    t=p->$0.tail; if(t)return t->$0.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void $$_LinkedList1::setTail($1* p,$2* c,int check){
    $2 *pp,*tail;

    tail=p->$0.tail; 
    if(check && tail){
        for(pp=tail->$0.next; pp; pp=pp->$0.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("$$ warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->$0.tail=c;
}

void $$_LinkedList1Iterator::start(const $1 *p){
    $$_Ring1Iterator::start(p->$0.tail); 
}

$2* $$_LinkedList1Iterator::fromHead($1 *p){
    return $$_Ring1Iterator::fromHead(p->$0.tail); 
}
