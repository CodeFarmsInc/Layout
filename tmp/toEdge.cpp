// --------------------------------------------------------
class EdgeRef;
class Edge;

Edge* const toEdge_SingleLink::target(EdgeRef *p){
    return p->ZZds.ZZtoEdge.linkTo;
}

void toEdge_SingleLink::add(EdgeRef *p,Edge *c){
    if(p->ZZds.ZZtoEdge.linkTo){
        printf("toEdge.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZtoEdge.linkTo = c;
}

void toEdge_SingleLink::remove(EdgeRef *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZtoEdge.linkTo = NULL;
}
