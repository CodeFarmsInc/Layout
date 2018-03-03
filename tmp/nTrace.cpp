// --------------------------------------------------------
class Node;
class Edge;

Edge* const nTrace_SingleLink::target(Node *p){
    return p->ZZds.ZZnTrace.linkTo;
}

void nTrace_SingleLink::add(Node *p,Edge *c){
    if(p->ZZds.ZZnTrace.linkTo){
        printf("nTrace.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZnTrace.linkTo = c;
}

void nTrace_SingleLink::remove(Node *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZnTrace.linkTo = NULL;
}
