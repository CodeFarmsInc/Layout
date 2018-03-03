// --------------------------------------------------------
class Node;
class Node;

Node* const firstTo_SingleLink::target(Node *p){
    return p->ZZds.ZZfirstTo.linkTo;
}

void firstTo_SingleLink::add(Node *p,Node *c){
    if(p->ZZds.ZZfirstTo.linkTo){
        printf("firstTo.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZfirstTo.linkTo = c;
}

void firstTo_SingleLink::remove(Node *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZfirstTo.linkTo = NULL;
}
