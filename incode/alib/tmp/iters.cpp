// --------------------------------------------------------

Iterator* const iters_Ring1::next(Iterator *tail, Iterator *c){
    Iterator* ret=c->ZZds.ZZiters.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the externally given tail
}

Iterator* const iters_Ring1::nextRing(Iterator *c){
    return c->ZZds.ZZiters.next;
}

Iterator* iters_Ring1::addHead(Iterator *tail, Iterator *c){
    if(c->ZZds.ZZiters.next){
        printf("iters.addHead() error: element=%d already in iters\n",c);
        return NULL;
    }
    if(tail){c->ZZds.ZZiters.next=tail->ZZds.ZZiters.next; tail->ZZds.ZZiters.next=c;}
    else        {tail=c; c->ZZds.ZZiters.next=c;}
    return tail; 
}
                          
Iterator* iters_Ring1::addTail(Iterator *tail, Iterator *c){
    if(c->ZZds.ZZiters.next){
        printf("iters.addTail() error: element=%d already in iters\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
Iterator* iters_Ring1::append(Iterator *tail,Iterator *c1, Iterator *c2){
    Iterator *x;

    if(c1->ZZds.ZZiters.next==NULL){
        printf("iters.append() error: element=%d not in iters\n",c1);
        return NULL;
    }
    if(c2->ZZds.ZZiters.next){
        printf("iters.append() error: element=%d already in iters\n",c2);
        return NULL;
    }
    c2->ZZds.ZZiters.next=c1->ZZds.ZZiters.next;
    c1->ZZds.ZZiters.next=c2;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// This function is not very efficient, must search for a predecessor.
// However, removing  while traversing is fast (no search).

Iterator* iters_Ring1::remove(Iterator *tail, Iterator *c){
    Iterator *x,*nxt;

    for(x=tail, nxt=NULL; x!=tail || nxt==NULL; x=nxt){
        nxt=x->ZZds.ZZiters.next;
        if(nxt==c)break;
    }
    if(!x || x->ZZds.ZZiters.next!=c){
        printf("iters:remove() error: node not on the list\n"); return NULL;
    }
    if(c==x)tail=NULL;
    else if(c==tail)tail=x;
    x->ZZds.ZZiters.next=c->ZZds.ZZiters.next;
    c->ZZds.ZZiters.next=NULL;
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

Iterator* iters_Ring1::sort(ZZsortFun cmp, Iterator *tail){
    Iterator *a1,*b1,*a2,*b2,*t1,*t2,*temp,*last,*nxt;
    int stopFlg,choice;

    if(!tail)return tail; // the list is empty
    if(tail==tail->ZZds.ZZiters.next)return tail; // the list has just one item

    temp=new Iterator; // the additional, temporary node
    if(!temp){
        printf("iters Ring1::sort cannot allocate temporary node\n"); return NULL;
    }
    temp->ZZds.ZZiters.next=tail->ZZds.ZZiters.next;
    tail->ZZds.ZZiters.next=temp;

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=temp->ZZds.ZZiters.next, last=temp; a1!=temp; a1=nxt){

            // detect the first sublist
            for(b1=a1; b1->ZZds.ZZiters.next!=temp; b1=b1->ZZds.ZZiters.next){
                if((*cmp)(b1,b1->ZZds.ZZiters.next)>0)break;
            }
   
            if(b1->ZZds.ZZiters.next==temp){ // last of the odd number of sublists
                if(a1==temp->ZZds.ZZiters.next) stopFlg=1; // list fully sorted
                last->ZZds.ZZiters.next=a1;
                last=b1;
                break;
            }

            // detect the second sublist
            a2=b1->ZZds.ZZiters.next;
            for(b2=a2; b2->ZZds.ZZiters.next!=temp; b2=b2->ZZds.ZZiters.next){
                if((*cmp)(b2,b2->ZZds.ZZiters.next)>0)break;
            }
            nxt=b2->ZZds.ZZiters.next; // remember it before b2 changes its position

            // the two sublists to be merged are (a1,b1) and (a2,b2)
           
            for(t1=a1, t2=a2; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){
                    last->ZZds.ZZiters.next=t1;
                    last=t1;
                    if(t1==b1)t1=NULL; else t1=t1->ZZds.ZZiters.next;
                }
                else {
                    last->ZZds.ZZiters.next=t2;
                    last=t2;
                    if(t2==b2)t2=NULL; else t2=t2->ZZds.ZZiters.next;
                }
            }
        }
        last->ZZds.ZZiters.next=temp;
        tail=last;
    }
    
    // remove the temporary node
    tail->ZZds.ZZiters.next=temp->ZZds.ZZiters.next;
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

void iters_Ring1::merge(Iterator *s,Iterator* t){
    Iterator *u,*v;

    if(s==t)return; // same objects, no action
    u=s->ZZds.ZZiters.next; v=t->ZZds.ZZiters.next;
    if(!u || !v ){
        printf("cannot merge/split iters=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->ZZds.ZZiters.next=u; 
    s->ZZds.ZZiters.next=v;
}


Iterator* iters_Ring1Iterator::fromHead(Iterator *p){ 
    Iterator *ret;

    tail=p;
    if(!tail)return NULL;
    ret=tail->ZZds.ZZiters.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->ZZds.ZZiters.next;
    return ret;
}


Iterator* const iters_Ring1Iterator::next(){ 
    Iterator *c;

    c=nxt;
    if(c==tail)nxt=tail=NULL; else nxt=c->ZZds.ZZiters.next;
    return(c);
}


void iters_Ring1Iterator::start(Iterator *p){ 
    Iterator *ret;

    tail=p; nxt=NULL;
}


Iterator* const iters_Ring1Iterator::operator++(){ 
    Iterator *ret;

    if(tail){
        if(nxt){
            ret=nxt; 
            nxt=nxt->ZZds.ZZiters.next;
            if(ret==tail)tail=NULL;
        }
        else {
            ret=tail->ZZds.ZZiters.next;
            if(tail==ret)tail=NULL;
            else nxt=ret->ZZds.ZZiters.next;
        }
        return ret;
    }
    return NULL;
}
