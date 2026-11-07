// --------------------------------------------------------
class Organization;
class Organization;

Organization* const inherits_SingleLink::next(Organization *p){
    return p->ZZds.ZZinherits.linkTo;
}

void inherits_SingleLink::add(Organization *p,Organization *c){
    if(p->ZZds.ZZinherits.linkTo){
        printf("inherits.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZinherits.linkTo = c;
}

void inherits_SingleLink::remove(Organization *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZinherits.linkTo = NULL;
}
