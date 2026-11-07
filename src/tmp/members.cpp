// --------------------------------------------------------

Member* const members_Ring1::next(Member *tail, Member *c){
    Member* ret=c->ZZds.ZZmembers.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the externally given tail
}

Member* const members_Ring1::nextRing(Member *c){
    return c->ZZds.ZZmembers.next;
}

Member* members_Ring1::addHead(Member *tail, Member *c){
    if(c->ZZds.ZZmembers.next){
        printf("members.addHead() error: element=%d already in members\n",c);
        return NULL;
    }
    if(tail){c->ZZds.ZZmembers.next=tail->ZZds.ZZmembers.next; tail->ZZds.ZZmembers.next=c;}
    else        {tail=c; c->ZZds.ZZmembers.next=c;}
    return tail; 
}
                          
Member* members_Ring1::addTail(Member *tail, Member *c){
    if(c->ZZds.ZZmembers.next){
        printf("members.addTail() error: element=%d already in members\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Member* members_Ring1::append(Member *tail,Member *c1, Member *c2){
    Member *x;

    if(c1->ZZds.ZZmembers.next==NULL){
        printf("members.append() error: element=%d not in members\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZmembers.next){
        printf("members.append() error: element=%d already in members\n",c2);
        return NULL;
    }
    c2->ZZds.ZZmembers.next=c1->ZZds.ZZmembers.next;
    c1->ZZds.ZZmembers.next=c2;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// This function is not very efficient, must search for a predecessor.
// However, removing  while traversing is fast (no search).

Member* members_Ring1::remove(Member *tail, Member *c){
    Member *x,*nxt;

    for(x=tail, nxt=NULL; x!=tail || nxt==NULL; x=nxt){
        nxt=x->ZZds.ZZmembers.next;
        if(nxt==c)break;
    }
    if(!x || x->ZZds.ZZmembers.next!=c){
        printf("members:remove() error: node not on the list\n"); return NULL;
    }
    if(c==x)tail=NULL;
    else if(c==tail)tail=x;
    x->ZZds.ZZmembers.next=c->ZZds.ZZmembers.next;
    c->ZZds.ZZmembers.next=NULL;
    return tail;
}


// Sort the ring and return the new tail.
// The algorithm is based on repeated merging of sorted sublists,
// and is O(n log n). Note that the function is coded without the overhead
// of using recursive functions.
//
// Algorithm:
// Repeatedly traverse the list and detect places where not sorted.
// This helps to find adjacent sorted lists, which are then merged.
// a1...b1 and a2...b2 are the sublists to be merged.
//
// In this process, the tail and the head (which is tail->next) may change,
// which significantly impacts the complexity of the logic. This can be
// avoided if we add a temporary node (marked ?) which marks the end/beginning
// of the real data. When the sorting is finished, this node is removed.
//
//                                       tail
//                                       |
// 5 9 8 10 14 16 4 11 37  3 5 7 2 6 12 13 ?
// --- ++++++++++ -------  +++++ ---------
//                |     |  |   |           |
//                a1    b1 a2  b2          temporaryNode
//
// This gets sorted to:
//
// 5 8 9 10 14 16 3 4 5 7 11 37 2 6 12 13
// -------------- +++++++++++++ ---------
//
// ---------------------------------------------------------------

Member* members_Ring1::sort(ZZsortFun cmp, Member *tail){
    Member *a1,*b1,*a2,*b2,*t1,*t2,*temp,*last,*nxt;
    int stopFlg,choice;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZmembers.next)return tail; // the list has just one item

    temp=new Member; // the additional, temporary node
    if(!temp){
        printf("members Ring1::sort cannot allocate temporary node\n"); return NULL;
    }
    temp->ZZds.ZZmembers.next=tail->ZZds.ZZmembers.next;
    tail->ZZds.ZZmembers.next=temp;

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=temp->ZZds.ZZmembers.next, last=temp; a1!=temp; a1=nxt){

            // detect the first sublist
            for(b1=a1; b1->ZZds.ZZmembers.next!=temp; b1=b1->ZZds.ZZmembers.next){
                if((*cmp)(b1,b1->ZZds.ZZmembers.next)>0)break;
            }
   
            if(b1->ZZds.ZZmembers.next==temp){ // last of the odd number of sublists
                if(a1==temp->ZZds.ZZmembers.next) stopFlg=1; // list fully sorted
                last->ZZds.ZZmembers.next=a1;
                last=b1;
                break;
            }

            // detect the second sublist
            a2=b1->ZZds.ZZmembers.next;
            for(b2=a2; b2->ZZds.ZZmembers.next!=temp; b2=b2->ZZds.ZZmembers.next){
                if((*cmp)(b2,b2->ZZds.ZZmembers.next)>0)break;
            }
            nxt=b2->ZZds.ZZmembers.next; // remember it before b2 changes its position

            // the two sublists to be merged are (a1,b1) and (a2,b2)
           
            for(t1=a1, t2=a2; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){
                    last->ZZds.ZZmembers.next=t1;
                    last=t1;
                    if(t1==b1)t1=NULL; else t1=t1->ZZds.ZZmembers.next;
                }
                else {
                    last->ZZds.ZZmembers.next=t2;
                    last=t2;
                    if(t2==b2)t2=NULL; else t2=t2->ZZds.ZZmembers.next;
                }
            }
        }
        last->ZZds.ZZmembers.next=temp;
        tail=last;
    }
    
    // remove the temporary node
    tail->ZZds.ZZmembers.next=temp->ZZds.ZZmembers.next;
    delete temp;
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

void members_Ring1::merge(Member *s,Member* t){
    Member *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZmembers.next; v=t->ZZds.ZZmembers.next;
    if(!u || !v ){
        printf("cannot merge/split members=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZmembers.next=u; 
    s->ZZds.ZZmembers.next=v;
}


Member* members_Ring1Iterator::fromHead(Member *p){ 
    Member *ret;

    tail=p;
    if(!tail)return NULL;
    ret=tail->ZZds.ZZmembers.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZmembers.next;
    return ret;
}


Member* const members_Ring1Iterator::next(){ 
    Member *c;

    c=nxt;
    if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZmembers.next;
    return(c);
}


void members_Ring1Iterator::start(Member *p){ 
    Member *ret;

    tail=p; nxt=NULL;
}


Member* const members_Ring1Iterator::operator++(){ 
    Member *ret;

    if(tail){
        if(nxt){
            ret=nxt; 
            nxt=nxt->ZZds.ZZmembers.next;
            if(ret==tail)tail=NULL;
        }
        else {
            ret=tail->ZZds.ZZmembers.next;
            if(tail==ret)tail=NULL;
            else nxt=ret->ZZds.ZZmembers.next;
        }
        return ret;
    }
    return NULL;
}
