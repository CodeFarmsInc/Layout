class Supplier;
class PartType;
                          
void supply_Aggregate2::addHead(Supplier *p, PartType *c){
    if(c->ZZds.ZZsupply.parent){
        printf("supply.addHead() error: Child=%d already in an Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZsupply.parent=p;
    supply_LinkedList2::addHead(p,c);
}
                          
void supply_Aggregate2::addTail(Supplier *p, PartType *c){
    if(c->ZZds.ZZsupply.parent){
        printf("supply.addTail() error: Child=%d already in an Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZsupply.parent=p;
    supply_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void supply_Aggregate2::append(PartType *c1, PartType *c2){
    Supplier* p=c1->ZZds.ZZsupply.parent;
    if(!p){
        printf("supply.append() error: c1=%d not in an Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZsupply.parent){
        printf("supply.addTail() error: c2=%d already in an Aggregate2\n",c2);
        return;
    }
    supply_LinkedList2::append(p,c1,c2);
}
                          
void supply_Aggregate2::remove(PartType *c){
    Supplier* p=c->ZZds.ZZsupply.parent;
    if(p) supply_LinkedList2::remove(p,c);
    else printf("WARNING: supply.remove() called, but c=%d disconnected\n",c);
}

Supplier* const supply_Aggregate2::parent(PartType *c){
                                                 return c->ZZds.ZZsupply.parent; }

