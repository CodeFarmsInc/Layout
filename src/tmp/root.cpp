// --------------------------------------------------------
class Layout;
class Node;

Node* const root_SingleLink::target(Layout *p){
    return p->ZZds.ZZroot.linkTo;
}

void root_SingleLink::add(Layout *p,Node *c){
    if(p->ZZds.ZZroot.linkTo){
        printf("root.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZroot.linkTo = c;
}

void root_SingleLink::remove(Layout *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZroot.linkTo = NULL;
}
