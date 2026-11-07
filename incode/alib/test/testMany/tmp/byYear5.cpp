class Took; // relation
class Student; // entity1
class Course; // entity2
class Year; // entity3
                          
void byYear_3XtoX::add(Took *r,Student *e1,Course *e2,Year *e3){ // equivalent of addTail()
    Took *head;

    if(r->ZZds.ZZbyYear.next3){
        printf("byYear.add() error: element=%d already in byYear\n",r);
        return;
    }
    if(e3->ZZds.ZZbyYear.tail3){
        head=e3->ZZds.ZZbyYear.tail3->ZZds.ZZbyYear.next3;
        r->ZZds.ZZbyYear.next3=head; e3->ZZds.ZZbyYear.tail3->ZZds.ZZbyYear.next3=r;
        r->ZZds.ZZbyYear.prev3=e3->ZZds.ZZbyYear.tail3; head->ZZds.ZZbyYear.prev3=r;
    }
    else {e3->ZZds.ZZbyYear.tail3=r->ZZds.ZZbyYear.next3=r->ZZds.ZZbyYear.prev3=r;}

    byYear_2XtoX::add(r,e1,e2);
    e3->ZZds.ZZbyYear.tail3=r;
    r->ZZds.ZZbyYear.parent3=e3;
}

void byYear_3XtoX::remove(Took *r){
    Took *prv,*nxt; Year *par;

    nxt=r->ZZds.ZZbyYear.next3;
    prv=r->ZZds.ZZbyYear.prev3;
    par=r->ZZds.ZZbyYear.parent3;
    if(nxt==NULL || prv==NULL || par==NULL){
        printf("byYear:remove() error: node=%d not on the list\n",r); return;
    }

    byYear_2XtoX::remove(r);

    if(r==nxt)par->ZZds.ZZbyYear.tail3=NULL;
    else {
        if(r==par->ZZds.ZZbyYear.tail3)par->ZZds.ZZbyYear.tail3=prv;
        prv->ZZds.ZZbyYear.next3=nxt;
        nxt->ZZds.ZZbyYear.prev3=prv;
    }
    r->ZZds.ZZbyYear.next3=r->ZZds.ZZbyYear.prev3=NULL;
    r->ZZds.ZZbyYear.parent3=NULL;
}

Year* const byYear_3XtoX::entity3(Took *r){return r->ZZds.ZZbyYear.parent3;}

Took* const byYear_3XtoX::next3(Took *r){   // returns NULL when s is the tail
    Year *p3;
    p3=r->ZZds.ZZbyYear.parent3;
    if(!r || !p3)return NULL;
    if(r==p3->ZZds.ZZbyYear.tail3)return NULL;
    return r->ZZds.ZZbyYear.next3;
}
    

Took* const byYear_3XtoX::prev3(Took *r){   // returns NULL when s is the head
    Year *p3; Took *prv;
    p3=r->ZZds.ZZbyYear.parent3;
    if(!r || !p3)return NULL;
    prv=r->ZZds.ZZbyYear.prev3;
    if(prv==p3->ZZds.ZZbyYear.tail3)return NULL;
    return prv;
}

Took* byYear_3XtoXIterator::from3(Year *e){
    Took *ret;

    tail3=e->ZZds.ZZbyYear.tail3;
    if(!tail3)return NULL;
    ret=tail3->ZZds.ZZbyYear.next3;
    if(ret==tail3)nxt3=tail3=NULL; 
    else nxt3=ret->ZZds.ZZbyYear.next3;
    return ret;
}

Took* const byYear_3XtoXIterator::next3(){
    Took *r;

    r=nxt3;
    if(r==tail3)nxt3=tail3=NULL; else nxt3=r->ZZds.ZZbyYear.next3;
    return r;
}
