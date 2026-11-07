class Node;
class Edge;
                          
void sources_Aggregate2::addHead(Node *p, Edge *c){
    if(c->ZZds.ZZsources.parent){
        printf("sources.addHead() error: Child=%d already in sources_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZsources.parent=p;
    sources_LinkedList2::addHead(p,c);
}
                          
void sources_Aggregate2::addTail(Node *p, Edge *c){
    if(c->ZZds.ZZsources.parent){
        printf("sources.addTail() error: Child=%d already in sources_Aggregate2\n",c);
        return;
    }
    c->ZZds.ZZsources.parent=p;
    sources_LinkedList2::addTail(p,c);
}
                          
// append Child c2 after Child c1
void sources_Aggregate2::append(Edge *c1, Edge *c2){
    Node* p=c1->ZZds.ZZsources.parent;
    if(!p){
        printf("sources.append() error: c1=%d not in sources_Aggregate2\n",c1);
        return;
    }
    if(c2->ZZds.ZZsources.parent){
        printf("sources.addTail() error: c2=%d already in sources_Aggregate2\n",c2);
        return;
    }
    c2->ZZds.ZZsources.parent=p;
    sources_LinkedList2::append(p,c1,c2);
}
                          
// insert Child c1 before Child c1
void sources_Aggregate2::insert(Edge *c1, Edge *c2){
    Node* p=c2->ZZds.ZZsources.parent;
    if(!p){
        printf("sources.append() error: c2=%d not in sources_Aggregate2\n",c2);
        return;
    }
    if(c1->ZZds.ZZsources.parent){
        printf("sources.addTail() error: c1=%d already in sources_Aggregate2\n",c1);
        return;
    }
    c1->ZZds.ZZsources.parent=p;
    sources_LinkedList2::insert(c1,c2);
}
                          
void sources_Aggregate2::remove(Edge *c){
    Node* p=c->ZZds.ZZsources.parent;
    if(p){sources_LinkedList2::remove(p,c); c->ZZds.ZZsources.parent=NULL;}
    else printf("WARNING: sources.remove() with c=%d already disconnected\n",c);
}

Node* const sources_Aggregate2::parent(Edge *c){
                                                 return c->ZZds.ZZsources.parent; }

