// --------------------------------------------------------
class OrgType;
class OrgType;

OrgType* const inherits_SingleLink::target(OrgType *p){
    return p->ZZds.ZZinherits.linkTo;
}

void inherits_SingleLink::add(OrgType *p,OrgType *c){
    if(p->ZZds.ZZinherits.linkTo){
        printf("inherits.add() error: object=%d already has a SingleLink\n",p);
        return;
    }
    p->ZZds.ZZinherits.linkTo = c;
}

void inherits_SingleLink::remove(OrgType *p){
    // no need for warning or error message if there is no link
    p->ZZds.ZZinherits.linkTo = NULL;
}
