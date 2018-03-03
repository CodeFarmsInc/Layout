class Takes; // relation
class Student; // entity1
class Course; // entity2
                          
void takes_2XtoX::add(Takes *r,Student *e1,Course *e2){ // equivalent of addTail()
    Takes *head;

    takes_1XtoX::add(r,e1);

    if(r->ZZds.ZZtakes.next2){
        printf("takes.add() error: element=%d already in takes\n",r);
        return;
    }
    if(e2->ZZds.ZZtakes.tail2){
        head=e2->ZZds.ZZtakes.tail2->ZZds.ZZtakes.next2;
        r->ZZds.ZZtakes.next2=head; e2->ZZds.ZZtakes.tail2->ZZds.ZZtakes.next2=r;
        r->ZZds.ZZtakes.prev2=e2->ZZds.ZZtakes.tail2; head->ZZds.ZZtakes.prev2=r;
    }
    else {e2->ZZds.ZZtakes.tail2=r->ZZds.ZZtakes.next2=r->ZZds.ZZtakes.prev2=r;}

    e2->ZZds.ZZtakes.tail2=r;
    r->ZZds.ZZtakes.parent2=e2;
}

void takes_2XtoX::remove(Takes *r){
    Takes *prv,*nxt; Course *par;

    takes_1XtoX::remove(r);

    nxt=r->ZZds.ZZtakes.next2;
    prv=r->ZZds.ZZtakes.prev2;
    par=r->ZZds.ZZtakes.parent2;
    if(nxt==NULL || prv==NULL || par==NULL){
        printf("takes:remove() error: node=%d not on the list\n",r); return;
    }

    if(r==nxt)par->ZZds.ZZtakes.tail2=NULL;
    else {
        if(r==par->ZZds.ZZtakes.tail2)par->ZZds.ZZtakes.tail2=prv;
        prv->ZZds.ZZtakes.next2=nxt;
        nxt->ZZds.ZZtakes.prev2=prv;
    }
    r->ZZds.ZZtakes.next2=r->ZZds.ZZtakes.prev2=NULL;
    r->ZZds.ZZtakes.parent2=NULL;
}

Course* const takes_2XtoX::entity2(Takes *r){return r->ZZds.ZZtakes.parent2;}

Takes* const takes_2XtoX::next2(Takes *r){   // returns NULL when s is the tail
    Course *p2;
    p2=r->ZZds.ZZtakes.parent2;
    if(!r || !p2)return NULL;
    if(r==p2->ZZds.ZZtakes.tail2)return NULL;
    return r->ZZds.ZZtakes.next2;
}
    

Takes* const takes_2XtoX::prev2(Takes *r){   // returns NULL when s is the head
    Course *p2; Takes *prv;
    p2=r->ZZds.ZZtakes.parent2;
    if(!r || !p2)return NULL;
    prv=r->ZZds.ZZtakes.prev2;
    if(prv==p2->ZZds.ZZtakes.tail2)return NULL;
    return prv;
}

Takes* takes_2XtoXIterator::from2(Course *e){
    Takes *ret;

    tail2=e->ZZds.ZZtakes.tail2;
    if(!tail2)return NULL;
    ret=tail2->ZZds.ZZtakes.next2;
    if(ret==tail2)nxt2=tail2=NULL; 
    else nxt2=ret->ZZds.ZZtakes.next2;
    return ret;
}

Takes* const takes_2XtoXIterator::next2(){
    Takes *r;

    r=nxt2;
    if(r==tail2)nxt2=tail2=NULL; else nxt2=r->ZZds.ZZtakes.next2;
    return r;
}
