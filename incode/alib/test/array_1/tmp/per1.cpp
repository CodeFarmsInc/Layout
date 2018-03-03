// --------------------------------------------------------
class Couple;
class Person;

Person* const per1_SingleLink::target(Couple *p){
    return p->ZZds.ZZper1.linkTo;
}

void per1_SingleLink::add(Couple *p,Person *c){
    if(p->ZZds.ZZper1.linkTo){
        printf("per1.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZper1.linkTo = c;
}

void per1_SingleLink::remove(Couple *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZper1.linkTo = NULL;
}
