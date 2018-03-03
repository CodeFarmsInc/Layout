// --------------------------------------------------------
class Department;
class Employee;

Employee* empl_LinkedList1::tail(Department *p){return p->ZZds.ZZempl.tail;}

Employee* empl_LinkedList1::head(Department *p){
    if(!(p->ZZds.ZZempl.tail) || !(p->ZZds.ZZempl.tail->ZZds.ZZempl.next))return NULL;
    else return p->ZZds.ZZempl.tail->ZZds.ZZempl.next;
}

void empl_LinkedList1::addHead(Department *p, Employee *c){
    p->ZZds.ZZempl.tail=empl_Ring1::addHead(p->ZZds.ZZempl.tail,c);
}

void empl_LinkedList1::addTail(Department *p, Employee *c){
    p->ZZds.ZZempl.tail=empl_Ring1::addTail(p->ZZds.ZZempl.tail,c);
}

void empl_LinkedList1::append(Department *p,Employee *c1, Employee *c2){
    p->ZZds.ZZempl.tail=empl_Ring1::append(p->ZZds.ZZempl.tail,c1,c2);
}

void empl_LinkedList1::remove(Department *p, Employee *c){
    p->ZZds.ZZempl.tail=empl_Ring1::remove(p->ZZds.ZZempl.tail,c);
}

Employee* const empl_LinkedList1::next(Department *p,Employee *c){
    return empl_Ring1::next(p->ZZds.ZZempl.tail,c);
}

Employee* const empl_LinkedList1::fwd(Employee *c){ return empl_Ring1::fwd(c);}

void empl_LinkedList1::sort(ZZsortFun cmpFun, Department *p){
    p->ZZds.ZZempl.tail=empl_Ring1::sort(cmpFun,p->ZZds.ZZempl.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void empl_LinkedList1::merge(Employee *s,Employee *t,Department *p){
    Employee *pp,*tail; int merge;
 
    tail=p->ZZds.ZZempl.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZempl.next; pp; pp=pp->ZZds.ZZempl.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("empl error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZempl.next; pp; pp=pp->ZZds.ZZempl.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("empl error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    empl_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZempl.tail=NULL; else p->ZZds.ZZempl.tail=t;
}

Employee* empl_LinkedList1::child(Department *p){
    Employee* t;
    t=p->ZZds.ZZempl.tail; if(t)return t->ZZds.ZZempl.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void empl_LinkedList1::setTail(Department* p,Employee* c,int check){
    Employee *pp,*tail;

    tail=p->ZZds.ZZempl.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZempl.next; pp; pp=pp->ZZds.ZZempl.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("empl warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZempl.tail=c;
}

void empl_LinkedList1Iterator::start(const Department *p){
    empl_Ring1Iterator::start(p->ZZds.ZZempl.tail); 
}

Employee* empl_LinkedList1Iterator::fromHead(Department *p){
    return empl_Ring1Iterator::fromHead(p->ZZds.ZZempl.tail); 
}
