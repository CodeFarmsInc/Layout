class $1; // relation
class $2; // entity1
class $3; // entity2
                          
void $$_2XtoX::add($1 *r,$2 *e1,$3 *e2){ // equivalent of addTail()
    $1 *head;

    $$_1XtoX::add(r,e1);

    if(r->$0.next2){
        printf("$$.add() error: element=%d already in $$\n",r);
        return;
    }
    if(e2->$0.tail2){
        head=e2->$0.tail2->$0.next2;
        r->$0.next2=head; e2->$0.tail2->$0.next2=r;
        r->$0.prev2=e2->$0.tail2; head->$0.prev2=r;
    }
    else {e2->$0.tail2=r->$0.next2=r->$0.prev2=r;}

    e2->$0.tail2=r;
    r->$0.parent2=e2;
}

void $$_2XtoX::remove($1 *r){
    $1 *prv,*nxt; $3 *par;

    $$_1XtoX::remove(r);

    nxt=r->$0.next2;
    prv=r->$0.prev2;
    par=r->$0.parent2;
    if(nxt==NULL || prv==NULL || par==NULL){
        printf("$$:remove() error: node=%d not on the list\n",r); return;
    }

    if(r==nxt)par->$0.tail2=NULL;
    else {
        if(r==par->$0.tail2)par->$0.tail2=prv;
        prv->$0.next2=nxt;
        nxt->$0.prev2=prv;
    }
    r->$0.next2=r->$0.prev2=NULL;
    r->$0.parent2=NULL;
}

$3* const $$_2XtoX::entity2($1 *r){return r->$0.parent2;}

$1* const $$_2XtoX::next2($1 *r){   // returns NULL when s is the tail
    $3 *p2;
    p2=r->$0.parent2;
    if(!r || !p2)return NULL;
    if(r==p2->$0.tail2)return NULL;
    return r->$0.next2;
}
    

$1* const $$_2XtoX::prev2($1 *r){   // returns NULL when s is the head
    $3 *p2; $1 *prv;
    p2=r->$0.parent2;
    if(!r || !p2)return NULL;
    prv=r->$0.prev2;
    if(prv==p2->$0.tail2)return NULL;
    return prv;
}

$1* $$_2XtoXIterator::from2($3 *e){
    $1 *ret;

    tail2=e->$0.tail2;
    if(!tail2)return NULL;
    ret=tail2->$0.next2;
    if(ret==tail2)nxt2=tail2=NULL; 
    else nxt2=ret->$0.next2;
    return ret;
}

$1* const $$_2XtoXIterator::next2(){
    $1 *r;

    r=nxt2;
    if(r==tail2)nxt2=tail2=NULL; else nxt2=r->$0.next2;
    return r;
}
