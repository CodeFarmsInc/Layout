class Warehouse;
class PartType;
                          
void stored_Aggregate2::addHead(Warehouse *p, PartType *c){
    if(c->ZZds.ZZstored.parent){
        printf("stored.addHead() error: Child=%d already in an Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZstored.parent=p;
    stored_LinkedList2::addHead(p,c);
}
                          
void stored_Aggregate2::addTail(Warehouse *p, PartType *c){
    if(c->ZZds.ZZstored.parent){
        printf("stored.addTail() error: Child=%d already in an Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZstored.parent=p;
    stored_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void stored_Aggregate2::append(PartType *c1, PartType *c2){
    Warehouse* p=c1->ZZds.ZZstored.parent;
    if(!p){
        printf("stored.append() error: c1=%d not in an Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZstored.parent){
        printf("stored.addTail() error: c2=%d already in an Aggregate2\n",c2);
        return;
    }
    stored_LinkedList2::append(p,c1,c2);
}
                          
void stored_Aggregate2::remove(PartType *c){
    Warehouse* p=c->ZZds.ZZstored.parent;
    if(p) stored_LinkedList2::remove(p,c);
    else printf("WARNING: stored.remove() called, but c=%d disconnected\n",c);
}

Warehouse* const stored_Aggregate2::parent(PartType *c){
                                                 return c->ZZds.ZZstored.parent; }

