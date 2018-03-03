// --------------------------------------------------------
class Organization;
class Participant;

Participant* const parts_LinkedList::next(Organization *p, Participant *c){
    Participant* ret=c->ZZds.ZZparts.next;
    if(ret==p->ZZds.ZZparts.tail)ret=NULL;
    return ret;
}

void parts_LinkedList::addHead(Organization *p, Participant *c){
    Participant* tail=p->ZZds.ZZparts.tail;
    if(c->ZZds.ZZparts.next){
        printf("parts.addHead() error: Child=%d already in a LinkedList\n",c);
        return;
    }
    if(tail){c->ZZds.ZZparts.next=tail->ZZds.ZZparts.next; tail->ZZds.ZZparts.next=c;}
    else        {p->ZZds.ZZparts.tail=c; c->ZZds.ZZparts.next=c;}
}
                          
void parts_LinkedList::addTail(Organization *p, Participant *c){
    if(c->ZZds.ZZparts.next){
        printf("parts.addTail() error: Child=%d already in a LinkedList\n",c);
        return;
    }
    addHead(p,c);
    p->ZZds.ZZparts.tail=c;
}
                          
                          
// append Child c2 after Child c1
void parts_LinkedList::append(Organization *p,Participant *c1, Participant *c2){
    Participant *x;

    if(c1->ZZds.ZZparts.next==NULL){
        printf("parts.append() error: Child=%d not in a LinkedList\n",c1);
        return;
    }
    if(c2->ZZds.ZZparts.next){
        printf("parts.append() error: Child=%d already in a LinkedList\n",c2);
        return;
    }
    for(x=p->ZZds.ZZparts.tail; x; ){
        if(x==c1)break;
        x=x->ZZds.ZZparts.next;
        if(x==p->ZZds.ZZparts.tail)x=NULL;
    }
    if(!x){
        printf("parts:append() error: child c1 not under parent=%d\n",p);
        return;
    }
    c2->ZZds.ZZparts.next=c1->ZZds.ZZparts.next;
    c1->ZZds.ZZparts.next=c2;
    if(p->ZZds.ZZparts.tail==c1)p->ZZds.ZZparts.tail=c2;
}
                          
                          
void parts_LinkedList::remove(Organization *p, Participant *c){
    Participant *x,*nxt;

    for(x=p->ZZds.ZZparts.tail, nxt=NULL; x; x=nxt){
        nxt=x->ZZds.ZZparts.next;
        if(nxt==c)break;
        if(x==p->ZZds.ZZparts.tail)nxt=NULL;
    }
    if(!x){
        printf("parts:remove() error: Child=%d not under parent=%d\n",c,p);
        return;
    }
    x->ZZds.ZZparts.next=c->ZZds.ZZparts.next;
    if(p->ZZds.ZZparts.tail==c)p->ZZds.ZZparts.tail=x;
    c->ZZds.ZZparts.next=NULL;
}
                          

void parts_LinkedListIterator::start(const Organization *p){ 
    if(p){tail=p->ZZds.ZZparts.tail; if(tail)nxt=tail->ZZds.ZZparts.next; else nxt=NULL;}
    else {tail=nxt=NULL; }
}


Participant* const parts_LinkedListIterator::operator++(){ 
    Participant *c;

    c=nxt;
    if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZparts.next;
    return(c);
}
