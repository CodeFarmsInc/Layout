// --------------------------------------------------------
class FixedType;
class PartType;

PartType* const inhFixed_SingleLink::target(FixedType *p){
    return p->ZZds.ZZinhFixed.linkTo;
}

void inhFixed_SingleLink::add(FixedType *p,PartType *c){
    if(p->ZZds.ZZinhFixed.linkTo){
        printf("inhFixed.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZinhFixed.linkTo = c;
}

void inhFixed_SingleLink::remove(FixedType *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZinhFixed.linkTo = NULL;
}
