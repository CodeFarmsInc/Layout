// --------------------------------------------------------

int takes_Ring2::debugFun(Takes *tail){
    Takes *p,*nxt,*head; int h,t,ret;
    takes_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZtakes.next;
        if(nxt->ZZds.ZZtakes.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZtakes.prev!=tail || tail->ZZds.ZZtakes.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZtakes.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZtakes.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZtakes.prev!=tail || tail->ZZds.ZZtakes.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Takes* const takes_Ring2::next(Takes *tail, Takes *c){
    Takes* ret=c->ZZds.ZZtakes.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Takes* const takes_Ring2::prev(Takes *tail, Takes *c){
    Takes* ret=c->ZZds.ZZtakes.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Takes* const takes_Ring2::nextRing(Takes *c){
    return c->ZZds.ZZtakes.next;
}

Takes* const takes_Ring2::prevRing(Takes *c){
    return c->ZZds.ZZtakes.prev;
}

Takes* takes_Ring2::addHead(Takes *tail, Takes *c){
    Takes *head;

    if(c->ZZds.ZZtakes.next || c->ZZds.ZZtakes.prev){
        printf("takes.addHead() error: element=%d already in takes\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZtakes.next;
        c->ZZds.ZZtakes.next=head; tail->ZZds.ZZtakes.next=c;
        c->ZZds.ZZtakes.prev=tail; head->ZZds.ZZtakes.prev=c;
    }
    else {tail=c; c->ZZds.ZZtakes.next=c; c->ZZds.ZZtakes.prev=c;}
    return tail; 
}
                          
Takes* takes_Ring2::addTail(Takes *tail, Takes *c){
    if(c->ZZds.ZZtakes.next){
        printf("takes.addTail() error: element=%d already in takes\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Takes* takes_Ring2::append(Takes *tail,Takes *c1, Takes *c2){
    Takes *nxt;

    if(c1->ZZds.ZZtakes.next==NULL){
        printf("takes.append() error: element=%d not in takes\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZtakes.next){
        printf("takes.append() error: element=%d already in takes\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZtakes.next;
    c2->ZZds.ZZtakes.next=nxt; c1->ZZds.ZZtakes.next=c2;
    nxt->ZZds.ZZtakes.prev=c2; c2->ZZds.ZZtakes.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void takes_Ring2::insert(Takes *c1, Takes *c2){
    Takes *prv;

    if(c1->ZZds.ZZtakes.next || c1->ZZds.ZZtakes.prev){
        printf("takes.insert() error: element=%d already in takes\n",c1);
        return;
    }
    if(c2->ZZds.ZZtakes.next==NULL || c2->ZZds.ZZtakes.prev==NULL){
        printf("takes.insert() error: element=%d not in takes\n",c2);
        return;
    }
    prv=c2->ZZds.ZZtakes.prev;
    prv->ZZds.ZZtakes.next=c1; c1->ZZds.ZZtakes.next=c2;
    c2->ZZds.ZZtakes.prev=c1; c1->ZZds.ZZtakes.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Takes* takes_Ring2::remove(Takes *tail, Takes *c){
    Takes *prv,*nxt; Takes *t;

    t=tail;
    if(c->ZZds.ZZtakes.next==NULL || c->ZZds.ZZtakes.prev==NULL){
        printf("takes:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZtakes.next;
    prv=c->ZZds.ZZtakes.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZtakes.next=nxt;
        nxt->ZZds.ZZtakes.prev=prv;
    }
    c->ZZds.ZZtakes.next=c->ZZds.ZZtakes.prev=NULL;
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

Takes* takes_Ring2::sort(ZZsortFun cmp, Takes *tail){
    Takes *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZtakes.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZtakes.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZtakes.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZtakes.next;
            if((*cmp)(p,p->ZZds.ZZtakes.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZtakes.next=NULL;
    }
    last->ZZds.ZZtakes.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZtakes.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZtakes.prev=a1; a1->ZZds.ZZtakes.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZtakes.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZtakes.next; }
                else         { t=t2; t2=t2->ZZds.ZZtakes.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZtakes.prev=t;
                    lastA1=t; lastA1->ZZds.ZZtakes.prev=NULL;
                }
                else last->ZZds.ZZtakes.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZtakes.next;
        if(nxt)nxt->ZZds.ZZtakes.prev=p;
        else {
            subs->ZZds.ZZtakes.prev=p;
            p->ZZds.ZZtakes.next=subs;
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

void takes_Ring2::merge(Takes *s,Takes* t){
    Takes *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZtakes.next; v=t->ZZds.ZZtakes.next;
    if(!u || !v ){
        printf("cannot merge/split takes=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZtakes.next=u; u->ZZds.ZZtakes.prev=t;
    s->ZZds.ZZtakes.next=v; v->ZZds.ZZtakes.prev=s;
}


Takes* takes_Ring2Iterator::fromHead(Takes *p){ 
    Takes *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZtakes.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZtakes.next;
    return ret;
}

Takes* takes_Ring2Iterator::fromTail(Takes *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZtakes.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Takes* const takes_Ring2Iterator::next(){ 
    Takes *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZtakes.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZtakes.prev; }
    return(c);
}


void takes_Ring2Iterator::start(Takes *p){ 
    Takes *ret;

    tail=p; nxt=NULL;
}


Takes* const takes_Ring2Iterator::operator++(){ 
    Takes *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZtakes.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZtakes.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZtakes.next;
    }
    else ret=NULL;
    return ret;
}


Takes* const takes_Ring2Iterator::operator--(){ 
    Takes *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZtakes.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZtakes.next)tail=NULL;
        else nxt=ret->ZZds.ZZtakes.prev;
    }
    else ret=NULL;
    return ret;
}
