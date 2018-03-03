class $1; // relation
class $2; // entity1
class $3; // entity2
class $4; // entity3
                          
void $$_3XtoX::add($1 *r,$2 *e1,$3 *e2,$4 *e3){ // equivalent of addTail()
    $1 *head;

    if(r->$0.next3){
        printf("$$.add() error: element=%d already in $$\n",r);
        return;
    }
    if(e3->$0.tail3){
        head=e3->$0.tail3->$0.next3;
        r->$0.next3=head; e3->$0.tail3->$0.next3=r;
        r->$0.prev3=e3->$0.tail3; head->$0.prev3=r;
    }
    else {e3->$0.tail3=r->$0.next3=r->$0.prev3=r;}

    $$_2XtoX::add(r,e1,e2);
    e3->$0.tail3=r;
    r->$0.parent3=e3;
}

void $$_3XtoX::remove($1 *r){
    $1 *prv,*nxt; $4 *par;

    nxt=r->$0.next3;
    prv=r->$0.prev3;
    par=r->$0.parent3;
    if(nxt==NULL || prv==NULL || par==NULL){
        printf("$$:remove() error: node=%d not on the list\n",r); return;
    }

    $$_2XtoX::remove(r);

    if(r==nxt)par->$0.tail3=NULL;
    else {
        if(r==par->$0.tail3)par->$0.tail3=prv;
        prv->$0.next3=nxt;
        nxt->$0.prev3=prv;
    }
    r->$0.next3=r->$0.prev3=NULL;
    r->$0.parent3=NULL;
}

$4* const $$_3XtoX::entity3($1 *r){return r->$0.parent3;}

$1* const $$_3XtoX::next3($1 *r){   // returns NULL when s is the tail
    $4 *p3;
    p3=r->$0.parent3;
    if(!r || !p3)return NULL;
    if(r==p3->$0.tail3)return NULL;
    return r->$0.next3;
}
    

$1* const $$_3XtoX::prev3($1 *r){   // returns NULL when s is the head
    $4 *p3; $1 *prv;
    p3=r->$0.parent3;
    if(!r || !p3)return NULL;
    prv=r->$0.prev3;
    if(prv==p3->$0.tail3)return NULL;
    return prv;
}

$1* $$_3XtoXIterator::from3($4 *e){
    $1 *ret;

    tail3=e->$0.tail3;
    if(!tail3)return NULL;
    ret=tail3->$0.next3;
    if(ret==tail3)nxt3=tail3=NULL; 
    else nxt3=ret->$0.next3;
    return ret;
}

$1* const $$_3XtoXIterator::next3(){
    $1 *r;

    r=nxt3;
    if(r==tail3)nxt3=tail3=NULL; else nxt3=r->$0.next3;
    return r;
}
