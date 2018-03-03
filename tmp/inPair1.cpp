// --------------------------------------------------------
class Pair;
class Node;

Node* const inPair1_SingleLink::target(Pair *p){
    return p->ZZds.ZZinPair1.linkTo;
}

void inPair1_SingleLink::add(Pair *p,Node *c){
    if(p->ZZds.ZZinPair1.linkTo){
        printf("inPair1.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZinPair1.linkTo = c;
}

void inPair1_SingleLink::remove(Pair *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZinPair1.linkTo = NULL;
}
