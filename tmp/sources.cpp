// --------------------------------------------------------

int sources_Ring2::debugFun(Edge *tail){
    Edge *p,*nxt,*head; int h,t,ret;
    sources_Ring2Iterator it;

    ret=0;
    for(p=it.fromHead(tail), h=0, head=NULL; p; p=it.next(), h++){
        if(h==0)head=p;
        nxt=p->ZZds.ZZsources.next;
        if(nxt->ZZds.ZZsources.prev!=p ||nxt==NULL){
            printf("debug error fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZsources.prev!=tail || tail->ZZds.ZZsources.next!=head){
        printf("debug tail-head error fromHead\n");
        ret=1;
    }

    for(p=it.fromTail(tail), t=0, head=NULL; p; p=it.next(), t++){
        nxt=p->ZZds.ZZsources.prev;
        if(nxt==tail)head=p;
        if(nxt->ZZds.ZZsources.next!=p ||nxt==NULL){
            printf("debug error2 fromHead index=%d\n",h);
            ret=1;
            break;
        }
    }
    if(!head || head->ZZds.ZZsources.prev!=tail || tail->ZZds.ZZsources.next!=head){
        printf("debug tail-head error fromTail\n");
        ret=1;
    }

    if(t!=h){
       printf("debug error counts fromHead=%d, fromTail=%d\n",h,t);
       ret=1;
    }
    return ret;
}

Edge* const sources_Ring2::next(Edge *tail, Edge *c){
    Edge* ret=c->ZZds.ZZsources.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Edge* const sources_Ring2::prev(Edge *tail, Edge *c){
    Edge* ret=c->ZZds.ZZsources.prev;
    if(ret==tail)ret=NULL;
    return ret; // return NULL when c is the tail
}

Edge* const sources_Ring2::nextRing(Edge *c){
    return c->ZZds.ZZsources.next;
}

Edge* const sources_Ring2::prevRing(Edge *c){
    return c->ZZds.ZZsources.prev;
}

Edge* sources_Ring2::addHead(Edge *tail, Edge *c){
    Edge *head;

    if(c->ZZds.ZZsources.next || c->ZZds.ZZsources.prev){
        printf("sources.addHead() error: element=%d already in sources\n",c);
        return NULL;
    }
    if(tail){
        head=tail->ZZds.ZZsources.next;
        c->ZZds.ZZsources.next=head; tail->ZZds.ZZsources.next=c;
        c->ZZds.ZZsources.prev=tail; head->ZZds.ZZsources.prev=c;
    }
    else {tail=c; c->ZZds.ZZsources.next=c; c->ZZds.ZZsources.prev=c;}
    return tail; 
}
                          
Edge* sources_Ring2::addTail(Edge *tail, Edge *c){
    if(c->ZZds.ZZsources.next){
        printf("sources.addTail() error: element=%d already in sources\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Edge* sources_Ring2::append(Edge *tail,Edge *c1, Edge *c2){
    Edge *nxt;

    if(c1->ZZds.ZZsources.next==NULL){
        printf("sources.append() error: element=%d not in sources\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZsources.next){
        printf("sources.append() error: element=%d already in sources\n",c2);
        return NULL;
    }
    nxt=c1->ZZds.ZZsources.next;
    c2->ZZds.ZZsources.next=nxt; c1->ZZds.ZZsources.next=c2;
    nxt->ZZds.ZZsources.prev=c2; c2->ZZds.ZZsources.prev=c1;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// append element c1 before element c2
void sources_Ring2::insert(Edge *c1, Edge *c2){
    Edge *prv;

    if(c1->ZZds.ZZsources.next || c1->ZZds.ZZsources.prev){
        printf("sources.insert() error: element=%d already in sources\n",c1);
        return;
    }
    if(c2->ZZds.ZZsources.next==NULL || c2->ZZds.ZZsources.prev==NULL){
        printf("sources.insert() error: element=%d not in sources\n",c2);
        return;
    }
    prv=c2->ZZds.ZZsources.prev;
    prv->ZZds.ZZsources.next=c1; c1->ZZds.ZZsources.next=c2;
    c2->ZZds.ZZsources.prev=c1; c1->ZZds.ZZsources.prev=prv;
}
                          
                          
// Compared to the singly-linked ring (Ring1), this function is much
// more efficient.

Edge* sources_Ring2::remove(Edge *tail, Edge *c){
    Edge *prv,*nxt; Edge *t;

    t=tail;
    if(c->ZZds.ZZsources.next==NULL || c->ZZds.ZZsources.prev==NULL){
        printf("sources:remove() error: node=%d not on the list\n",c); return NULL;
    }
    nxt=c->ZZds.ZZsources.next;
    prv=c->ZZds.ZZsources.prev;
    if(c==nxt)t=NULL;
    else {
        if(c==t)t=prv;
        prv->ZZds.ZZsources.next=nxt;
        nxt->ZZds.ZZsources.prev=prv;
    }
    c->ZZds.ZZsources.next=c->ZZds.ZZsources.prev=NULL;
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

Edge* sources_Ring2::sort(ZZsortFun cmp, Edge *tail){
    Edge *a1,*a2,*t,*t1,*t2,*p,*nxt,*subs,*last,*lastA1;
    int stopFlg,choice,closeSublist;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZsources.next)return tail; // the list has just one item

    // detect the initial sorted sublists
    for(p=subs=last=tail->ZZds.ZZsources.next, closeSublist=0; p; p=nxt){
        if(closeSublist){
            last->ZZds.ZZsources.prev=p;
            last=p;
            closeSublist=0;
        }

        if(p==tail){
            if(subs==last)return tail; // the list is already sorted
            nxt=NULL;
            closeSublist=1;
        }
        else {
            nxt=p->ZZds.ZZsources.next;
            if((*cmp)(p,p->ZZds.ZZsources.next)>0)closeSublist=1;
        }

        if(closeSublist)p->ZZds.ZZsources.next=NULL;
    }
    last->ZZds.ZZsources.prev=NULL; // close the chain

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=subs, lastA1=NULL; a1; a1=nxt){
            a2=a1->ZZds.ZZsources.prev;
            if(a2==NULL){
                if(subs==a1)stopFlg=1;
                else { lastA1->ZZds.ZZsources.prev=a1; a1->ZZds.ZZsources.prev=NULL;}
                break; // last odd sublist, do nothing
            }
            nxt=a2->ZZds.ZZsources.prev;

            // the two sublists to be merged start at a1 and a2
           
            for(t1=a1, t2=a2, last=NULL; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){ t=t1; t1=t1->ZZds.ZZsources.next; }
                else         { t=t2; t2=t2->ZZds.ZZsources.next; }

                if(last==NULL){
                    if(lastA1==NULL)subs=t;
                    else lastA1->ZZds.ZZsources.prev=t;
                    lastA1=t; lastA1->ZZds.ZZsources.prev=NULL;
                }
                else last->ZZds.ZZsources.next=t;

                last=t;
            }
        }
    }
    tail=last; // from merging the last two sublists

    // reset the ring and all the 'prev' pointers, 'subs' is the list head
    for(p=subs; p; p=nxt){
        nxt=p->ZZds.ZZsources.next;
        if(nxt)nxt->ZZds.ZZsources.prev=p;
        else {
            subs->ZZds.ZZsources.prev=p;
            p->ZZds.ZZsources.next=subs;
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

void sources_Ring2::merge(Edge *s,Edge* t){
    Edge *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZsources.next; v=t->ZZds.ZZsources.next;
    if(!u || !v ){
        printf("cannot merge/split sources=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZsources.next=u; u->ZZds.ZZsources.prev=t;
    s->ZZds.ZZsources.next=v; v->ZZds.ZZsources.prev=s;
}


Edge* sources_Ring2Iterator::fromHead(Edge *p){ 
    Edge *ret;

    dir=0;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    ret=tail->ZZds.ZZsources.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZsources.next;
    return ret;
}

Edge* sources_Ring2Iterator::fromTail(Edge *p){ 
    dir=1;
    if(p==NULL){nxt=tail=NULL; return NULL;}
    tail=p;
    nxt=tail->ZZds.ZZsources.prev;
    if(nxt==tail)nxt=tail=NULL; 
    return p;
}


Edge* const sources_Ring2Iterator::next(){ 
    Edge *c;

    c=nxt;
    if(dir==0){ if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZsources.next; }
    else      { if(c==tail)c=nxt=tail=NULL; else nxt=c->ZZds.ZZsources.prev; }
    return(c);
}


void sources_Ring2Iterator::start(Edge *p){ 
    Edge *ret;

    tail=p; nxt=NULL;
}


Edge* const sources_Ring2Iterator::operator++(){ 
    Edge *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZsources.next;
    }
    else if(tail) {
        ret=tail->ZZds.ZZsources.next;
        if(ret==tail)tail=NULL;
        else nxt=ret->ZZds.ZZsources.next;
    }
    else ret=NULL;
    return ret;
}


Edge* const sources_Ring2Iterator::operator--(){ 
    Edge *ret;

    if(nxt){
        ret=nxt; 
        if(ret==tail)ret=tail=nxt=NULL;
        else nxt=nxt->ZZds.ZZsources.prev;
    }
    else if(tail) {
        ret=tail;
        if(ret==tail->ZZds.ZZsources.next)tail=NULL;
        else nxt=ret->ZZds.ZZsources.prev;
    }
    else ret=NULL;
    return ret;
}
