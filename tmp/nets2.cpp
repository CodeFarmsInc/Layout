class Layout;
class Net;
                          
void nets_Aggregate2::addHead(Layout *p, Net *c){
    if(c->ZZds.ZZnets.parent){
        printf("nets.addHead() error: Child=%d already in nets_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZnets.parent=p;
    nets_LinkedList2::addHead(p,c);
}
                          
void nets_Aggregate2::addTail(Layout *p, Net *c){
    if(c->ZZds.ZZnets.parent){
        printf("nets.addTail() error: Child=%d already in nets_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZnets.parent=p;
    nets_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void nets_Aggregate2::append(Net *c1, Net *c2){
    Layout* p=c1->ZZds.ZZnets.parent;
    if(!p){
        printf("nets.append() error: c1=%d not in nets_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZnets.parent){
        printf("nets.addTail() error: c2=%d already in nets_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZnets.parent=p;
    nets_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void nets_Aggregate2::insert(Net *c1, Net *c2){
    Layout* p=c2->ZZds.ZZnets.parent;
    if(!p){
        printf("nets.append() error: c2=%d not in nets_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZnets.parent){
        printf("nets.addTail() error: c1=%d already in nets_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZnets.parent=p;
    nets_LinkedList2::insert(c1,c2);
}
                          
void nets_Aggregate2::remove(Net *c){
    Layout* p=c->ZZds.ZZnets.parent;
    if(p){nets_LinkedList2::remove(p,c); c->ZZds.ZZnets.parent=NULL;}
    else printf("WARNING: nets.remove() with c=%d already disconnected\n",c);
}

Layout* const nets_Aggregate2::parent(Net *c){
                                                 return c->ZZds.ZZnets.parent; }

