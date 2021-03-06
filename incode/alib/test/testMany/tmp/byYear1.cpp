// --------------------------------------------------------
class Student;
class Took;

Took* const byYear_LinkedList2::tail(Student *p){return p->ZZds.ZZbyYear.tail;}

Took* const byYear_LinkedList2::head(Student *p){
    if(!(p->ZZds.ZZbyYear.tail) || !(p->ZZds.ZZbyYear.tail->ZZds.ZZbyYear.next))return NULL;
    else return p->ZZds.ZZbyYear.tail->ZZds.ZZbyYear.next;
}

void byYear_LinkedList2::addHead(Student *p, Took *c){
    p->ZZds.ZZbyYear.tail=byYear_Ring2::addHead(p->ZZds.ZZbyYear.tail,c);
}

void byYear_LinkedList2::addTail(Student *p, Took *c){
    p->ZZds.ZZbyYear.tail=byYear_Ring2::addTail(p->ZZds.ZZbyYear.tail,c);
}

void byYear_LinkedList2::append(Student *p,Took *c1, Took *c2){
    p->ZZds.ZZbyYear.tail=byYear_Ring2::append(p->ZZds.ZZbyYear.tail,c1,c2);
}

void byYear_LinkedList2::insert(Took *c1, Took *c2){byYear_Ring2::insert(c1,c2);}

void byYear_LinkedList2::sort(ZZsortFun cmpFun, Student *p){
    p->ZZds.ZZbyYear.tail=byYear_Ring2::sort(cmpFun,p->ZZds.ZZbyYear.tail);
}

void byYear_LinkedList2::remove(Student *p, Took *c){
    p->ZZds.ZZbyYear.tail=byYear_Ring2::remove(p->ZZds.ZZbyYear.tail,c);
}

Took* const byYear_LinkedList2::next(Student *p,Took *c){ 
                               return byYear_Ring2::next(p->ZZds.ZZbyYear.tail,c);}

Took* const byYear_LinkedList2::prev(Student *p,Took *c){ 
                               return byYear_Ring2::prev(p->ZZds.ZZbyYear.tail,c);}

Took* const byYear_LinkedList2::nextRing(Took *c){ return byYear_Ring2::nextRing(c);}

Took* const byYear_LinkedList2::prevRing(Took *c){ return byYear_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void byYear_LinkedList2::merge(Took *s,Took *t,Student *p){
    Took *pp,*tail; int merge;
 
    tail=p->ZZds.ZZbyYear.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZbyYear.next; pp; pp=pp->ZZds.ZZbyYear.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("byYear error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZbyYear.next; pp; pp=pp->ZZds.ZZbyYear.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("byYear error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    byYear_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZbyYear.tail=NULL; else p->ZZds.ZZbyYear.tail=t;
}

Took* byYear_LinkedList2::child(Student *p){
    Took* t;
    t=p->ZZds.ZZbyYear.tail; if(t)return t->ZZds.ZZbyYear.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void byYear_LinkedList2::setTail(Student* p,Took* c,int check){
    Took *pp,*tail;

    tail=p->ZZds.ZZbyYear.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZbyYear.next; pp; pp=pp->ZZds.ZZbyYear.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("byYear warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZbyYear.tail=c;
}

void byYear_LinkedList2Iterator::start(const Student *p){
    byYear_Ring2Iterator::start(p->ZZds.ZZbyYear.tail);
}

Took* byYear_LinkedList2Iterator::fromHead(Student *p){
    return byYear_Ring2Iterator::fromHead(p->ZZds.ZZbyYear.tail); 
}

Took* byYear_LinkedList2Iterator::fromTail(Student *p){
    return byYear_Ring2Iterator::fromTail(p->ZZds.ZZbyYear.tail); 
}
