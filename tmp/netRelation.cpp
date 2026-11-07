// --------------------------------------------------------
class Net;
class Node;

Node* const netRelation_SingleLink::target(Net *p){
    return p->ZZds.ZZnetRelation.linkTo;
}

void netRelation_SingleLink::add(Net *p,Node *c){
    if(p->ZZds.ZZnetRelation.linkTo){
        printf("netRelation.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZnetRelation.linkTo = c;
}

void netRelation_SingleLink::remove(Net *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZnetRelation.linkTo = NULL;
}
