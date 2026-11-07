class Track;
class Edge;
                          
void byTrack_Aggregate2::addHead(Track *p, Edge *c){
    if(c->ZZds.ZZbyTrack.parent){
        printf("byTrack.addHead() error: Child=%d already in byTrack_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbyTrack.parent=p;
    byTrack_LinkedList2::addHead(p,c);
}
                          
void byTrack_Aggregate2::addTail(Track *p, Edge *c){
    if(c->ZZds.ZZbyTrack.parent){
        printf("byTrack.addTail() error: Child=%d already in byTrack_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbyTrack.parent=p;
    byTrack_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void byTrack_Aggregate2::append(Edge *c1, Edge *c2){
    Track* p=c1->ZZds.ZZbyTrack.parent;
    if(!p){
        printf("byTrack.append() error: c1=%d not in byTrack_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZbyTrack.parent){
        printf("byTrack.addTail() error: c2=%d already in byTrack_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZbyTrack.parent=p;
    byTrack_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void byTrack_Aggregate2::insert(Edge *c1, Edge *c2){
    Track* p=c2->ZZds.ZZbyTrack.parent;
    if(!p){
        printf("byTrack.append() error: c2=%d not in byTrack_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZbyTrack.parent){
        printf("byTrack.addTail() error: c1=%d already in byTrack_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZbyTrack.parent=p;
    byTrack_LinkedList2::insert(c1,c2);
}
                          
void byTrack_Aggregate2::remove(Edge *c){
    Track* p=c->ZZds.ZZbyTrack.parent;
    if(p){byTrack_LinkedList2::remove(p,c); c->ZZds.ZZbyTrack.parent=NULL;}
    else printf("WARNING: byTrack.remove() with c=%d already disconnected\n",c);
}

Track* const byTrack_Aggregate2::parent(Edge *c){
                                                 return c->ZZds.ZZbyTrack.parent; }

