// --------------------------------------------------------
class Student;
class Mark;

Mark* const marks_LinkedList2::tail(Student *p){return p->ZZds.ZZmarks.tail;}

Mark* const marks_LinkedList2::head(Student *p){
    if(!(p->ZZds.ZZmarks.tail) || !(p->ZZds.ZZmarks.tail->ZZds.ZZmarks.next))return NULL;
    else return p->ZZds.ZZmarks.tail->ZZds.ZZmarks.next;
}

void marks_LinkedList2::addHead(Student *p, Mark *c){
    p->ZZds.ZZmarks.tail=marks_Ring2::addHead(p->ZZds.ZZmarks.tail,c);
}

void marks_LinkedList2::addTail(Student *p, Mark *c){
    p->ZZds.ZZmarks.tail=marks_Ring2::addTail(p->ZZds.ZZmarks.tail,c);
}

void marks_LinkedList2::append(Student *p,Mark *c1, Mark *c2){
    p->ZZds.ZZmarks.tail=marks_Ring2::append(p->ZZds.ZZmarks.tail,c1,c2);
}

void marks_LinkedList2::insert(Mark *c1, Mark *c2){marks_Ring2::insert(c1,c2);}

void marks_LinkedList2::sort(ZZsortFun cmpFun, Student *p){
    p->ZZds.ZZmarks.tail=marks_Ring2::sort(cmpFun,p->ZZds.ZZmarks.tail);
}

void marks_LinkedList2::remove(Student *p, Mark *c){
    p->ZZds.ZZmarks.tail=marks_Ring2::remove(p->ZZds.ZZmarks.tail,c);
}

Mark* const marks_LinkedList2::next(Student *p,Mark *c){ 
                               return marks_Ring2::next(p->ZZds.ZZmarks.tail,c);}

Mark* const marks_LinkedList2::prev(Student *p,Mark *c){ 
                               return marks_Ring2::prev(p->ZZds.ZZmarks.tail,c);}

Mark* const marks_LinkedList2::nextRing(Mark *c){ return marks_Ring2::nextRing(c);}

Mark* const marks_LinkedList2::prevRing(Mark *c){ return marks_Ring2::prevRing(c);}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void marks_LinkedList2::merge(Mark *s,Mark *t,Student *p){
    Mark *pp,*tail; int merge;
 
    tail=p->ZZds.ZZmarks.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZmarks.next; pp; pp=pp->ZZds.ZZmarks.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("marks error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZmarks.next; pp; pp=pp->ZZds.ZZmarks.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("marks error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    marks_Ring2::merge(s,t); 
    if(merge)p->ZZds.ZZmarks.tail=NULL; else p->ZZds.ZZmarks.tail=t;
}

Mark* marks_LinkedList2::child(Student *p){
    Mark* t;
    t=p->ZZds.ZZmarks.tail; if(t)return t->ZZds.ZZmarks.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void marks_LinkedList2::setTail(Student* p,Mark* c,int check){
    Mark *pp,*tail;

    tail=p->ZZds.ZZmarks.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZmarks.next; pp; pp=pp->ZZds.ZZmarks.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("marks warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZmarks.tail=c;
}

void marks_LinkedList2Iterator::start(const Student *p){
    marks_Ring2Iterator::start(p->ZZds.ZZmarks.tail);
}

Mark* marks_LinkedList2Iterator::fromHead(Student *p){
    return marks_Ring2Iterator::fromHead(p->ZZds.ZZmarks.tail); 
}

Mark* marks_LinkedList2Iterator::fromTail(Student *p){
    return marks_Ring2Iterator::fromTail(p->ZZds.ZZmarks.tail); 
}
