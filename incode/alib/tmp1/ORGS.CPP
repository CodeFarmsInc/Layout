// --------------------------------------------------------
class Generator;
class Organization;

Organization* const orgs_LinkedList::next(Generator *p, Organization *c){
    Organization* ret=c->ZZds.ZZorgs.next;
    if(ret==p->ZZds.ZZorgs.tail)ret=NULL;
    return ret;
}

void orgs_LinkedList::addHead(Generator *p, Organization *c){
    Organization* tail=p->ZZds.ZZorgs.tail;
    if(c->ZZds.ZZorgs.next){
        printf("orgs.addHead() error: Child=%d already in a LinkedList\n",c);
        return;
    }
    if(tail){c->ZZds.ZZorgs.next=tail->ZZds.ZZorgs.next; tail->ZZds.ZZorgs.next=c;}
    else        {p->ZZds.ZZorgs.tail=c; c->ZZds.ZZorgs.next=c;}
}
                          
void orgs_LinkedList::addTail(Generator *p, Organization *c){
    if(c->ZZds.ZZorgs.next){
        printf("orgs.addTail() error: Child=%d already in a LinkedList\n",c);
        return;
    }
    addHead(p,c);
    p->ZZds.ZZorgs.tail=c;
}
                          
                          
// append Child c2 after Child c1
void orgs_LinkedList::append(Generator *p,Organization *c1, Organization *c2){
    Organization *x;

    if(c1->ZZds.ZZorgs.next==NULL){
        printf("orgs.append() error: Child=%d not in a LinkedList\n",c1);
        return;
    }
    if(c2->ZZds.ZZorgs.next){
        printf("orgs.append() error: Child=%d already in a LinkedList\n",c2);
        return;
    }
    for(x=p->ZZds.ZZorgs.tail; x; ){
        if(x==c1)break;
        x=x->ZZds.ZZorgs.next;
        if(x==p->ZZds.ZZorgs.tail)x=NULL;
    }
    if(!x){
        printf("orgs:append() error: child c1 not under parent=%d\n",p);
        return;
    }
    c2->ZZds.ZZorgs.next=c1->ZZds.ZZorgs.next;
    c1->ZZds.ZZorgs.next=c2;
    if(p->ZZds.ZZorgs.tail==c1)p->ZZds.ZZorgs.tail=c2;
}
                          
                          
void orgs_LinkedList::remove(Generator *p, Organization *c){
    Organization *x,*nxt;

    for(x=p->ZZds.ZZorgs.tail, nxt=NULL; x; x=nxt){
        nxt=x->ZZds.ZZorgs.next;
        if(nxt==c)break;
        if(x==p->ZZds.ZZorgs.tail)nxt=NULL;
    }
    if(!x){
        printf("orgs:remove() error: Child=%d not under parent=%d\n",c,p);
        return;
    }
    x->ZZds.ZZorgs.next=c->ZZds.ZZorgs.next;
    if(p->ZZds.ZZorgs.tail==c)p->ZZds.ZZorgs.tail=x;
    c->ZZds.ZZorgs.next=NULL;
}
                          

void orgs_LinkedListIterator::start(const Generator *p){ 
    if(p){tail=p->ZZds.ZZorgs.tail; if(tail)nxt=tail->ZZds.ZZorgs.next; else nxt=NULL;}
    else {tail=nxt=NULL; }
}


Organization* const orgs_LinkedListIterator::operator++(){ 
    Organization *c;

    c=nxt;
    if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZorgs.next;
    return(c);
}
