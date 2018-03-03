// --------------------------------------------------------
class Pair;
class Node;

Node* const inPair2_SingleLink::target(Pair *p){
    return p->ZZds.ZZinPair2.linkTo;
}

void inPair2_SingleLink::add(Pair *p,Node *c){
    if(p->ZZds.ZZinPair2.linkTo){
        printf("inPair2.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZinPair2.linkTo = c;
}

void inPair2_SingleLink::remove(Pair *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZinPair2.linkTo = NULL;
}
