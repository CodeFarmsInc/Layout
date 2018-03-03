// --------------------------------------------------------
class Organization;
class Iterator;

Iterator* const iters_LinkedList::next(Organization *p, Iterator *c){
    Iterator* ret=c->ZZds.ZZiters.next;
    if(ret==p->ZZds.ZZiters.tail)ret=NULL;
    return ret;
}

void iters_LinkedList::addHead(Organization *p, Iterator *c){
    Iterator* tail=p->ZZds.ZZiters.tail;
    if(c->ZZds.ZZiters.next){
        printf("iters.addHead() error: Child=%d already in a LinkedList\n",c);
        return;
    }
    if(tail){c->ZZds.ZZiters.next=tail->ZZds.ZZiters.next; tail->ZZds.ZZiters.next=c;}
    else        {p->ZZds.ZZiters.tail=c; c->ZZds.ZZiters.next=c;}
}
                          
void iters_LinkedList::addTail(Organization *p, Iterator *c){
    if(c->ZZds.ZZiters.next){
        printf("iters.addTail() error: Child=%d already in a LinkedList\n",c);
        return;
    }
    addHead(p,c);
    p->ZZds.ZZiters.tail=c;
}
                          
                          
// append Child c2 after Child c1
void iters_LinkedList::append(Organization *p,Iterator *c1, Iterator *c2){
    Iterator *x;

    if(c1->ZZds.ZZiters.next==NULL){
        printf("iters.append() error: Child=%d not in a LinkedList\n",c1);
        return;
    }
    if(c2->ZZds.ZZiters.next){
        printf("iters.append() error: Child=%d already in a LinkedList\n",c2);
        return;
    }
    for(x=p->ZZds.ZZiters.tail; x; ){
        if(x==c1)break;
        x=x->ZZds.ZZiters.next;
        if(x==p->ZZds.ZZiters.tail)x=NULL;
    }
    if(!x){
        printf("iters:append() error: child c1 not under parent=%d\n",p);
        return;
    }
    c2->ZZds.ZZiters.next=c1->ZZds.ZZiters.next;
    c1->ZZds.ZZiters.next=c2;
    if(p->ZZds.ZZiters.tail==c1)p->ZZds.ZZiters.tail=c2;
}
                          
                          
void iters_LinkedList::remove(Organization *p, Iterator *c){
    Iterator *x,*nxt;

    for(x=p->ZZds.ZZiters.tail, nxt=NULL; x; x=nxt){
        nxt=x->ZZds.ZZiters.next;
        if(nxt==c)break;
        if(x==p->ZZds.ZZiters.tail)nxt=NULL;
    }
    if(!x){
        printf("iters:remove() error: Child=%d not under parent=%d\n",c,p);
        return;
    }
    x->ZZds.ZZiters.next=c->ZZds.ZZiters.next;
    if(p->ZZds.ZZiters.tail==c)p->ZZds.ZZiters.tail=x;
    c->ZZds.ZZiters.next=NULL;
}
                          

void iters_LinkedListIterator::start(const Organization *p){ 
    if(p){tail=p->ZZds.ZZiters.tail; if(tail)nxt=tail->ZZds.ZZiters.next; else nxt=NULL;}
    else {tail=nxt=NULL; }
}


Iterator* const iters_LinkedListIterator::operator++(){ 
    Iterator *c;

    c=nxt;
    if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZiters.next;
    return(c);
}
