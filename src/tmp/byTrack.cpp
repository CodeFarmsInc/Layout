// --------------------------------------------------------

int byTrack_Ring2::debugFun(Edge *tail){
    Edge *p,*nxt,*head; int h,t,ret;
    byTrack_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZbyTrack.next;
        if(nxt->ZZds.ZZbyTrack.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbyTrack.prev!=tail || tail->ZZds.ZZbyTrack.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZbyTrack.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZbyTrack.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbyTrack.prev!=tail || tail->ZZds.ZZbyTrack.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Edge* const byTrack_Ring2::next(Edge *tail, Edge *c){
    Edge* ret=c->ZZds.ZZbyTrack.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Edge* const byTrack_Ring2::prev(Edge *tail, Edge *c){
    Edge* ret=c->ZZds.ZZbyTrack.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Edge* const byTrack_Ring2::nextRing(Edge *c){
    return c->ZZds.ZZbyTrack.next;
}

Edge* const byTrack_Ring2::prevRing(Edge *c){
    return c->ZZds.ZZbyTrack.prev;
}

Edge* byTrack_Ring2::addHead(Edge *tail, Edge *c){
    Edge *head;

    if(c->ZZds.ZZbyTrack.next || c->ZZds.ZZbyTrack.prev){
        printf("byTrack.addHead() error: element=%d already in byTrack\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZbyTrack.next;
        c->ZZds.ZZbyTrack.next=head; tail->ZZds.ZZbyTrack.next=c;
        c->ZZds.ZZbyTrack.prev=tail; head->ZZds.ZZbyTrack.prev=c;
    }
    else {tail=c; c->ZZds.ZZbyTrack.next=c; c->ZZds.ZZbyTrack.prev=c;}
    return tail; 
}
                          
Edge* byTrack_Ring2::addTail(Edge *tail, Edge *c){
    if(c->ZZds.ZZbyTrack.next){
        printf("byTrack.addTail() error: element=%d already in byTrack\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Edge* byTrack_Ring2::append(Edge *tail,Edge *c1, Edge *c2){
    Edge *nxt;

    if(c1->ZZds.ZZbyTrack.next==NULL){
        printf("byTrack.append() error: element=%d not in byTrack\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZbyTrack.next){
        printf("byTrack.append() error: element=%d already in byTrack\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZbyTrack.next;
    c2->ZZds.ZZbyTrack.next=nxt; c1->ZZds.ZZbyTrack.next=c2;
    nxt->ZZds.ZZbyTrack.prev=c2; c2->ZZds.ZZbyTrack.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void byTrack_Ring2::insert(Edge *c1, Edge *c2){
    Edge *prv;

    if(c1->ZZds.ZZbyTrack.next || c1->ZZds.ZZbyTrack.prev){
        printf("byTrack.insert() error: element=%d already in byTrack\n",c1);
        return;
    }
    if(c2->ZZds.ZZbyTrack.next==NULL || c2->ZZds.ZZbyTrack.prev==NULL){
        printf("byTrack.insert() error: element=%d not in byTrack\n",c2);
        return;
    }
    prv=c2->ZZds.ZZbyTrack.prev;
    prv->ZZds.ZZbyTrack.next=c1; c1->ZZds.ZZbyTrack.next=c2;
    c2->ZZds.ZZbyTrack.prev=c1; c1->ZZds.ZZbyTrack.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Edge* byTrack_Ring2::remove(Edge *tail, Edge *c){
    Edge *prv,*nxt; Edge *t;

    t=tail;
    if(c->ZZds.ZZbyTrack.next==NULL || c->ZZds.ZZbyTrack.prev==NULL){
        printf("byTrack:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZbyTrack.next;
    prv=c->ZZds.ZZbyTrack.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZbyTrack.next=nxt;
        nxt->ZZds.ZZbyTrack.prev=prv;
    }
    c->ZZds.ZZbyTrack.next=c->ZZds.ZZbyTrack.prev=NULL;
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

Edge* byTrack_Ring2::sort(ZZsortFun cmp, Edge *tail){
    Edge *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZbyTrack.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZbyTrack.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZbyTrack.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZbyTrack.next;
            if((*cmp)(p,p->ZZds.ZZbyTrack.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZbyTrack.next=NULL;
    }
    last->ZZds.ZZbyTrack.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZbyTrack.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZbyTrack.prev=a1; a1->ZZds.ZZbyTrack.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZbyTrack.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZbyTrack.next; }
                else         { t=t2; t2=t2->ZZds.ZZbyTrack.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZbyTrack.prev=t;
                    lastA1=t; lastA1->ZZds.ZZbyTrack.prev=NULL;
                }
                else last->ZZds.ZZbyTrack.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZbyTrack.next;
        if(nxt)nxt->ZZds.ZZbyTrack.prev=p;
        else {
            subs->ZZds.ZZbyTrack.prev=p;
            p->ZZds.ZZbyTrack.next=subs;
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

void byTrack_Ring2::merge(Edge *s,Edge* t){
    Edge *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZbyTrack.next; v=t->ZZds.ZZbyTrack.next;
    if(!u || !v ){
        printf("cannot merge/split byTrack=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZbyTrack.next=u; u->ZZds.ZZbyTrack.prev=t;
    s->ZZds.ZZbyTrack.next=v; v->ZZds.ZZbyTrack.prev=s;
}


Edge* byTrack_Ring2Iterator::fromHead(Edge *p){ 
    Edge *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZbyTrack.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZbyTrack.next;
    return ret;
}

Edge* byTrack_Ring2Iterator::fromTail(Edge *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZbyTrack.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Edge* const byTrack_Ring2Iterator::next(){ 
    Edge *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZbyTrack.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZbyTrack.prev; }
    return(c);
}


void byTrack_Ring2Iterator::start(Edge *p){ 
    Edge *ret;

    tail=p; nxt=NULL;
}


Edge* const byTrack_Ring2Iterator::operator++(){ 
    Edge *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbyTrack.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZbyTrack.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZbyTrack.next;
    }
    else ret=NULL;
    return ret;
}


Edge* const byTrack_Ring2Iterator::operator--(){ 
    Edge *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbyTrack.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZbyTrack.next)tail=NULL;
        else nxt=ret->ZZds.ZZbyTrack.prev;
    }
    else ret=NULL;
    return ret;
}
