class Node;
class Edge;
                          
void targets_Aggregate2::addHead(Node *p, Edge *c){
    if(c->ZZds.ZZtargets.parent){
        printf("targets.addHead() error: Child=%d already in targets_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZtargets.parent=p;
    targets_LinkedList2::addHead(p,c);
}
                          
void targets_Aggregate2::addTail(Node *p, Edge *c){
    if(c->ZZds.ZZtargets.parent){
        printf("targets.addTail() error: Child=%d already in targets_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZtargets.parent=p;
    targets_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void targets_Aggregate2::append(Edge *c1, Edge *c2){
    Node* p=c1->ZZds.ZZtargets.parent;
    if(!p){
        printf("targets.append() error: c1=%d not in targets_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZtargets.parent){
        printf("targets.addTail() error: c2=%d already in targets_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZtargets.parent=p;
    targets_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void targets_Aggregate2::insert(Edge *c1, Edge *c2){
    Node* p=c2->ZZds.ZZtargets.parent;
    if(!p){
        printf("targets.append() error: c2=%d not in targets_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZtargets.parent){
        printf("targets.addTail() error: c1=%d already in targets_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZtargets.parent=p;
    targets_LinkedList2::insert(c1,c2);
}
                          
void targets_Aggregate2::remove(Edge *c){
    Node* p=c->ZZds.ZZtargets.parent;
    if(p){targets_LinkedList2::remove(p,c); c->ZZds.ZZtargets.parent=NULL;}
    else printf("WARNING: targets.remove() with c=%d already disconnected\n",c);
}

Node* const targets_Aggregate2::parent(Edge *c){
                                                 return c->ZZds.ZZtargets.parent; }

