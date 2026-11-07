// --------------------------------------------------------

int ring1_Ring2::debugFun(A *tail){
    A *p,*nxt,*head; int h,t,ret;
    ring1_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZring1.next;
        if(nxt->ZZds.ZZring1.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZring1.prev!=tail || tail->ZZds.ZZring1.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZring1.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZring1.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZring1.prev!=tail || tail->ZZds.ZZring1.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

A* const ring1_Ring2::next(A *tail, A *c){
    A* ret=c->ZZds.ZZring1.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

A* const ring1_Ring2::prev(A *tail, A *c){
    A* ret=c->ZZds.ZZring1.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

A* const ring1_Ring2::nextRing(A *c){
    return c->ZZds.ZZring1.next;
}

A* const ring1_Ring2::prevRing(A *c){
    return c->ZZds.ZZring1.prev;
}

A* ring1_Ring2::addHead(A *tail, A *c){
    A *head;

    if(c->ZZds.ZZring1.next || c->ZZds.ZZring1.prev){
        printf("ring1.addHead() error: element=%d already in ring1\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZring1.next;
        c->ZZds.ZZring1.next=head; tail->ZZds.ZZring1.next=c;
        c->ZZds.ZZring1.prev=tail; head->ZZds.ZZring1.prev=c;
    }
    else {tail=c; c->ZZds.ZZring1.next=c; c->ZZds.ZZring1.prev=c;}
    return tail; 
}
                          
A* ring1_Ring2::addTail(A *tail, A *c){
    if(c->ZZds.ZZring1.next){
        printf("ring1.addTail() error: element=%d already in ring1\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
A* ring1_Ring2::append(A *tail,A *c1, A *c2){
    A *nxt;

    if(c1->ZZds.ZZring1.next==NULL){
        printf("ring1.append() error: element=%d not in ring1\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZring1.next){
        printf("ring1.append() error: element=%d already in ring1\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZring1.next;
    c2->ZZds.ZZring1.next=nxt; c1->ZZds.ZZring1.next=c2;
    nxt->ZZds.ZZring1.prev=c2; c2->ZZds.ZZring1.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void ring1_Ring2::insert(A *c1, A *c2){
    A *prv;

    if(c1->ZZds.ZZring1.next || c1->ZZds.ZZring1.prev){
        printf("ring1.insert() error: element=%d already in ring1\n",c1);
        return;
    }
    if(c2->ZZds.ZZring1.next==NULL || c2->ZZds.ZZring1.prev==NULL){
        printf("ring1.insert() error: element=%d not in ring1\n",c2);
        return;
    }
    prv=c2->ZZds.ZZring1.prev;
    prv->ZZds.ZZring1.next=c1; c1->ZZds.ZZring1.next=c2;
    c2->ZZds.ZZring1.prev=c1; c1->ZZds.ZZring1.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

A* ring1_Ring2::remove(A *tail, A *c){
    A *prv,*nxt; A *t;

    t=tail;
    if(c->ZZds.ZZring1.next==NULL || c->ZZds.ZZring1.prev==NULL){
        printf("ring1:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZring1.next;
    prv=c->ZZds.ZZring1.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZring1.next=nxt;
        nxt->ZZds.ZZring1.prev=prv;
    }
    c->ZZds.ZZring1.next=c->ZZds.ZZring1.prev=NULL;
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

A* ring1_Ring2::sort(ZZsortFun cmp, A *tail){
    A *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZring1.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZring1.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZring1.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZring1.next;
            if((*cmp)(p,p->ZZds.ZZring1.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZring1.next=NULL;
    }
    last->ZZds.ZZring1.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZring1.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZring1.prev=a1; a1->ZZds.ZZring1.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZring1.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZring1.next; }
                else         { t=t2; t2=t2->ZZds.ZZring1.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZring1.prev=t;
                    lastA1=t; lastA1->ZZds.ZZring1.prev=NULL;
                }
                else last->ZZds.ZZring1.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZring1.next;
        if(nxt)nxt->ZZds.ZZring1.prev=p;
        else {
            subs->ZZds.ZZring1.prev=p;
            p->ZZds.ZZring1.next=subs;
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

void ring1_Ring2::merge(A *s,A* t){
    A *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZring1.next; v=t->ZZds.ZZring1.next;
    if(!u || !v ){
        printf("cannot merge/split ring1=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZring1.next=u; u->ZZds.ZZring1.prev=t;
    s->ZZds.ZZring1.next=v; v->ZZds.ZZring1.prev=s;
}


A* ring1_Ring2Iterator::fromHead(A *p){ 
    A *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZring1.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZring1.next;
    return ret;
}

A* ring1_Ring2Iterator::fromTail(A *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZring1.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


A* const ring1_Ring2Iterator::next(){ 
    A *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZring1.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZring1.prev; }
    return(c);
}


void ring1_Ring2Iterator::start(A *p){ 
    A *ret;

    tail=p; nxt=NULL;
}


A* const ring1_Ring2Iterator::operator++(){ 
    A *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZring1.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZring1.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZring1.next;
    }
    else ret=NULL;
    return ret;
}


A* const ring1_Ring2Iterator::operator--(){ 
    A *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZring1.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZring1.next)tail=NULL;
        else nxt=ret->ZZds.ZZring1.prev;
    }
    else ret=NULL;
    return ret;
}
