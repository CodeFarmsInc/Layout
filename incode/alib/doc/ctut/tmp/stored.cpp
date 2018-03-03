// --------------------------------------------------------

int stored_Ring2::debugFun(PartType *tail){
    PartType *p,*nxt,*head; int h,t,ret;
    stored_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZstored.next;
        if(nxt->ZZds.ZZstored.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZstored.prev!=tail || tail->ZZds.ZZstored.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZstored.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZstored.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZstored.prev!=tail || tail->ZZds.ZZstored.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

PartType* const stored_Ring2::next(PartType *tail, PartType *c){
    PartType* ret=c->ZZds.ZZstored.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

PartType* const stored_Ring2::prev(PartType *tail, PartType *c){
    PartType* ret=c->ZZds.ZZstored.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

PartType* const stored_Ring2::fwd(PartType *c){
    return c->ZZds.ZZstored.next;
}

PartType* const stored_Ring2::bwd(PartType *c){
    return c->ZZds.ZZstored.prev;
}

PartType* stored_Ring2::addHead(PartType *tail, PartType *c){
    PartType *head;

    if(c->ZZds.ZZstored.next){
        printf("stored.addHead() error: element=%d already in stored\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZstored.next;
        c->ZZds.ZZstored.next=head; tail->ZZds.ZZstored.next=c;
        c->ZZds.ZZstored.prev=tail; head->ZZds.ZZstored.prev=c;
    }
    else {tail=c->ZZds.ZZstored.next=c->ZZds.ZZstored.prev=c;}
    return tail; 
}
                          
PartType* stored_Ring2::addTail(PartType *tail, PartType *c){
    if(c->ZZds.ZZstored.next){
        printf("stored.addTail() error: element=%d already in stored\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
PartType* stored_Ring2::append(PartType *tail,PartType *c1, PartType *c2){
    PartType *nxt;

    if(c1->ZZds.ZZstored.next==NULL){
        printf("stored.append() error: element=%d not in stored\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZstored.next){
        printf("stored.append() error: element=%d already in stored\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZstored.next;
    c2->ZZds.ZZstored.next=nxt; c1->ZZds.ZZstored.next=c2;
    nxt->ZZds.ZZstored.prev=c2; c2->ZZds.ZZstored.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void stored_Ring2::insert(PartType *c1, PartType *c2){
    PartType *prv;

    if(c1->ZZds.ZZstored.next || c1->ZZds.ZZstored.prev){
        printf("stored.insert() error: element=%d already in stored\n",c1);
        return;
    }
    if(c2->ZZds.ZZstored.next==NULL || c2->ZZds.ZZstored.prev==NULL){
        printf("stored.insert() error: element=%d not in stored\n",c2);
        return;
    }
    prv=c2->ZZds.ZZstored.prev;
    prv->ZZds.ZZstored.next=c1; c1->ZZds.ZZstored.next=c2;
    c2->ZZds.ZZstored.prev=c1; c1->ZZds.ZZstored.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

PartType* stored_Ring2::remove(PartType *tail, PartType *c){
    PartType *prv,*nxt;

    if(c->ZZds.ZZstored.next==NULL || c->ZZds.ZZstored.prev==NULL){
        printf("stored:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZstored.next;
    prv=c->ZZds.ZZstored.prev;
    if(c==nxt)tail=NULL;
    else {
        if(c==tail)tail=prv;
        prv->ZZds.ZZstored.next=nxt;
        nxt->ZZds.ZZstored.prev=prv;
    }
    c->ZZds.ZZstored.next=c->ZZds.ZZstored.prev=NULL;
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

PartType* stored_Ring2::sort(ZZsortFun cmp, PartType *tail){
    PartType *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZstored.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZstored.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZstored.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZstored.next;
            if((*cmp)(p,p->ZZds.ZZstored.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZstored.next=NULL;
    }
    last->ZZds.ZZstored.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZstored.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZstored.prev=a1; a1->ZZds.ZZstored.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZstored.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZstored.next; }
                else         { t=t2; t2=t2->ZZds.ZZstored.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZstored.prev=t;
                    lastA1=t; lastA1->ZZds.ZZstored.prev=NULL;
                }
                else last->ZZds.ZZstored.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZstored.next;
        if(nxt)nxt->ZZds.ZZstored.prev=p;
        else {
            subs->ZZds.ZZstored.prev=p;
            p->ZZds.ZZstored.next=subs;
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

void stored_Ring2::merge(PartType *s,PartType* t){
    PartType *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZstored.next; v=t->ZZds.ZZstored.next;
    if(!u || !v ){
        printf("cannot merge/split stored=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZstored.next=u; u->ZZds.ZZstored.prev=t;
    s->ZZds.ZZstored.next=v; v->ZZds.ZZstored.prev=s;
}


PartType* stored_Ring2Iterator::fromHead(PartType *p){ 
    PartType *ret;

    dir=0;
    tail=p;
    ret=tail->ZZds.ZZstored.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZstored.next;
    return ret;
}

PartType* stored_Ring2Iterator::fromTail(PartType *p){ 
    dir=1;
    tail=p;
    nxt=tail->ZZds.ZZstored.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


PartType* const stored_Ring2Iterator::next(){ 
    PartType *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZstored.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZstored.prev; }
    return(c);
}


void stored_Ring2Iterator::start(PartType *p){ 
    PartType *ret;

    tail=p; nxt=NULL;
}


PartType* const stored_Ring2Iterator::operator++(){ 
    PartType *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZstored.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZstored.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZstored.next;
    }
    else ret=NULL;
    return ret;
}


PartType* const stored_Ring2Iterator::operator--(){ 
    PartType *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZstored.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZstored.next)tail=NULL;
        else nxt=ret->ZZds.ZZstored.prev;
    }
    else ret=NULL;
    return ret;
}
