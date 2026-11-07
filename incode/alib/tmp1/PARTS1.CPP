class Organization;
class Participant;
                          
void parts_Aggregate::addHead(Organization *p, Participant *c){
    if(c->ZZds.ZZparts.parent){
        printf("parts.addHead() error: Child=%d already in an Aggregate\n",c);
        return;
    }
    c->ZZds.ZZparts.parent=p;
    parts_LinkedList::addHead(p,c);
}
                          
void parts_Aggregate::addTail(Organization *p, Participant *c){
    if(c->ZZds.ZZparts.parent){
        printf("parts.addTail() error: Child=%d already in an Aggregate\n",c);
        return;
    }
    c->ZZds.ZZparts.parent=p;
    parts_LinkedList::addTail(p,c);
}
                          
// append Child c2 after Child c1
void parts_Aggregate::append(Participant *c1, Participant *c2){
    Organization* p=c1->ZZds.ZZparts.parent;
    if(!p){
        printf("parts.append() error: c1=%d not in an Aggregate\n",c1);
        return;
    }
    if(c2->ZZds.ZZparts.parent){
        printf("parts.addTail() error: c2=%d already in an Aggregate\n",c2);
        return;
    }
    parts_LinkedList::append(p,c1,c2);
}
                          
void parts_Aggregate::remove(Participant *c){
    Organization* p=c->ZZds.ZZparts.parent;
    if(p) parts_LinkedList::remove(p,c);
    else printf("WARNING: parts.remove() called, but c=%d disconnected\n",c);
}

Organization* const parts_Aggregate::parent(Participant *c){
                                                 return c->ZZds.ZZparts.parent; }

