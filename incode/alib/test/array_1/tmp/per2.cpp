// --------------------------------------------------------
class Couple;
class Person;

Person* const per2_SingleLink::target(Couple *p){
    return p->ZZds.ZZper2.linkTo;
}

void per2_SingleLink::add(Couple *p,Person *c){
    if(p->ZZds.ZZper2.linkTo){
        printf("per2.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZper2.linkTo = c;
}

void per2_SingleLink::remove(Couple *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZper2.linkTo = NULL;
}
