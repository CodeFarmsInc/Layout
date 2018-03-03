// --------------------------------------------------------

int orgs_Ring2::debugFun(Organization *tail){
    Organization *p,*nxt,*head; int h,t,ret;
    orgs_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZorgs.next;
        if(nxt->ZZds.ZZorgs.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZorgs.prev!=tail || tail->ZZds.ZZorgs.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZorgs.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZorgs.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZorgs.prev!=tail || tail->ZZds.ZZorgs.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Organization* const orgs_Ring2::next(Organization *tail, Organization *c){
    Organization* ret=c->ZZds.ZZorgs.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Organization* const orgs_Ring2::prev(Organization *tail, Organization *c){
    Organization* ret=c->ZZds.ZZorgs.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Organization* const orgs_Ring2::nextRing(Organization *c){
    return c->ZZds.ZZorgs.next;
}

Organization* const orgs_Ring2::prevRing(Organization *c){
    return c->ZZds.ZZorgs.prev;
}

Organization* orgs_Ring2::addHead(Organization *tail, Organization *c){
    Organization *head;

    if(c->ZZds.ZZorgs.next || c->ZZds.ZZorgs.prev){
        printf("orgs.addHead() error: element=%d already in orgs\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZorgs.next;
        c->ZZds.ZZorgs.next=head; tail->ZZds.ZZorgs.next=c;
        c->ZZds.ZZorgs.prev=tail; head->ZZds.ZZorgs.prev=c;
    }
    else {tail=c; c->ZZds.ZZorgs.next=c; c->ZZds.ZZorgs.prev=c;}
    return tail; 
}
                          
Organization* orgs_Ring2::addTail(Organization *tail, Organization *c){
    if(c->ZZds.ZZorgs.next){
        printf("orgs.addTail() error: element=%d already in orgs\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Organization* orgs_Ring2::append(Organization *tail,Organization *c1, Organization *c2){
    Organization *nxt;

    if(c1->ZZds.ZZorgs.next==NULL){
        printf("orgs.append() error: element=%d not in orgs\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZorgs.next){
        printf("orgs.append() error: element=%d already in orgs\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZorgs.next;
    c2->ZZds.ZZorgs.next=nxt; c1->ZZds.ZZorgs.next=c2;
    nxt->ZZds.ZZorgs.prev=c2; c2->ZZds.ZZorgs.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void orgs_Ring2::insert(Organization *c1, Organization *c2){
    Organization *prv;

    if(c1->ZZds.ZZorgs.next || c1->ZZds.ZZorgs.prev){
        printf("orgs.insert() error: element=%d already in orgs\n",c1);
        return;
    }
    if(c2->ZZds.ZZorgs.next==NULL || c2->ZZds.ZZorgs.prev==NULL){
        printf("orgs.insert() error: element=%d not in orgs\n",c2);
        return;
    }
    prv=c2->ZZds.ZZorgs.prev;
    prv->ZZds.ZZorgs.next=c1; c1->ZZds.ZZorgs.next=c2;
    c2->ZZds.ZZorgs.prev=c1; c1->ZZds.ZZorgs.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Organization* orgs_Ring2::remove(Organization *tail, Organization *c){
    Organization *prv,*nxt; Organization *t;

    t=tail;
    if(c->ZZds.ZZorgs.next==NULL || c->ZZds.ZZorgs.prev==NULL){
        printf("orgs:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZorgs.next;
    prv=c->ZZds.ZZorgs.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZorgs.next=nxt;
        nxt->ZZds.ZZorgs.prev=prv;
    }
    c->ZZds.ZZorgs.next=c->ZZds.ZZorgs.prev=NULL;
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

Organization* orgs_Ring2::sort(ZZsortFun cmp, Organization *tail){
    Organization *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZorgs.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZorgs.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZorgs.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZorgs.next;
            if((*cmp)(p,p->ZZds.ZZorgs.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZorgs.next=NULL;
    }
    last->ZZds.ZZorgs.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZorgs.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZorgs.prev=a1; a1->ZZds.ZZorgs.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZorgs.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZorgs.next; }
                else         { t=t2; t2=t2->ZZds.ZZorgs.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZorgs.prev=t;
                    lastA1=t; lastA1->ZZds.ZZorgs.prev=NULL;
                }
                else last->ZZds.ZZorgs.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZorgs.next;
        if(nxt)nxt->ZZds.ZZorgs.prev=p;
        else {
            subs->ZZds.ZZorgs.prev=p;
            p->ZZds.ZZorgs.next=subs;
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

void orgs_Ring2::merge(Organization *s,Organization* t){
    Organization *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZorgs.next; v=t->ZZds.ZZorgs.next;
    if(!u || !v ){
        printf("cannot merge/split orgs=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZorgs.next=u; u->ZZds.ZZorgs.prev=t;
    s->ZZds.ZZorgs.next=v; v->ZZds.ZZorgs.prev=s;
}


Organization* orgs_Ring2Iterator::fromHead(Organization *p){ 
    Organization *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZorgs.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZorgs.next;
    return ret;
}

Organization* orgs_Ring2Iterator::fromTail(Organization *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZorgs.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Organization* const orgs_Ring2Iterator::next(){ 
    Organization *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZorgs.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZorgs.prev; }
    return(c);
}


void orgs_Ring2Iterator::start(Organization *p){ 
    Organization *ret;

    tail=p; nxt=NULL;
}


Organization* const orgs_Ring2Iterator::operator++(){ 
    Organization *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZorgs.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZorgs.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZorgs.next;
    }
    else ret=NULL;
    return ret;
}


Organization* const orgs_Ring2Iterator::operator--(){ 
    Organization *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZorgs.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZorgs.next)tail=NULL;
        else nxt=ret->ZZds.ZZorgs.prev;
    }
    else ret=NULL;
    return ret;
}
