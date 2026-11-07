// --------------------------------------------------------
class PartType;
class PartType;

PartType* const inhMatch_SingleLink::target(PartType *p){
    return p->ZZds.ZZinhMatch.linkTo;
}

void inhMatch_SingleLink::add(PartType *p,PartType *c){
    if(p->ZZds.ZZinhMatch.linkTo){
        printf("inhMatch.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZinhMatch.linkTo = c;
}

void inhMatch_SingleLink::remove(PartType *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZinhMatch.linkTo = NULL;
}
