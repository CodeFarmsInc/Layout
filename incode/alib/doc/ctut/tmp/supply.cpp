// --------------------------------------------------------

int supply_Ring2::debugFun(PartType *tail){
    PartType *p,*nxt,*head; int h,t,ret;
    supply_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZsupply.next;
        if(nxt->ZZds.ZZsupply.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZsupply.prev!=tail || tail->ZZds.ZZsupply.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZsupply.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZsupply.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZsupply.prev!=tail || tail->ZZds.ZZsupply.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

PartType* const supply_Ring2::next(PartType *tail, PartType *c){
    PartType* ret=c->ZZds.ZZsupply.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

PartType* const supply_Ring2::prev(PartType *tail, PartType *c){
    PartType* ret=c->ZZds.ZZsupply.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

PartType* const supply_Ring2::fwd(PartType *c){
    return c->ZZds.ZZsupply.next;
}

PartType* const supply_Ring2::bwd(PartType *c){
    return c->ZZds.ZZsupply.prev;
}

PartType* supply_Ring2::addHead(PartType *tail, PartType *c){
    PartType *head;

    if(c->ZZds.ZZsupply.next){
        printf("supply.addHead() error: element=%d already in supply\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZsupply.next;
        c->ZZds.ZZsupply.next=head; tail->ZZds.ZZsupply.next=c;
        c->ZZds.ZZsupply.prev=tail; head->ZZds.ZZsupply.prev=c;
    }
    else {tail=c->ZZds.ZZsupply.next=c->ZZds.ZZsupply.prev=c;}
    return tail; 
}
                          
PartType* supply_Ring2::addTail(PartType *tail, PartType *c){
    if(c->ZZds.ZZsupply.next){
        printf("supply.addTail() error: element=%d already in supply\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
PartType* supply_Ring2::append(PartType *tail,PartType *c1, PartType *c2){
    PartType *nxt;

    if(c1->ZZds.ZZsupply.next==NULL){
        printf("supply.append() error: element=%d not in supply\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZsupply.next){
        printf("supply.append() error: element=%d already in supply\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZsupply.next;
    c2->ZZds.ZZsupply.next=nxt; c1->ZZds.ZZsupply.next=c2;
    nxt->ZZds.ZZsupply.prev=c2; c2->ZZds.ZZsupply.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void supply_Ring2::insert(PartType *c1, PartType *c2){
    PartType *prv;

    if(c1->ZZds.ZZsupply.next || c1->ZZds.ZZsupply.prev){
        printf("supply.insert() error: element=%d already in supply\n",c1);
        return;
    }
    if(c2->ZZds.ZZsupply.next==NULL || c2->ZZds.ZZsupply.prev==NULL){
        printf("supply.insert() error: element=%d not in supply\n",c2);
        return;
    }
    prv=c2->ZZds.ZZsupply.prev;
    prv->ZZds.ZZsupply.next=c1; c1->ZZds.ZZsupply.next=c2;
    c2->ZZds.ZZsupply.prev=c1; c1->ZZds.ZZsupply.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

PartType* supply_Ring2::remove(PartType *tail, PartType *c){
    PartType *prv,*nxt;

    if(c->ZZds.ZZsupply.next==NULL || c->ZZds.ZZsupply.prev==NULL){
        printf("supply:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZsupply.next;
    prv=c->ZZds.ZZsupply.prev;
    if(c==nxt)tail=NULL;
    else {
        if(c==tail)tail=prv;
        prv->ZZds.ZZsupply.next=nxt;
        nxt->ZZds.ZZsupply.prev=prv;
    }
    c->ZZds.ZZsupply.next=c->ZZds.ZZsupply.prev=NULL;
    return tail;
}


// Sort the ring and return the new tail.
// The algorithm is based on repeated merging of sorted sublists,
// and is O(n log n). Note that the function is coded without the overhead
// of using recursive functions.
// Even though of the same order, this algorithm is faster than the one
// used for Ring1 - there are repeated searches for the sorted subsets.
//
// Algorithm:
// First traverse the list using the 'next' pointer, and detect sorted
// sublists. Make these sublists NULL-ending and, temporarily, connect
// the heads of these sublists.
// In repeated passes, merge the sublists until there is only one sublist.
// Then convert the representation back to ring, and set the 'prev' pointers.
//
//
// a1   a2            a1        a2      a1
// |    |             |         |       |
// 5->9 8->10->14->16 4->11->37 3->5->7 2->6->12->13     'next' pointer
// |   /|            /|        /|      /|  
// ->-- ------->----- ---->---- --->--- ----->NULL       'prev' pointer
//
//
//
// This gets sorted to:
//
// 5->8->9->10->14->16 3->4->5->7->11->37 2->6->12->13
//  |                 /|                 /|
//  --------->-------- ---------->------- ------>NULL
//
// ---------------------------------------------------------------

PartType* supply_Ring2::sort(ZZsortFun cmp, PartType *tail){
    PartType *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZsupply.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZsupply.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZsupply.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZsupply.next;
            if((*cmp)(p,p->ZZds.ZZsupply.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZsupply.next=NULL;
    }
    last->ZZds.ZZsupply.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZsupply.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZsupply.prev=a1; a1->ZZds.ZZsupply.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZsupply.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZsupply.next; }
                else         { t=t2; t2=t2->ZZds.ZZsupply.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZsupply.prev=t;
                    lastA1=t; lastA1->ZZds.ZZsupply.prev=NULL;
                }
                else last->ZZds.ZZsupply.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZsupply.next;
        if(nxt)nxt->ZZds.ZZsupply.prev=p;
        else {
            subs->ZZds.ZZsupply.prev=p;
            p->ZZds.ZZsupply.next=subs;
        }
    }
    return tail;
}


// ---------------------------------------------------------------
// This method provides two functions:
// If s and t are on different rings, the two rings merge.
// If s and t are on the same ring, the ring splits into two,
// and s and t can then be used as reference points (new tails).
//
//             spliting                 merging
//
//     ..<...v....t..<..              ......<.....
//     .     |    |    .              .          .
//     ..>...s....u..>..              ....v..t....
//                                        |  |
//                                    ....s..u....
//                                    .          .
//                                    ......<.....
//
// Algorithm:
// Assuming that u=s->next, and v=t->next,
// we only disconnect s-u and t-v, and connect s-v and t-u.
// When s==t or s or t are not in a ring, no action is taken.
// ---------------------------------------------------------------

void supply_Ring2::merge(PartType *s,PartType* t){
    PartType *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZsupply.next; v=t->ZZds.ZZsupply.next;
    if(!u || !v ){
        printf("cannot merge/split supply=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZsupply.next=u; u->ZZds.ZZsupply.prev=t;
    s->ZZds.ZZsupply.next=v; v->ZZds.ZZsupply.prev=s;
}


PartType* supply_Ring2Iterator::fromHead(PartType *p){ 
    PartType *ret;

    dir=0;
    tail=p;
    ret=tail->ZZds.ZZsupply.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZsupply.next;
    return ret;
}

PartType* supply_Ring2Iterator::fromTail(PartType *p){ 
    dir=1;
    tail=p;
    nxt=tail->ZZds.ZZsupply.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


PartType* const supply_Ring2Iterator::next(){ 
    PartType *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZsupply.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZsupply.prev; }
    return(c);
}


void supply_Ring2Iterator::start(PartType *p){ 
    PartType *ret;

    tail=p; nxt=NULL;
}


PartType* const supply_Ring2Iterator::operator++(){ 
    PartType *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZsupply.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZsupply.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZsupply.next;
    }
    else ret=NULL;
    return ret;
}


PartType* const supply_Ring2Iterator::operator--(){ 
    PartType *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZsupply.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZsupply.next)tail=NULL;
        else nxt=ret->ZZds.ZZsupply.prev;
    }
    else ret=NULL;
    return ret;
}
