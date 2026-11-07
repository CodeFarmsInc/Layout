// --------------------------------------------------------

$1* const $$_Ring1::next($1 *tail, $1 *c){
    $1* ret=c->$0.next;
    if(c==tail)ret=NULL;
    return ret; // return NULL when c is the externally given tail
}

$1* const $$_Ring1::nextRing($1 *c){
    return c->$0.next;
}

$1* $$_Ring1::addHead($1 *tail, $1 *c){
    if(c->$0.next){
        printf("$$.addHead() error: element=%d already in $$\n",c);
        return NULL;
    }
    if(tail){c->$0.next=tail->$0.next; tail->$0.next=c;}
    else        {tail=c; c->$0.next=c;}
    return tail; 
}
                          
$1* $$_Ring1::addTail($1 *tail, $1 *c){
    if(c->$0.next){
        printf("$$.addTail() error: element=%d already in $$\n",c);
        return NULL;
    }
    addHead(tail,c);
    return c; // returns new tail
}
                          
                          
// append element c2 after element c1
$1* $$_Ring1::append($1 *tail,$1 *c1, $1 *c2){
    $1 *x;

    if(c1->$0.next==NULL){
        printf("$$.append() error: element=%d not in $$\n",c1);
        return NULL;
    }
    if(c2->$0.next){
        printf("$$.append() error: element=%d already in $$\n",c2);
        return NULL;
    }
    c2->$0.next=c1->$0.next;
    c1->$0.next=c2;
    if(tail==c1)tail=c2;
    return tail;
}
                          
                          
// This function is not very efficient, must search for a predecessor.
// However, removing  while traversing is fast (no search).

$1* $$_Ring1::remove($1 *tail, $1 *c){
    $1 *x,*nxt;

    for(x=tail, nxt=NULL; x!=tail || nxt==NULL; x=nxt){
        nxt=x->$0.next;
        if(nxt==c)break;
    }
    if(!x || x->$0.next!=c){
        printf("$$:remove() error: node not on the list\n"); return NULL;
    }
    if(c==x)tail=NULL;
    else if(c==tail)tail=x;
    x->$0.next=c->$0.next;
    c->$0.next=NULL;
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

$1* $$_Ring1::sort(ZZsortFun cmp, $1 *tail){
    $1 *a1,*b1,*a2,*b2,*t1,*t2,*temp,*last,*nxt;
    int stopFlg,choice;

    if(!tail)return tail; // the list is empty
    if(tail==tail->$0.next)return tail; // the list has just one item

    temp=new $1; // the additional, temporary node
    if(!temp){
        printf("$$ Ring1::sort cannot allocate temporary node\n"); return NULL;
    }
    temp->$0.next=tail->$0.next;
    tail->$0.next=temp;

    // keep sorting adjacent sublists until everything is one list
    for(stopFlg=0; !stopFlg;){ // keep repeating

        // process all sublist pairs
        for(a1=temp->$0.next, last=temp; a1!=temp; a1=nxt){

            // detect the first sublist
            for(b1=a1; b1->$0.next!=temp; b1=b1->$0.next){
                if((*cmp)(b1,b1->$0.next)>0)break;
            }
   
            if(b1->$0.next==temp){ // last of the odd number of sublists
                if(a1==temp->$0.next) stopFlg=1; // list fully sorted
                last->$0.next=a1;
                last=b1;
                break;
            }

            // detect the second sublist
            a2=b1->$0.next;
            for(b2=a2; b2->$0.next!=temp; b2=b2->$0.next){
                if((*cmp)(b2,b2->$0.next)>0)break;
            }
            nxt=b2->$0.next; // remember it before b2 changes its position

            // the two sublists to be merged are (a1,b1) and (a2,b2)
           
            for(t1=a1, t2=a2; t1||t2; ){

                if(t1==NULL)choice=2;
                else if(t2==NULL)choice=1;
                else {
                    if((*cmp)(t1,t2)<=0)choice=1;
                    else choice=2;
                }

                if(choice==1){
                    last->$0.next=t1;
                    last=t1;
                    if(t1==b1)t1=NULL; else t1=t1->$0.next;
                }
                else {
                    last->$0.next=t2;
                    last=t2;
                    if(t2==b2)t2=NULL; else t2=t2->$0.next;
                }
            }
        }
        last->$0.next=temp;
        tail=last;
    }
    
    // remove the temporary node
    tail->$0.next=temp->$0.next;
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

void $$_Ring1::merge($1 *s,$1* t){
    $1 *u,*v;

    if(s==t)return; // same objects, no action
    u=s->$0.next; v=t->$0.next;
    if(!u || !v ){
        printf("cannot merge/split $$=",s);
        return;
    }
    // re-linking s-u, t-v to s-v, t-u
    t->$0.next=u; 
    s->$0.next=v;
}


$1* $$_Ring1Iterator::fromHead($1 *p){ 
    $1 *ret;

    tail=p;
    if(!tail)return NULL;
    ret=tail->$0.next;
    if(ret==tail)nxt=tail=NULL; 
    else nxt=ret->$0.next;
    return ret;
}


$1* const $$_Ring1Iterator::next(){ 
    $1 *c;

    c=nxt;
    if(c==tail)nxt=tail=NULL; else nxt=c->$0.next;
    return(c);
}


void $$_Ring1Iterator::start($1 *p){ 
    $1 *ret;

    tail=p; nxt=NULL;
}


$1* const $$_Ring1Iterator::operator++(){ 
    $1 *ret;

    if(tail){
        if(nxt){
            ret=nxt; 
            nxt=nxt->$0.next;
            if(ret==tail)tail=NULL;
        }
        else {
            ret=tail->$0.next;
            if(tail==ret)tail=NULL;
            else nxt=ret->$0.next;
        }
        return ret;
    }
    return NULL;
}
