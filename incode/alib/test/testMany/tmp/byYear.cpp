// --------------------------------------------------------

int byYear_Ring2::debugFun(Took *tail){
    Took *p,*nxt,*head; int h,t,ret;
    byYear_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZbyYear.next;
        if(nxt->ZZds.ZZbyYear.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbyYear.prev!=tail || tail->ZZds.ZZbyYear.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZbyYear.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZbyYear.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZbyYear.prev!=tail || tail->ZZds.ZZbyYear.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Took* const byYear_Ring2::next(Took *tail, Took *c){
    Took* ret=c->ZZds.ZZbyYear.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Took* const byYear_Ring2::prev(Took *tail, Took *c){
    Took* ret=c->ZZds.ZZbyYear.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Took* const byYear_Ring2::nextRing(Took *c){
    return c->ZZds.ZZbyYear.next;
}

Took* const byYear_Ring2::prevRing(Took *c){
    return c->ZZds.ZZbyYear.prev;
}

Took* byYear_Ring2::addHead(Took *tail, Took *c){
    Took *head;

    if(c->ZZds.ZZbyYear.next || c->ZZds.ZZbyYear.prev){
        printf("byYear.addHead() error: element=%d already in byYear\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZbyYear.next;
        c->ZZds.ZZbyYear.next=head; tail->ZZds.ZZbyYear.next=c;
        c->ZZds.ZZbyYear.prev=tail; head->ZZds.ZZbyYear.prev=c;
    }
    else {tail=c; c->ZZds.ZZbyYear.next=c; c->ZZds.ZZbyYear.prev=c;}
    return tail; 
}
                          
Took* byYear_Ring2::addTail(Took *tail, Took *c){
    if(c->ZZds.ZZbyYear.next){
        printf("byYear.addTail() error: element=%d already in byYear\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Took* byYear_Ring2::append(Took *tail,Took *c1, Took *c2){
    Took *nxt;

    if(c1->ZZds.ZZbyYear.next==NULL){
        printf("byYear.append() error: element=%d not in byYear\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZbyYear.next){
        printf("byYear.append() error: element=%d already in byYear\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZbyYear.next;
    c2->ZZds.ZZbyYear.next=nxt; c1->ZZds.ZZbyYear.next=c2;
    nxt->ZZds.ZZbyYear.prev=c2; c2->ZZds.ZZbyYear.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void byYear_Ring2::insert(Took *c1, Took *c2){
    Took *prv;

    if(c1->ZZds.ZZbyYear.next || c1->ZZds.ZZbyYear.prev){
        printf("byYear.insert() error: element=%d already in byYear\n",c1);
        return;
    }
    if(c2->ZZds.ZZbyYear.next==NULL || c2->ZZds.ZZbyYear.prev==NULL){
        printf("byYear.insert() error: element=%d not in byYear\n",c2);
        return;
    }
    prv=c2->ZZds.ZZbyYear.prev;
    prv->ZZds.ZZbyYear.next=c1; c1->ZZds.ZZbyYear.next=c2;
    c2->ZZds.ZZbyYear.prev=c1; c1->ZZds.ZZbyYear.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Took* byYear_Ring2::remove(Took *tail, Took *c){
    Took *prv,*nxt; Took *t;

    t=tail;
    if(c->ZZds.ZZbyYear.next==NULL || c->ZZds.ZZbyYear.prev==NULL){
        printf("byYear:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZbyYear.next;
    prv=c->ZZds.ZZbyYear.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZbyYear.next=nxt;
        nxt->ZZds.ZZbyYear.prev=prv;
    }
    c->ZZds.ZZbyYear.next=c->ZZds.ZZbyYear.prev=NULL;
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

Took* byYear_Ring2::sort(ZZsortFun cmp, Took *tail){
    Took *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZbyYear.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZbyYear.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZbyYear.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZbyYear.next;
            if((*cmp)(p,p->ZZds.ZZbyYear.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZbyYear.next=NULL;
    }
    last->ZZds.ZZbyYear.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZbyYear.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZbyYear.prev=a1; a1->ZZds.ZZbyYear.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZbyYear.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZbyYear.next; }
                else         { t=t2; t2=t2->ZZds.ZZbyYear.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZbyYear.prev=t;
                    lastA1=t; lastA1->ZZds.ZZbyYear.prev=NULL;
                }
                else last->ZZds.ZZbyYear.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZbyYear.next;
        if(nxt)nxt->ZZds.ZZbyYear.prev=p;
        else {
            subs->ZZds.ZZbyYear.prev=p;
            p->ZZds.ZZbyYear.next=subs;
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

void byYear_Ring2::merge(Took *s,Took* t){
    Took *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZbyYear.next; v=t->ZZds.ZZbyYear.next;
    if(!u || !v ){
        printf("cannot merge/split byYear=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZbyYear.next=u; u->ZZds.ZZbyYear.prev=t;
    s->ZZds.ZZbyYear.next=v; v->ZZds.ZZbyYear.prev=s;
}


Took* byYear_Ring2Iterator::fromHead(Took *p){ 
    Took *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZbyYear.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZbyYear.next;
    return ret;
}

Took* byYear_Ring2Iterator::fromTail(Took *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZbyYear.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Took* const byYear_Ring2Iterator::next(){ 
    Took *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZbyYear.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZbyYear.prev; }
    return(c);
}


void byYear_Ring2Iterator::start(Took *p){ 
    Took *ret;

    tail=p; nxt=NULL;
}


Took* const byYear_Ring2Iterator::operator++(){ 
    Took *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbyYear.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZbyYear.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZbyYear.next;
    }
    else ret=NULL;
    return ret;
}


Took* const byYear_Ring2Iterator::operator--(){ 
    Took *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZbyYear.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZbyYear.next)tail=NULL;
        else nxt=ret->ZZds.ZZbyYear.prev;
    }
    else ret=NULL;
    return ret;
}
