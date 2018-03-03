// --------------------------------------------------------
class Edge;
class Node;

Node* const eTrace_SingleLink::target(Edge *p){
    return p->ZZds.ZZeTrace.linkTo;
}

void eTrace_SingleLink::add(Edge *p,Node *c){
    if(p->ZZds.ZZeTrace.linkTo){
        printf("eTrace.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZeTrace.linkTo = c;
}

void eTrace_SingleLink::remove(Edge *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZeTrace.linkTo = NULL;
}
