class OrgType;
class PartType;
                          
void partTypes_Aggregate2::addHead(OrgType *p, PartType *c){
    if(c->ZZds.ZZpartTypes.parent){
        printf("partTypes.addHead() error: Child=%d already in partTypes_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZpartTypes.parent=p;
    partTypes_LinkedList2::addHead(p,c);
}
                          
void partTypes_Aggregate2::addTail(OrgType *p, PartType *c){
    if(c->ZZds.ZZpartTypes.parent){
        printf("partTypes.addTail() error: Child=%d already in partTypes_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZpartTypes.parent=p;
    partTypes_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void partTypes_Aggregate2::append(PartType *c1, PartType *c2){
    OrgType* p=c1->ZZds.ZZpartTypes.parent;
    if(!p){
        printf("partTypes.append() error: c1=%d not in partTypes_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZpartTypes.parent){
        printf("partTypes.addTail() error: c2=%d already in partTypes_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZpartTypes.parent=p;
    partTypes_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void partTypes_Aggregate2::insert(PartType *c1, PartType *c2){
    OrgType* p=c2->ZZds.ZZpartTypes.parent;
    if(!p){
        printf("partTypes.append() error: c2=%d not in partTypes_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZpartTypes.parent){
        printf("partTypes.addTail() error: c1=%d already in partTypes_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZpartTypes.parent=p;
    partTypes_LinkedList2::insert(c1,c2);
}
                          
void partTypes_Aggregate2::remove(PartType *c){
    OrgType* p=c->ZZds.ZZpartTypes.parent;
    if(p){partTypes_LinkedList2::remove(p,c); c->ZZds.ZZpartTypes.parent=NULL;}
    else printf("WARNING: partTypes.remove() with c=%d already disconnected\n",c);
}

OrgType* const partTypes_Aggregate2::parent(PartType *c){
                                                 return c->ZZds.ZZpartTypes.parent; }

