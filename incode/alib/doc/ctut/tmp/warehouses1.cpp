// --------------------------------------------------------
class Company;
class Warehouse;

Warehouse* warehouses_LinkedList1::tail(Company *p){return p->ZZds.ZZwarehouses.tail;}

Warehouse* warehouses_LinkedList1::head(Company *p){
    if(!(p->ZZds.ZZwarehouses.tail) || !(p->ZZds.ZZwarehouses.tail->ZZds.ZZwarehouses.next))return NULL;
    else return p->ZZds.ZZwarehouses.tail->ZZds.ZZwarehouses.next;
}

void warehouses_LinkedList1::addHead(Company *p, Warehouse *c){
    p->ZZds.ZZwarehouses.tail=warehouses_Ring1::addHead(p->ZZds.ZZwarehouses.tail,c);
}

void warehouses_LinkedList1::addTail(Company *p, Warehouse *c){
    p->ZZds.ZZwarehouses.tail=warehouses_Ring1::addTail(p->ZZds.ZZwarehouses.tail,c);
}

void warehouses_LinkedList1::append(Company *p,Warehouse *c1, Warehouse *c2){
    p->ZZds.ZZwarehouses.tail=warehouses_Ring1::append(p->ZZds.ZZwarehouses.tail,c1,c2);
}

void warehouses_LinkedList1::remove(Company *p, Warehouse *c){
    p->ZZds.ZZwarehouses.tail=warehouses_Ring1::remove(p->ZZds.ZZwarehouses.tail,c);
}

Warehouse* const warehouses_LinkedList1::next(Company *p,Warehouse *c){
    return warehouses_Ring1::next(p->ZZds.ZZwarehouses.tail,c);
}

Warehouse* const warehouses_LinkedList1::fwd(Warehouse *c){ return warehouses_Ring1::fwd(c);}

void warehouses_LinkedList1::sort(ZZsortFun cmpFun, Company *p){
    p->ZZds.ZZwarehouses.tail=warehouses_Ring1::sort(cmpFun,p->ZZds.ZZwarehouses.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void warehouses_LinkedList1::merge(Warehouse *s,Warehouse *t,Company *p){
    Warehouse *pp,*tail; int merge;
 
    tail=p->ZZds.ZZwarehouses.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZwarehouses.next; pp; pp=pp->ZZds.ZZwarehouses.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("warehouses error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZwarehouses.next; pp; pp=pp->ZZds.ZZwarehouses.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("warehouses error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    warehouses_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZwarehouses.tail=NULL; else p->ZZds.ZZwarehouses.tail=t;
}

Warehouse* warehouses_LinkedList1::child(Company *p){
    Warehouse* t;
    t=p->ZZds.ZZwarehouses.tail; if(t)return t->ZZds.ZZwarehouses.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void warehouses_LinkedList1::setTail(Company* p,Warehouse* c,int check){
    Warehouse *pp,*tail;

    tail=p->ZZds.ZZwarehouses.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZwarehouses.next; pp; pp=pp->ZZds.ZZwarehouses.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("warehouses warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZwarehouses.tail=c;
}

void warehouses_LinkedList1Iterator::start(const Company *p){
    warehouses_Ring1Iterator::start(p->ZZds.ZZwarehouses.tail); 
}

Warehouse* warehouses_LinkedList1Iterator::fromHead(Company *p){
    return warehouses_Ring1Iterator::fromHead(p->ZZds.ZZwarehouses.tail); 
}
