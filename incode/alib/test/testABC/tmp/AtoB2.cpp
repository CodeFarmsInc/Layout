class A;
class B;
                          
void AtoB_Aggregate2::addHead(A *p, B *c){
    if(c->ZZds.ZZAtoB.parent){
        printf("AtoB.addHead() error: Child=%d already in AtoB_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZAtoB.parent=p;
    AtoB_LinkedList2::addHead(p,c);
}
                          
void AtoB_Aggregate2::addTail(A *p, B *c){
    if(c->ZZds.ZZAtoB.parent){
        printf("AtoB.addTail() error: Child=%d already in AtoB_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZAtoB.parent=p;
    AtoB_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void AtoB_Aggregate2::append(B *c1, B *c2){
    A* p=c1->ZZds.ZZAtoB.parent;
    if(!p){
        printf("AtoB.append() error: c1=%d not in AtoB_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZAtoB.parent){
        printf("AtoB.addTail() error: c2=%d already in AtoB_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZAtoB.parent=p;
    AtoB_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void AtoB_Aggregate2::insert(B *c1, B *c2){
    A* p=c2->ZZds.ZZAtoB.parent;
    if(!p){
        printf("AtoB.append() error: c2=%d not in AtoB_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZAtoB.parent){
        printf("AtoB.addTail() error: c1=%d already in AtoB_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZAtoB.parent=p;
    AtoB_LinkedList2::insert(c1,c2);
}
                          
void AtoB_Aggregate2::remove(B *c){
    A* p=c->ZZds.ZZAtoB.parent;
    if(p){AtoB_LinkedList2::remove(p,c); c->ZZds.ZZAtoB.parent=NULL;}
    else printf("WARNING: AtoB.remove() with c=%d already disconnected\n",c);
}

A* const AtoB_Aggregate2::parent(B *c){
                                                 return c->ZZds.ZZAtoB.parent; }

