// --------------------------------------------------------
class Net;
class Node;

Node* const netSource_SingleLink::target(Net *p){
    return p->ZZds.ZZnetSource.linkTo;
}

void netSource_SingleLink::add(Net *p,Node *c){
    if(p->ZZds.ZZnetSource.linkTo){
        printf("netSource.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZnetSource.linkTo = c;
}

void netSource_SingleLink::remove(Net *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZnetSource.linkTo = NULL;
}
