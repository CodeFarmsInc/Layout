// --------------------------------------------------------
class Node;
class Group;

Group* const myGroup_SingleLink::target(Node *p){
    return p->ZZds.ZZmyGroup.linkTo;
}

void myGroup_SingleLink::add(Node *p,Group *c){
    if(p->ZZds.ZZmyGroup.linkTo){
        printf("myGroup.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZmyGroup.linkTo = c;
}

void myGroup_SingleLink::remove(Node *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZmyGroup.linkTo = NULL;
}
