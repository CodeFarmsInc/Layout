// --------------------------------------------------------

int parts_Ring2::debugFun(Participant *tail){
    Participant *p,*nxt,*head; int h,t,ret;
    parts_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZparts.next;
        if(nxt->ZZds.ZZparts.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZparts.prev!=tail || tail->ZZds.ZZparts.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZparts.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZparts.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZparts.prev!=tail || tail->ZZds.ZZparts.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Participant* const parts_Ring2::next(Participant *tail, Participant *c){
    Participant* ret=c->ZZds.ZZparts.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Participant* const parts_Ring2::prev(Participant *tail, Participant *c){
    Participant* ret=c->ZZds.ZZparts.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Participant* const parts_Ring2::nextRing(Participant *c){
    return c->ZZds.ZZparts.next;
}

Participant* const parts_Ring2::prevRing(Participant *c){
    return c->ZZds.ZZparts.prev;
}

Participant* parts_Ring2::addHead(Participant *tail, Participant *c){
    Participant *head;

    if(c->ZZds.ZZparts.next || c->ZZds.ZZparts.prev){
        printf("parts.addHead() error: element=%d already in parts\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZparts.next;
        c->ZZds.ZZparts.next=head; tail->ZZds.ZZparts.next=c;
        c->ZZds.ZZparts.prev=tail; head->ZZds.ZZparts.prev=c;
    }
    else {tail=c; c->ZZds.ZZparts.next=c; c->ZZds.ZZparts.prev=c;}
    return tail; 
}
                          
Participant* parts_Ring2::addTail(Participant *tail, Participant *c){
    if(c->ZZds.ZZparts.next){
        printf("parts.addTail() error: element=%d already in parts\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Participant* parts_Ring2::append(Participant *tail,Participant *c1, Participant *c2){
    Participant *nxt;

    if(c1->ZZds.ZZparts.next==NULL){
        printf("parts.append() error: element=%d not in parts\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZparts.next){
        printf("parts.append() error: element=%d already in parts\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZparts.next;
    c2->ZZds.ZZparts.next=nxt; c1->ZZds.ZZparts.next=c2;
    nxt->ZZds.ZZparts.prev=c2; c2->ZZds.ZZparts.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void parts_Ring2::insert(Participant *c1, Participant *c2){
    Participant *prv;

    if(c1->ZZds.ZZparts.next || c1->ZZds.ZZparts.prev){
        printf("parts.insert() error: element=%d already in parts\n",c1);
        return;
    }
    if(c2->ZZds.ZZparts.next==NULL || c2->ZZds.ZZparts.prev==NULL){
        printf("parts.insert() error: element=%d not in parts\n",c2);
        return;
    }
    prv=c2->ZZds.ZZparts.prev;
    prv->ZZds.ZZparts.next=c1; c1->ZZds.ZZparts.next=c2;
    c2->ZZds.ZZparts.prev=c1; c1->ZZds.ZZparts.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Participant* parts_Ring2::remove(Participant *tail, Participant *c){
    Participant *prv,*nxt; Participant *t;

    t=tail;
    if(c->ZZds.ZZparts.next==NULL || c->ZZds.ZZparts.prev==NULL){
        printf("parts:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZparts.next;
    prv=c->ZZds.ZZparts.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZparts.next=nxt;
        nxt->ZZds.ZZparts.prev=prv;
    }
    c->ZZds.ZZparts.next=c->ZZds.ZZparts.prev=NULL;
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

Participant* parts_Ring2::sort(ZZsortFun cmp, Participant *tail){
    Participant *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZparts.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZparts.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZparts.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZparts.next;
            if((*cmp)(p,p->ZZds.ZZparts.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZparts.next=NULL;
    }
    last->ZZds.ZZparts.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZparts.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZparts.prev=a1; a1->ZZds.ZZparts.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZparts.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZparts.next; }
                else         { t=t2; t2=t2->ZZds.ZZparts.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZparts.prev=t;
                    lastA1=t; lastA1->ZZds.ZZparts.prev=NULL;
                }
                else last->ZZds.ZZparts.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZparts.next;
        if(nxt)nxt->ZZds.ZZparts.prev=p;
        else {
            subs->ZZds.ZZparts.prev=p;
            p->ZZds.ZZparts.next=subs;
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

void parts_Ring2::merge(Participant *s,Participant* t){
    Participant *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZparts.next; v=t->ZZds.ZZparts.next;
    if(!u || !v ){
        printf("cannot merge/split parts=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZparts.next=u; u->ZZds.ZZparts.prev=t;
    s->ZZds.ZZparts.next=v; v->ZZds.ZZparts.prev=s;
}


Participant* parts_Ring2Iterator::fromHead(Participant *p){ 
    Participant *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZparts.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZparts.next;
    return ret;
}

Participant* parts_Ring2Iterator::fromTail(Participant *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZparts.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Participant* const parts_Ring2Iterator::next(){ 
    Participant *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZparts.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZparts.prev; }
    return(c);
}


void parts_Ring2Iterator::start(Participant *p){ 
    Participant *ret;

    tail=p; nxt=NULL;
}


Participant* const parts_Ring2Iterator::operator++(){ 
    Participant *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZparts.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZparts.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZparts.next;
    }
    else ret=NULL;
    return ret;
}


Participant* const parts_Ring2Iterator::operator--(){ 
    Participant *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZparts.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZparts.next)tail=NULL;
        else nxt=ret->ZZds.ZZparts.prev;
    }
    else ret=NULL;
    return ret;
}
