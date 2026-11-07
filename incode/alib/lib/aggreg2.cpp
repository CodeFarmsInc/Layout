class $1;
class $2;
                          
void $$_Aggregate2::addHead($1 *p, $2 *c){
    if(c->$0.parent){
        printf("$$.addHead() error: Child=%d already in $$_Aggregate2\n",c);
        return;
    }
    c->$0.parent=p;
    $$_LinkedList2::addHead(p,c);
}
                          
void $$_Aggregate2::addTail($1 *p, $2 *c){
    if(c->$0.parent){
        printf("$$.addTail() error: Child=%d already in $$_Aggregate2\n",c);
        return;
    }
    c->$0.parent=p;
    $$_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void $$_Aggregate2::append($2 *c1, $2 *c2){
    $1* p=c1->$0.parent;
    if(!p){
        printf("$$.append() error: c1=%d not in $$_Aggregate2\n",c1);
        return;
    }
    if(c2->$0.parent){
        printf("$$.addTail() error: c2=%d already in $$_Aggregate2\n",c2);
        return;
    }
    c2->$0.parent=p;
    $$_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void $$_Aggregate2::insert($2 *c1, $2 *c2){
    $1* p=c2->$0.parent;
    if(!p){
        printf("$$.append() error: c2=%d not in $$_Aggregate2\n",c2);
        return;
    }
    if(c1->$0.parent){
        printf("$$.addTail() error: c1=%d already in $$_Aggregate2\n",c1);
        return;
    }
    c1->$0.parent=p;
    $$_LinkedList2::insert(c1,c2);
}
                          
void $$_Aggregate2::remove($2 *c){
    $1* p=c->$0.parent;
    if(p){$$_LinkedList2::remove(p,c); c->$0.parent=NULL;}
    else printf("WARNING: $$.remove() with c=%d already disconnected\n",c);
}

$1* const $$_Aggregate2::parent($2 *c){
                                                 return c->$0.parent; }

