// --------------------------------------------------------

int AtoB_Ring2::debugFun(B *tail){
    B *p,*nxt,*head; int h,t,ret;
    AtoB_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZAtoB.next;
        if(nxt->ZZds.ZZAtoB.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZAtoB.prev!=tail || tail->ZZds.ZZAtoB.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZAtoB.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZAtoB.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZAtoB.prev!=tail || tail->ZZds.ZZAtoB.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

B* const AtoB_Ring2::next(B *tail, B *c){
    B* ret=c->ZZds.ZZAtoB.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

B* const AtoB_Ring2::prev(B *tail, B *c){
    B* ret=c->ZZds.ZZAtoB.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

B* const AtoB_Ring2::nextRing(B *c){
    return c->ZZds.ZZAtoB.next;
}

B* const AtoB_Ring2::prevRing(B *c){
    return c->ZZds.ZZAtoB.prev;
}

B* AtoB_Ring2::addHead(B *tail, B *c){
    B *head;

    if(c->ZZds.ZZAtoB.next || c->ZZds.ZZAtoB.prev){
        printf("AtoB.addHead() error: element=%d already in AtoB\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZAtoB.next;
        c->ZZds.ZZAtoB.next=head; tail->ZZds.ZZAtoB.next=c;
        c->ZZds.ZZAtoB.prev=tail; head->ZZds.ZZAtoB.prev=c;
    }
    else {tail=c; c->ZZds.ZZAtoB.next=c; c->ZZds.ZZAtoB.prev=c;}
    return tail; 
}
                          
B* AtoB_Ring2::addTail(B *tail, B *c){
    if(c->ZZds.ZZAtoB.next){
        printf("AtoB.addTail() error: element=%d already in AtoB\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
B* AtoB_Ring2::append(B *tail,B *c1, B *c2){
    B *nxt;

    if(c1->ZZds.ZZAtoB.next==NULL){
        printf("AtoB.append() error: element=%d not in AtoB\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZAtoB.next){
        printf("AtoB.append() error: element=%d already in AtoB\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZAtoB.next;
    c2->ZZds.ZZAtoB.next=nxt; c1->ZZds.ZZAtoB.next=c2;
    nxt->ZZds.ZZAtoB.prev=c2; c2->ZZds.ZZAtoB.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void AtoB_Ring2::insert(B *c1, B *c2){
    B *prv;

    if(c1->ZZds.ZZAtoB.next || c1->ZZds.ZZAtoB.prev){
        printf("AtoB.insert() error: element=%d already in AtoB\n",c1);
        return;
    }
    if(c2->ZZds.ZZAtoB.next==NULL || c2->ZZds.ZZAtoB.prev==NULL){
        printf("AtoB.insert() error: element=%d not in AtoB\n",c2);
        return;
    }
    prv=c2->ZZds.ZZAtoB.prev;
    prv->ZZds.ZZAtoB.next=c1; c1->ZZds.ZZAtoB.next=c2;
    c2->ZZds.ZZAtoB.prev=c1; c1->ZZds.ZZAtoB.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

B* AtoB_Ring2::remove(B *tail, B *c){
    B *prv,*nxt; B *t;

    t=tail;
    if(c->ZZds.ZZAtoB.next==NULL || c->ZZds.ZZAtoB.prev==NULL){
        printf("AtoB:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZAtoB.next;
    prv=c->ZZds.ZZAtoB.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZAtoB.next=nxt;
        nxt->ZZds.ZZAtoB.prev=prv;
    }
    c->ZZds.ZZAtoB.next=c->ZZds.ZZAtoB.prev=NULL;
    return t;
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

B* AtoB_Ring2::sort(ZZsortFun cmp, B *tail){
    B *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZAtoB.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZAtoB.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZAtoB.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZAtoB.next;
            if((*cmp)(p,p->ZZds.ZZAtoB.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZAtoB.next=NULL;
    }
    last->ZZds.ZZAtoB.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZAtoB.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZAtoB.prev=a1; a1->ZZds.ZZAtoB.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZAtoB.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZAtoB.next; }
                else         { t=t2; t2=t2->ZZds.ZZAtoB.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZAtoB.prev=t;
                    lastA1=t; lastA1->ZZds.ZZAtoB.prev=NULL;
                }
                else last->ZZds.ZZAtoB.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZAtoB.next;
        if(nxt)nxt->ZZds.ZZAtoB.prev=p;
        else {
            subs->ZZds.ZZAtoB.prev=p;
            p->ZZds.ZZAtoB.next=subs;
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

void AtoB_Ring2::merge(B *s,B* t){
    B *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZAtoB.next; v=t->ZZds.ZZAtoB.next;
    if(!u || !v ){
        printf("cannot merge/split AtoB=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZAtoB.next=u; u->ZZds.ZZAtoB.prev=t;
    s->ZZds.ZZAtoB.next=v; v->ZZds.ZZAtoB.prev=s;
}


B* AtoB_Ring2Iterator::fromHead(B *p){ 
    B *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZAtoB.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZAtoB.next;
    return ret;
}

B* AtoB_Ring2Iterator::fromTail(B *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZAtoB.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


B* const AtoB_Ring2Iterator::next(){ 
    B *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZAtoB.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZAtoB.prev; }
    return(c);
}


void AtoB_Ring2Iterator::start(B *p){ 
    B *ret;

    tail=p; nxt=NULL;
}


B* const AtoB_Ring2Iterator::operator++(){ 
    B *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZAtoB.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZAtoB.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZAtoB.next;
    }
    else ret=NULL;
    return ret;
}


B* const AtoB_Ring2Iterator::operator--(){ 
    B *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZAtoB.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZAtoB.next)tail=NULL;
        else nxt=ret->ZZds.ZZAtoB.prev;
    }
    else ret=NULL;
    return ret;
}
