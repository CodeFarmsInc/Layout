class Organization;
class Participant;
                          
void parts_Aggregate2::addHead(Organization *p, Participant *c){
    if(c->ZZds.ZZparts.parent){
        printf("parts.addHead() error: Child=%d already in parts_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZparts.parent=p;
    parts_LinkedList2::addHead(p,c);
}
                          
void parts_Aggregate2::addTail(Organization *p, Participant *c){
    if(c->ZZds.ZZparts.parent){
        printf("parts.addTail() error: Child=%d already in parts_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZparts.parent=p;
    parts_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void parts_Aggregate2::append(Participant *c1, Participant *c2){
    Organization* p=c1->ZZds.ZZparts.parent;
    if(!p){
        printf("parts.append() error: c1=%d not in parts_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZparts.parent){
        printf("parts.addTail() error: c2=%d already in parts_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZparts.parent=p;
    parts_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void parts_Aggregate2::insert(Participant *c1, Participant *c2){
    Organization* p=c2->ZZds.ZZparts.parent;
    if(!p){
        printf("parts.append() error: c2=%d not in parts_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZparts.parent){
        printf("parts.addTail() error: c1=%d already in parts_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZparts.parent=p;
    parts_LinkedList2::insert(c1,c2);
}
                          
void parts_Aggregate2::remove(Participant *c){
    Organization* p=c->ZZds.ZZparts.parent;
    if(p){parts_LinkedList2::remove(p,c); c->ZZds.ZZparts.parent=NULL;}
    else printf("WARNING: parts.remove() with c=%d already disconnected\n",c);
}

Organization* const parts_Aggregate2::parent(Participant *c){
                                                 return c->ZZds.ZZparts.parent; }

