// --------------------------------------------------------
class Participant;
class PartType;

PartType* const myPartType_SingleLink::target(Participant *p){
    return p->ZZds.ZZmyPartType.linkTo;
}

void myPartType_SingleLink::add(Participant *p,PartType *c){
    if(p->ZZds.ZZmyPartType.linkTo){
        printf("myPartType.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZmyPartType.linkTo = c;
}

void myPartType_SingleLink::remove(Participant *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZmyPartType.linkTo = NULL;
}
