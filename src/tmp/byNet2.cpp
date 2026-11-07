class Net;
class Edge;
                          
void byNet_Aggregate2::addHead(Net *p, Edge *c){
    if(c->ZZds.ZZbyNet.parent){
        printf("byNet.addHead() error: Child=%d already in byNet_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbyNet.parent=p;
    byNet_LinkedList2::addHead(p,c);
}
                          
void byNet_Aggregate2::addTail(Net *p, Edge *c){
    if(c->ZZds.ZZbyNet.parent){
        printf("byNet.addTail() error: Child=%d already in byNet_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZbyNet.parent=p;
    byNet_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void byNet_Aggregate2::append(Edge *c1, Edge *c2){
    Net* p=c1->ZZds.ZZbyNet.parent;
    if(!p){
        printf("byNet.append() error: c1=%d not in byNet_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZbyNet.parent){
        printf("byNet.addTail() error: c2=%d already in byNet_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZbyNet.parent=p;
    byNet_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void byNet_Aggregate2::insert(Edge *c1, Edge *c2){
    Net* p=c2->ZZds.ZZbyNet.parent;
    if(!p){
        printf("byNet.append() error: c2=%d not in byNet_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZbyNet.parent){
        printf("byNet.addTail() error: c1=%d already in byNet_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZbyNet.parent=p;
    byNet_LinkedList2::insert(c1,c2);
}
                          
void byNet_Aggregate2::remove(Edge *c){
    Net* p=c->ZZds.ZZbyNet.parent;
    if(p){byNet_LinkedList2::remove(p,c); c->ZZds.ZZbyNet.parent=NULL;}
    else printf("WARNING: byNet.remove() with c=%d already disconnected\n",c);
}

Net* const byNet_Aggregate2::parent(Edge *c){
                                                 return c->ZZds.ZZbyNet.parent; }

