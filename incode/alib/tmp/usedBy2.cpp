class ApplClass;
class Participant;
                          
void usedBy_Aggregate2::addHead(ApplClass *p, Participant *c){
    if(c->ZZds.ZZusedBy.parent){
        printf("usedBy.addHead() error: Child=%d already in usedBy_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZusedBy.parent=p;
    usedBy_LinkedList2::addHead(p,c);
}
                          
void usedBy_Aggregate2::addTail(ApplClass *p, Participant *c){
    if(c->ZZds.ZZusedBy.parent){
        printf("usedBy.addTail() error: Child=%d already in usedBy_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZusedBy.parent=p;
    usedBy_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void usedBy_Aggregate2::append(Participant *c1, Participant *c2){
    ApplClass* p=c1->ZZds.ZZusedBy.parent;
    if(!p){
        printf("usedBy.append() error: c1=%d not in usedBy_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZusedBy.parent){
        printf("usedBy.addTail() error: c2=%d already in usedBy_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZusedBy.parent=p;
    usedBy_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void usedBy_Aggregate2::insert(Participant *c1, Participant *c2){
    ApplClass* p=c2->ZZds.ZZusedBy.parent;
    if(!p){
        printf("usedBy.append() error: c2=%d not in usedBy_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZusedBy.parent){
        printf("usedBy.addTail() error: c1=%d already in usedBy_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZusedBy.parent=p;
    usedBy_LinkedList2::insert(c1,c2);
}
                          
void usedBy_Aggregate2::remove(Participant *c){
    ApplClass* p=c->ZZds.ZZusedBy.parent;
    if(p){usedBy_LinkedList2::remove(p,c); c->ZZds.ZZusedBy.parent=NULL;}
    else printf("WARNING: usedBy.remove() with c=%d already disconnected\n",c);
}

ApplClass* const usedBy_Aggregate2::parent(Participant *c){
                                                 return c->ZZds.ZZusedBy.parent; }

