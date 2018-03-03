// --------------------------------------------------------
class NodeRef;
class Node;

Node* const toNode_SingleLink::target(NodeRef *p){
    return p->ZZds.ZZtoNode.linkTo;
}

void toNode_SingleLink::add(NodeRef *p,Node *c){
    if(p->ZZds.ZZtoNode.linkTo){
        printf("toNode.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZtoNode.linkTo = c;
}

void toNode_SingleLink::remove(NodeRef *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZtoNode.linkTo = NULL;
}
