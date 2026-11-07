// --------------------------------------------------------

int types_Ring2::debugFun(OrgType *tail){
    OrgType *p,*nxt,*head; int h,t,ret;
    types_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZtypes.next;
        if(nxt->ZZds.ZZtypes.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZtypes.prev!=tail || tail->ZZds.ZZtypes.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZtypes.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZtypes.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZtypes.prev!=tail || tail->ZZds.ZZtypes.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

OrgType* const types_Ring2::next(OrgType *tail, OrgType *c){
    OrgType* ret=c->ZZds.ZZtypes.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

OrgType* const types_Ring2::prev(OrgType *tail, OrgType *c){
    OrgType* ret=c->ZZds.ZZtypes.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

OrgType* const types_Ring2::nextRing(OrgType *c){
    return c->ZZds.ZZtypes.next;
}

OrgType* const types_Ring2::prevRing(OrgType *c){
    return c->ZZds.ZZtypes.prev;
}

OrgType* types_Ring2::addHead(OrgType *tail, OrgType *c){
    OrgType *head;

    if(c->ZZds.ZZtypes.next || c->ZZds.ZZtypes.prev){
        printf("types.addHead() error: element=%d already in types\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZtypes.next;
        c->ZZds.ZZtypes.next=head; tail->ZZds.ZZtypes.next=c;
        c->ZZds.ZZtypes.prev=tail; head->ZZds.ZZtypes.prev=c;
    }
    else {tail=c; c->ZZds.ZZtypes.next=c; c->ZZds.ZZtypes.prev=c;}
    return tail; 
}
                          
OrgType* types_Ring2::addTail(OrgType *tail, OrgType *c){
    if(c->ZZds.ZZtypes.next){
        printf("types.addTail() error: element=%d already in types\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
OrgType* types_Ring2::append(OrgType *tail,OrgType *c1, OrgType *c2){
    OrgType *nxt;

    if(c1->ZZds.ZZtypes.next==NULL){
        printf("types.append() error: element=%d not in types\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZtypes.next){
        printf("types.append() error: element=%d already in types\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZtypes.next;
    c2->ZZds.ZZtypes.next=nxt; c1->ZZds.ZZtypes.next=c2;
    nxt->ZZds.ZZtypes.prev=c2; c2->ZZds.ZZtypes.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void types_Ring2::insert(OrgType *c1, OrgType *c2){
    OrgType *prv;

    if(c1->ZZds.ZZtypes.next || c1->ZZds.ZZtypes.prev){
        printf("types.insert() error: element=%d already in types\n",c1);
        return;
    }
    if(c2->ZZds.ZZtypes.next==NULL || c2->ZZds.ZZtypes.prev==NULL){
        printf("types.insert() error: element=%d not in types\n",c2);
        return;
    }
    prv=c2->ZZds.ZZtypes.prev;
    prv->ZZds.ZZtypes.next=c1; c1->ZZds.ZZtypes.next=c2;
    c2->ZZds.ZZtypes.prev=c1; c1->ZZds.ZZtypes.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

OrgType* types_Ring2::remove(OrgType *tail, OrgType *c){
    OrgType *prv,*nxt; OrgType *t;

    t=tail;
    if(c->ZZds.ZZtypes.next==NULL || c->ZZds.ZZtypes.prev==NULL){
        printf("types:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZtypes.next;
    prv=c->ZZds.ZZtypes.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZtypes.next=nxt;
        nxt->ZZds.ZZtypes.prev=prv;
    }
    c->ZZds.ZZtypes.next=c->ZZds.ZZtypes.prev=NULL;
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

OrgType* types_Ring2::sort(ZZsortFun cmp, OrgType *tail){
    OrgType *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZtypes.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZtypes.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZtypes.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZtypes.next;
            if((*cmp)(p,p->ZZds.ZZtypes.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZtypes.next=NULL;
    }
    last->ZZds.ZZtypes.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZtypes.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZtypes.prev=a1; a1->ZZds.ZZtypes.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZtypes.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZtypes.next; }
                else         { t=t2; t2=t2->ZZds.ZZtypes.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZtypes.prev=t;
                    lastA1=t; lastA1->ZZds.ZZtypes.prev=NULL;
                }
                else last->ZZds.ZZtypes.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZtypes.next;
        if(nxt)nxt->ZZds.ZZtypes.prev=p;
        else {
            subs->ZZds.ZZtypes.prev=p;
            p->ZZds.ZZtypes.next=subs;
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

void types_Ring2::merge(OrgType *s,OrgType* t){
    OrgType *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZtypes.next; v=t->ZZds.ZZtypes.next;
    if(!u || !v ){
        printf("cannot merge/split types=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZtypes.next=u; u->ZZds.ZZtypes.prev=t;
    s->ZZds.ZZtypes.next=v; v->ZZds.ZZtypes.prev=s;
}


OrgType* types_Ring2Iterator::fromHead(OrgType *p){ 
    OrgType *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZtypes.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZtypes.next;
    return ret;
}

OrgType* types_Ring2Iterator::fromTail(OrgType *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZtypes.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


OrgType* const types_Ring2Iterator::next(){ 
    OrgType *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZtypes.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZtypes.prev; }
    return(c);
}


void types_Ring2Iterator::start(OrgType *p){ 
    OrgType *ret;

    tail=p; nxt=NULL;
}


OrgType* const types_Ring2Iterator::operator++(){ 
    OrgType *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZtypes.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZtypes.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZtypes.next;
    }
    else ret=NULL;
    return ret;
}


OrgType* const types_Ring2Iterator::operator--(){ 
    OrgType *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZtypes.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZtypes.next)tail=NULL;
        else nxt=ret->ZZds.ZZtypes.prev;
    }
    else ret=NULL;
    return ret;
}
