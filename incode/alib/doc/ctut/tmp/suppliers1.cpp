// --------------------------------------------------------
class Company;
class Supplier;

Supplier* suppliers_LinkedList1::tail(Company *p){return p->ZZds.ZZsuppliers.tail;}

Supplier* suppliers_LinkedList1::head(Company *p){
    if(!(p->ZZds.ZZsuppliers.tail) || !(p->ZZds.ZZsuppliers.tail->ZZds.ZZsuppliers.next))return NULL;
    else return p->ZZds.ZZsuppliers.tail->ZZds.ZZsuppliers.next;
}

void suppliers_LinkedList1::addHead(Company *p, Supplier *c){
    p->ZZds.ZZsuppliers.tail=suppliers_Ring1::addHead(p->ZZds.ZZsuppliers.tail,c);
}

void suppliers_LinkedList1::addTail(Company *p, Supplier *c){
    p->ZZds.ZZsuppliers.tail=suppliers_Ring1::addTail(p->ZZds.ZZsuppliers.tail,c);
}

void suppliers_LinkedList1::append(Company *p,Supplier *c1, Supplier *c2){
    p->ZZds.ZZsuppliers.tail=suppliers_Ring1::append(p->ZZds.ZZsuppliers.tail,c1,c2);
}

void suppliers_LinkedList1::remove(Company *p, Supplier *c){
    p->ZZds.ZZsuppliers.tail=suppliers_Ring1::remove(p->ZZds.ZZsuppliers.tail,c);
}

Supplier* const suppliers_LinkedList1::next(Company *p,Supplier *c){
    return suppliers_Ring1::next(p->ZZds.ZZsuppliers.tail,c);
}

Supplier* const suppliers_LinkedList1::fwd(Supplier *c){ return suppliers_Ring1::fwd(c);}

void suppliers_LinkedList1::sort(ZZsortFun cmpFun, Company *p){
    p->ZZds.ZZsuppliers.tail=suppliers_Ring1::sort(cmpFun,p->ZZds.ZZsuppliers.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void suppliers_LinkedList1::merge(Supplier *s,Supplier *t,Company *p){
    Supplier *pp,*tail; int merge;
 
    tail=p->ZZds.ZZsuppliers.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZsuppliers.next; pp; pp=pp->ZZds.ZZsuppliers.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("suppliers error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZsuppliers.next; pp; pp=pp->ZZds.ZZsuppliers.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("suppliers error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    suppliers_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZsuppliers.tail=NULL; else p->ZZds.ZZsuppliers.tail=t;
}

Supplier* suppliers_LinkedList1::child(Company *p){
    Supplier* t;
    t=p->ZZds.ZZsuppliers.tail; if(t)return t->ZZds.ZZsuppliers.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void suppliers_LinkedList1::setTail(Company* p,Supplier* c,int check){
    Supplier *pp,*tail;

    tail=p->ZZds.ZZsuppliers.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZsuppliers.next; pp; pp=pp->ZZds.ZZsuppliers.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("suppliers warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZsuppliers.tail=c;
}

void suppliers_LinkedList1Iterator::start(const Company *p){
    suppliers_Ring1Iterator::start(p->ZZds.ZZsuppliers.tail); 
}

Supplier* suppliers_LinkedList1Iterator::fromHead(Company *p){
    return suppliers_Ring1Iterator::fromHead(p->ZZds.ZZsuppliers.tail); 
}
