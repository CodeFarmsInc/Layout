// --------------------------------------------------------

int usedBy_Ring2::debugFun(Participant *tail){
    Participant *p,*nxt,*head; int h,t,ret;
    usedBy_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZusedBy.next;
        if(nxt->ZZds.ZZusedBy.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZusedBy.prev!=tail || tail->ZZds.ZZusedBy.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZusedBy.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZusedBy.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZusedBy.prev!=tail || tail->ZZds.ZZusedBy.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Participant* const usedBy_Ring2::next(Participant *tail, Participant *c){
    Participant* ret=c->ZZds.ZZusedBy.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Participant* const usedBy_Ring2::prev(Participant *tail, Participant *c){
    Participant* ret=c->ZZds.ZZusedBy.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Participant* const usedBy_Ring2::nextRing(Participant *c){
    return c->ZZds.ZZusedBy.next;
}

Participant* const usedBy_Ring2::prevRing(Participant *c){
    return c->ZZds.ZZusedBy.prev;
}

Participant* usedBy_Ring2::addHead(Participant *tail, Participant *c){
    Participant *head;

    if(c->ZZds.ZZusedBy.next || c->ZZds.ZZusedBy.prev){
        printf("usedBy.addHead() error: element=%d already in usedBy\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZusedBy.next;
        c->ZZds.ZZusedBy.next=head; tail->ZZds.ZZusedBy.next=c;
        c->ZZds.ZZusedBy.prev=tail; head->ZZds.ZZusedBy.prev=c;
    }
    else {tail=c; c->ZZds.ZZusedBy.next=c; c->ZZds.ZZusedBy.prev=c;}
    return tail; 
}
                          
Participant* usedBy_Ring2::addTail(Participant *tail, Participant *c){
    if(c->ZZds.ZZusedBy.next){
        printf("usedBy.addTail() error: element=%d already in usedBy\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Participant* usedBy_Ring2::append(Participant *tail,Participant *c1, Participant *c2){
    Participant *nxt;

    if(c1->ZZds.ZZusedBy.next==NULL){
        printf("usedBy.append() error: element=%d not in usedBy\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZusedBy.next){
        printf("usedBy.append() error: element=%d already in usedBy\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZusedBy.next;
    c2->ZZds.ZZusedBy.next=nxt; c1->ZZds.ZZusedBy.next=c2;
    nxt->ZZds.ZZusedBy.prev=c2; c2->ZZds.ZZusedBy.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void usedBy_Ring2::insert(Participant *c1, Participant *c2){
    Participant *prv;

    if(c1->ZZds.ZZusedBy.next || c1->ZZds.ZZusedBy.prev){
        printf("usedBy.insert() error: element=%d already in usedBy\n",c1);
        return;
    }
    if(c2->ZZds.ZZusedBy.next==NULL || c2->ZZds.ZZusedBy.prev==NULL){
        printf("usedBy.insert() error: element=%d not in usedBy\n",c2);
        return;
    }
    prv=c2->ZZds.ZZusedBy.prev;
    prv->ZZds.ZZusedBy.next=c1; c1->ZZds.ZZusedBy.next=c2;
    c2->ZZds.ZZusedBy.prev=c1; c1->ZZds.ZZusedBy.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Participant* usedBy_Ring2::remove(Participant *tail, Participant *c){
    Participant *prv,*nxt; Participant *t;

    t=tail;
    if(c->ZZds.ZZusedBy.next==NULL || c->ZZds.ZZusedBy.prev==NULL){
        printf("usedBy:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZusedBy.next;
    prv=c->ZZds.ZZusedBy.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZusedBy.next=nxt;
        nxt->ZZds.ZZusedBy.prev=prv;
    }
    c->ZZds.ZZusedBy.next=c->ZZds.ZZusedBy.prev=NULL;
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

Participant* usedBy_Ring2::sort(ZZsortFun cmp, Participant *tail){
    Participant *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZusedBy.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZusedBy.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZusedBy.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZusedBy.next;
            if((*cmp)(p,p->ZZds.ZZusedBy.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZusedBy.next=NULL;
    }
    last->ZZds.ZZusedBy.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZusedBy.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZusedBy.prev=a1; a1->ZZds.ZZusedBy.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZusedBy.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZusedBy.next; }
                else         { t=t2; t2=t2->ZZds.ZZusedBy.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZusedBy.prev=t;
                    lastA1=t; lastA1->ZZds.ZZusedBy.prev=NULL;
                }
                else last->ZZds.ZZusedBy.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZusedBy.next;
        if(nxt)nxt->ZZds.ZZusedBy.prev=p;
        else {
            subs->ZZds.ZZusedBy.prev=p;
            p->ZZds.ZZusedBy.next=subs;
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

void usedBy_Ring2::merge(Participant *s,Participant* t){
    Participant *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZusedBy.next; v=t->ZZds.ZZusedBy.next;
    if(!u || !v ){
        printf("cannot merge/split usedBy=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZusedBy.next=u; u->ZZds.ZZusedBy.prev=t;
    s->ZZds.ZZusedBy.next=v; v->ZZds.ZZusedBy.prev=s;
}


Participant* usedBy_Ring2Iterator::fromHead(Participant *p){ 
    Participant *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZusedBy.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZusedBy.next;
    return ret;
}

Participant* usedBy_Ring2Iterator::fromTail(Participant *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZusedBy.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Participant* const usedBy_Ring2Iterator::next(){ 
    Participant *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZusedBy.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZusedBy.prev; }
    return(c);
}


void usedBy_Ring2Iterator::start(Participant *p){ 
    Participant *ret;

    tail=p; nxt=NULL;
}


Participant* const usedBy_Ring2Iterator::operator++(){ 
    Participant *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZusedBy.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZusedBy.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZusedBy.next;
    }
    else ret=NULL;
    return ret;
}


Participant* const usedBy_Ring2Iterator::operator--(){ 
    Participant *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZusedBy.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZusedBy.next)tail=NULL;
        else nxt=ret->ZZds.ZZusedBy.prev;
    }
    else ret=NULL;
    return ret;
}
