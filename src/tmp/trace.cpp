// --------------------------------------------------------
class Node;
class Edge;

Edge* const trace_SingleLink::target(Node *p){
    return p->ZZds.ZZtrace.linkTo;
}

void trace_SingleLink::add(Node *p,Edge *c){
    if(p->ZZds.ZZtrace.linkTo){
        printf("trace.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZtrace.linkTo = c;
}

void trace_SingleLink::remove(Node *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZtrace.linkTo = NULL;
}
