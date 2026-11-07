// --------------------------------------------------------
class Department;
class Employee;

Employee* eList_LinkedList1::tail(Department *p){return p->ZZds.ZZeList.tail;}

Employee* eList_LinkedList1::head(Department *p){
    if(!(p->ZZds.ZZeList.tail) || !(p->ZZds.ZZeList.tail->ZZds.ZZeList.next))return NULL;
    else return p->ZZds.ZZeList.tail->ZZds.ZZeList.next;
}

void eList_LinkedList1::addHead(Department *p, Employee *c){
    p->ZZds.ZZeList.tail=eList_Ring1::addHead(p->ZZds.ZZeList.tail,c);
}

void eList_LinkedList1::addTail(Department *p, Employee *c){
    p->ZZds.ZZeList.tail=eList_Ring1::addTail(p->ZZds.ZZeList.tail,c);
}

void eList_LinkedList1::append(Department *p,Employee *c1, Employee *c2){
    p->ZZds.ZZeList.tail=eList_Ring1::append(p->ZZds.ZZeList.tail,c1,c2);
}

void eList_LinkedList1::remove(Department *p, Employee *c){
    p->ZZds.ZZeList.tail=eList_Ring1::remove(p->ZZds.ZZeList.tail,c);
}

Employee* const eList_LinkedList1::next(Department *p,Employee *c){
    return eList_Ring1::next(p->ZZds.ZZeList.tail,c);
}

Employee* const eList_LinkedList1::nextRing(Employee *c){ return eList_Ring1::nextRing(c);}

void eList_LinkedList1::sort(ZZsortFun cmpFun, Department *p){
    p->ZZds.ZZeList.tail=eList_Ring1::sort(cmpFun,p->ZZds.ZZeList.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void eList_LinkedList1::merge(Employee *s,Employee *t,Department *p){
    Employee *pp,*tail; int merge;
 
    tail=p->ZZds.ZZeList.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZeList.next; pp; pp=pp->ZZds.ZZeList.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("eList error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZeList.next; pp; pp=pp->ZZds.ZZeList.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("eList error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    eList_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZeList.tail=NULL; else p->ZZds.ZZeList.tail=t;
}

Employee* eList_LinkedList1::child(Department *p){
    Employee* t;
    t=p->ZZds.ZZeList.tail; if(t)return t->ZZds.ZZeList.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void eList_LinkedList1::setTail(Department* p,Employee* c,int check){
    Employee *pp,*tail;

    tail=p->ZZds.ZZeList.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZeList.next; pp; pp=pp->ZZds.ZZeList.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("eList warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZeList.tail=c;
}

void eList_LinkedList1Iterator::start(const Department *p){
    eList_Ring1Iterator::start(p->ZZds.ZZeList.tail); 
}

Employee* eList_LinkedList1Iterator::fromHead(Department *p){
    return eList_Ring1Iterator::fromHead(p->ZZds.ZZeList.tail); 
}
