class Took; // relation
class Student; // entity1
class Course; // entity2
                          
void byYear_2XtoX::add(Took *r,Student *e1,Course *e2){ // equivalent of addTail()
    Took *head;

    byYear_1XtoX::add(r,e1);

    if(r->ZZds.ZZbyYear.next2){
        printf("byYear.add() error: element=%d already in byYear\n",r);
        return;
    }
    if(e2->ZZds.ZZbyYear.tail2){
        head=e2->ZZds.ZZbyYear.tail2->ZZds.ZZbyYear.next2;
        r->ZZds.ZZbyYear.next2=head; e2->ZZds.ZZbyYear.tail2->ZZds.ZZbyYear.next2=r;
        r->ZZds.ZZbyYear.prev2=e2->ZZds.ZZbyYear.tail2; head->ZZds.ZZbyYear.prev2=r;
    }
    else {e2->ZZds.ZZbyYear.tail2=r->ZZds.ZZbyYear.next2=r->ZZds.ZZbyYear.prev2=r;}

    e2->ZZds.ZZbyYear.tail2=r;
    r->ZZds.ZZbyYear.parent2=e2;
}

void byYear_2XtoX::remove(Took *r){
    Took *prv,*nxt; Course *par;

    byYear_1XtoX::remove(r);

    nxt=r->ZZds.ZZbyYear.next2;
    prv=r->ZZds.ZZbyYear.prev2;
    par=r->ZZds.ZZbyYear.parent2;
    if(nxt==NULL || prv==NULL || par==NULL){
        printf("byYear:remove() error: node=%d not on the list\n",r); return;
    }

    if(r==nxt)par->ZZds.ZZbyYear.tail2=NULL;
    else {
        if(r==par->ZZds.ZZbyYear.tail2)par->ZZds.ZZbyYear.tail2=prv;
        prv->ZZds.ZZbyYear.next2=nxt;
        nxt->ZZds.ZZbyYear.prev2=prv;
    }
    r->ZZds.ZZbyYear.next2=r->ZZds.ZZbyYear.prev2=NULL;
    r->ZZds.ZZbyYear.parent2=NULL;
}

Course* const byYear_2XtoX::entity2(Took *r){return r->ZZds.ZZbyYear.parent2;}

Took* const byYear_2XtoX::next2(Took *r){   // returns NULL when s is the tail
    Course *p2;
    p2=r->ZZds.ZZbyYear.parent2;
    if(!r || !p2)return NULL;
    if(r==p2->ZZds.ZZbyYear.tail2)return NULL;
    return r->ZZds.ZZbyYear.next2;
}
    

Took* const byYear_2XtoX::prev2(Took *r){   // returns NULL when s is the head
    Course *p2; Took *prv;
    p2=r->ZZds.ZZbyYear.parent2;
    if(!r || !p2)return NULL;
    prv=r->ZZds.ZZbyYear.prev2;
    if(prv==p2->ZZds.ZZbyYear.tail2)return NULL;
    return prv;
}

Took* byYear_2XtoXIterator::from2(Course *e){
    Took *ret;

    tail2=e->ZZds.ZZbyYear.tail2;
    if(!tail2)return NULL;
    ret=tail2->ZZds.ZZbyYear.next2;
    if(ret==tail2)nxt2=tail2=NULL; 
    else nxt2=ret->ZZds.ZZbyYear.next2;
    return ret;
}

Took* const byYear_2XtoXIterator::next2(){
    Took *r;

    r=nxt2;
    if(r==tail2)nxt2=tail2=NULL; else nxt2=r->ZZds.ZZbyYear.next2;
    return r;
}
