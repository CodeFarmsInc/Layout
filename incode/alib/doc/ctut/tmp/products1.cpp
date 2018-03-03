// --------------------------------------------------------
class Company;
class Product;

Product* products_LinkedList1::tail(Company *p){return p->ZZds.ZZproducts.tail;}

Product* products_LinkedList1::head(Company *p){
    if(!(p->ZZds.ZZproducts.tail) || !(p->ZZds.ZZproducts.tail->ZZds.ZZproducts.next))return NULL;
    else return p->ZZds.ZZproducts.tail->ZZds.ZZproducts.next;
}

void products_LinkedList1::addHead(Company *p, Product *c){
    p->ZZds.ZZproducts.tail=products_Ring1::addHead(p->ZZds.ZZproducts.tail,c);
}

void products_LinkedList1::addTail(Company *p, Product *c){
    p->ZZds.ZZproducts.tail=products_Ring1::addTail(p->ZZds.ZZproducts.tail,c);
}

void products_LinkedList1::append(Company *p,Product *c1, Product *c2){
    p->ZZds.ZZproducts.tail=products_Ring1::append(p->ZZds.ZZproducts.tail,c1,c2);
}

void products_LinkedList1::remove(Company *p, Product *c){
    p->ZZds.ZZproducts.tail=products_Ring1::remove(p->ZZds.ZZproducts.tail,c);
}

Product* const products_LinkedList1::next(Company *p,Product *c){
    return products_Ring1::next(p->ZZds.ZZproducts.tail,c);
}

Product* const products_LinkedList1::fwd(Product *c){ return products_Ring1::fwd(c);}

void products_LinkedList1::sort(ZZsortFun cmpFun, Company *p){
    p->ZZds.ZZproducts.tail=products_Ring1::sort(cmpFun,p->ZZds.ZZproducts.tail);
}

// ---------------------------------------------------------------
// This function either merges two lists (if s and t are on different lists)
// or splits a list (if s and t are on the same list).
//
// When merging lists, p must be a parent of t, and will be set p->tail=NULL.
// When splitting a list, p must be an empty list holder (p->tail==NULL)
// and will be set p->tail=t.
// ---------------------------------------------------------------
void products_LinkedList1::merge(Product *s,Product *t,Company *p){
    Product *pp,*tail; int merge;
 
    tail=p->ZZds.ZZproducts.tail;
    if(tail==NULL)merge=0; else merge=1; // 0=splitting
    if(merge){
        // check that t is child of p
        for(pp=t->ZZds.ZZproducts.next; pp; pp=pp->ZZds.ZZproducts.next){
            if(pp==tail)break;
            if(pp==t)pp=NULL;
        }
        if(!pp){
            printf("products error in merge(): merging, inconsistent input\n    ");
            printf("p is not the parent of t\n");
        }
    }
    else {
        // check that s and t are on the same list
        for(pp=s->ZZds.ZZproducts.next; pp; pp=pp->ZZds.ZZproducts.next){
            if(pp==t)break;
            if(pp==s)pp=NULL;
        }
        if(!pp){
            printf("products error in merge(): splitting, inconsistent input\n    ");
            printf("p has not children but s and t are not in the same list\n");
        }
    }
    
    products_Ring1::merge(s,t); 
    if(merge)p->ZZds.ZZproducts.tail=NULL; else p->ZZds.ZZproducts.tail=t;
}

Product* products_LinkedList1::child(Company *p){
    Product* t;
    t=p->ZZds.ZZproducts.tail; if(t)return t->ZZds.ZZproducts.next; return NULL;
}

// ------------------------------------------------------------------
// check=1 checks for consistency,
// check=0 is fast but a mistake can cause a hard-to-find error
// ------------------------------------------------------------------
void products_LinkedList1::setTail(Company* p,Product* c,int check){
    Product *pp,*tail;

    tail=p->ZZds.ZZproducts.tail; 
    if(check && tail){
        for(pp=tail->ZZds.ZZproducts.next; pp; pp=pp->ZZds.ZZproducts.next){
            if(pp==c || pp==tail)break;
        }
        if(pp!=c){
            printf("products warning: setTail() for a wrong set of children,");
            printf(" nothing done\n");
            return;
        }
    }
    p->ZZds.ZZproducts.tail=c;
}

void products_LinkedList1Iterator::start(const Company *p){
    products_Ring1Iterator::start(p->ZZds.ZZproducts.tail); 
}

Product* products_LinkedList1Iterator::fromHead(Company *p){
    return products_Ring1Iterator::fromHead(p->ZZds.ZZproducts.tail); 
}
