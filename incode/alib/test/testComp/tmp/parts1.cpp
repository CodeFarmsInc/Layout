// --------------------------------------------------------
class Picture;
class Graphics;

Graphics* parts_LinkedList1::tail(Picture *p){return p->ZZds.ZZparts.tail;}

Graphics* parts_LinkedList1::head(Picture *p){
    if(!(p->ZZds.ZZparts.tail) || !(p->ZZds.ZZparts.tail->ZZds.ZZparts.next))return NULL;
    else return p->ZZds.ZZparts.tail->ZZds.ZZparts.next;
}

void parts_LinkedList1::addHead(Picture *p, Graphics *c){
    p->ZZds.ZZparts.tail=parts_Ring1::addHead(p->ZZds.ZZparts.tail,c);
}

void parts_LinkedList1::addTail(Picture *p, Graphics *c){
    p->ZZds.ZZparts.tail=parts_Ring1::addTail(p->ZZds.ZZparts.tail,c);
}

void parts_LinkedList1::append(Picture *p,Graphics *c1, Graphics *c2){
    p->ZZds.ZZparts.tail=parts_Ring1::append(p->ZZds.ZZparts.tail,c1,c2);
}

void parts_LinkedList1::remove(Picture *p, Graphics *c){
    p->ZZds.ZZparts.tail=parts_Ring1::remove(p->ZZds.ZZparts.tail,c);
}

Graphics* const parts_LinkedList1::next(Picture *p,Graphics *c){
    return parts_Ring1::next(p->ZZds.ZZparts.tail,c);
}

Graphics* const parts_LinkedList1::nextRing(Graphics *c){ return parts_Ring1::nextRing(c);}

void parts_LinkedList1::sort(ZZsortFun cmpFun, Picture *p){
    p->ZZds.ZZparts.tail=parts_Ring1::sort(cmpFun,p->ZZds.ZZparts.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void parts_LinkedList1::merge(Graphics *s,Graphics *t,Picture *p){
    Graphics *pp,*tail; int merge;
 
    tail=p->ZZds.ZZparts.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZparts.next; pp; pp=pp->ZZds.ZZparts.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("parts error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZparts.next; pp; pp=pp->ZZds.ZZparts.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("parts error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    parts_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZparts.tail=NULL; else p->ZZds.ZZparts.tail=t;
}

Graphics* parts_LinkedList1::child(Picture *p){
    Graphics* t;
    t=p->ZZds.ZZparts.tail; if(t)return t->ZZds.ZZparts.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void parts_LinkedList1::setTail(Picture* p,Graphics* c,int check){
    Graphics *pp,*tail;

    tail=p->ZZds.ZZparts.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZparts.next; pp; pp=pp->ZZds.ZZparts.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("parts warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZparts.tail=c;
}

void parts_LinkedList1Iterator::start(const Picture *p){
    parts_Ring1Iterator::start(p->ZZds.ZZparts.tail); 
}

Graphics* parts_LinkedList1Iterator::fromHead(Picture *p){
    return parts_Ring1Iterator::fromHead(p->ZZds.ZZparts.tail); 
}
